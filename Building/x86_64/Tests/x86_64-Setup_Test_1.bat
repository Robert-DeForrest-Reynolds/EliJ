ECHO "Checking for GCC by Running Version Check"
START /B /WAIT msys64\mingw64 gcc Building\x86_64\Tests\x86_64_Test.c -o Building\x86_64\Tests\x86_64_Test.exe
START /B /WAIT msys64\mingw64 Building\x86_64\Tests\x86_64_Test
Building\x86_64\Tests\x86_64_Test