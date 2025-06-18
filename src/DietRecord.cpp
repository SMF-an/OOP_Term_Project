#include "DietRecord.h"
#include "Database.h"
#include <fstream>


using std::cout;
using std::endl;
using std::string;
using std::to_string;
using std::domain_error;
using std::cerr;


DietRecord::DietRecord(const Date& d, char c, const string& n, int w, int calorie) : date(d), food_category(c), food_name(n), weight_intake(w) 
{
    calorie_intake = (double)calorie * weight_intake / 100.0;
}


DietRecord::DietRecord(int i) 
{
    string filename = "../database/diet_records.csv";
    Database<string> db_date(filename, "Date", i);
    Database<string> db_category(filename, "Category", i);
    Database<string> db_food_name(filename, "Name", i);
    Database<int> db_weight(filename, "Weight (g)", i);
    Database<int> db_calorie(filename, "Calories (kcal)", i);
    date = db_date.Read();
    food_category = db_category.Read().front();
    food_name = db_food_name.Read();
    weight_intake = db_weight.Read();
    calorie_intake = db_calorie.Read();
}


void DietRecord::Save() const 
{
    Database<DietRecord> db("../database/diet_records.csv");
    string data = date.Format() + ',' + 
                  CategoryToString(food_category) + ',' + food_name + ',' + 
                  to_string(weight_intake) + ',' + to_string(calorie_intake);
    try
    {
        db.AddNewLine(data);
        cout << "Diet record saved." << endl;
    }
    catch(const domain_error& e)
    {
        cerr << e.what() << endl;
    }
}