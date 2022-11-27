#ifndef FACULTY_H_
#define FACULTY_H_

#include "Employee.h"
#include "Skill.h"
#include "exceptions.h"
namespace mtm {

class Condition {
   public:
    virtual bool operator()(Employee* employee) = 0;
};

template <class T>
class Faculty {
   private:
    int id;
    T* cond;
    Skill skill;
    int addedPoints;

   public:
    // creates a new faculty with a given id, skill, addedpoints, condition
    Faculty(int id, Skill skill, int addedPoints, T* cond) : skill(skill) {
        this->id = id;
        this->cond = cond;
        this->addedPoints = addedPoints;
    }

    // a method to get
    int getId() const { return id; }

    // returns how many points the faculty adds to someone who studies.
    int getAddedPoints() const { return addedPoints; }

    // returns the skill that the faculty teaches
    Skill getSkill() const { return skill; }

    // teach an employee the skill that the faculty teaches if he has enough points.
    void teach(Employee* employee) {
        if ((*cond)(employee)) {
            employee->learnSkill(skill);
            employee->setScore(addedPoints);
        } else {
            throw EmployeeNotAccepted();
        }
    }
};

}  // namespace mtm

#endif /* FACULTY_H_ */