#include "User.h"
#include "Database.h"
#include "RIO.h"
#include <iostream>
#include <map>


using std::cin;
using std::cout;
using std::endl;
using std::cerr;
using std::string;
using std::to_string;
using std::domain_error;


void User::ComputeBMI()
{
    bmi = (double)weight / height / height * 10000;
}


void User::ComputeBasicMetabolism()
{
    /* Mifflin-St Jeor Formula */
    if(gender == 'M')
        basic_metabolism = weight * 10 + height * 6.25 - age * 5 + 5;
    else
        basic_metabolism = weight * 10 + height * 6.25 - age * 5 - 161;
}


void User::ComputeCalorieIntakeValue()
{
    calorie_intake_value = basic_metabolism * activity;
}


void User::ClassifyPhysicalStatus()
{
    for(int i = 0; i < 4; ++i)
    {
        if(bmi < bmi_range[i])
        {
            physical_status = bmi_classification[i];
            return;
        }
    }
}


bool User::Load()
{
    try
    {
        Database<string> db_name("../database/user.csv", "Name");
        Database<int> db_age("../database/user.csv", "Age");
        Database<char> db_gender("../database/user.csv", "Gender");
        Database<int> db_height("../database/user.csv", "Height");
        Database<int> db_weight("../database/user.csv", "Weight");
        name = db_name.Read();
        age = db_age.Read();
        gender = db_gender.Read();
        height = db_height.Read();
        weight = db_weight.Read();

        ComputeBMI();
        ClassifyPhysicalStatus();
        ComputeBasicMetabolism();   
        ComputeCalorieIntakeValue();
    }
    catch(const domain_error& e)
    {
        //cerr << e.what() << endl;
        return false;
    }
    return true;
}


void User::Init()
{
    cout << "Enter your personal data:" << endl;
    cout << "Name: ";
    cin >> name;
    cout << "Age: ";
    cin >> age;

    gender = GetGender(cin);
 
    cout << "Height(cm): ";
    cin >> height;
    cout << "Weight(kg): ";
    cin >> weight;

    ComputeBMI();
    ClassifyPhysicalStatus();
    ComputeBasicMetabolism();   
    ComputeCalorieIntakeValue();

    Database<User> db("../database/user.csv");
    string data = name + "," + to_string(age) + "," + gender + "," + to_string(height) + "," + to_string(weight);
    try
    {
        db.AddNewLine(data);
        cout << "User record saved." << endl;
    }
    catch(const domain_error& e)
    {
        cerr << e.what() << endl;
    }
}


void User::Configure()
{
    ComputeBMI();
    ClassifyPhysicalStatus();
    ComputeBasicMetabolism();   
    ComputeCalorieIntakeValue();

    Database<User> db("../database/user.csv");
    string data = name + "," + to_string(age) + "," + gender + "," 
                  + to_string(height) + "," + to_string(weight);
    try
    {
        db.WriteNewLine(data);
        cout << "User database saved." << endl;
    }
    catch(const domain_error& e)
    {
        cerr << e.what() << endl;
    }
}