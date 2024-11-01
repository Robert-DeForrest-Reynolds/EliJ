SourceFiles = $(wildcard Iwa/Source/*.c)\
			  $(wildcard  Iwa/Source/Strings/*.c)\
			  $(wildcard  Iwa/Source/Files/*.c)\
			  $(wildcard  Iwa/Source/Interpreter/*.c)\

Include = Iwa/Source/Include

Build:
	clang $(SourceFiles) -I$(Include) -o Iwa
build: Build

Debug:
	clang -g $(SourceFiles) -I$(Include) -o Iwa -Wno-deprecated-non-prototype -DDEBUG=1
debug: Debug

Release:
	clang $(SourceFiles) -I$(Include) -o Iwa -Wno-deprecated-non-prototype
release: Release

Test:
	clang -g $(SourceFiles) -I$(Include) -o Iwa -Wno-deprecated-non-prototype -DDEBUG=1
	@echo ""
	./Iwa.exe Examples/Test.papple
test: Test

timetest:
	clang -g $(SourceFiles) -I$(Include) -o Iwa -Wno-deprecated-non-prototype -DDEBUG=1
	@echo ""
	time ./Iwa.exe Examples/HelloWorld.papple
	