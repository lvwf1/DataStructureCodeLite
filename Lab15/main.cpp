#include <iostream>
#include "graph.h"

using namespace std;
using namespace main_savitch_15;

template<class Item>
void displaygraph(graph<Item> g)
{
    cout<<"  ";
    for(size_t h=0;h<g.size();h++)//Display the vertices horizontally
    {
        cout<<g[h]<<" ";
    }
    cout<<endl;
    for(size_t i=0;i<g.size();i++)
    {
        cout<<g[i]<<" ";//Display the vertices vertically
        for(size_t j=0;j<g.size();j++)
        {
            cout<<g.is_edge(i,j)<<" ";//Display if the edges are existed
        }
        cout<<endl;
    }
}

int main()
{
    graph<char> g;
    g.add_vertex('a');
    g.add_vertex('b');
    g.add_vertex('c');
    g.add_edge(1,2);
    g.add_edge(2,1);
    g.add_edge(2,0);
    g.remove_edge(2,1);
    displaygraph(g);//Display the graph like the vector
    return 0;
}