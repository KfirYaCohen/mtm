#include "Citizen.h"

namespace mtm {
Citizen::Citizen(int id, string firstName, string lastName, int birthYear) {
    this->id = id;
    this->firstName = firstName;
    this->lastName = lastName;
    this->birthYear = birthYear;
}


int Citizen::getId() const { return this->id; }
string Citizen::getFirstName() const { return firstName; }
string Citizen::getLastName() const { return lastName; }
int Citizen::getBirthYear() const { return birthYear; }

bool operator==(const Citizen& c1, const Citizen& c2) {  // c1==c2 
    return (c1.id == c2.id);
}
bool operator<(const Citizen& c1, const Citizen& c2) {  // c1<c2
    return c1.id < c2.id;
}
bool operator>(const Citizen& c1, const Citizen& c2) {  // c1>c2
    return c1 < c2;
}
bool operator<=(const Citizen& c1, const Citizen& c2) {  // c1<=c2
    return c1 == c2 || c1 < c2;
}
bool operator>=(const Citizen& c1, const Citizen& c2) {  // c1>=c2
    return c1 == c2 || c1 > c2;
}
bool operator!=(const Citizen& c1, const Citizen& c2) {  // c1!=c2
    return !(c1 == c2);
}

}  // namespace mtm