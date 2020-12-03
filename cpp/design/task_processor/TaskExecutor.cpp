#include "TaskExecutor.hpp"

TaskExecutor::TaskExecutor() {
    this->tasks = std::make_unique<std::queue<Task>>();
}

void TaskExecutor::add(Task&& task) {
    std::lock_guard<std::mutex> lock(mutex);
    tasks->push(std::move(task));
}

void TaskExecutor::process() {
    std::lock_guard<std::mutex> lock(mutex);
    while(!tasks->empty()) {
        auto task = std::move(tasks->front());
        tasks->pop();
        task.execute();
    }
}
