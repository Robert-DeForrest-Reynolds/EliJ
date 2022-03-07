# If on Linux, you must run this script using sudo
# `sudo python3 VEnvGeneration.py`

from os import system, path
from sys import platform

def Verifications():
    if platform == "win32":
        return "Generation for Win32"
    elif platform == "linux":
        return "Generation for Linux"
    else:
        print("Generation Verifications Failure")
        return ("Cannot build on this platform")

VerificationsReturn = Verifications()
print(VerificationsReturn)

def VEnvGenerate():
    if VerificationsReturn == "Generation for Win32":
        system("python -m venv .venv")
        print("Generated")
        return "Generated for Win32"
    elif VerificationsReturn == "Generation for Linux":
        system("sudo python3 -m venv .venv")
        print("Generated")
        return "Generated for Linux"
    else:
        print("Failed to generate")

VEnvGenerateReturn = VEnvGenerate()
print(VEnvGenerateReturn)

def InstallPipPackages():
    if VEnvGenerateReturn == "Generated for Win32":
        system(".venv\Scripts\activate && pip install rich")
    elif VEnvGenerateReturn == "Generated for Linux":
        system(". .venv/bin/activate && pip install rich && pip list")

if path.exists(".venv"):
    print("Installing pip packages")
    InstallPipPackages()
    print("Seems to have been successfu")