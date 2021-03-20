import time
from itertools import combinations

from dimacs import loadGraph, edgeList, isVC


def solve(graph, k):
    edges = edgeList(graph)
    vertices = list(range(1, len(graph)))

    for subset in list(combinations(vertices, k)):
        if isVC(edges, subset):
            return True

    return False


def solution(path):
    G = loadGraph(path)
    for k in range(1, len(G)):
        res = solve(G, k)
        if res:
            return k

    return -1


# tests = os.listdir("graph/graph/")
tests = ['e5', 'e10', 'e20']

for i in tests:
    time1 = time.time()
    res2 = solution('graph/' + i)
    time2 = time.time()

    print("The smallest k for graph " + i + " is " + str(res2))

    print("It took ", time2 - time1, "s time")
