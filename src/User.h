#ifndef GUARD_User_h
#define GUARD_User_h

#include <string>

class User
{
    friend class Menu;

    public:
        User() : age(0) , height(0), weight(0)  {   }
        bool Load();
        void Init();
        void Configure(); 

        std::string Name() const   {   return name;    }
        int Age()   const   {   return age; }
        char Gender() const   {   return gender; }
        int Height() const   {   return height; }   
        int Weight() const   {   return weight; }
        double BMI() const   {   return bmi; }
        std::string PhysicalStatus() const   {   return physical_status; }
        double CalorieIntakeValue() const   {   return calorie_intake_value; }
        
    private:
        std::string name;
        int age;
        char gender;
        int height; // cm
        int weight; // kg
        
        double basic_metabolism;
        double activity = 1.2;
        double bmi;
        double calorie_intake_value;    // daily calorie intake recommendation value
        std::string physical_status;

        void ComputeBMI();
        void ComputeBasicMetabolism();
        void ComputeCalorieIntakeValue();
        void ClassifyPhysicalStatus();

        static constexpr const double bmi_range[4] = {
            18.5, 24, 28, 100
        };
        static constexpr const char* bmi_classification[4] = {
            "Underweight", "Normal", "Overweight", "Obesity"
        };
};
#endif