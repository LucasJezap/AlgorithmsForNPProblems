import os
import time
import pycosat

from dimacs import loadGraph, edgeList


def solve(edges):
    cnf = []
    for edge in edges:
        cnf.append([edge[0], edge[1]])
    return cnf


def solution(path):
    graph = loadGraph(path)
    edges = edgeList(graph)
    cnf = solve(edges)

    return cnf


# tests = [file for file in os.listdir("graph/") if os.path.splitext(file)[1] != '.sol']
tests = ["e5", "e10", "e20"]

for i in tests:
    time1 = time.time()
    res = solution('graph/' + i)
    time2 = time.time()

    print("The sat solution for sat file " + i + " is " + str(res))
    print("It took ", time2 - time1, "s time\n\n")
    # saveCNF('sat/' + i + ".sol", res)
