import os

import pycosat

from dimacs import loadX3C


def create_clause(j, list_of_sets):
    return [ind + 1 for ind, val in enumerate(list_of_sets) if j in val]


def create_clauses(clause):
    clauses = []
    for i in range(len(clause)):
        for j in range(i + 1, len(clause)):
            clauses.append([-clause[i], -clause[j]])

    return clauses


def x3c_to_sat_reduction(filename):
    exists_solution, elements, list_of_sets = read_test_data(filename)

    clauses1 = [create_clause(j, list_of_sets) for j in range(1, elements + 1)]
    clauses2 = []
    for clause in clauses1:
        clauses2 = clauses2 + create_clauses(clause)

    all_clauses = clauses1 + clauses2

    solved = pycosat.solve(all_clauses)
    if isinstance(solved, str):
        return "NO"

    solution = [1 if sol > 0 else 0 for sol in solved[:elements]]
    return solution


def read_test_data(filename):
    elements, list_of_sets = loadX3C(filename)
    exists_solution = filename.find("yes") != -1

    return exists_solution, elements, list_of_sets


base = 'x3c/'
tests = [file for file in os.listdir(base)]

for i in tests:
    print(str(i) + " " + str(x3c_to_sat_reduction(base + i)))
