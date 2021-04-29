import os
import time

from dimacs import loadGraph, edgeList, saveSolution


def solve(graph):
    edges = edgeList(graph)
    S = set()

    while len(edges) != 0:
        edge = edges.pop()
        S.add(edge[0])
        S.add(edge[1])
        edges = [e for e in edges if e[0] not in [edge[0], edge[1]] and e[1] not in [edge[0], edge[1]]]

    return S


def solution(path):
    G = loadGraph(path)
    res = solve(G)

    return res


tests = [file for file in os.listdir("graph/") if os.path.splitext(file)[1] != '.sol']
# tests = ['e5']

for i in tests:
    time1 = time.time()
    res2 = solution('graph/' + i)
    time2 = time.time()

    print("The 2-approximation vertex cover for graph " + i + " is " + str(res2))
    print("It took ", time2 - time1, "s time")
    saveSolution('graph/' + i + ".sol", res2)
