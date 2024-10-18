SourceFiles = $(wildcard Iwa/Source/*.c)\
			  $(wildcard  Iwa/Source/Strings/*.c)\
			  $(wildcard  Iwa/Source/Files/*.c)\

Include = Iwa/Source/Include

Build:
	clang $(SourceFiles) -I$(Include) -o CIwa
build: Build

Test:
	clang $(SourceFiles) -I$(Include) -o CIwa && ./CIwa.exe Examples/HelloWorld.papple
test: Test
