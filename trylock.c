/*

  Demonstrate a simple use of pthread_try_lock. The
  counter_thread updates a shared counter at intervals,
  and a monitor_thread occassinally reports the current values
  of the counter -- but only if the mutex is not already 
  locked by counter_thread

  Special notes: On a Solaris system, call thr_setcouncurrency()
  to allo interleaved thread execution, since threds are not
  timesliced

*/

#include <pthread.h>
#include "errors.h"

#define SPIN 10000000

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
long counter;
time_t end_time;

/*
 
 Thread start routine that repeatedly locks a mutex
 and increments a counter.

*/

void *counter_thread (void *arg) {
  int status;
  int spin;

  /*

    Until end_time, increment the counter
    each second. Instead of just incrementing the counter, it
    sleeps for another second with mutex unlocked, to give 
    monitor_thread a reasonable chance of running.

  */
  while (time (NULL) < end_time) {
    status = pthread_mutex_lock (&mutex);

    if (status != 0)
      err_abort (status, "Lock mutex");
    
    for (spin = 0; spin < SPIN; spin++) 
      counter++;

    status = pthread_mutex_unlock (&mutex);

    if (status !=0)
      err_abort (status, "Unlock mutex");

    sleep (1);
  }

  printf("Counter is %#lx\n", counter);
  return NULL;
}


/*

  Thread start routine to "monitor" the counter. Every 3
  seconds, try to lock the mutex and read the counter. If 
  the trylock fails, skip the cycle.

*/
void *monitor_thread (void *arg) {
  int status;
  int misses = 0;

  /*
    
    Loop until end_time, checking the counter every 3 seconds.

  */
  while (time (NULL) < end_time) {
    sleep (3);
    status = pthread_mutex_lock (&mutex);

    if (status != EBUSY) {
      if (status != 0)
        err_abort (status, "Trylock mutex");

      printf("Counter is %ld\n", counter/SPIN);

      status = pthread_mutex_unlock (&mutex);

      if (status != 0)
        err_abort (status, "Unlock mutex");

    } else
        misses++; // Count "misses" on the lock
  }

  printf("Monitor thread missed update %d times.\n", misses);
  return NULL;
}


int main (int argc, char *argv[]) {

  int status;
  pthread_t counter_thread_id;
  pthread_t monitor_thread_id;

  end_time = time (NULL) + 60;

  status = pthread_create (&counter_thread_id, NULL, counter_thread, NULL);
  if (status != 0)
    err_abort (status, "Create counter thread");

  status = pthread_create (&monitor_thread_id, NULL, monitor_thread, NULL);
  if (status !=0)
    err_abort (status, "Monitor counter thread");

  status = pthread_join (counter_thread_id, NULL);
  if (status !=0)
    err_abort (status, "Join Counter Thread");

  status = pthread_join (monitor_thread_id, NULL);
  if (status !=0)
    err_abort (status, "Join monitor thread");

  return 0;
}











