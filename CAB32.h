/*

This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <https://unlicense.org>

*/
#ifndef CAB32_HASHES_H
#define CAB32_HASHES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#define cab_hash_t uint32_t

#define CAB_BLOCK_SIZE (size_t)8

/*

Exact reasoning for picking these primes is unknown 

*/
#define CAB_PRIME (cab_hash_t)2576980349
#define CAB_MIXER_A (cab_hash_t)1000000439
#define CAB_MIXER_B (cab_hash_t)2500001401
#define CAB_MIXER_C (cab_hash_t)1500001387
#define CAB_MIXER_D (cab_hash_t)3000001259

typedef union CABBlock {
	uint64_t integer;
	uint8_t bytearray[CAB_BLOCK_SIZE];
	uint32_t split[CAB_BLOCK_SIZE / sizeof(uint32_t)];

} CABBlock;

static inline cab_hash_t CAB32_mixer(union CABBlock* a, uint32_t seed) {		// This is the part where the name came from 
	cab_hash_t out = seed ^ (a->split[1] ^ a->split[0]);		// This section here is endian-dependent. Use with caution unless hashes across systems don't need to match 
	out += CAB_MIXER_C;
	out ^= out << 16;
	out += CAB_MIXER_A;
	out ^= out >> 12;
	out += CAB_MIXER_B;
	return out;

}

// Name is derived from the combination of primes used in the "mixer" function. It was originally named "ChANDlier32" due to it being an "AND" heavy hash function, but that was scrapped 
cab_hash_t CAB32_1(const void* data, const size_t size, const uint32_t seed) { 
	cab_hash_t hash = CAB_PRIME;
	
	size_t max = size / CAB_BLOCK_SIZE;
	size_t i = 0;

	// Main hashing loop
	for (i = 0; i < max; i++) {
		union CABBlock obj;
		memcpy(&obj.integer, (const uint8_t *)data + i * CAB_BLOCK_SIZE, sizeof(uint64_t));
		
		hash ^= CAB32_mixer(&obj, seed); 
		hash ^= hash >> 24;
		hash += CAB_MIXER_A;
		 
	}

	// Handle any remaining data
	for (i = i * CAB_BLOCK_SIZE; i < size; i++) {
		const uint8_t BYTE = *((const uint8_t*)data + i);
		hash ^= hash << 12;
		hash += CAB_MIXER_B;
		hash += CAB_MIXER_C;
		hash ^= hash >> 16;
		hash += (cab_hash_t)BYTE;
		

	}

	// Finalize
	hash ^= hash >> 12;
	hash *= CAB_MIXER_C;		// No multiplications in loops since they slow down performance 
	hash ^= seed;
	hash *= CAB_MIXER_A;		// Multiplications are used sparingly to avoid bad performance with small strings 
	hash ^= hash << 24;
	hash *= CAB_MIXER_B;
	hash ^= hash >> 16;
	hash *= CAB_MIXER_D;

	return hash;

}

/*

TO-DO: Write an even faster version that processes 16/32/64 bytes of input in the future

*/
cab_hash_t CAB32_2 (const void* data, const size_t size, const uint32_t seed);

#ifdef __cplusplus
}
#endif

#endif		// CAB32_HASHES_H

