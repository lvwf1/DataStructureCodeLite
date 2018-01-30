#include <iostream>
#include "card.h"
#include "throttle.h"
using namespace std;

int main(int argc, char **argv)
{
    card c(DIAMONDS, 5);
    throttle t1(8,0);
    throttle t2(9,0);
    bool s=t1<t2;//compare number of total positions between throttle1 and throttle2
    cout<<s<<endl;
    cout<<"number of throttle1 positions:"<<t1.get_pos()<<endl;
    cout<<"number of throttle2 positions:"<<t2.get_pos()<<endl;
    return 0;
}