import os
import time

import pycosat

from dimacs import loadGraph, edgeList, saveSolution


def index(i, j, n):
    return (i + j) * (i + j + 1) // 2 + i + n + 1


def add_edge_cases(cnf, n):
    for idx in range(n + 1):
        cnf.append([index(idx, 0, n)])
    for idx in range(1, n + 1):
        cnf.append([-index(0, idx, n)])

    return cnf


def add_implications(cnf, n):
    for i in range(1, n + 1):
        for j in range(1, n + 1):
            cnf.append([-index(i - 1, j, n), index(i, j, n)])
            cnf.append([-index(i - 1, j - 1, n), -i, index(i, j, n)])
    return cnf


def solve(graph, edges, k):
    cnf = []
    n = len(graph) - 1
    for edge in edges:
        cnf.append([edge[0], edge[1]])

    cnf = add_edge_cases(cnf, n)
    cnf = add_implications(cnf, n)
    cnf.append([-index(n, k + 1, n)])

    return cnf


def get_vertices(sol, n):
    return set([vertex for vertex in sol if abs(vertex) <= n and vertex > 0])


def solution(path):
    graph = loadGraph(path)
    edges = edgeList(graph)
    for k in range(1, len(graph)):
        cnf = solve(graph, edges, k)
        sol = pycosat.solve(cnf)
        if sol != "UNSAT":
            return get_vertices(sol, len(graph) - 1)


# tests = [file for file in os.listdir("graph/") if os.path.splitext(file)[1] != '.sol']
tests = ["e5", "e10", "e20", "e40", "m20", "m30", "m40", "m50", "p20", "p35", "p60"]

for t in tests:
    time1 = time.time()
    res = solution('graph/' + t)
    time2 = time.time()

    print("The sat solution for sat file " + t + " is " + str(res))
    print("It took ", time2 - time1, "s time\n\n")
    saveSolution('graph/' + t + ".sol", res)
