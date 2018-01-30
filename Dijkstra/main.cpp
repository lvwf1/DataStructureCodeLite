#include <iostream>
#include "graph.h"
#include <string>
#include <climits>
#include <set>

using namespace main_savitch_15;
using namespace std;

template <typename T>
void shortest_path (const graph<T>& g, size_t start, size_t*& distance, size_t*& predecessor);

graph<string>* create_graph();
// postcondition: pointer to graph containing strings has been returned

template <typename T>
void display_shortest_paths (const graph<T>& g, const size_t* distance, const size_t* predecessor, size_t start);

int main(int argc, char **argv)
{
	graph<string>* g = create_graph ();
     size_t* distance = NULL;
    size_t* predecessor = NULL;
    size_t start = 0;
    shortest_path(*g, start, distance, predecessor);
    display_shortest_paths (*g, distance, predecessor, start);
    delete g;
	return 0;
}

graph<string>* create_graph()
{
    graph<string>* g = new graph<string>;
    g -> add_vertex ("A");
    g -> add_vertex ("B");
    g -> add_vertex ("C");
    g -> add_vertex ("D");
    g -> add_vertex ("E");
    g -> add_vertex ("F");
    g -> add_edge (0, 5, 9);
    g -> add_edge (0, 1, 2);
    g -> add_edge (1, 5, 6);
    g -> add_edge (1, 2, 8);
    g -> add_edge (1, 3, 15);
    g -> add_edge (2, 3, 1);
    g -> add_edge (4, 3, 3); 
    g -> add_edge (4, 2, 7);
    g -> add_edge (5, 4, 3);
    return g;
}

size_t find_next_vertex (size_t start, size_t* distance, const set<size_t>& allowed_vertices, size_t size)
{
    size_t location = start;
    size_t value = UINT_MAX;
    for (size_t i = 0; i < size; ++i)
        if ((distance[i] < value) && (allowed_vertices.find(i) == allowed_vertices.end()))
        {
            location = i;
            value = distance[i];
        }
    return location;
}

template <typename T>
void update (const graph<T>& g, size_t v, size_t* distance, size_t* predecessor)
{
    for (size_t i = 0; i < g.size(); ++i)
        if (g.is_edge (v, i))
            if (distance[v] + g.weight (v,i) < distance[i])
            {
                distance[i] = distance[v] + g.weight(v,i);
                predecessor[i] = v;
            }            
}

template <typename T>
void shortest_path (const graph<T>& g, size_t start, size_t*& distance, size_t*& predecessor)
{
    distance = new size_t[g.size()];
    predecessor = new size_t[g.size()];
    for (size_t i = 0; i < g.size(); ++i)
        distance[i] = UINT_MAX;
    distance[start] = 0;
    for (size_t i = 0; i < g.size(); ++i)
        predecessor[i] = UINT_MAX;
    set<size_t> allowed_vertices;
    for (size_t i = 0; i < g.size(); ++i)
    {
        size_t v = find_next_vertex (start, distance, allowed_vertices, g.size());
        allowed_vertices.insert (v);
        update (g, v, distance, predecessor);
    }
}

template <typename T>
void display_shortest_paths (const graph<T>& g, const size_t* distance, const size_t* predecessor, size_t start)
{
    for (size_t i = 0; i < g.size(); ++i)
    {
        size_t current = i;
        cout << distance[i] << ": ";
        cout << current << " ";
        while (current != start)
        {
            current = predecessor[current];
            cout << current << " ";
        }
        cout << endl;
     }
}
