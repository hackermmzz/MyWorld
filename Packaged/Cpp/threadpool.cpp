#include"Include/threadpool.h"
Task::Task(Uint priority_, const function<void ()> &fun_)
    : priority(priority_), fun(fun_) {}

Task::Task(const function<void ()> &fun_) : Task(0, fun_) {}

bool Task::TaskPriority::operator()(Task &t1, Task &t2){
    return t1.priority < t2.priority;
}

void ThreadPool::Process() {
    while (run) {
        function<void()> task;
        {
            unique_lock<mutex> lck(lock);
            cv.wait(lck, [&]() { return !TaskQueue.empty(); });
            task = TaskQueue.top().fun;
            TaskQueue.pop();
        }
        task();

    }
}

ThreadPool::ThreadPool(Uint thread_nums) {
    run = 1;
    for (Uint i = 0; i < thread_nums; ++i) {
        WorkThread.emplace_back(&ThreadPool::Process, this);
        WorkThread[i].detach();
    }
}

void ThreadPool::append(const Task &task) {
    {
        unique_lock<mutex> lck(lock);
        TaskQueue.emplace(Task(task));
    }
    cv.notify_one();
}

void ThreadPool::append(const function<void ()> &fun) {
    append(Task(fun));
}

bool ThreadPool::empty() {
    return TaskQueue.empty();
}

ThreadPool::~ThreadPool() {
    run = 0;
    cv.notify_all();
    for (auto &worker: WorkThread) {
        if (worker.joinable())
            worker.join();
    }
}
