#include "Skill.h"

using std::endl;
namespace mtm {
Skill::Skill(int id, string name, int requiredPoints) {
    this->id = id;
    this->name = name;
    this->requiredPoints = requiredPoints;
}

int Skill::getId() const { return id; }
string Skill::getName() const { return name; }
int Skill::getRequiredPoints() const { return requiredPoints; }

Skill Skill::operator++(int) {
    Skill old = *this;
    this->requiredPoints++;
    return old;
}

Skill& Skill::operator+=(int n) {
    if (n < 0) {
        throw NegativePoints();
    }
    this->requiredPoints += n;
    return *this;
}

Skill& operator+(Skill& skill, int n) {
    if (n < 0) {
        throw NegativePoints();
    }
    skill.requiredPoints += n;
    return skill;
}
Skill& operator+(int n, Skill& skill) { return skill + n; }

bool operator==(const Skill& s1, const Skill& s2) {  // s1==s2
    return (s1.id == s2.id);
}
bool operator<(const Skill& s1, const Skill& s2) {  // s1<s2  1-2<0
    return (s1.id < s2.id);
}
bool operator>(const Skill& s1, const Skill& s2) {  // s1>s2
    return s2 < s1;
}
bool operator<=(const Skill& s1, const Skill& s2) {  // s1<=s2
    return s1 == s2 || s1 < s2;
}
bool operator>=(const Skill& s1, const Skill& s2) {  // s1>=s2
    return s1 == s2 || s1 > s2;
}
bool operator!=(const Skill& s1, const Skill& s2) {  // s1!=s2
    return !(s1 == s2);
}

std::ostream& operator<<(std::ostream& os, const Skill& skill) {
    os << skill.name << /*" level: " << skill.level <<*/ endl;
    return os;
}

}  // namespace mtm
