#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint> // for uint8_t
#include <iomanip> // for std::hex
#include <fstream>
#include <vector>
#include <string>
#include <cstdint>
#include <iostream>
#include <algorithm>
#include <sstream>

/**
 * Reads a binary file, skips a defined number of header bits, 
 * and breaks the remaining bits into equal-sized chunks, 
 * returning each chunk as a string of '0's and '1's.
 *
 * @param filename The path to the binary file.
 * @param header_bits The number of bits to skip from the start (header size).
 * @param chunk_size The size of the data chunks to extract, in bits.
 * @return A vector of strings, where each string is a binary representation 
 * of a chunk (e.g., "010010110101111").
 */
static std::vector<std::string> ExtractBitChunks(
    const char* filename, 
    int header_bits, 
    int chunk_size) 
{
    std::ifstream file(filename, std::ios::binary | std::ios::in);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return {};
    }

    // --- Step 1: Skip the header ---
    
    // Calculate how many full bytes to skip
    int bytes_to_skip = header_bits / 8;
    
    // Calculate the remaining bit offset
    int header_bit_offset = header_bits % 8;

    file.seekg(bytes_to_skip, std::ios::beg);

    // --- Step 2: Read the remaining file content into a byte buffer ---
    
    // This is the most reliable way to handle non-byte-aligned reads.
    std::vector<uint8_t> buffer;
    char byte;
    while (file.read(&byte, 1)) {
        buffer.push_back(static_cast<uint8_t>(byte));
    }
    file.close();

    // --- Step 3: Handle the remaining header bit offset ---
    
    // Total bits available after skipping full bytes
    uint64_t total_bits = buffer.size() * 8;
    
    // Start reading at the first data bit, which is after the header offset
    uint64_t current_bit = header_bit_offset; 

    // --- Step 4: Extract chunks using bitwise operations ---
    
    std::vector<std::string> result_chunks;
    
    // Safety check: chunk_size cannot exceed 64 (the size of uint64_t)
    if (chunk_size <= 0 || chunk_size > 64) {
        std::cerr << "Error: Chunk size must be between 1 and 64 bits." << std::endl;
        return {};
    }

    // Stop when there aren't enough bits left for a full chunk
    while (current_bit + chunk_size <= total_bits) {
        
        // 1. Determine the starting byte index and bit offset
        uint64_t byte_index = current_bit / 8;
        uint64_t bit_offset_in_byte = current_bit % 8;

        // 2. Load the relevant bytes into a large integer (uint64_t for up to 64-bit chunks)
        uint64_t temp_chunk = 0;
        
        // Read up to 8 bytes (64 bits) starting from the current position
        for (int i = 0; i < 8 && byte_index + i < buffer.size(); ++i) {
            // Shift the byte into the temp_chunk. Assumes native byte order for simplicity.
            temp_chunk |= (static_cast<uint64_t>(buffer[byte_index + i]) << (i * 8));
        }

        // 3. Perform Bit Extraction:
        
        // a. Right-shift to align the start of the chunk with the LSB (bit 0)
        temp_chunk >>= bit_offset_in_byte;

        // b. Mask to isolate only the required bits (2^chunk_size - 1)
        uint64_t mask = (chunk_size == 64) ? UINT64_MAX : ((1ULL << chunk_size) - 1);
        uint64_t value = temp_chunk & mask;

        // 4. Convert the extracted value to a binary string
        std::string binary_str;
        // Iterate from the most significant bit of the chunk down to the LSB
        for (int i = chunk_size - 1; i >= 0; --i) {
            binary_str += ((value >> i) & 1) ? '1' : '0';
        }

        result_chunks.push_back(binary_str);
        
        // 5. Advance the bit position by the chunk size
        current_bit += chunk_size;
    }

    return result_chunks;
}