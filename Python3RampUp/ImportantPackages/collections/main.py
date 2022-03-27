# Collections module has specialized containers that can be used to replace general purpose
# containers like (list, tuple, dict and set)

from collections import ChainMap, Counter, defaultdict, deque, namedtuple
from email.policy import default
from weakref import finalize
import ipdb
def chain_map():
    defaults = {'username':'bobonete', 'password':'1234', 'email':'bobonete@gmail.com'}
    inputs = {'email':'bobita@gmail.com'}
    cmap = ChainMap(inputs, defaults)

    # inputs is overwritten by defaults
    print(cmap['email'])

def counter():
    in1 = [(1,2), (3,4), (5,6), (1,2), (3,4)]
    in2 = [(1,2),(1,2)]
    counter1 = Counter(in1)
    counter1.subtract(Counter(in2))
    print(counter1)

def default_dict():
    # defaultdict accepts a default factory as its primary argument 
    # default factory can be a type like int,list or a lambda 
    # Default to result of lambda 
    df_lambda = defaultdict(lambda : 5)
    
    # Default to 0 
    df_type = defaultdict(int)
    
    print(df_lambda['a'])
    print(df_type['a'])


    listOfIncomes = [("Roland", 150), ("Alex", 100), ("Roland", -25), ("Alex", -10)];
    finalList = defaultdict(list)
    for name, value in listOfIncomes:
        finalList[name].append(value)
    print(sum(finalList["Roland"]))
    print(sum(finalList["Alex"]))

import ipdb
def named_tuple():
    inputData = {"regularFiles":1249, "directories":90, "links": 15}
    FSInfo = namedtuple("FSInfo", inputData.keys())
    obj = FSInfo(**inputData)
    print(obj.regularFiles)
    

def double_end_queue():
    dq = deque(maxlen=3);
    dq.append(1)
    dq.append(2)
    dq.append(3)

    #[2,3,4]
    dq.append(4)

    #[7,2,3]
    dq.appendleft(7)

    print("Pop item : " + str(dq.pop()))
    # [7, 2]

    # [2, 7, 12]
    dq.append(12)
    
    # [12, 7, 2]
    dq.rotate(1);
    print(dq)


if __name__ == "__main__":
    chain_map();
    counter();
    default_dict();
    double_end_queue();
    named_tuple();