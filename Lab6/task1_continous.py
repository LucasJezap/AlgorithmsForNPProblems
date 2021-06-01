from pulp import *

model = LpProblem("Task 1 (Continuous)", LpMinimize)

x = LpVariable("x", cat="Continuous")
y = LpVariable("y", cat="Continuous")

model += x + y

model += y >= x - 1
model += y >= -4 * x + 4
model += y <= -0.5 * x + 3

print(model)

model.solve()
print(LpStatus[model.status])

for var in model.variables():
    print(var.name, "=", var.varValue)

print(value(model.objective))
