#include "City.h"
namespace mtm {

City::City(string name) {
    this->name = name;
    this->employees = set<Employee*, PointerCompare>();
    this->managers = set<Manager*, PointerCompare>();
    this->workplaces = set<Workplace>();
    this->faculties = vector<Faculty<Condition>>();
}
City::~City() {
    for (Employee* e : employees) {
        delete (e);
    }
    for (Manager* m : managers) {
        delete (m);
    }
}

void City::addEmployee(int id, string firstName, string lastName, int birthYear) {
    if (hasCitizenWithId(id) == true) {  // checks if there is a manager with the same ID
        throw CitizenAlreadyExists();
    }
    Employee* e = new Employee(id, firstName, lastName, birthYear);
    employees.insert(e);
}
void City::addManager(int id, string firstName, string lastName, int birthYear) {
    if (hasCitizenWithId(id) == true) {  // checks if there is a manager with the same ID
        throw CitizenAlreadyExists();
    }
    Manager* m = new Manager(id, firstName, lastName, birthYear);
    managers.insert(m);
}

void City::createWorkplace(int id, string name, int employeesSalary, int managerSalary) {
    Workplace w = Workplace(id, name, employeesSalary, managerSalary);
    if (workplaces.find(w) != workplaces.end()) {
        throw WorkplaceAlreadyExists();
    }
    workplaces.insert(w);
}
void City::teachAtFaculty(int employeeId, int facultyId) {
    for (Faculty<Condition> f : faculties) {
        if (f.getId() == facultyId) {
            Employee* e = findEmployee(employeeId);
            f.teach(e);
            employees.erase(e);
            employees.insert(e);
            return;
        }
    }
    throw FacultyDoesNotExist();
}

void City::hireManagerAtWorkplace(int managerId, int workplaceId) {
    for (Workplace w : workplaces) {
        if (w.getId() == workplaceId) {
            for (Manager* m : managers) {
                if (m->getId() == managerId) {
                    w.hireManager(m);
                    workplaces.erase(w);
                    workplaces.insert(w);
                    // managers.erase(m);
                    // managers.insert(m);
                    return;
                }
            }
            throw ManagerDoesNotExist();
        }
    }
    throw WorkplaceDoesNotExist();
}
void City::fireEmployeeAtWorkplace(int employeeId, int managerId, int workplaceId) {
    if (findEmployee(employeeId) == NULL) {
        throw EmployeeDoesNotExist();
    }
    if (findManager(managerId) == NULL) {
        throw ManagerDoesNotExist();
    }
    for (Workplace w : workplaces) {
        if (w.getId() == workplaceId) {
            w.fireEmployee(employeeId, managerId);
            return;
        }
    }
    throw WorkplaceDoesNotExist();
}
void City::fireManagerAtWorkplace(int managerId, int workplaceId) {
    for (Workplace w : workplaces) {
        if (w.getId() == workplaceId) {
            try {
                w.fireManager(managerId);
                workplaces.erase(w);
                workplaces.insert(w);
                Manager* m = findManager(managerId);
                for (Employee* e : m->getEmployees()) {
                    e->setSalary((-1) * w.getWorkersSalary());
                }
                m->getEmployees().clear();
            } catch (ManagerIsNotHired&) {
                throw ManagerDoesNotExist();
            }
            return;
        }
        throw WorkplaceDoesNotExist();
    }
}

int City::getAllAboveSalary(std::ostream& os, int salary) {
    set<Citizen*, PointerCompare> citizens;
    for (Employee* e : employees) {
        if (e->getSalary() >= salary) {
            citizens.insert(e);
        }
    }
    for (Manager* m : managers) {
        if (m->getSalary() >= salary) {
            citizens.insert(m);
        }
    }

    for (Citizen* c : citizens) {
        c->printShort(os);
    }

    return citizens.size();
}

bool City::isWorkingInTheSameWorkplace(int id1, int id2) {
    int sum = 0;
    for (Employee* e : employees) {
        if (e->getId() == id1 || e->getId() == id2) {
            sum++;
        }
    }
    if (sum != 2) {
        throw EmployeeDoesNotExist();
    }

    for (Workplace w : workplaces) {
        if (w.hasEmployee(id1) && w.hasEmployee(id2)) {
            return true;
        }
    }
    return false;
}
std::ostream& City::printAllEmployeesWithSkill(std::ostream& os, int skillId) {
    // set<Employee*, PointerCompare> employeesToPrint;  // Sorting by ID to print
    // for (Employee* e : employees) {
    //     employeesToPrint.insert(e);
    // }

    for (Employee* e : employees) {
        if (e->hasSkill(skillId)) {
            e->printShort(os);
        }
    }
    return os;
}

Employee* City::findEmployee(int id) {
    for (Employee* e : employees) {
        if (e->getId() == id) {
            return e;
        }
    }
    throw EmployeeDoesNotExist();
}
Manager* City::findManager(int id) {
    for (Manager* m : managers) {
        if (m->getId() == id) {
            return m;
        }
    }
    throw ManagerDoesNotExist();
}

bool City::hasCitizenWithId(int id) {
    for (Manager* m : managers) {
        if (m->getId() == id) {
            return true;
        }
    }
    for (Employee* e : employees) {
        if (e->getId() == id) {
            return true;
        }
    }
    return false;
}

bool City::hasFaculty(int id) {
    for (Faculty<Condition> f : faculties) {
        if (f.getId() == id) {
            throw FacultyAlreadyExists();
        }
    }
    return true;
}

}  // namespace mtm