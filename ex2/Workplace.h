#ifndef WORKPLACE_H_
#define WORKPLACE_H_
#include <iostream>
#include <set>
#include <string>

#include "Manager.h"
#include "exceptions.h"

using std::endl;
using std::set;
using std::string;

namespace mtm {
class Workplace {
   private:
    int id;
    string name;
    int employeesSalary;
    int managerSalary;
    set<Manager*> managers;

   public:
    // Creates a new workplace with a given name, with standard employees and managers salary
    Workplace(int id, string name, int employeesSalary, int managerSalary);

    // returns the managers salary
    int getManagersSalary() const;

    // returns the employees salary
    int getWorkersSalary() const;

    // returns the workplace name
    string getName() const;

    // returns the workplace id
    int getId() const;

    // checks if an employee with a given id exists in the workplace
    bool hasEmployee(int id) const;
    // checks if a manager with a given id exists in the workplace
    bool hasManager(int id) const;

    // hires a new manager to the workplace. increasing his salary.
    void hireManager(Manager* manager);

    // a generic method that gets a hiring condition functor and hires an employee if he qualifies
    template <class Cond>
    void hireEmployee(Cond& cond, Employee* employee, int managerId) {
        if (cond(employee)) {  // condition satisfied
            for (Manager* m : managers) {
                if (m->getId() == managerId) {
                    m->addEmployee(employee);
                    employee->setSalary(employeesSalary);
                    return;
                }
            }
            throw ManagerIsNotHired();
        }
        throw EmployeeNotSelected();
    }
    // a method to fire an employee from the workplace
    void fireEmployee(int employeeId, int managerId);

    // a method to fire a manager from the workplace and all his workers
    void fireManager(int managerId);

    // overloading the << operator to print a short description of the workplace.
    friend std::ostream& operator<<(std::ostream& os, const Workplace& wp);

    // overloading the operator < to compare workplaces by their ID's
    friend bool operator<(const Workplace& w1, const Workplace& w2);
};
}  // namespace mtm

#endif /* WORKPLACE_H_ */