
d = {"fulala":3,"bunica":19,"ohaba":7}

print(d.items())
print(sorted(d.items()))
print(sorted(d.items() , key=lambda x : x[1]))

print(sorted(d.items(), key = lambda x : x[0]))
