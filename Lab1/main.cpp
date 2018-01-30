#include <iostream>    // Provides cout
#include <iomanip>     // Provides setw function for setting output width
#include <cstdlib>     // Provides EXIT_SUCCESS
#include <cassert>     // Provides assert function
#include <ctime>       // Provides time analysis tool
using namespace std;   // Allows all standard library items to be used

double feettometer(double feet)
{
    double min_feet=0;
    assert(feet>=min_feet);
    return 0.3048*feet;  
}

double miletokm(double mile)
{
    double min_mile=0;
    assert(mile>=min_mile);
    return mile*1.60934;
}

void setup_cout_fractions(int fraction_digits)
// Precondition: fraction_digits is not negative.
// Postcondition: All double or float numbers printed to cout will now be
// rounded to the specified digits on the right of the decimal.
{
    assert(fraction_digits > 0);
    cout.precision(fraction_digits);
    cout.setf(ios::fixed, ios::floatfield);
    if (fraction_digits == 0)
        cout.unsetf(ios::showpoint);
    else
        cout.setf(ios::showpoint); 
}

int main( )
{
    cout<<"Question1:"<<endl;
    cout<<"Hey! What's up!"<<endl;
    cout<<"Question2:"<<endl;
    const char   HEADING1[]  = "     Feets"; // Heading for table's 1st column
    const char   HEADING2[]  = "     Meters"; // Heading for table's 2nd column
    const char   HEADING3[]  = "      Miles"; //Heading for table's 3rd column
    const char   HEADING4[]  = "Value of n"; //Heading for table's 4th column
    const char   HEADING5[]  = "       Sum";//Heading for table's 5th column
    const char   HEADING6[]  = "            Time Elapsed";//Heading for table's 6th column
    const char   LABEL1      = '     f'; // Label for numbers in 1st column
    const char   LABEL2      = '     m'; // Label for numbers in 2nd column
    const char   LABEL3[]    = "mi";// Label for numbers in 3rd column
    const char   LABEL4[]    = "km";// Label for numbers in 4th column
    const char   LABEL5[]    = "ms";// Label for numbers in 5th column
    const double TABLE_BEGIN =        0; // The table's first Celsius temp.
    const double TABLE_END   =         100; // The table's final Celsius temp.
    const double TABLE_STEP  =         10.0; // Increment between temperatures
    const int    WIDTH       =            9; // Number chars in output numbers
    const int    WIDTH2      =           18; // Number chars in output numbers
    const int    DIGITS      =            1; // Number digits right of decimal pt

    double value1;  // A value from the table's first column
    double value2;  // A value from the table's second column
    
    // Set up the output for fractions and print the table headings.
    setup_cout_fractions(DIGITS);
    cout << "CONVERSIONS from " << TABLE_BEGIN << " to " << TABLE_END << endl;
    cout << HEADING1 << "  " << HEADING2 << endl;
    
    // Each iteration of the loop prints one line of the table.
    for (value1 = TABLE_BEGIN; value1 <= TABLE_END; value1 += TABLE_STEP) 
    {   
        value2 = feettometer(value1);
        cout << setw(WIDTH) << value1 << LABEL1 << "  "; 
        cout << setw(WIDTH) << value2 << LABEL2 << endl; 
    }
    
    cout<<"Question3:"<<endl;
    cout <<HEADING4<<" "<<HEADING5<<" "<<HEADING6<< endl;
    
    long long sum=0;
    int n=10000000;
    for(int j=0;j<10;j++){
    unsigned t0=clock();
    for(int i=0;i<n*j;i++){
        sum+=i;
    }
    unsigned elapsed=clock()-t0;
    cout<<setw(WIDTH)<<n*j<<setw(WIDTH2)<<sum<<setw(WIDTH2)<<elapsed<<LABEL5<<endl;
    }
    
    cout<<"Question4:"<<endl;
    
    cout << "CONVERSIONS from " << TABLE_BEGIN << " to " << TABLE_END << endl;
    cout << HEADING3 << "  " << HEADING2 << endl;
    
    // Each iteration of the loop prints one line of the table.
    for (value1 = TABLE_BEGIN; value1 <= TABLE_END; value1 += TABLE_STEP) 
    {   
        value2 = miletokm(value1);
        cout << setw(WIDTH) << value1 << LABEL3 << "  "; 
        cout << setw(WIDTH) << value2 << LABEL4 << endl; 
    }
    
    return EXIT_SUCCESS;
}