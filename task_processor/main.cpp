#include "TaskExecutor.hpp"
#include <thread>
#include <iostream>
#include <cstdlib>
#include <chrono>

void createTasks(std::shared_ptr<TaskExecutor> taskExecutor) {
    int i = 0;
    std::cout << "Starting task creator..." << std::endl;
    while(1) {
        std::string taskName = "Task_" + std::to_string(++i);
        std::cout << "Enqueuing task..." << std::endl;
        taskExecutor->add(std::move(Task(taskName)));
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 80 + 20));
    }
}

void processTasks(std::shared_ptr<TaskExecutor> taskExecutor) {
    std::cout << "Starting task processor..." << std::endl;
    while(1) {
        std::cout << "Processing tasks..." << std::endl;
        taskExecutor->process();
        std::this_thread::sleep_for(std::chrono::milliseconds((rand() % 5) * 100));
    }
}

int main(int argc, char** argv) {
    auto taskExecutor = std::make_shared<TaskExecutor>();

    std::thread producer = std::thread(createTasks, taskExecutor);
    std::thread processor = std::thread(processTasks, taskExecutor);

    producer.join();
    processor.join();

    return 0;
}
