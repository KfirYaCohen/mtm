#include "Employee.h"
using std::cout;

using std::endl;
namespace mtm {

Employee::Employee(int id, string firstName, string lastName, int birthYear)
    : Citizen(id, firstName, lastName, birthYear) {
    salary = 0;
    score = 0;
    skills = std::set<Skill>();
}

int Employee::getSalary() const { return salary; }
int Employee::getScore() const { return score; }
bool Employee::hasSkill(int id) const {  // not sure if right.
    for (Skill i : skills) {
        if (i.getId() == id) {
            return true;
        }
    }
    return false;
}
void Employee::learnSkill(const Skill& s) {
    if (hasSkill(s.getId())) {
        throw SkillAlreadyLearned();
    } else if (s.getRequiredPoints() > getScore()) {
        throw CanNotLearnSkill();
    }
    skills.insert(s);
}
void Employee::forgetSkill(int id) {
    if (!hasSkill(id)) {
        throw DidNotLearnSkill();
    }
    for (Skill s : skills) {
        if (s.getId() == id) {
            this->skills.erase(s);
            return;
        }
    }
}

void Employee::setSalary(int amount) {
    salary += amount;
    if (salary < 0) {
        salary = 0;
    }
}
void Employee::setScore(int amount) {
    score += amount;
    if (score < 0) {
        score = 0;
    }
}
std::ostream& Employee::printShort(std::ostream& os) const {
    os << getFirstName() << " " << getLastName() << endl;
    os << "Salary: " << this->salary << " Score: " << this->score << endl;
    return os;
}
std::ostream& Employee::printLong(std::ostream& os) const {
    os << getFirstName() << " " << getLastName() << endl;
    os << "id - " << getId() << " birth_year - " << getBirthYear() << endl;
    os << "Salary: " << salary << " Score: " << score;
    if (skills.empty() == false) {
        os << " Skills: " << endl;
        for (Skill i : skills) {
            os << i.getName() << endl;
        }
    } else {
        os << endl;
    }

    return os;
}

Employee* Employee::clone() const {
    Employee* copy = new Employee(getId(), getFirstName(), getLastName(), getBirthYear());
    copy->setSalary(salary);
    copy->setScore(score);
    copy->skills = skills;  
    return copy;
}

}  // namespace mtm
