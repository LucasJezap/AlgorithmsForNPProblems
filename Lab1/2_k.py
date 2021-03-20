import time

from dimacs import loadGraph, edgeList, saveSolution


def solve(edges, k, S):
    if len(edges) == 0:
        return S
    if k == 0:
        return None

    edge = edges.pop()

    new_edges_1 = [e for e in edges if edge[0] not in [e[0], e[1]]]
    new_edges_2 = [e for e in edges if edge[1] not in [e[0], e[1]]]
    new_S_1 = S.copy()
    new_S_2 = S.copy()
    new_S_1.add(edge[0])
    new_S_2.add(edge[1])

    S1 = solve(new_edges_1, k - 1, new_S_1)
    S2 = solve(new_edges_2, k - 1, new_S_2)

    if S1:
        return S1
    if S2:
        return S2


def solution(path):
    G = loadGraph(path)
    for k in range(1, len(G)):
        S = set()
        edges = set(edgeList(G))
        res = solve(edges, k, S)
        if res is not None:
            return res

    return -1


# tests = os.listdir("graph/")
tests = ['e5', 'e10', 'e20', 'e40']

for i in tests:
    time1 = time.time()
    res2 = solution('graph/' + i)
    time2 = time.time()

    print("The result for graph " + i + " is " + str(res2))
    print("It took ", time2 - time1, "s time")
    saveSolution('graph/' + i + ".sol", res2)
