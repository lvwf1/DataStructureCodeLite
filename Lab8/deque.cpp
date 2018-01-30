#include <iostream>
#include "deque.h"

using namespace std;

int main()
{
    deque<char> d1,d2;
    d1.push_back('a');
    cout<<d1<<endl;
    d1.push_front('b');
    cout<<d1<<endl;
    d1.push_back('c');
    cout<<d1<<endl;
    d1.push_front('d');
    cout<<d1<<endl;
    d1.pop_front();
    cout<<d1<<endl;
    d2.push_front('b');
    cout<<d2<<endl;
    d2.push_back('a');
    cout<<d2<<endl;
    d2.push_back('c');
    cout<<d2<<endl;
    if(d1==d2)
        cout<<"They are exactly the same"<<endl;
    else
        cout<<"They are different"<<endl;
    d2.push_front('h');
    cout<<d2<<endl;
    if(d1==d2)
        cout<<"They are exactly the same"<<endl;
    else
        cout<<"They are different"<<endl;
    d2.pop_back();
    cout<<d2<<endl;
    if(d1==d2)
        cout<<"They are exactly the same"<<endl;
    else
        cout<<"They are different"<<endl;
    return 0;
}