#include "Task.hpp"
#include <iostream>

Task::Task(std::string&& name) {
    this->name = std::move(name);
}

Task::Task(std::string name) {
    this->name = name;
}
    
Task::Task(Task&& task) {
    this->name = std::move(task.getName());
}

const std::string& Task::getName() {
    return this->name;
}

void Task::execute() {
    std::cout << "Executing: " << name << std::endl;
}
