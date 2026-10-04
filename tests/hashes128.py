"""

* Tested against a table of 128 buckets with a 60% load factor
* The number of elements tested was 76
* Seed used for both hash functions was 1234567890 

Output:

CAB32_1 total hashes: 76
CAB32_1 unique hashes: 59
MurmurHash3 total hashes: 76
MurmurHash3 unique hashes: 58

"""

# My own, hand-rolled CAB32_1 hash function 
hashes = [89,72,37,111,48,14,28,118,103,29,72,83,9,105,24,48,66,125,118,70,54,63,108,79,11,89,25,74,51,59,113,103,83,76,20,66,51,119,30,56,72,15,81,27,58,25,101,120,38,1,52,89,82,57,40,90,114,104,20,67,50,29,46,115,95,12,23,4,96,76,60,92,113,92,28,71]
unique = set(hashes)

print(f"CAB32_1 total hashes: {len(hashes)}")
print(f"CAB32_1 unique hashes: {len(unique)}")

# MurmurHash3
hashes = [58,34,16,85,61,94,30,125,114,72,1,75,32,85,61,11,90,58,55,28,108,81,107,5,101,104,5,83,60,63,66,108,62,121,48,91,12,36,7,17,82,42,10,94,99,109,61,96,54,61,32,87,97,123,67,107,114,99,112,41,71,58,21,65,48,68,78,126,63,100,77,61,125,23,52,96]
unique = set(hashes)

print(f"MurmurHash3 total hashes: {len(hashes)}")
print(f"MurmurHash3 unique hashes: {len(unique)}")

