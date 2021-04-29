import math
import os
import time
from random import random, choice

from dimacs import loadGraph, saveSolution, isVC, edgeList


def solve_logn(graph):
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


def start_point(graph):
    return solve_logn(graph)


def list_of_vertices(graph):
    return list(range(1, len(graph)))


def create_neighbour_solution(graph, S):
    edges = edgeList(graph)
    new_S = S.copy()

    for i in range(100):
        vertex_to_remove = choice([v for v in list_of_vertices(graph) if v in S])
        new_S.remove(vertex_to_remove)
        if isVC(edges, new_S):
            return new_S

        new_S.add(vertex_to_remove)

    return new_S


def calculate_temperature(t, beta):
    return t / (1 + beta * t)


def f(S):
    return 1.0 / len(S)


def simulated_annealing(graph):
    global temp
    S = start_point(graph)
    best_S = S

    for cool_iteration in range(1, num_of_iterations + 1):
        new_S = create_neighbour_solution(graph, S)
        temp = calculate_temperature(temp, cool_iteration)
        if f(new_S) >= f(S):
            S = new_S
            if f(S) >= f(best_S):
                best_S = S

        elif math.exp((f(S) - f(new_S)) / temp) > random():
            S = new_S

    return best_S


def solution3(path):
    G = loadGraph(path)
    res = simulated_annealing(G)

    return res


tests = [file for file in os.listdir("graph/") if os.path.splitext(file)[1] != '.sol']
#tests = ['f56']
temp = 1
num_of_iterations = 200

for i in tests:
    time1 = time.time()
    res2 = solution3('graph/' + i)
    time2 = time.time()

    print(len(res2))

    print("The simulated-annealing-approximation vertex cover for graph " + i + " is " + str(res2))
    print("It took ", time2 - time1, "s time")
    saveSolution('graph/' + i + ".sol", res2)
