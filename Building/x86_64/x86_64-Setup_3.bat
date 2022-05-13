ECHO "Run MSYS2 and install MinGW64 toolchain"
START /WAIT msys64\usr\bin\bash -l -c "Pacman -Syu && pacman -S --needed base-devel mingw-w64-x86_64-toolchain"

EXIT 0