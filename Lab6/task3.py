import time

from pulp import *

from dimacs import loadGraph, saveSolution, edgeList


def add_variables(graph, k):
    variables = []
    for idx in range(1, len(graph) - 1):
        for j in range(1, k + 1):
            var = LpVariable("x" + str(idx) + "_" + str(j), cat="Binary")
            variables.append(var)

    return variables


def add_cost_function(model, variables):
    model += sum(variables)


def add_one_color_constraints(model, variables, k):
    for idx in range(0, len(variables), k):
        model += sum(variables[idx: idx + k]) == 1


def add_only_one_color_constraint(model, variables, k, edges):
    for edge in edges:
        for j in range(1, k + 1):
            model += variables[(edge[0] - 1) * k + j - 1] + variables[(edge[1] - 1) * k + j - 1] <= 1


def get_answer(variables):
    values = [v.name[1:] for v in variables if v.varValue]
    used_colors = set()
    for v in values:
        print("Vertex " + str(v.rsplit('_', 1)[0]) + " is colored with color " + str(v.rsplit('_', 1)[1]))
        used_colors.add(v.rsplit('_', 1)[1])

    print("Used colors: " + str(len(used_colors)))
    return values


def solve(graph, k):
    model = LpProblem("GraphColoring", LpMinimize)

    variables = add_variables(graph, k)
    add_one_color_constraints(model, variables, k)
    add_only_one_color_constraint(model, variables, k, edgeList(graph))
    add_cost_function(model, variables)

    model.solve(PULP_CBC_CMD(msg=False))

    return get_answer(model.variables())


def solution(path):
    graph = loadGraph(path)
    k = 5
    vertex_cover = solve(graph, k)

    return vertex_cover


# tests = [file for file in os.listdir("graph/") if os.path.splitext(file)[1] != '.sol']
tests = ["e5", "e10", "e20"]

for i in tests:
    print(i)
    time1 = time.time()
    res = solution('graph/' + i)
    time2 = time.time()

    print("The graph coloring for graph " + i + " is " + str(res))
    print("It took ", time2 - time1, "s time\n\n")
    saveSolution('graph/' + i + ".sol", res)
