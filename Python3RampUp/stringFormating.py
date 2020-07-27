
var = 10;

print(f"Roland are {var} mere ")

from string import Template

t = Template("Hey my name is $name and I am $age years old ! ");
print(t.substitute(name="Roland" , age=28))

