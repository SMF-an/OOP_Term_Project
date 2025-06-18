#include "Menu.h"
#include "RIO.h"
#include <iostream>
#include <iomanip>


using std::cin;
using std::cout;
using std::endl;
using std::cerr;
using std::vector;
using std::string;
using std::domain_error;
using std::setw;
using std::istream;


Menu::Menu()
{
    LoadFoods();
    LoadDietRecords();
    date.SetToday();
}


void Menu::LoadFoods()
{
    int i = 1;
    try
    {
        while(1) 
        {
            foods.push_back(Food(i));
            i++;
        }
    }
    catch(const domain_error& e)
    {
        //cout << e.what() << endl;
    }
}


void Menu::LoadDietRecords()
{
    int i = 1;
    try
    {
        while(1) 
        {
            diet_records.push_back(DietRecord(i));
            i++;
        }
    }
    catch(const domain_error& e)
    {
        //cout << e.what() << endl;
    }
}


void Menu::Greeting()
{
    string greeting = "Welcome to Calorie Track Daily";
    string::size_type len = greeting.size();
    string border(len + 4, '*');
    string str = "* " + greeting + " *";
    string padding = "* " + string(len, ' ') + " *";

    cout << border << endl;
    cout << padding << endl;
    cout << str << endl;
    cout << padding << endl;
    cout << border << endl;
}


void Menu::ConfigureUser()
{
    // if user already exists, load it
    if(user.Load())
    {
        cout << "Hi " << user.Name() << "! Current time : ";
        ShowCurrentTime(cout);
        cout << endl;
    }
    // if user does not exist, initialize it
    else
    {
        user.Init();
    }
}


void Menu::MainMenu()
{
    while(1)
    {
        cout << endl << "1. Configure Profile 2. Log Meals 3. Nutritional Insights 4. View Meal History 5. Exit" << endl;
        int command;
        cout << "Enter command (1-5): ";
        cin >> command;

        switch(command)
        {
            case 1:
                UserMenu();
                break;
            case 2:
                DietMenu();
                break;
            case 3:
                ReportMenu();
                break;
            case 4:
                RecordMenu();
                break;
            case 5:
                ExitMenu();
                return;
            default:
                Clear(cin);       
                cout << "Invalid choice." << endl;
        }
    }
}


void Menu::UserMenu()
{
    while(1)
    {
        cout << endl << "1. Name 2. Age 3. Gender 4. Height 5. Weight 6. Exit" << endl;
        int command;
        cout << "Enter command (1-6): ";
        cin >> command;

        switch(command)
        {
            case 1:
            {
                string name;
                cout << "Name: ";
                cin >> name;
                user.name = name;
                break;
            }
            case 2:
            {
                int age;
                cout << "Age: ";
                cin >> age;
                user.age = age;
                break;
            }
            case 3:
            {
                user.gender = GetGender(cin);
                break;
            }
            case 4:
            {
                int height;
                cout << "Height: ";
                cin >> height;
                user.height = height;
                break;
            }
            case 5:
            {
                int weight;
                cout << "Weight: ";
                cin >> weight;
                user.weight = weight;
                break;
            }
            case 6:
                user.Configure();
                return; 
            default:
                Clear(cin);
                cout << "Invalid choice." << endl;
        }
    }
}


void Menu::DietMenu()
{
    char category = GetCategory(cin);

    string food_name;
    cout << "Food Name: ";
    Clear(cin);   
    getline(cin, food_name);    // Use getline to allow spaces in food names 

    int calorie;
    // if the food is already in the database, search for its calorie value
    try
    {
        calorie = SearchFoodCalorie(foods, category, food_name);      
    }
    // if the food is not in the database, prompt user to register it
    catch(const domain_error& e)
    {
        cerr << e.what() << endl;
        cout << "Enter calories per 100g (kcal/100g): ";
        cin >> calorie;
        Food food(food_name, category, calorie);
        foods.push_back(food);
        food.Save(); 
    }

    int food_weight;
    cout << "Food Weight (g): ";
    cin >> food_weight;
    DietRecord record(date, category, food_name, food_weight, calorie);
    diet_records.push_back(record);
    record.Save();
}


void Menu::ReportMenu()
{
    DietReport report(user, diet_records);
    report.GenerateReport();
}


void PrintDietRecords(const vector<DietRecord>& records)
{
    for(const auto& record : records)
    {
        cout << setw(10) << record.DATE().Format()
             << setw(20) << CategoryToString(record.FoodCategory())
             << setw(25) << record.FoodName() 
             << setw(12) << record.WeightIntake()
             << setw(15) << record.CalorieIntake() << endl; 
    }
}


void Menu::RecordMenu()
{
    // input date
    Date input_date;
    string date_str;
    while(1)
    {   
        cout << "Enter date (yyyy/mm/dd): ";
        try
        {
            cin >> date_str;
            input_date = Date(date_str);
            break;
        }
        catch(const domain_error& e)
        {
            Clear(cin);
            cerr << e.what() << endl;
        }
    }
    
    // find records for the input date
    vector<DietRecord> valid_records;
    for(const auto& record : diet_records)
    {
        if(record.DATE() == input_date)
        {
            valid_records.push_back(record);
        }
    }

    if(valid_records.empty())
    {
        Clear(cin);
        cout << "No dietary records found for " << input_date.Format() << ", in the database" << endl;
        return;
    }

    // categorize records
    vector<DietRecord> staple_food_records;
    vector<DietRecord> animal_proteins_records;
    vector<DietRecord> vegetables_records;
    vector<DietRecord> fruits_records;
    vector<DietRecord> Beverages_records;

    for(const auto& record : valid_records)
    {
        switch(record.FoodCategory())
        {
            case 'S':
                staple_food_records.push_back(record);
                break;
            case 'A':
                animal_proteins_records.push_back(record);
                break;
            case 'V':
                vegetables_records.push_back(record);
                break;
            case 'F':
                fruits_records.push_back(record);
                break;
            case 'B':
                Beverages_records.push_back(record);
                break;
            default:
                cerr << "Unknown food category: " << record.FoodCategory() << endl;
        }
    }

    cout << setw(10) << "Date" 
         << setw(20) << "Category"
         << setw(25) << "Name" 
         << setw(12) << "Weight (g)" 
         << setw(15) << "Calories (kcal)" << endl;
    PrintDietRecords(staple_food_records);
    PrintDietRecords(animal_proteins_records);
    PrintDietRecords(vegetables_records);
    PrintDietRecords(fruits_records);
    PrintDietRecords(Beverages_records);
}


void Menu::ExitMenu()
{
    cout << "========================================" << endl;
    cout << endl;
    cout << "Start Tracking -> Start Shining, Goodbye, Uncertainty ^_^" << endl;
    cout << endl;
    cout << "========================================" << endl;
}