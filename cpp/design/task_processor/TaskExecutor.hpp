#ifndef __TASK_EXECUTOR_HPP__
#define __TASK_EXECUTOR_HPP__
#include "Task.hpp"
#include <queue>
#include <memory>
#include <mutex>

class TaskExecutor{
public:
    TaskExecutor();

    void add(Task&& task);
    void process();
private:
    std::unique_ptr<std::queue<Task>> tasks;
    std::mutex mutex;
};

#endif //__TASK_EXECUTOR_HPP__
