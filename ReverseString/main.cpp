#include<iostream>
#include<stack>
#include<array>

using namespace std;

int main()
{
    char g[]="goodluck";
    stack<char> s;
    cout<<sizeof(g)<<endl;
    for(size_t i=0;i<sizeof(g);i++)
    {
        s.push(g[i]);
    }
    while(!s.empty())
    {
        cout<<s.top();
        s.pop();
    }
    return 0;
}
