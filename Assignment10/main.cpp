#include<iostream>
#include "set.h"

using namespace std;
using namespace main_savitch_11;

int main()
{
    set<int> *s=new set<int>();
    cout<<"Enter i for insertion, Enter d for deletion, Enter s for search, Enter q if you are done"<<endl;
    char input;
    int n;
    while(input!='q')
    {
        cin>>input;
            if(input=='i')
            {
                while(n>=0)
                {
                    cout<<"Input the number then hit enter, input an negative number to exit insertion: ";
                    cin>>n;
                    if(n>0)
                    {
                        s->insert(n);
                        s->print(0);
                    }
                    else
                        break;
                }
            }
            else if(input=='d')
            {
                while(n>=0)
                {
                    cout<<"Input the number then hit enter, input an negative number to exit deletion:";
                    cin>>n;
                    if(n>=0)
                    {
                        s->erase(n);
                        s->print(0);
                    }
                    else
                        break;
                }
            }
            else if(input=='s')
            {
                while(n>=0)
                {
                    cout<<"Input the number then hit enter, input an negative number to exit search:"<<endl;
                    s->print(0);
                    cin>>n;
                    if(n>=0)
                    {
                        cout<<"There is "<<s->count(n)<< " here"<<endl;
                    }
                    else
                        break;
                }
            }
            cout<<"Enter i for insertion, Enter d for deletion, Enter s for search, Enter q if you are done"<<endl;
            n=0;
    }
    set<int> *c=s;
    cout<<"Test Copy Constructor"<<endl;
    c->print(0);
    set<int> *a;
    cout<<"Test Assignment Operator"<<endl;
    a=c;
    a->print(0);
    return 0;
}