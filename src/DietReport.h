#ifndef GUARD_DietReport_h
#define GUARD_DietReport_h

#include <vector>
#include "User.h"
#include "DietRecord.h"
#include "Date.h"

class DietReport
{
    public:
        DietReport()  {  }
        DietReport(User, std::vector<DietRecord>);

        void GenerateReport() const;
    private:
        User user;
        std::vector<DietRecord> diet_records;
        Date today;
        
        int calorie_intake; // total calorie intake for the day
        int staple_food_intake; // total staple food intake for the day
        int animal_proteins_intake; // total animal protein intake for the day
        int vegetable_intake; // total vegetable intake for the day
        int fruit_intake; // total fruit intake for the day
        int milk_intake; // total milk intake for the day

        void ComputeIntake();
};

#endif