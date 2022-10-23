ECHO "Download cygwin exe"
curl -LO https://www.cygwin.com/setup-x86_64.exe

ECHO "Running Cygwin Installer"
setup-x86_64.exe --quiet-mode
