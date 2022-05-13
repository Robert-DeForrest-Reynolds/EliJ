START /WAIT git clone https://github.com/python/cpython

cd cpython

set string=%CD%

set string=%string:cpython=msys64%

set PATH=%PATH%;%string%;
ECHO %string%

START /WAIT mingw64 ./configure
START /WAIT mingw64 make
START /WAIT mingw64 make test
START /WAIT mingw64 make install