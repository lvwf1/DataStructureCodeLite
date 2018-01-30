#include<iostream>
using namespace std;

int main(){
    int num1=15;
    int num2=45;
    
    int *p1=&num1;
    int *p2=&num2;
    
    cout<<"Pointer 1: "<<*p1<<endl;
    cout<<"Pointer 2: "<<*p2<<endl;
    
    p1=p2;
    
    cout<<"Pointer 1: "<<*p1<<endl;
    cout<<"Pointer 2: "<<*p2<<endl;
    
    cout<<"num1: "<<num1<<endl;
    cout<<"num2: "<<num2<<endl;
    
    return 0;
}