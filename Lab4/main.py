import os
import time

from dimacs import saveCNF, loadCNF


def is_clause_correct(C, V):
    return len([l for l in C if l in V and V[l] == 1]) > 0


def simplifyClause(C, V):
    if is_clause_correct(C, V):
        return None
    newC = [l for l in C if l not in V or V[l] != -1]
    return newC


def simplifyCNF(cnf, V):
    newCnf = (cnf[0], [])
    for c in cnf[1]:
        simp = simplifyClause(c, V)
        if simp is None:
            continue
        if len(simp) == 0:
            return None
        newCnf[1].append(simp)

    return newCnf


def get_V_with_v_1(V, v):
    new_V = V.copy()
    new_V[v] = 1
    new_V[-v] = -1
    return new_V


def unit_propagation(cnf, V):
    newCnf = cnf[1].copy()
    newV = V.copy()

    while True:
        one_clause = next((c for c in newCnf if len(c) == 1), None)
        if one_clause is None:
            return (cnf[0], newCnf), newV
        if one_clause[0] in newV and newV[one_clause[0]] == -1:
            return None, newV

        newV[one_clause[0]] = 1
        newV[-one_clause[0]] = -1
        tmp = simplifyCNF((cnf[0], newCnf), newV)
        if tmp is None:
            return None, newV
        newCnf = tmp[1]


def is_in_every_clause(clauses, l):
    for c in clauses:
        if not l in c:
            return False
    return True


def fix_const(cnf, V):
    newCnf = cnf[1].copy()
    newV = V.copy()
    for l in range(-cnf[0], cnf[0] + 1):
        if l == 0:
            continue
        if is_in_every_clause(newCnf, l):
            newV[l] = 1
            newV[-l] = -1
            tmp = simplifyCNF((cnf[0], newCnf), newV)
            if tmp is None:
                return None, newV
            newCnf = tmp[1]

    return (cnf[0], newCnf), newV


def solve(cnf, V):
    if not cnf[1]:
        return V

    cnf, V = unit_propagation(cnf, V)
    if cnf is None:
        return "UNSAT"
    if not cnf[1]:
        return V

    cnf, V = fix_const(cnf, V)
    if cnf is None:
        return "UNSAT"
    if not cnf[1]:
        return V

    v = abs(cnf[1][0][0])
    V1 = get_V_with_v_1(V, v)
    V2 = get_V_with_v_1(V, -v)
    cnf1 = simplifyCNF(cnf, V1)
    cnf2 = simplifyCNF(cnf, V2)

    if cnf1 is not None:
        sol = solve(cnf1, V1)
        if sol != "UNSAT":
            return sol
    if cnf2 is not None:
        sol = solve(cnf2, V2)
        if sol != "UNSAT":
            return sol

    return "UNSAT"


def solution(path):
    cnf = loadCNF(path)
    V = {}

    return solve(cnf, V)


def is_result_correct(path, result):
    if result == "UNSAT" and path.find(".no.") != -1:
        return "The result is correct."
    elif result == "UNSAT" and path.find(".no.") == -1:
        return "The result is incorrect."

    cnf = loadCNF(path)
    for c in cnf[1]:
        if not is_clause_correct(c, result):
            return "The result is incorrect."

    return "The result is correct."


tests = [file for file in os.listdir("sat/") if os.path.splitext(file)[1] != '.sol']
# tests = ['5.no.sat', '5.yes.sat', '10.no.sat', '10.yes.sat', '20.no.sat', '20.yes.sat', '30.no.sat', '30.yes.sat',
#          'anna.11.sat', 'anna.15.sat']

for i in tests:
    time1 = time.time()
    res = solution('sat/' + i)
    time2 = time.time()

    print("The sat solution for sat file " + i + " is " + str(res))
    print(is_result_correct('sat/' + i, res))
    print("It took ", time2 - time1, "s time\n\n")
    # saveCNF('sat/' + i + ".sol", res)
