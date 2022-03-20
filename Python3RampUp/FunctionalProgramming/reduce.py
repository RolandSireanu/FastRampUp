import functools as ft
from collections import namedtuple

Salary = namedtuple("Salary",["name", "value"]);

listOfSalaries = [Salary(name="Roland", value=3), Salary(name="Alexandru", value=7), Salary(name="Popescu", value=2)];


a = ft.reduce(lambda x, y: x if x.value>y.value else y ,listOfSalaries)
print(a)