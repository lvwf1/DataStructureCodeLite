//4.
//Implement a function with three arguments: a graph, starting vertex number, 
//and an ending vertex number. The function determines whether there is a 
//directed path from the starting vertex to the ending vertex.
//problem 4: If there is a path, the function should also return a path.

#include<iostream>
#include "graph.h"
#include <queue>

using namespace std;
using namespace main_savitch_15;

template<class Item>
bool findpath(graph<Item> g,size_t start,size_t end)
{
    // Base case
    if (start == end)
        return true;
 
    // Mark all the vertices as not visited
    bool *visited = new bool[g.size()];
    for (size_t i = 0; i < g.size(); i++)
        visited[i] = false;
 
    // Create a queue for BFS
    queue<size_t> q;
 
    // Mark the current node as visited and enqueue it
    visited[start] = true;
    q.push(start);
 
    while (!q.empty())
    {
        // Dequeue a vertex from queue and print it
        start = q.front();
        q.pop();
 
        // Get all adjacent vertices of the dequeued vertex s
        // If a adjacent has not been visited, then mark it visited
        // and enqueue it
        
        set<size_t> s=g.neighbors(start);
        
        for (set<size_t>::iterator i = s.begin(); i != s.end(); ++i)
        {
            // If this adjacent node is the destination node, then return true
            if (*i == end)
                return true;
            // Else, continue to do BFS
            if (!visited[*i])
            {
                visited[*i] = true;
                q.push(*i);
            }
        }
    }
 
    return false;
}

int main()
{
    graph<char> g;
    g.add_vertex('a');
    g.add_vertex('b');
    g.add_vertex('c');
    g.add_vertex('d');
    g.add_vertex('e');
    g.add_vertex('f');
    g.add_edge(1,2);
    g.add_edge(2,5);
    g.add_edge(2,3);
    g.add_edge(2,4);
    g.add_edge(3,5);
    g.add_edge(5,0);
    g.displaygraph();//Display the graph like the vector
    size_t s=1,e=0;
    if(findpath(g,s,e))
    {
        cout<<"The following path(s) is(are) from "<<s<<" to "<<e<<endl;
        g.printAllPaths(s,e);
    }
    else
        cout<<"No path exists"<<endl;
    return 0;
}