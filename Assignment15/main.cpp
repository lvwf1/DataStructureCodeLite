//8.
//Choose some graph implementation and implement a graph member function to delete
//a vertex from the graph. The function should not only remove the vertex but all 
//edges that have the vertex as the source or target.
//problem 8: You may use either the adjacency matrix implementation provided by the 
//author or the adjacency set implementation from lab 13.

#include <iostream>
#include "graph.h"

using namespace std;
using namespace main_savitch_15;

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
    g.add_edge(2,1);
    g.add_edge(2,0);
    g.add_edge(3,1);
    g.add_edge(4,2);
    g.add_edge(0,5);
    g.add_edge(3,4);
    g.remove_vertex(1);
    g.displaygraph();//Display the graph like the vector
    return 0;
}