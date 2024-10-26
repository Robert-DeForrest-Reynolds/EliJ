SourceFiles = $(wildcard Iwa/Source/*.c)\
			  $(wildcard  Iwa/Source/Strings/*.c)\
			  $(wildcard  Iwa/Source/Files/*.c)\
			  $(wildcard  Iwa/Source/Interpreter/*.c)\

Include = Iwa/Source/Include

Build:
	clang $(SourceFiles) -I$(Include) -o Iwa
build: Build

Test:
	clang $(SourceFiles) -I$(Include) -o Iwa
	@echo ""
	./Iwa.exe Examples/HelloWorld.papple
test: Test

timetest:
	time clang $(SourceFiles) -I$(Include) -o Iwa
	time ./Iwa.exe Examples/HelloWorld.papple
	