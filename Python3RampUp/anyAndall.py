
l = [2,4,6,8]
#Any takes in an itterable and returns True if at least one element evaluates to True

if any([(e % 2) == 0 for e in l]) :
	print("At least one even number !");

if all([(e%2==0) for e in l]):
	print("All the numbers are even ! ");
else:
	print("At least one number is not even !")

