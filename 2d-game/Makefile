COMPILER = clang++

# 1. Added -Isrc so the compiler can find headers anywhere in your source tree
SOURCE_LIBS = -Ilib/ -Isrc/

# 2. Use 'find' to recursively gather all .cpp files in 'src' and any subfolders
CFILES := $(shell find src -name "*.cpp")

OSX_OPT = -std=c++20 -Llib/ -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL lib/libraylib.a
OSX_OUT = -o "bin/build_osx"

build_osx:
	$(COMPILER) $(CFILES) $(SOURCE_LIBS) $(OSX_OUT) $(OSX_OPT)