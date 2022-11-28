ECHO "Run MSYS2 and install MinGW64 toolchain"
START /B /WAIT msys64\usr\bin\bash -l -c "yes | Pacman -Syu"
START /B /WAIT msys64\usr\bin\bash -l -c "Printf '\n yes' | Pacman -S --needed base-devel mingw-w64-x86_64-clang"
START /B /WAIT msys64\usr\bin\bash -l -c "yes | Pacman -S --needed base-devel python"

EXIT 0