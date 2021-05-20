import ipdb

graph = {
  'A' : ['B','C'],
  'B' : ['D', 'E'],
  'C' : ['F'],
  'D' : [],
  'E' : ['F'],
  'F' : []
}

def getFirstUnvisited(l,v):
    for node in l :
        if node not in v:
            return node;
    return None;

# def bfs(start):
#     Q = [start];
#     visited = [start];
    
#     # ipdb.set_trace()
#     while(len(Q) > 0):
#         start = getFirstUnvisited(graph[start], visited);
#         if start is not None : 
#             Q.append(start);
#             visited.append(start);
#         else:
#             temp = Q.pop();
#             if temp not in visited :
#                 print(temp);
#                 start = Q.pop();
#             else:
#                 print(temp);
#                 start = temp;
    

def dfs(node, visited):
    if node not in visited:
        print(node);
        visited.add(node);

        for nextNode in graph[node]:
            if nextNode not in visited:
                bfs(nextNode, visited);


dfs('A',set());
    

            
