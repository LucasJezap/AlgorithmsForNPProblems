import time

from dimacs import loadGraph, edgeList, saveSolution


def find_good_vertex(edges, n):
    count = [0] * n
    for edge in edges:
        count[edge[0]] += 1
        count[edge[1]] += 1

    one_neighbour = next((ind for ind, v in enumerate(count) if v == 1), -1)
    if one_neighbour != -1:
        vertex = next(edge for edge in edges if one_neighbour in [edge[0], edge[1]])
        neighbour = [v for v in [vertex[0], vertex[1]] if v != one_neighbour][0]
        return True, vertex, neighbour

    return False, count.index(max(count))


def solve(graph, k, S, edges):
    if k < 0:
        return None
    if len(edges) == 0:
        return S
    if k == 0:
        return None

    tmp = find_good_vertex(edges, len(graph) - 1)
    if tmp[0]:
        new_edges = [e for e in edges if tmp[1][0] not in [e[0], e[1]] and tmp[1][1] not in [e[0], e[1]]]
        new_S = S.copy()
        new_S.add(tmp[2])

        S = solve(graph, k - len(new_S) + len(S), new_S, new_edges)

        if S:
            return S
    else:
        vertex = next(v for v in edges if tmp[1] in [v[0], v[1]])
        # vertex = edges.pop()
        new_edges_1 = [e for e in edges if vertex[0] not in [e[0], e[1]]]
        new_S_1 = S.copy()
        new_S_1.add(vertex[0])
        new_S_2 = S.union([vertex[1]]).union([x[1] for x in edges if x[0] == vertex[0]]).union(
            [x[0] for x in edges if x[1] == vertex[0]])
        new_edges_2 = [e for e in edges if e[0] not in new_S_2 and e[1] not in new_S_2]

        S1 = solve(graph, k - 1, new_S_1, new_edges_1)
        S2 = solve(graph, k - len(new_S_2) + len(S), new_S_2, new_edges_2)

        if S1:
            return S1
        if S2:
            return S2


def kernelisation(edges, n, k):
    new_k = k
    new_edges = edges
    new_S = set()
    while True:
        changed = False
        count = [0] * n
        for edge in new_edges:
            count[edge[0]] += 1
            count[edge[1]] += 1

        one = next((ind for ind, v in enumerate(count) if v == 1), -1)
        k_neigh = next((ind for ind, v in enumerate(count) if v > new_k), -1)
        if one != -1:
            changed = True
            vertex = next(edge for edge in new_edges if one in [edge[0], edge[1]])
            neighbour = [v for v in [vertex[0], vertex[1]] if v != one][0]
            new_S.add(neighbour)
            new_k -= 1
            new_edges = [e for e in new_edges if neighbour not in [e[0], e[1]]]
        elif k_neigh != -1:
            changed = True
            new_S.add(k_neigh)
            new_k -= 1
            new_edges = [e for e in new_edges if k_neigh not in [e[0], e[1]]]

        if new_k == 0 or not changed:
            break

    return new_edges, new_k, new_S


def solution(path):
    G = loadGraph(path)
    for k in range(1, len(G)):
        edges = edgeList(G)
        new_edges, new_k, new_S = kernelisation(edges, len(G), k)
        print(k)
        print(new_k)
        print(len(new_edges))
        print()
        res = solve(G, new_k, new_S, new_edges)
        if res is not None:
            return res

    return -1


# tests = os.listdir("graph/graph/")
# tests = ['b100']
# tests = ['k330_b']
# tests = ['k330_c']
# tests = ['m100']

for i in tests:
    time1 = time.time()
    res2 = solution('graph/' + i)
    time2 = time.time()

    print("The result for graph " + i + " is " + str(res2))
    print("It took ", time2 - time1, "s time")
    saveSolution('graph/' + i + ".sol", res2)
