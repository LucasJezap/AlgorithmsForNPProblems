import os
import subprocess

base = "cha6"

for filename in os.listdir("maps"):
    if filename.endswith(".out"):
        os.remove("maps/" + filename)

for filename in os.listdir("maps"):
    if filename.endswith(".in"):
        subprocess.call(
            "C:/Users/yyy/OneDrive/Pulpit/AGHSemestr6/APTO/Sokoban_checkpoint3/cmake-build-debug/best_first_search.exe "
            "C:/Users/yyy/OneDrive/Pulpit/AGHSemestr6/APTO/judge/maps/" + filename +
            " >> C:/Users/yyy/OneDrive/Pulpit/AGHSemestr6/APTO/judge/maps/" + filename[:len(filename) - 2] + "out",
            shell=True)
        print(filename + " done.")
