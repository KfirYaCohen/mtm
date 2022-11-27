#include "Manager.h"

using std::endl;
namespace mtm {
Manager::Manager(int id, string firstName, string lastName, int birthYear)
    : Citizen(id, firstName, lastName, birthYear) {
    salary = 0;
    employees = set<Employee*, PointerCompare>();
}

int Manager::getSalary() { return salary; }

set<Employee*, PointerCompare>& Manager::getEmployees() { return employees; }

void Manager::addEmployee(Employee* employee) {
    for (Employee* e : employees) {
        if (e->getId() == employee->getId()) {
            throw EmployeeAlreadyHired();
        }
    }
    employees.insert(employee);
}
void Manager::removeEmployee(int id) {
    for (Employee* e : employees) {
        if (e->getId() == id) {
            employees.erase(e);
            return;
        }
    }
    throw EmployeeIsNotHired();
}

void Manager::setSalary(int amount) {
    salary += amount;
    if (salary < 0) {
        salary = 0;
    }
}

std::ostream& Manager::printShort(std::ostream& os) const {
    os << getFirstName() << " " << getLastName() << endl;
    os << "Salary: " << salary << endl;

    return os;
}
std::ostream& Manager::printLong(std::ostream& os) const {
    os << getFirstName() << " " << getLastName() << endl;
    os << "id - " << getId() << " birth_year - " << getBirthYear() << endl;
    os << "Salary: " << salary << endl;
    if (employees.empty() == false) {
        os << "Employees: " << endl;
        for (Employee* e : employees) {
            e->printShort(os);
        }
    }
    return os;
}
Manager* Manager::clone() const {
    Manager* copy = new Manager(getId(), getFirstName(), getLastName(), getBirthYear());
    copy->setSalary(salary);
    copy->employees = employees;  // IS IT OK DADDY ?!
    return copy;
}

bool Manager::hasEmployee(int id) const {
    for (Employee* e : employees) {
        if (e->getId() == id) {
            return true;
        }
    }
    return false;
}

}  // namespace mtm
