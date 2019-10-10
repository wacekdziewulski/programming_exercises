#ifndef __TASK_HPP__
#define __TASK_HPP__
#include <string>

class Task {
public:
    Task(std::string&& name);
    Task(std::string name);
    Task(const Task&) = delete;
    Task(Task&& task);
    Task operator=(Task& task) = delete;

    const std::string& getName();

    virtual void execute();
private:
    std::string name;
};

#endif // __TASK_HPP__
