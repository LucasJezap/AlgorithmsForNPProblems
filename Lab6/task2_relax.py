import time

from pulp import *

from dimacs import loadGraph, edgeList, saveSolution


def add_variables(graph):
    variables = []
    for idx in range(1, len(graph) - 1):
        var = LpVariable("x" + str(idx), lowBound=0, upBound=1, cat="Continuous")
        variables.append(var)

    return variables


def add_cost_function(model, variables):
    model += sum(variables)


def add_constraints(model, variables, edges):
    for edge in edges:
        model += variables[edge[0] - 1] + variables[edge[1] - 1] >= 1


def get_answer(variables):
    return set([int(v.name[1:]) for v in variables if v.varValue >= 0.5])


def solve(graph):
    model = LpProblem("VertexCover", LpMinimize)

    variables = add_variables(graph)
    add_cost_function(model, variables)
    add_constraints(model, variables, edgeList(graph))

    model.solve(PULP_CBC_CMD(msg=True))

    return get_answer(model.variables())


def solution(path):
    graph = loadGraph(path)
    vertex_cover = solve(graph)

    return vertex_cover


tests = [file for file in os.listdir("graph/") if os.path.splitext(file)[1] != '.sol']
# tests = ["e5", "e10", "e20"]

for i in tests:
    if i[0] != "f":
        print(i)
        time1 = time.time()
        res = solution('graph/' + i)
        time2 = time.time()

        print("The vertex cover for graph " + i + " is " + str(res))
        print("It took ", time2 - time1, "s time\n\n")
        saveSolution('graph/' + i + ".sol", res)
