//Write a recursive function to convert a character string
//of digits to an integer. Example: convert ("1234") returns
//1234. Hint: To convert a character to a number, subtract
//the ASCII value '0' from the character. For example, if the
//string s has but one character, then the function can return
//the value s[0] - '0'

#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

int convert(const string& s)
/*
* Precondition:string type object has been passed to function 
* containing only numbers.
* Postcondition: A numeric version of the string has been returned, and 
* the original string parameters have been unchanged.
*/
{
	int n = s.length() - 1;
	
	// the string is empty, the value should be zero
	if(s.empty()) 
		return 0;
	if(s[0] == '-')
		return -convert(s.substr(1, n--) ) ;	
		//recursive call - changes each subsequent numeric value to a negative number
		
	if ( s.length()  == 1)
	{
		if(isdigit(s[0]))
			return s[0]- '0'; // translate the character to its numeric value
		else 
			cout<<"Invalid numeric character: "<<s<<endl;
			return 0;
	}
	 return convert(s.substr(s.length() - 1,1)) + convert(s.substr(0, n--) ) * 10 ;	 //recursive call
}
int main()
{
	// Make some strings 
	string test1("1234");
	string test2("921");
	string test3("0");
	string test4("");
	string test5("0034");
	string test6("-4");
	string test7("-400001");
	string test8("123ABC");
	string test9("12 34 56");
	// test calls to convert
	cout<<"Value of \""<<test1<<"\" is " <<convert(test1)<<endl;
	cout<<"Value of \""<<test2<<"\" is " <<convert(test2)<<endl;
	cout<<"Value of \""<<test3<<"\" is " <<convert(test3)<<endl;
	cout<<"Value of \""<<test4<<"\" is " <<convert(test4)<<endl;
	cout<<"Value of \""<<test5<<"\" is " <<convert(test5)<<endl;
	cout<<"Value of \""<<test6<<"\" is " <<convert(test6)<<endl;
	cout<<"Value of \""<<test7<<"\" is " <<convert(test7)<<endl;
	cout<<"Value of \""<<test8<<"\" is " <<convert(test8)<<endl;
	cout<<"Value of \""<<test9<<"\" is " <<convert(test9)<<endl;
	return EXIT_SUCCESS;
}