#ifndef GUARD_Menu_h
#define GUARD_Menu_h

#include <vector>
#include "Date.h"
#include "User.h"
#include "Food.h"
#include "DietRecord.h"
#include "DietReport.h"

class Menu
{
    public:
        Menu();
        void Greeting();
        void ConfigureUser();
        void MainMenu();

    private:
        User user;
        std::vector<Food> foods;
        std::vector<DietRecord> diet_records;
        Date date;

        void LoadFoods();
        void LoadDietRecords();

        void UserMenu();
        void DietMenu();
        void ReportMenu();
        void RecordMenu();
        void ExitMenu();
};

#endif