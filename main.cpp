#include <stdio.h>
#include "threadpool.h"

void Test() {
  fprintf (stdout,"test Task!");
}

int main () 
{
  const auto advised_threads = std::thread::hardware_concurrency();
  size_t num_threads = 6;
  if (num_threads > (size_t) advised_threads) {
    fprintf(stderr, "Advised threads 0x%x >  num_threads 0x%lx\n", advised_threads, num_threads);
  }
  threadpool pool(num_threads); 
  // for (size_t i=0; i < num_threads; ++i){
  //   pool.add_task(Test);
  // }
  return 0;
}
