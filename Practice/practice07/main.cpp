#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <sstream>
#include <iomanip>
#include <limits>

class Employee {
protected:
    std::string name;
    int id;
public:
    Employee(std::string name, int id) : name(name), id(id) {}
    virtual ~Employee() {}
    virtual double calculateSalary() const = 0;
    virtual void displayInfo() const {
        std::cout << "ID: " << id << ", Name: " << name;
    }
};

class SalariedEmployee : public Employee {
    double monthlySalary;
public:
    SalariedEmployee(std::string name, int id, double monthlySalary) 
        : Employee(name, id), monthlySalary(monthlySalary) {}
    double calculateSalary() const override {
        return monthlySalary;
    }
    void displayInfo() const override {
        Employee::displayInfo();
        std::cout << ", Type: Salaried, Monthly Salary: $" << std::fixed << std::setprecision(2) << monthlySalary << "\n";
    }
};

class HourlyEmployee : public Employee {
    double hourlyRate;
    int hoursWorked;
public:
    HourlyEmployee(std::string name, int id, double hourlyRate, int hoursWorked) 
        : Employee(name, id), hourlyRate(hourlyRate), hoursWorked(hoursWorked) {}
    double calculateSalary() const override {
        return hourlyRate * hoursWorked;
    }
    void displayInfo() const override {
        Employee::displayInfo();
        std::cout << ", Type: Hourly, Hours Worked: " << hoursWorked
                  << ", Hourly Rate: $" << std::fixed << std::setprecision(2) << hourlyRate
                  << ", Salary: $" << calculateSalary() << "\n";
    }
};

class CommissionEmployee : public Employee {
    double baseSalary, salesAmount, commissionRate;
public:
    CommissionEmployee(std::string name, int id, double baseSalary, double salesAmount, double commissionRate)
        : Employee(name, id), baseSalary(baseSalary), salesAmount(salesAmount), commissionRate(commissionRate) {}
    double calculateSalary() const override {
        return baseSalary + (salesAmount * commissionRate);
    }
    void displayInfo() const override {
        Employee::displayInfo();
        std::cout << ", Type: Commission, Base Salary: $" << std::fixed << std::setprecision(2) << baseSalary
                  << ", Sales: $" << salesAmount << ", Commission Rate: " << (commissionRate * 100) << "%"
                  << ", Salary: $" << calculateSalary() << "\n";
    }
};

int main() {
    std::vector<Employee*> employees;
    std::ifstream file("employees.txt");
    if (!file) {
        std::cerr << "Error: Unable to open employees.txt\n";
        return 1;
    }

    std::string type, name;
    int id;
    while (file >> type >> id >> name) {
        if (type == "Salaried") {
            double salary;
            if (file >> salary) {
                employees.push_back(new SalariedEmployee(name, id, salary));
            } else {
                std::cerr << "Error reading salary for Salaried employee: " << name << "\n";
                file.clear();
                file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        } else if (type == "Hourly") {
            double rate;
            int hours;
            if (file >> rate >> hours) {
                employees.push_back(new HourlyEmployee(name, id, rate, hours));
            } else {
                std::cerr << "Error reading data for Hourly employee: " << name << "\n";
                file.clear();
                file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        } else if (type == "Commission") {
            double baseSalary, sales, commission;
            if (file >> baseSalary >> sales >> commission) {
                employees.push_back(new CommissionEmployee(name, id, baseSalary, sales, commission));
            } else {
                std::cerr << "Error reading data for Commission employee: " << name << "\n";
                file.clear();
                file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        } else {
            std::cerr << "Unknown employee type: " << type << "\n";
            file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    file.close();

    for (const auto& emp : employees) {
        emp->displayInfo();
    }

    for (auto emp : employees) {
        delete emp;
    }

    return 0;
}
