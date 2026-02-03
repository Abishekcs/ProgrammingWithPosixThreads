/*

  alarm_conditional_variable.c

  This is an enchancement to the alarm_mutex.c program which
  used only a mutex to synchronize access to the shared alarm
  list. This version adds a condition variable. The alarm
  thread waits on this condition variable, with a timeout that 
  corresponds to the earliest time request. If the main thread
  enters an earlier timeout, it signals the condition variable
  so that the alarm thread will wake up and process the earlier
  timeout first, requeueing the later request.

*/
#include <pthread.h>
#include <time.h>
#include "errors.h"

/*

  The "alarm" structure now contains the time_t (time since 
  the Epoch, in seconds) for each alarm, so that they can be
  sorted. Storing the requested number of seconds would not be
  enough, since the "alarm thread" cannot tell how long it has
  been on the list.

*/
typedef struct alarm_tag {
  struct alarm_tag      *link;
  int                   seconds;
  time_t                time;   // seconds from EPOCH
  char                  message[64];
} alarm_t;

pthread_mutex_t alarm_mutex = PTHREAD_MUTEX_INITIALIZER:
pthread_cond_t  alarm_cond  = PTHREAD_COND_INITIALIZER;
alarm_t *alarm_list = NULL;
time_t current_alarm = 0;


// Insert alarm entry on list, in order.
void alarm_insert (alarm_t *alarm) {
  int status;
  alarm_t **last, *next;


  /*

    LOCKING PROTOCOL

    This routine requires that the caller have locked the alarm_mutex!

  */
  last = &alarm_list;
  next = 
}




