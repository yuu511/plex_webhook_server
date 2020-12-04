#ifndef __THREADPOOL_H_
#define __THREADPOOL_H_

#include <queue>
#include <thread>
#include <memory>
#include <mutex>
#include <condition_variable>

typedef void (*task)();

struct threadpool {
  threadpool(size_t num_threads);
  ~threadpool();
  //TODO: fix lazy copy & move ctors
  threadpool(const threadpool&) = delete;
  threadpool &operator= (const threadpool&) = delete;
  threadpool(threadpool&&) = delete;

  void add_task(task Task);

  std::queue<task> tasks;
  std::unique_ptr<std::vector<std::thread>> threads;
  std::mutex mtx;
  std::condition_variable newWork;
  size_t work;
};

void thread_work(threadpool *pool);

#endif 
