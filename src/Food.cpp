#include "Food.h"
#include "Database.h"
#include <fstream>


using std::cout;
using std::endl;
using std::string;
using std::to_string;
using std::vector;
using std::domain_error;
using std::cerr;


Food::Food(int i) 
{
    string filename = "../database/food_database.csv";
    Database<string> db_name(filename, "Food Name", i);
    Database<int> db_calorie(filename, "Calories (kacl/100g)", i);
    Database<string> db_category(filename, "Category", i);
    name = db_name.Read();
    calorie = db_calorie.Read();
    category = db_category.Read().front();
}


void Food::Save() const
{
    Database<Food> db("../database/food_database.csv");
    string data = name + "," + to_string(calorie) + "," + CategoryToString(category);
    try
    {
        db.AddNewLine(data);
        cout << "Food record saved." << endl;
    }
    catch(const domain_error& e)
    {
        cerr << e.what() << endl;
    }
}


int SearchFoodCalorie(vector<Food> foods, char category, const string& food_name)
{
    for(const auto& food : foods)
    {
        if(food.Category() == category && food.Name() == food_name)
        {
            return food.Calorie();
        }
    }
    throw domain_error(food_name + " is not in the food database.");
}


string CategoryToString(char category)
{
    switch(category)
    {
        case 'S': return "Staple Food";
        case 'A': return "Animal Proteins";
        case 'V': return "Vegetables";
        case 'F': return "Fruits";
        case 'B': return "Beverages";
        default: throw domain_error("Invalid food category: " + string(1, category));
    }
}