#include "RIO.h"


using std::istream;
using std::cout;
using std::cerr;
using std::cin;
using std::endl;


istream& Clear(istream& is)
{
    is.clear();
    is.ignore(10000, '\n');
    return is;
}


char GetGender(istream& is)
{
    char gender;
    do
    {   
        cout << "Gender(F/M): ";
        is >> gender;
        if(gender != 'F' && gender != 'M')
        {
            Clear(is);
            cerr << "Invalid input." << endl;
        }
    } while (gender != 'F' && gender != 'M');
    return gender;
}


char GetCategory(istream& is)
{
    char category;
    do
    {   
        cout << "Select a category (S/A/V/F/B: Staple Food/Animal Proteins/Vegetables/Fruits/Beverages): ";
        is >> category;
        if(category != 'S' && category != 'A' && category != 'V' && category != 'F' && category != 'B')
        {
            Clear(is);
            cerr << "Invalid input." << endl;
        }
    } while (category != 'S' && category != 'A' && category != 'V' && category != 'F' && category != 'B');
    return category;
}