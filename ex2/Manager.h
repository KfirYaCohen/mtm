#ifndef MANAGER_H_
#define MANAGER_H_

#include <iostream>
#include <set>
#include <string>

#include "Citizen.h"
#include "Employee.h"
#include "exceptions.h"
using std::endl;
using std::set;

namespace mtm {
class Manager : public Citizen {
   private:
    int salary;
    set<Employee*, PointerCompare> employees;

   public:
    // creats a new manager with given id, first name, last name and birthyear
    Manager(int id, string firstName, string lastName, int birthYear);
    // returns the manager's salary
    int getSalary();
    // adds an employee under this manager.
    void addEmployee(Employee* employee);

    // a method to remove an employee from this manager's supervision
    void removeEmployee(int id);

    // changes the manager's salary by the given amount.
    void setSalary(int amount);

    // prints a short description of the manager
    std::ostream& printShort(std::ostream& os) const override;

    // prints a long description of the manager
    std::ostream& printLong(std::ostream& os) const override;

    // returns a pointer to a newly allocated cloned manager
    Manager* clone() const override;

    // checks if there exists an employee with a given id under this manager
    bool hasEmployee(int id) const;

    // returns the set of employees under this manager.
    set<Employee*, PointerCompare>& getEmployees();
};

}  // namespace mtm

#endif /* MANAGER_H_ */