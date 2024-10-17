Build:
	clang Iwa/Source/Iwa.c -o CIwa 
build: Build

Test:
	clang Iwa/Source/Iwa.c -o CIwa && ./CIwa.exe test.papple flag1 flag2
test: Test
