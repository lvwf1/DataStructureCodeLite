#include<iostream>
#include "newpoint.h"
using namespace std;
using namespace main_savitch_2B;

int main()
{
    cout<<"hello world"<<endl;
    point np(1,2);
    cout<<np.get_x()<<" "<<np.get_y()<<endl;
    np.shift(3,4);
    np.rotate90();
    cout<<np.get_x()<<" "<<np.get_y()<<endl;
    return 0;
}