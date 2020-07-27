

class Cars :

    def __init__(self,l):
        self.listOfCars = l;
        self.length = len(l);
        self.currentIndex = -1;
   
    def f(self):
        for c in self.listOfCars:
            print(c)

    def __next__(self):
        
        self.currentIndex = self.currentIndex + 1;
        if(self.currentIndex >= self.length):
            raise StopIteration
        else:
            return self.listOfCars[self.currentIndex];

    def __iter__(self):
        return self;



c = Cars(["Dacia","Ford","Audi","Seat"])


for i in c:
    print(i)
