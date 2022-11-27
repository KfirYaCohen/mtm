#ifndef EMPLOYEE_H_
#define EMPLOYEE_H_

#include <iostream>
#include <set>
#include <string>

#include "Citizen.h"
#include "Skill.h"
#include "exceptions.h"

using std::set;

namespace mtm {

class Employee : public Citizen {
   private:
    int salary;
    int score;
    set<Skill> skills;

   public:
    // Creates a new Employee with a given id, first name, last name and birth year.
    Employee(int id, string firstName, string lastName, int birthYear);

    Employee(const Employee& e) = default;  // using the default copy constructor
    // a
    int getSalary() const;
    // a method to get this employee score
    int getScore() const;

    // learns a new skill, adding it to the skills set
    void learnSkill(const Skill& s);

    // forgets a skill, erasing it from the skills set.
    void forgetSkill(int id);

    // checks if a skill exists with the given id
    bool hasSkill(int id) const;

    // changes the salary by the given amount
    void setSalary(int amount);
    
    // changes the score by the given amount
    void setScore(int amount);
    
    //print a short description of the citizen
    std::ostream& printShort(std::ostream& os) const override;

    //print a long description of the citizen
    std::ostream& printLong(std::ostream& os) const override;

    //returns the pointer to a newly allocated cloned employee.
    Employee* clone() const override;
};

}  // namespace mtm
#endif /* EMPLOYEE_H_ */