#include "DietReport.h"
#include <fstream>
#include <iomanip>


using std::cout;
using std::endl;
using std::vector;
using std::ofstream;
using std::streamsize;
using std::setprecision;


DietReport::DietReport(User u, std::vector<DietRecord> records)
{
    user = u;
    diet_records = records;
    today.SetToday();

    ComputeIntake();
}


void DietReport::ComputeIntake()
{
    calorie_intake = 0;
    staple_food_intake = 0;
    animal_proteins_intake = 0;
    vegetable_intake = 0;
    fruit_intake = 0;
    milk_intake = 0;

    for (const auto& record : diet_records) 
    {
        // Skip records not from today
        if( record.DATE() != today) 
        {
            continue; 
        }

        calorie_intake += record.CalorieIntake();

        if( record.FoodCategory() == 'S' ) 
        {
            staple_food_intake += record.WeightIntake();
        }
        else if( record.FoodCategory() == 'A' ) 
        {
            animal_proteins_intake += record.WeightIntake();
        }
        else if( record.FoodCategory() == 'V' ) 
        {
            vegetable_intake += record.WeightIntake();
        }
        else if( record.FoodCategory() == 'F' ) 
        {
            fruit_intake += record.WeightIntake();
        }
        else if( record.FoodCategory() == 'B' && (record.FoodName() == "Milk" || record.FoodName() == "Yogurt"))
        {
            milk_intake += record.WeightIntake();
        }
    }
}


void DietReport::GenerateReport()   const
{
    /* print the report to the file */
    ofstream outfile("../result/diet_report.txt");
    streamsize prec = outfile.precision();
    outfile << setprecision(3);
    outfile << "========================================" << endl;
    outfile << "Daily Diet Analysis Report" << endl;
    outfile << "----------------------------------------" << endl;

    outfile << "Name: " << user.Name() << endl;
    outfile << "Age: " << user.Age() << endl; 
    outfile << "Gender(F/M): " << user.Gender() << endl; 
    outfile << "Height(cm): " << user.Height() << endl; 
    outfile << "Weight(kg): " << user.Weight() << endl; 
    
    outfile << "BMI: " << user.BMI() << endl; 
    outfile << "Physical Status: " << user.PhysicalStatus() << endl; 
    outfile << setprecision(prec); 
         
    outfile << "Nutritional Intake Profile (daily recommendation in parentheses) :" << endl;
    outfile << "Food Energy Intake: " << calorie_intake << " (" << user.CalorieIntakeValue() << "kcal)" << endl;
    outfile << "Staple Food: " << staple_food_intake << " (200-300g)" << endl;
    outfile << "Animal Proteins: " << animal_proteins_intake << " (120-200g)" << endl;
    outfile << "Vegetables: " << vegetable_intake << " (300-500g)" << endl;
    outfile << "Fruits: " << fruit_intake << " (200-350g)" << endl;
    outfile << "Dairy: " << milk_intake << " (300g)" << endl;

    outfile << "========================================" << endl;
    outfile.close();
    
    /* print the report to the screen */
    prec = cout.precision();
    cout << setprecision(3);
    cout << "========================================" << endl;
    cout << "Daily Diet Analysis Report" << endl;
    cout << "----------------------------------------" << endl;

    cout << "Name: " << user.Name() << endl;
    cout << "Age: " << user.Age() << endl; 
    cout << "Gender(F/M): " << user.Gender() << endl; 
    cout << "Height(cm): " << user.Height() << endl; 
    cout << "Weight(kg): " << user.Weight() << endl; 
    cout << "BMI: " << user.BMI() << endl; 
    cout << "Physical Status: " << user.PhysicalStatus() << endl; 
    cout << setprecision(prec);
         
    cout << "Nutritional Intake Profile (daily recommendation in parentheses) :" << endl;
    cout << "Food Energy Intake: " << calorie_intake << " (" << user.CalorieIntakeValue() << "kcal)" << endl;
    cout << "Staple Food: " << staple_food_intake << " (200-300g)" << endl;
    cout << "Animal Proteins: " << animal_proteins_intake << " (120-200g)" << endl;
    cout << "Vegetables: " << vegetable_intake << " (300-500g)" << endl;
    cout << "Fruits: " << fruit_intake << " (200-350g)" << endl;
    cout << "Dairy: " << milk_intake << " (300g)" << endl;

    cout << "========================================" << endl;
}