import time

from dimacs import loadGraph, edgeList, saveSolution


def solve(k, S, edges):
    if k < 0:
        return None
    if len(edges) == 0:
        return S
    if k == 0:
        return None

    vertex = edges.pop()
    new_edges_1 = [e for e in edges if vertex[0] not in [e[0], e[1]]]
    new_S_1 = S.copy()
    new_S_1.add(vertex[0])
    new_S_2 = S.union([vertex[1]]).union([x[1] for x in edges if x[0] == vertex[0]]).union(
        [x[0] for x in edges if x[1] == vertex[0]])
    new_edges_2 = [e for e in edges if e[0] not in new_S_2 and e[1] not in new_S_2]

    S1 = solve(k - 1, new_S_1, new_edges_1)
    S2 = solve(k - len(new_S_2) + len(S), new_S_2, new_edges_2)

    if S1:
        return S1
    if S2:
        return S2

def solution(path):
    G = loadGraph(path)
    for k in range(1, len(G)):
        S = set()
        edges = edgeList(G)
        res = solve(k, S, edges)
        if res is not None:
            return res

    return -1


# tests = os.listdir("graph/graph/")
tests = ['s50']

for i in tests:
    time1 = time.time()
    res2 = solution('graph/' + i)
    time2 = time.time()

    print("The result for graph " + i + " is " + str(res2))
    print("It took ", time2 - time1, "s time")
    saveSolution('graph/' + i + ".sol", res2)
