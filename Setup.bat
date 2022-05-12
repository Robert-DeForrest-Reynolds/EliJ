START /wait x86_64-Setup.bat
START /wait x86_64-Setup_2.bat

ECHO "Checking for GCC by Running Version Check"
\msys64\mingw64\bin\gcc --version