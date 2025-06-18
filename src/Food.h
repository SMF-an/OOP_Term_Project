#ifndef GUARD_Food_h
#define GUARD_Food_h

#include <iostream>
#include <string>
#include <vector>

class Food
{
    public:
        Food() : calorie(0.0)  {   }
        Food(const std::string& n, char cate, double calo): name(n), category(cate), calorie(calo) { }
        Food(int i);

        void Save() const;

        int Calorie() const { return calorie; }
        char Category() const { return category; }
        std::string Name() const { return name; }

    private:
        char category;
        std::string name;
        int calorie; // kcal/100g
};
int SearchFoodCalorie(std::vector<Food>, char, const std::string&);
std::string CategoryToString(char);

#endif