#include <iostream>
#include <list>
#include <stack>
using namespace std;

void print(const list<string>& s) 
{
    cout<<"Postfix expression: ";
	for(list<string>::const_iterator i = s.begin(); i != s.end(); ++i)
		cout << *i << " ";
	cout << endl;
}
//Postcondition: Display the postfix expression

list<string> get_postfix_expression()
{
    list<string> l;
    l.push_back("1");
    l.push_back("2");
    l.push_back("3");
    l.push_back("*");
    l.push_back("4");
    l.push_back("5");
    l.push_back("-");
    l.push_back("/");
    l.push_back("+");
    print(l);
    
    return l;
}
//Postcondition: the list with the postfix expression is returned

int evaluate_postfix_expression (list<string> l)
{
    stack<int> s;
    int x,y,answer=0,temp;
    for(list<string>::const_iterator it=l.begin();it!=l.end();it++)//Use the iterator to loop through the whole list and get every elements
    {
        if(*it=="+"||*it=="-"||*it=="*"||*it=="/")//Evaluate the previous two operands with the current operator then push the answer back to the stack
        {
            x=s.top();
            s.pop();
            y=s.top();
            s.pop();
            if(*it=="+")
                s.push(x+y);
            if(*it=="-")
                s.push(y-x);
            if(*it=="*")
                s.push(x*y);
            if(*it=="/")
                s.push(y/x);
        }
        else
        {
            temp=std::stoi(*it);//Convert from string to int
            s.push(temp);//Store the operands into the stack
        }
    }
    answer=s.top();
    s.pop();
    return answer;
}

//Postcondition: The evaluation of postfix expression is performed, the answer will be returned

int main()
{
    int myanswer=evaluate_postfix_expression(get_postfix_expression());
    cout<<"The answer is "<<myanswer<<endl;//Display the answer
    return 0;
}