#include "CAB32.h"

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

/*

MurmurHash3 is in the public domain. Code copied and pasted from here: https://en.wikipedia.org/wiki/MurmurHash 

*/
static inline uint32_t murmur_32_scramble(uint32_t k) {
    k *= 0xcc9e2d51;
    k = (k << 15) | (k >> 17);
    k *= 0x1b873593;
    return k;
}
uint32_t murmur3_32(const uint8_t* key, size_t len, uint32_t seed)
{
	uint32_t h = seed;
    uint32_t k;
    /* Read in groups of 4. */
    for (size_t i = len >> 2; i; i--) {
        // Here is a source of differing results across endiannesses.
        // A swap here has no effects on hash properties though.
        memcpy(&k, key, sizeof(uint32_t));
        key += sizeof(uint32_t);
        h ^= murmur_32_scramble(k);
        h = (h << 13) | (h >> 19);
        h = h * 5 + 0xe6546b64;
    }
    /* Read the rest. */
    k = 0;
    for (size_t i = len & 3; i; i--) {
        k <<= 8;
        k |= key[i - 1];
    }
    // A swap is *not* necessary here because the preceding loop already
    // places the low bytes in the low places according to whatever endianness
    // we use. Swaps only apply when the memory is copied in a chunk.
    h ^= murmur_32_scramble(k);
    /* Finalize. */
	h ^= len;
	h ^= h >> 16;
	h *= 0x85ebca6b;
	h ^= h >> 13;
	h *= 0xc2b2ae35;
	h ^= h >> 16;
	return h;
}

int main(void) {
	// printf("Hello World\n");

	// Change to whatever you like 
	uint32_t seed = 1234567890;

	union CABBlock data;
	cab_hash_t result = 0;

	data.bytearray[0] = 0b11111101;
	data.bytearray[1] = 0b11101111;
	data.bytearray[2] = 0b11010110;
	data.bytearray[3] = 0b10010000;
	data.bytearray[4] = 0b11101000;
	data.bytearray[5] = 0b11011110;
	data.bytearray[6] = 0b10011000;
	data.bytearray[7] = 0b11011111;
	
	result = CAB32_1(data.bytearray, sizeof(data.bytearray) / sizeof(uint8_t), seed); 

	printf("Hash = %u\n", result);

	/* */

	// Distribution testing with integers 
	for (uint64_t i = 0; i < 2000; i++) { 
		printf("%llu :: %u\n", i, CAB32_1(&i, sizeof(uint64_t), seed));

	}
	
	// Benchmark
	size_t size = 2e+9;		// Two gigabytes, perfect for our benchmark 
	uint8_t* block = (uint8_t*)malloc(size * sizeof(uint8_t));		// No need to memset it since we don't care about its contents 

	assert(block);
	
	LARGE_INTEGER frequency;
	LARGE_INTEGER start;
	LARGE_INTEGER end;
	double elapsed_seconds;

	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&start);

	result = CAB32_1(block, size * sizeof(uint8_t), seed);

	QueryPerformanceCounter(&end);

	elapsed_seconds = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;

	printf("CAB32_1: %u :: %.6f seconds\n", result, elapsed_seconds);

	// MurmurHash3 benchmark
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&start);

	result = murmur3_32(block, size * sizeof(uint8_t), seed);

	QueryPerformanceCounter(&end);

	elapsed_seconds = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;

	printf("MurmurHash3: %u :: %.6f seconds\n", result, elapsed_seconds);

	free(block);

	return 0;

}

