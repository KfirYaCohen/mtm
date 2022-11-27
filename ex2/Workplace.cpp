
#include "Workplace.h"


namespace mtm {

Workplace::Workplace(int id, string name, int employeesSalary, int managerSalary) {
    this->id = id;
    this->name = name;
    this->employeesSalary = employeesSalary;
    this->managerSalary = managerSalary;
    this->managers = set<Manager*>();
}
int Workplace::getManagersSalary() const { return managerSalary; }
int Workplace::getWorkersSalary() const { return employeesSalary; }
string Workplace::getName() const { return name; }
int Workplace::getId() const { return id; }
bool Workplace::hasManager(int id) const {  // not sure if right.
    for (Manager* m : managers) {
        if (m->getId() == id) {
            return true;
        }
    }
    return false;
}
bool Workplace::hasEmployee(int id) const {  // not sure if right.
    for (Manager* m : managers) {
        if (m->hasEmployee(id)) {
            return true;
        }
    }
    return false;
}

void Workplace::hireManager(Manager* m) {
    if (hasManager(m->getId())) {
        throw ManagerAlreadyHired();
    } else if (m->getSalary() != 0) {
        throw CanNotHireManager();
    } else {
        m->setSalary(managerSalary);
        managers.insert(m);
    }
}

void Workplace::fireEmployee(int employeeId, int managerId) {
    for (Manager* m : managers) {
        if (m->getId() == managerId) {
            for (Employee* e : m->getEmployees()) {
                if (e->getId() == employeeId) {
                    m->getEmployees().erase(e);
                    e->setSalary(-employeesSalary);
                    return;
                }
            }
            throw EmployeeIsNotHired();
        }
    }
    throw ManagerIsNotHired();
}

void Workplace::fireManager(int managerId) {
    for (Manager* m : managers) {
        if (m->getId() == managerId) {
            //apperenatly there is no need to fire the employees if you invoke this function from workplace. why?
            // for (Employee* e : m->getEmployees()) {
            //     e->setSalary((-1)*employeesSalary);
            // }
            // m->getEmployees().clear();
            managers.erase(m);
            m->setSalary(-managerSalary);
            return;
        }
    }
    throw ManagerIsNotHired();
}

std::ostream& operator<<(std::ostream& os, const Workplace& wp) {
    if (wp.managers.empty()) {
        os << "Workplace name - " << wp.name << endl;
    } else {
        os << "Workplace name - " << wp.name << " Groups:" << endl;
        for (Manager* m : wp.managers) {
            os << "Manager ";
            m->printLong(os);
        }
    }
    return os;
}

bool operator<(const Workplace& w1, const Workplace& w2) { return (w1.id < w2.id); }

}  // namespace mtm
