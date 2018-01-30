#include<iostream>
#include "polynomial.h"

using namespace std;

int main()
{
    polynomial p1,p2,p;
    p1.add_to_coef(1,1);
    p1.assign_coef(2,2);
    p2.assign_coef(3,3);
    p2.add_to_coef(4,1);
    cout<<p1+p2<<endl;
}
