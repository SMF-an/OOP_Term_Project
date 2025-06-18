#ifndef GUARD_DietRecord_h
#define GUARD_DietRecord_h


#include <string>
#include "Date.h"
#include "Food.h"


class DietRecord
{
    public:
        DietRecord() : weight_intake(0), calorie_intake(0) { }
        DietRecord(const Date&, char, const std::string&, int, int);
        DietRecord(int i);

        void Save() const;

        Date DATE() const { return date; }
        char FoodCategory() const { return food_category; }
        std::string FoodName() const { return food_name; }
        int WeightIntake() const { return weight_intake; } 
        int CalorieIntake() const { return calorie_intake; } 

    private:
        Date date;
        char food_category;
        std::string food_name;
        int weight_intake;  // g
        int calorie_intake; // kcal
};

#endif