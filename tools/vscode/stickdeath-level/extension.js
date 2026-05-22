"use strict";

const vscode = require("vscode");

function activate(context) {
    const diagnostics =
        vscode.languages.createDiagnosticCollection("stickdeath-level");
    context.subscriptions.push(diagnostics);

    const refreshDocument = (document) => {
        if (!document || document.languageId !== "stickdeath-level") {
            return;
        }

        diagnostics.set(document.uri, validateDocument(document));
    };

    const createBoilerplateCommand = vscode.commands.registerCommand(
        "stickdeath-sdlvl-tools.createBoilerplate",
        createBoilerplateLevel,
    );

    for (const document of vscode.workspace.textDocuments) {
        refreshDocument(document);
    }

    context.subscriptions.push(
        createBoilerplateCommand,
        vscode.workspace.onDidOpenTextDocument(refreshDocument),
        vscode.workspace.onDidChangeTextDocument((event) =>
            refreshDocument(event.document),
        ),
        vscode.workspace.onDidSaveTextDocument(refreshDocument),
        vscode.workspace.onDidCloseTextDocument((document) =>
            diagnostics.delete(document.uri),
        ),
    );
}

function deactivate() { }

async function createBoilerplateLevel() {
    const version = await vscode.window.showQuickPick(["1"], {
        placeHolder: "Choose SDLVL version",
    });
    if (!version) {
        return;
    }

    const width = await promptForInteger({
        prompt: "Choose level width",
        placeHolder: "20",
        validate: (value) => value > 0,
        errorMessage: "Width must be greater than 0.",
    });
    if (width === undefined) {
        return;
    }

    const height = await promptForInteger({
        prompt: "Choose level height",
        placeHolder: "8",
        validate: (value) => value > 0,
        errorMessage: "Height must be greater than 0.",
    });
    if (height === undefined) {
        return;
    }

    const spawnX = await promptForInteger({
        prompt: "Choose spawn X",
        placeHolder: "0",
        validate: (value) => value >= 0 && value < width,
        errorMessage: "Spawn X must be within the level width.",
    });
    if (spawnX === undefined) {
        return;
    }

    const spawnY = await promptForInteger({
        prompt: "Choose spawn Y",
        placeHolder: "0",
        validate: (value) => value >= 0 && value < height,
        errorMessage: "Spawn Y must be within the level height.",
    });
    if (spawnY === undefined) {
        return;
    }

    const legendLines = [];
    const usedSymbols = new Set();

    while (true) {
        const legendEntry = await vscode.window.showInputBox({
            prompt: "Legend entry as '<symbol> <blockName>' (empty Enter or 'done' to finish)",
            placeHolder: "# floor",
            validateInput: (value) => {
                const trimmed = value.trim();

                if (trimmed === "" || trimmed.toLowerCase() === "done") {
                    return null;
                }

                const match = /^(\S)\s+([A-Za-z_][A-Za-z0-9_./-]*)$/.exec(trimmed);
                if (!match) {
                    return "Use the format '<symbol> <blockName>', for example '# floor'.";
                }

                const symbol = match[1];
                if (symbol === ".") {
                    return "'.' is reserved for empty space.";
                }

                if (usedSymbols.has(symbol)) {
                    return "That legend symbol has already been used.";
                }

                return null;
            },
        });

        if (legendEntry === undefined) {
            return;
        }

        const trimmed = legendEntry.trim();
        if (trimmed === "" || trimmed.toLowerCase() === "done") {
            break;
        }

        const symbol = trimmed.split(/\s+/, 1)[0];
        usedSymbols.add(symbol);
        legendLines.push(trimmed);
    }

    const rows = Array.from({ length: height }, () => ".".repeat(width));

    const content = [
        "version " + version,
        "size " + width + " " + height,
        "spawn " + spawnX + " " + spawnY,
        "",
        "legend",
        ...legendLines,
        "",
        "rows",
        ...rows,
        "",
    ].join("\n");

    await writeBoilerplateToActiveEditor(content);
}

async function promptForInteger(options) {
    const rawValue = await vscode.window.showInputBox({
        prompt: options.prompt,
        placeHolder: options.placeHolder,
        validateInput: (value) => {
            if (!/^-?\d+$/.test(value.trim())) {
                return "Enter a whole number.";
            }

            const parsed = Number(value.trim());
            if (!options.validate(parsed)) {
                return options.errorMessage;
            }

            return null;
        },
    });

    if (rawValue === undefined) {
        return undefined;
    }

    return Number(rawValue.trim());
}

async function writeBoilerplateToActiveEditor(content) {
    const editor = vscode.window.activeTextEditor;

    if (!editor) {
        const document = await vscode.workspace.openTextDocument({
            language: "stickdeath-level",
            content,
        });
        await vscode.window.showTextDocument(document);
        return;
    }

    const document = editor.document;
    const lastLineIndex = Math.max(document.lineCount - 1, 0);
    const lastLine = document.lineAt(lastLineIndex);

    const fullRange = new vscode.Range(
        0,
        0,
        lastLineIndex,
        lastLine.text.length,
    );

    await editor.edit((editBuilder) => {
        editBuilder.replace(fullRange, content);
    });
}

function validateDocument(document) {
    const diagnostics = [];
    const lines = document.getText().split(/\r?\n/);

    let version = null;
    let versionLine = 0;

    let size = null;
    let sizeLine = 0;

    let spawn = null;
    let spawnLine = 0;

    let legendLine = 0;
    let rowsLine = 0;

    let section = "header";

    const seen = {
        version: false,
        size: false,
        spawn: false,
        legend: false,
        rows: false,
    };

    const legend = new Map();
    const rowEntries = [];

    const addDiagnostic = (
        line,
        startChar,
        endChar,
        message,
        severity = vscode.DiagnosticSeverity.Error,
    ) => {
        const safeLine = clamp(line, 0, Math.max(lines.length - 1, 0));
        const lineText = lines[safeLine] ?? "";

        const safeStart = clamp(startChar, 0, lineText.length);
        const safeEnd =
            lineText.length === 0
                ? 0
                : clamp(Math.max(endChar, safeStart + 1), 0, lineText.length);

        diagnostics.push(
            new vscode.Diagnostic(
                new vscode.Range(safeLine, safeStart, safeLine, safeEnd),
                message,
                severity,
            ),
        );
    };

    const wholeLineRange = (lineIndex) => {
        const lineText = lines[lineIndex] ?? "";
        return [0, Math.max(lineText.length, 1)];
    };

    const tokenRange = (lineText, token) => {
        const start = lineText.indexOf(token);
        if (start === -1) {
            return [0, Math.max(lineText.length, 1)];
        }
        return [start, start + token.length];
    };

    for (let lineIndex = 0; lineIndex < lines.length; lineIndex++) {
        const rawLine = lines[lineIndex];
        const trimmed = rawLine.trim();

        if (trimmed.length === 0 || trimmed.startsWith(";")) {
            continue;
        }

        if (section !== "rows" && trimmed === "legend") {
            if (seen.legend) {
                const [start, end] = tokenRange(rawLine, "legend");
                addDiagnostic(lineIndex, start, end, "Duplicate legend section.");
            }
            seen.legend = true;
            legendLine = lineIndex;
            section = "legend";
            continue;
        }

        if (section !== "rows" && trimmed === "rows") {
            if (!seen.legend) {
                const [start, end] = tokenRange(rawLine, "rows");
                addDiagnostic(
                    lineIndex,
                    start,
                    end,
                    "The rows section must come after the legend section.",
                );
            }

            if (seen.rows) {
                const [start, end] = tokenRange(rawLine, "rows");
                addDiagnostic(lineIndex, start, end, "Duplicate rows section.");
            }

            seen.rows = true;
            rowsLine = lineIndex;
            section = "rows";
            continue;
        }

        if (section === "header") {
            let match = /^version\s+(\d+)\s*$/.exec(trimmed);
            if (match) {
                if (seen.version) {
                    const [start, end] = tokenRange(rawLine, "version");
                    addDiagnostic(lineIndex, start, end, "Duplicate version header.");
                }

                seen.version = true;
                version = Number(match[1]);
                versionLine = lineIndex;
                continue;
            }

            match = /^size\s+(\d+)\s+(\d+)\s*$/.exec(trimmed);
            if (match) {
                if (seen.size) {
                    const [start, end] = tokenRange(rawLine, "size");
                    addDiagnostic(lineIndex, start, end, "Duplicate size header.");
                }

                seen.size = true;
                size = {
                    width: Number(match[1]),
                    height: Number(match[2]),
                };
                sizeLine = lineIndex;
                continue;
            }

            match = /^spawn\s+(-?\d+)\s+(-?\d+)\s*$/.exec(trimmed);
            if (match) {
                if (seen.spawn) {
                    const [start, end] = tokenRange(rawLine, "spawn");
                    addDiagnostic(lineIndex, start, end, "Duplicate spawn header.");
                }

                seen.spawn = true;
                spawn = {
                    x: Number(match[1]),
                    y: Number(match[2]),
                };
                spawnLine = lineIndex;
                continue;
            }

            const [start, end] = wholeLineRange(lineIndex);
            addDiagnostic(
                lineIndex,
                start,
                end,
                "Expected a header line: version, size, spawn, legend, or rows.",
            );
            continue;
        }

        if (section === "legend") {
            const match = /^(\S)\s+([A-Za-z_][A-Za-z0-9_./-]*)\s*$/.exec(trimmed);

            if (!match) {
                const [start, end] = wholeLineRange(lineIndex);
                addDiagnostic(
                    lineIndex,
                    start,
                    end,
                    "Expected a legend entry like '# floor'.",
                );
                continue;
            }

            const symbol = match[1];
            const blockName = match[2];

            if (symbol === ".") {
                const symbolIndex = rawLine.indexOf(".");
                addDiagnostic(
                    lineIndex,
                    symbolIndex === -1 ? 0 : symbolIndex,
                    symbolIndex === -1 ? 1 : symbolIndex + 1,
                    "'.' is reserved for empty space and cannot be used in the legend.",
                );
            }

            if (legend.has(symbol)) {
                const symbolIndex = rawLine.indexOf(symbol);
                addDiagnostic(
                    lineIndex,
                    symbolIndex === -1 ? 0 : symbolIndex,
                    symbolIndex === -1 ? 1 : symbolIndex + 1,
                    `Duplicate legend symbol '${symbol}'.`,
                );
            } else {
                legend.set(symbol, blockName);
            }

            continue;
        }

        if (section === "rows") {
            rowEntries.push({
                line: lineIndex,
                text: rawLine,
            });

            if (/\s/.test(rawLine)) {
                const [start, end] = wholeLineRange(lineIndex);
                addDiagnostic(
                    lineIndex,
                    start,
                    end,
                    "Row lines cannot contain whitespace.",
                );
            }

            continue;
        }
    }

    if (!seen.version) {
        addDiagnostic(0, 0, 0, "Missing version header.");
    } else if (version !== 1) {
        const [start, end] = tokenRange(lines[versionLine] ?? "", "version");
        addDiagnostic(
            versionLine,
            start,
            end,
            `Unsupported level version '${version}'. Expected version 1.`,
            vscode.DiagnosticSeverity.Warning,
        );
    }

    if (!seen.size) {
        addDiagnostic(0, 0, 0, "Missing size header.");
    } else if (size.width <= 0 || size.height <= 0) {
        const [start, end] = tokenRange(lines[sizeLine] ?? "", "size");
        addDiagnostic(
            sizeLine,
            start,
            end,
            "Size values must be greater than zero.",
        );
    }

    if (!seen.spawn) {
        addDiagnostic(0, 0, 0, "Missing spawn header.");
    }

    if (!seen.legend) {
        addDiagnostic(0, 0, 0, "Missing legend section.");
    }

    if (!seen.rows) {
        addDiagnostic(0, 0, 0, "Missing rows section.");
    }

    if (seen.legend && legend.size === 0) {
        const [start, end] = tokenRange(lines[legendLine] ?? "", "legend");
        addDiagnostic(
            legendLine,
            start,
            end,
            "Legend section is empty.",
            vscode.DiagnosticSeverity.Warning,
        );
    }

    if (seen.rows && size && rowEntries.length !== size.height) {
        const [start, end] = tokenRange(lines[rowsLine] ?? "", "rows");
        addDiagnostic(
            rowsLine,
            start,
            end,
            `Expected ${size.height} row(s), but found ${rowEntries.length}.`,
        );
    }

    for (const rowEntry of rowEntries) {
        if (size && rowEntry.text.length !== size.width) {
            const [start, end] = wholeLineRange(rowEntry.line);
            addDiagnostic(
                rowEntry.line,
                start,
                end,
                `Expected row width ${size.width}, but found ${rowEntry.text.length}.`,
            );
        }

        for (let charIndex = 0; charIndex < rowEntry.text.length; charIndex++) {
            const ch = rowEntry.text[charIndex];

            if (ch === "." || /\s/.test(ch)) {
                continue;
            }

            if (!legend.has(ch)) {
                addDiagnostic(
                    rowEntry.line,
                    charIndex,
                    charIndex + 1,
                    `Tile symbol '${ch}' is not declared in the legend.`,
                );
            }
        }
    }

    if (spawn && size) {
        const spawnInBounds =
            spawn.x >= 0 &&
            spawn.x < size.width &&
            spawn.y >= 0 &&
            spawn.y < size.height;

        if (!spawnInBounds) {
            const [start, end] = tokenRange(lines[spawnLine] ?? "", "spawn");
            addDiagnostic(
                spawnLine,
                start,
                end,
                `Spawn (${spawn.x}, ${spawn.y}) is outside the declared size ${size.width}x${size.height}.`,
            );
        }
    }

    return diagnostics;
}

function clamp(value, min, max) {
    return Math.min(Math.max(value, min), max);
}

module.exports = {
    activate,
    deactivate,
};