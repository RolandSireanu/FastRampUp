#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
using namespace std;

 
void DFS(std::size_t arg_node, unordered_set<int>& arg_visited, const vector<vector<int>>& arg_adjList)
{
    cout << arg_node << " ";
    arg_visited.insert(arg_node);
    for(const auto& e : arg_adjList[arg_node])
    {
        if(arg_visited.find(e) == arg_visited.end())
            DFS(e, arg_visited, arg_adjList);
    }
}

int main()
{
    constexpr std::size_t NR_OF_NODES = 5;
    constexpr std::size_t STARTING_NODE = 0;
    vector<vector<int>> adjList (NR_OF_NODES);
    queue<int> q;
    unordered_set<int> visited(NR_OF_NODES);


    adjList[0].push_back(1);
    adjList[1].push_back(2);
    adjList[1].push_back(4);
    adjList[2].push_back(1);
    adjList[2].push_back(3);
    adjList[2].push_back(4);
    adjList[3].push_back(2);
    adjList[3].push_back(4);
    adjList[4].push_back(1);
    adjList[4].push_back(2);
    adjList[4].push_back(3);

    q.push(STARTING_NODE);
    visited.insert(STARTING_NODE);

    cout << "BFS: ";
    while(q.empty() == false)
    {
        cout << q.front() << " ";        

        for(const auto& n : adjList[q.front()])
        {
            // cout << "For parent " << q.front() << " n = " << n << endl;            
            if(visited.find(n) == visited.end())
            {
                q.push(n);                
                visited.insert(n);
            }
        }        

        q.pop();
    }

    visited.clear();    
    visited.insert(STARTING_NODE);
    cout << "\nDFS: ";
    DFS(STARTING_NODE, visited, adjList);

    
    return 0;
}

