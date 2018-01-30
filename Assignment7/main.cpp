#include <iostream>
#include "deque.h"

using namespace std;

int main()
{
    //Test single push&pop
    deque<char> d;
    d.push_front('f');
    cout<<"Push f to the front of d: "<<d<<endl;
    d.pop_back();
    cout<<"Pop f from the back of d: "<<d<<endl;
    d.push_back('b');
    cout<<"Push b to the back of d: "<<d<<endl;
    d.pop_front();
    cout<<"Pop b from the front of d: "<<d<<endl;
    deque<int> d1,d2;
    //Test multiple push_front
    for(int i=0;i<3;i++)
    {
        d1.push_front(i);
        cout<<"Push "<<i<<" to the front of d1: "<<d1<<endl;
    }
    //Test multiple push_back
    for(int i=5;i>2;i--)
    {
        d1.push_back(i);
        cout<<"Push "<<i<<" to the back of d1: "<<d1<<endl;
    }
    //Test multiple push_front & push_back
    d2.push_back(3);
    cout<<"Push 3 to the back of d2: "<<d2<<endl;
    d2.push_front(4);
    cout<<"Push 4 to the front of d2: "<<d2<<endl;
    d2.push_front(5);
    cout<<"Push 5 to the front of d2: "<<d2<<endl;
    d2.push_back(6);
    cout<<"Push 6 to the back of d2: "<<d2<<endl;
    //Test Copy constructor and assignment operator
    deque<int> d3=d2,d4;
    cout<<"Copy d2 to d3: "<<d3<<endl;
    d4=d1;
    cout<<"Assign d1 to d4: "<<d4<<endl;
    //Test pop_front
    d4.pop_front();
    cout<<"Pop 2 from the front of d4: "<<d4<<endl;
    d4.pop_front();
    cout<<"Pop 1 from the front of d4: "<<d4<<endl;
    //Test compare different deques
    if(d3==d4)
        cout<<"d3 and d4 are the same"<<endl;
    else
        cout<<"d3 and d4 are different"<<endl;
    //Test pop_back
    d3.pop_back();
    cout<<"Pop 6 from the back of d3: "<<d3<<endl;
    d3.push_front(0);
    cout<<"Push 0 to the front of d3: "<<d3<<endl;
    //Test compare identical deques
    if(d3==d4)
        cout<<"d3 and d4 are the same"<<endl;
    else
        cout<<"d3 and d4 are different"<<endl;
    return 0;
}