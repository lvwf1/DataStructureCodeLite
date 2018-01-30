#include "throttle.h"
#include <cassert>

//p.51 11. void throttle(int size) is wrong, this is the correct way to create throttle constructor
//p.51 12. create a new throttle constructor with two parameters: total number of positions for the throttle and its initial position
throttle::throttle(int pos,int ini_pos){
    assert (ini_pos<=pos&&ini_pos>=0);
    totalpos=pos;
    initialpos=ini_pos;
}
//p.74 22.the other two constructors unnecessarily exist once default arguments are added to my throttle constructor. However, they should be added if you want to directly access its number of throttle positions or its initial position from main function or other function.
int throttle::get_pos() const{
    return totalpos;
}
int throttle::get_ini_pos() const{
    return initialpos;
}
    // NONMEMBER FUNCTIONS for the throttle class 
//p.85 27.The function should return true if the flow of the first throttle is less than the flow of the second
bool operator <(const throttle& th1,const throttle& th2){
    return th1.get_pos()<th2.get_pos();
}
