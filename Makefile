SourceFiles = $(wildcard Iwa/Source/*.c)\
			  $(wildcard  Iwa/Source/Strings/*.c)\

Include = Iwa/Source/Include

Build:
	clang Iwa/Source/Iwa.c -o CIwa 
build: Build

Test:
	clang $(SourceFiles) -I$(Include) -o CIwa && ./CIwa.exe test.papple flag1 flag2
test: Test
