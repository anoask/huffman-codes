# huffman-codes
Implementation of a Huffman Tree in C++, a data structure used for efficient data compression and decompression based on the frequency of characters in the input data. 

Header Files: HuffmanTree.hpp, HuffmanBase.hpp.

HuffmanNode Class

HuffmanTree Class: Construction and Destruction, Building the Tree (buildTree()), Building the Code Table (buildCodeTable()), Compression (compress()), Tree Serialization (serializeTree() and serializeTreeHelper()), Decompression (decompress()).

Decompression process: Deserialize, Decode. 

// How to compile: g++ -std=c++17 -Wall -I$(CATCH_SINGLE_INCLUDE) (All cpp files)

// Example if Catch2 and source files are in this directory and at directory level: 

//    Example: g++ -std=c++17 -Wall *.cpp

// To see what tests were successful and failed, run your executable with the -s flag

//    Example: a.out -s

// A successful test should output: All tests passed (12 assertions in 1 test case)
