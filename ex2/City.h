#ifndef CITY_H_
#define CITY_H_
#include <set>
#include <string>
#include <vector>

#include "Employee.h"
#include "Faculty.h"
#include "Manager.h"
#include "Workplace.h"
#include "exceptions.h"

using std::set;
using std::vector;

namespace mtm {

class City {
   private:
    string name;
    set<Employee*, PointerCompare> employees;
    set<Manager*, PointerCompare> managers;
    set<Workplace> workplaces;
    vector<Faculty<Condition>> faculties;

   public:
    // Creates a new city with a given name
    City(string name);

    // Destroy a city, freeing all allocated citizens.
    ~City();

    // a method to add an employee to the city
    void addEmployee(int id, string firstName, string lastName, int birthYear);

    // a method to add an manager to the city
    void addManager(int id, string firstName, string lastName, int birthYear);

    // a method to add a Faculty to the city
    void addFaculty(int id, Skill skill, int addedPoints, Condition* cond) {
        hasFaculty(id);
        Faculty<Condition> f = Faculty<Condition>(id, skill, addedPoints, cond);
        faculties.push_back(f);
    }
    // a method to add a new workplace to the city
    void createWorkplace(int id, string name, int employeesSalary, int managerSalary);

    // a method that sends an employee to learn at a faculty, giving him the skill and points if he
    // is qualifies
    void teachAtFaculty(int id, int facultyId);

    // a method to hire an employee to a given workplace if he is qualifies
    // generic function that can get different hiring conditions.
    template <class HiringCondition>
    void hireEmployeeAtWorkplace(HiringCondition& hiringCondition, int employeeId, int managerId,
                                 int workplaceId) {
        Employee* e = findEmployee(employeeId);
        if (findManager(managerId) != NULL) {
            for (Workplace w : workplaces) {
                if (w.getId() == workplaceId) {
                    w.hireEmployee(hiringCondition, e, managerId);
                    employees.erase(e);
                    employees.insert(e);
                    workplaces.erase(w);
                    workplaces.insert(w);
                    return;
                }
            }
            throw WorkplaceDoesNotExist();
        }
    }

    // a method to hire a manager to a workplace.
    void hireManagerAtWorkplace(int id, int workplaceId);

    // a method to fire an employee from a workplace.
    void fireEmployeeAtWorkplace(int employeeId, int managerId, int workplaceId);

    // a method to fire a manager from a workplace.
    void fireManagerAtWorkplace(int managerId, int workplaceId);

    // a method to print a short description of all the employees with a salary higher than "salary"
    //  sorted by their id's
    int getAllAboveSalary(std::ostream& os, int salary);

    // a method that checks if two employees are working in the same workplace
    bool isWorkingInTheSameWorkplace(int id1, int id2);

    // a method to print a short description of all the employees with the given skill
    std::ostream& printAllEmployeesWithSkill(std::ostream& os, int skillId);

    // returns a pointer to the employee with the given id
    Employee* findEmployee(int id);

    // returns a pointer to the manager with the given id
    Manager* findManager(int id);

    // a method to check if there exists a citizen with a given ID
    bool hasCitizenWithId(int id);

    // Checks if there exists a faculty with a given id.
    bool hasFaculty(int id);
};

}  // namespace mtm
#endif /* CITY_H_ */