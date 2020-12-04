#include <stdio.h>
#include "threadpool.h"

void thread_work(threadpool *pool)
{
  for (;;) {
    std::unique_lock<std::mutex>lock (pool->mtx);
    while (pool->tasks.empty()) {
      printf ("something!");
      pool->newWork.wait(lock);
    }
    pool->work++;
    task Task = pool->tasks.front();
    pool->tasks.pop();
    lock.unlock();
    Task();
    lock.lock();
    pool->work--;
    if (!pool->work) printf("done!");
  }
}

threadpool::threadpool(size_t num_threads) 
: threads(std::make_unique<std::vector<std::thread>>()),
  work(0)
{
  while (num_threads--) {
    auto thread = std::thread(thread_work, this); 
    threads->push_back(std::move(thread));
  }
}

threadpool::~threadpool() {
  for (auto &thread : *threads) thread.join();
}

void threadpool::add_task(task Task) 
{
  printf("add task");
  std::unique_lock<std::mutex> lck (mtx);
  printf("added");
  tasks.push(Task);
  newWork.notify_one();
}
