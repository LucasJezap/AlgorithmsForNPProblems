import random

import matplotlib.pyplot as plt
import pycosat


def generate_random_variable(n):
    S = [1, -1]
    V = range(1, n + 1)
    return random.choice(V) * random.choice(S)


def generate_random_clause(n, k):
    return [generate_random_variable(n) for _ in range(k)]


def generate_random_formula(n, k, a_n):
    return [generate_random_clause(n, k) for _ in range(a_n)]


def generate_list_of_random_formulas(n, k, a_n, T):
    return [generate_random_formula(n, k, a_n) for _ in range(T)]


def experiment(step, n, k, T, file):
    a = 1.0
    x = []
    y = []

    while a <= 10.0:
        formulas = generate_list_of_random_formulas(n, k, int(a * n), T)
        solved_formulas = [pycosat.solve(formula) for formula in formulas]
        satisfied_formulas = [solved_formula for solved_formula in solved_formulas if
                              not isinstance(solved_formula, str)]
        file.write(str(a) + " " + str(len(satisfied_formulas) / T) + "\n")
        x.append(a)
        y.append(len(satisfied_formulas) / T)
        a += step

    return x, y


def plot(x, y):
    plt.plot(x, y)
    plt.show()


k = 3
n = 100
T = 100
step = 0.1
file = open("data_task1", "w")

x, y = experiment(step, n, k, T, file)
file.close()
for xx, yy in zip(x, y):
    print(str(xx) + '\t\t\t' + str(yy))
plot(x, y)
