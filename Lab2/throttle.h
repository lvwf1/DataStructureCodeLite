#ifndef throttle_h
#define throttle_h

class throttle
{
public:
    //precondition:throttle pos must be greater than ini_pos, int_pos must be greater than 0
    //postcondition:throttle with properties has been created
    throttle(int pos,int ini_pos);
    //postcondition:number of positions has been created
    int get_pos() const;
    //postcondition:initial position has been created
    int get_ini_pos() const;
private:
    int totalpos;
    int initialpos;
};
bool operator <(const throttle& th1,const throttle& th2);
#endif // throttle_h
