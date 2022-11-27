#ifndef CITIZEN_H_
#define CITIZEN_H_
#include <iostream>
#include <string>

#include "exceptions.h"

using std::endl;
using std::string;

namespace mtm {

class Citizen {
   private:
    int id;
    string lastName;
    string firstName;
    int birthYear;

   public:
    // Creates a new Citizen with a given id, first name, last name and birth year.
    Citizen(int id, string firstName, string lastName, int birthYear);

    Citizen(const Citizen& c) = default; //using the default copy constructor
    virtual ~Citizen(){}; //polimorphic class, needs to have virtual destructor

    // a method to get this citizen ID
    int getId() const;
    // a method to get this FirstName
    string getFirstName() const;
    // a method to get this citizen LastName
    string getLastName() const;
    // a method to get this citizen BirthYear
    int getBirthYear() const;

    //virtual methods that will be implemented by the derived classes

    //print a short description of the citizen
    virtual std::ostream& printShort(std::ostream& os) const = 0;
    
    //print a long description of the citizen
    virtual std::ostream& printLong(std::ostream& os) const = 0;
    
    //Clone a citizen, returns a newly allocated pointer to the copy.
    virtual Citizen* clone() const = 0;

    // Overloading the == operator to compare using ID's
    friend bool operator==(const Citizen& c1, const Citizen& c2);
    // Overloading the < operator to compare using ID's
    friend bool operator<(const Citizen& c1, const Citizen& c2);
};

// Overloading the != operator to compare using ID's
bool operator!=(const Citizen& c1, const Citizen& c2);
// Overloading the <= operator to compare using ID's
bool operator<=(const Citizen& c1, const Citizen& c2);
// Overloading the > operator to compare using ID's
bool operator>(const Citizen& c1, const Citizen& c2);
// Overloading the >= operator to compare using ID's
bool operator>=(const Citizen& c1, const Citizen& c2);

//Object function for comparing 2 citizen's pointers 
class PointerCompare {
   public:
    bool operator()(const Citizen* c1, const Citizen* c2) {
        if (c1->getId() < c2->getId()) {  // Allowing two citizens with the same id to exist in the
                                          // set. just for printing purposes.
            return true;
        } else
            return false;
    }
};

}  // namespace mtm

#endif /* CITIZEN_H_ */
