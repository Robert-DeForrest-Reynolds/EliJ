Build:
	gcc CIwa/Iwa.c -o CIwa
build: Build

Run:
	rm CIwa.exe
	gcc CIwa/Iwa.c -o CIwa
	./CIwa.exe
run: Run
