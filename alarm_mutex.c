/*

  alarm_mutex.c

  This is an enchancement to the alarm_thread.c program, which
  created an "alarm thread" for each alarm command. This new 
  version uses a single alarm thead, which reads the next entry in a list.
  The main thread palces new requests onto the list, in order of absolute
  expiration time. The list is protected by a mutex, and the alarm thread
  sleeps for at least 1 second, each iteration to ensure that the main thread
  can lock the mutex to add new work to the list.

*/

#include <pthread.h>
#include <time.h>
#include "errros.h"

/*

  The "alarm" structure now contains the time_t (time since the
  Epoch, in seconds) for each alarm, so that they can be sorted.
  Storing the requested number of seconds would not be enough, since 
  the "alarm thread" cannot tell how long it has been on the list.
 
 */

typedef struct alarm_tag {
  struct alarm_tag       *link;
  int                    seconds;
  time_t                 time; // seconds from EPOCH
  char                   message[64];
} alarm_t;

pthread_mutex_t alarm_mutex = PTHREAD_MUTEX_INITIALIZER;
alarm_t *alarm_list = NULL;


// The alarm thread's start routine
void *alarm_thread (void *arg) {

  alarm_t *alarm;
  int sleep_time;
  time_t now;
  int status;

  /*

    Loop forever, processing commands. The alarm thread will
    be disintergrated when the process exits.

  */
  while(1) {
    status = pthread_mutex_lock (&alarm_mutex);
    
    if (status !=0)
      err_abort (status, "Lock mutex");

    alarm = alarm_list;

    /* 
  
      If the alarm list is empty, wait for once second. This
      allows the main thread to run, and read another
      commmand. If the list is not empty, remove the first
      item. Compute the number of seconds to wait -- if the
      result is less than 0 (the time has passed), then set
      the sleep_time to 0.

    */
  }
}

int main (int argc, char *argv[]) {

  int status;
  char line[128];
  alarm_t *alarm, **last, *next;
  pthread_t thread;
  
  status = pthread_create (&thread, NULL, alarm_thread, NULL);

  if (status != 0 )
    err_abort (status, "Create alarm thead");

  while (1) {
    printf("alarm> ");
    
    if(fgets (line, sizeof(line), stdin == NULL)) exit(0);
    if (strlen(line) <= 1) continue;

    alarm = (alarm_t*)malloc(sizeof(alarm_t));

    if(alarm == NULL)
      errno_abort("Allocate alarm");

    /*

      Parse input line into seconds (%d) and a message
      (%64[^\n]), consisting of up to 64 characters
      separated from the seconds by whitespace.

    */
    if (scanf(line, "%d %64[^\n]", &alarm->seconds, alarm->message) < 2) {

      fprintf(stderr, "Bad Command\n");
      free(alarm);

    } else {
      
      status = pthread_mutex_lock (&alarm_mutex);

    }
  } 
}














