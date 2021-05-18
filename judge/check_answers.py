import os
import subprocess

files = os.listdir("maps")

for x, y in zip(*[iter(files)] * 2):
    print(x[:len(x) - 3] + ": ", end='')
    subprocess.call(
        "C:/Users/yyy/AppData/Local/Programs/Python/Python38/python.exe "
        "C:/Users/yyy/OneDrive/Pulpit/AGHSemestr6/APTO/judge/judge.py maps/" + x + " maps/" + y,
        shell=True)
