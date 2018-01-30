//7.
//write a program to help you make better social connections.The program should
//read a file of data containing a list of people in your community and a list 
//of who knows who. Allow the user to enter various queries about which people 
//know each other, such as "How many people does Harry know?" or "Is there anyone
//that both Harry and Cathy know?"
//problem 7: I will be providing some code that illustrates how to read data from a text file.
//  I will post on Piazza when that code is available.

#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include "graph.h"

using namespace std;
using namespace main_savitch_15;

void tokenize (const string& s, string& first, string& second)
{
    stringstream ss (s);
    ss >> first;
    ss >> second;
}

size_t get_index (const graph<string>& g, const string& target)
{
    size_t i = 0;
    while (i < g.size() && g[i] != target)
        ++i;
    assert (i < g.size());
    return i;
}


graph<string>* create_graph (const string& file_name)
{
    graph<string>* g = new graph<string>;
    ifstream input(file_name.c_str());
    size_t num;
    input >> num;
    string temp;
    getline (input, temp);
    assert (num <= g -> MAXIMUM);
    string* names = new string[num];
    for (size_t i = 0; i < num; ++i)
    {
        string s;
       getline (input, s);
        names[i] = s;
        g -> add_vertex (s);
    }
    string line;
    while (getline (input, line))
    {
        string first, second;
        tokenize (line, first, second);
        g -> add_edge (get_index (*g, first), get_index (*g, second));
    }
    input.close();
    return g;
}

set<size_t> bothknow(graph<string> *g,size_t i1,size_t i2)
{
    set<size_t> s;
    
    for(size_t i=0;i<g->size();i++)
        if(g->is_edge(i1,i)&&g->is_edge(i2,i))
            s.insert(i);
    return s;
}
//Postcondition: return the vertex that two edges pointing to

size_t howmany(graph<string> *g,size_t index)
{
    return g->neighbors(index).size();
}
//Postcondition: return the size of neighbors set

template<class Item>
void findfri(graph<Item> *g)
{
    cout<<"Enter two persons'names, press enter to separate, we will find their common friends"<<endl;
    string f1,f2;
    cin>>f1;
    cin>>f2;
    size_t i1=get_index(*g,f1);
    size_t i2=get_index(*g,f2);
    set<size_t> myfri=bothknow(g,i1,i2);
    if(myfri.size()>0)
    {
        for (set<size_t>::iterator i = myfri.begin(); i != myfri.end(); ++i)
            g->get_name(*i);
        cout<<"is(are) their common friend(s)."<<endl;
    }
    else
    {
        cout<<"They have no common friend"<<endl;
    }
}

template<class Item>
size_t numoffri(graph<Item> *g)
{
    cout<<"Enter the person's name, we will find how many friends he(she) had"<<endl;
    string f;
    cin>>f;
    size_t i=get_index(*g,f);
    size_t numf=howmany(g,i);
    return numf;
}

int main()
{
    graph<string> *g=create_graph("C:/Users/Weifeng/Desktop/Everything/Data Structure/CodeLite/Assignment14/friend.txt");
    g->displaygraph();
    bool retry=true;
    while(retry)
    {
        cout<<numoffri(g)<<endl;
        cout<<"Enter R to retry, enter any key to continue"<<endl;
        char yn;
        cin>>yn;
        if(yn=='R')
            retry=true;
        else
            retry=false;
    }
    retry=true;
    while(retry)
    {
        findfri(g);
        cout<<"Enter R to retry, enter any key to continue"<<endl;
        char yn;
        cin>>yn;
        if(yn=='R')
            retry=true;
        else
            retry=false;
    }
    return 0;
}