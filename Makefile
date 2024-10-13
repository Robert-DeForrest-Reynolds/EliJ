Build_Iwa:
	clang++ Iwa/Main.cpp -o Iwa
build_iwa: Build_Iwa

Build_Iwa_Debug:
	clang++ -E -Fa Iwa/Main.cpp -o Iwa
build_iwa_debug: Build_Iwa_Debug

Release_Iwa:
	clang++ -O2 Iwa/Main.cpp -o Iwa
release_iwa: Release_Iwa

Run:
	clang Iwa/Source/Iwa.c -o CIwa && ./CIwa.exe
run: Run
