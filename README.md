# (Undergoing maintenence in .README) Boltpawn's Hash Collection
* Public domain under Unlicense, no royalties, no cost, no need to even include the license
* Just like the hash itself, the Unlicense also applies to everything in this repository 
* tl;dr everything here is Public Domain

# TBN and TBA djb2-like hash
* Self contained in a single C header file
* Slight performance edge over djb2
* Functional with any unsigned integer of at least 16 bits
* ANSI C89 for maximum portability 

# CAB32 Family of Hash Functions
* Self-contained in a single C header file 
* Fast hash function with exceptional performance and competitive avalanche distribution
* Beats MurmurHash3 consistently in raw execution from 5-25% with -O3/-Ofast and distribution
* C99 with no dependencies, just compile it with any compliant compiler 
* Hashes are 32-bits long, great for embedded systems

# LLM Usage
No AI models were used in this repository except to generate a list of sequential strings in `tests/sequentialstrings.c`. Everything else here is 100% human.
