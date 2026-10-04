"""

* Tested against a table of 32 buckets with a 60% load factor
* The number of elements tested was 19
* Seed used for both hash functions was 1234567890 

Output:

CAB32_1 total hashes: 19
CAB32_1 unique hashes: 14
MurmurHash3 total hashes: 19
MurmurHash3 unique hashes: 12

"""

# My own, hand-rolled CAB32_1 hash function 
hashes = [25,8,5,15,16,14,28,22,7,29,8,19,9,9,24,16,2,29,22]
unique = set(hashes)

print(f"CAB32_1 total hashes: {len(hashes)}")
print(f"CAB32_1 unique hashes: {len(unique)}")

# MurmurHash3
hashes = [26,2,16,21,29,30,30,29,18,8,1,11,0,21,29,11,26,26,23]
unique = set(hashes)

print(f"MurmurHash3 total hashes: {len(hashes)}")
print(f"MurmurHash3 unique hashes: {len(unique)}")

