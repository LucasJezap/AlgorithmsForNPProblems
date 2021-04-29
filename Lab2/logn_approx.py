import os
import time

from dimacs import loadGraph, edgeList, saveSolution


def solve(graph):
    count = [len(vertex) for vertex in graph]
    edges = edgeList(graph)
    S = set()

    while len(edges) != 0:
        vertex = count.index(max(count))
        S.add(vertex)
        for edge in edges:
            if edge[0] == vertex or edge[1] == vertex:
                count[edge[0]] -= 1
                count[edge[1]] -= 1
        edges = [e for e in edges if vertex not in [e[0], e[1]]]

    return S


def solution2(path):
    G = loadGraph(path)
    res = solve(G)

    return res


tests = [file for file in os.listdir("graph/") if os.path.splitext(file)[1] != '.sol']
# tests = ['e10']

for i in tests:
    time1 = time.time()
    res2 = solution2('graph/' + i)
    time2 = time.time()

    print("The log-n-approximation vertex cover for graph " + i + " is " + str(res2))
    print("It took ", time2 - time1, "s time")
    saveSolution('graph/' + i + ".sol", res2)
