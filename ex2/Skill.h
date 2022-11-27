#ifndef SKILL_H_
#define SKILL_H_
#include <iostream>
#include <string>

#include "exceptions.h"

using std::string;
namespace mtm {

class Skill {
   private:
    int id;
    string name;
    int requiredPoints;

   public:
    // creates a new skill with a given id, name, requiredPoints
    Skill(int id, string name, int requiredPoints);

    ~Skill() = default;  // using the default destructor.

    Skill(const Skill& s) = default;  // using the default copy constructor.

    // a method to get this skill ID
    int getId() const;

    // a method to get this skill name
    string getName() const;

    // returns the required points needed to learn the skill
    int getRequiredPoints() const;

    // overloading the ++ operator to increase the required points
    Skill operator++(int);

    // overloading the operator += increase the required points
    Skill& operator+=(int n);

    // overloading the + operator to increase the required points
    friend Skill& operator+(Skill& skill, int n);

    // overloading the + operator to increase the required points
    friend Skill& operator+(int n, Skill& skill);

    // overloading the << operator to print skills
    friend std::ostream& operator<<(std::ostream& os, const Skill& skill);

    // overloading the operator == to compare skills by thier id
    friend bool operator==(const Skill& s1, const Skill& s2);
    // overloading the operator < to compare skills by thier id
    friend bool operator<(const Skill& s1, const Skill& s2);
};
// overloading the operator != to compare skills by thier id
bool operator!=(const Skill& skill1, const Skill& skill2);
// overloading the operator <= to compare skills by thier id
bool operator<=(const Skill& skill1, const Skill& skill2);
// overloading the operator > to compare skills by thier id
bool operator>(const Skill& skill1, const Skill& skill2);
// overloading the operator >= to compare skills by thier id
bool operator>=(const Skill& skill1, const Skill& skill2);
// overloading the operator + to increase the required points
Skill& operator+(Skill& skill, int n);
// overloading the operator + to increase the required points
Skill& operator+(int n, Skill& skill);

}  // namespace mtm

#endif /* SKILL_H_ */