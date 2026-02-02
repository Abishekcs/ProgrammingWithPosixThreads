// conditional_variable_dynamic.c
// Demonstrate dynamic initialization of a condition variable.
#include <pthread.h>
#include "errors.h"

// Define a structure, with a mutex and condition variable
typedef struct my_struct_tag {
  pthread_mutex_t     mutex;  // Protects access to value 
  pthread_cond_t      cond;  // Signals change to value
  int                 value; // Access protected by mutex
} my_struct_t;

int main (int argc, char *argv[]) {
  my_struct_t *data;
  int status;

  data = malloc (sizeof (my_struct_t));

  if (data == NULL)
    errno_abort ("Allocate Structure");
  status = pthread_mutex_init (&data->mutex, NULL);
  if (status != 0)
    err_abort (status, "Init Mutex");
  status = pthread_cond_init (&data->cond, NULL); 
  if (status != 0)
    err_abort (status, "Init Condition");
  status = pthread_cond_destroy (&data->cond);
  if (status != 0)
    err_abort (status, "Destory Condition");
  status = pthread_mutex_destroy (&data->mutex);
  if (status !=0)
    err_abort (status, "Destory Mutex");
  (void)free (data);
  return status;
}
