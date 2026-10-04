"""

* Tested against a table of 16 buckets with a 60% load factor
* The number of elements tested was 9, 64-bit, sequential integers 
* Seed used for both hash functions was 1234567890 

Output:

CAB32_1 total hashes: 9
CAB32_1 unique hashes: 9
MurmurHash3 total hashes: 9
MurmurHash3 unique hashes: 6

"""

# My own, hand-rolled CAB32_1 hash function 
hashes = [9,8,5,15,0,14,12,6,7]
unique = set(hashes)

print(f"CAB32_1 total hashes: {len(hashes)}")
print(f"CAB32_1 unique hashes: {len(unique)}")

# MurmurHash3
hashes = [10,2,0,5,13,14,14,13,2]
unique = set(hashes)

print(f"MurmurHash3 total hashes: {len(hashes)}")
print(f"MurmurHash3 unique hashes: {len(unique)}")

