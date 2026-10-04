import string
from random import randint

def generateDataset(count, minimum, maximum):
	LONGSTRING = f"{string.ascii_letters}{string.ascii_lowercase}{string.ascii_uppercase}0123456789" 
	LONGSTRING_LEN = len(LONGSTRING)

	out = []

	for i in range(0, count):
		J_MAX = randint(minimum, maximum)
		it = []
		for j in range(0, J_MAX):
			it.append(LONGSTRING[randint(0, LONGSTRING_LEN - 1)]) 
		out.append(''.join(it))
	
	return out

def main():
	# print("Hello World")

	result = generateDataset(1000, 8, 1024)

	print("#define DATASET_MAX 1000\nconst char* DATASET[DATASET_MAX] = { ")

	for index in range(0, len(result) - 1):
		print(f"\"{result[index]}\",")

	print(f"\"{result[len(result) - 1]}\"\n\n}};")
	print("\n#include <stdio.h>\n\nint main(void) {\n\tprintf(\"Hello World\\n\");\n\n}") 

if __name__ == "__main__":
	main()
