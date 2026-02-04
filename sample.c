#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main () {
  int value = 1;
  int *value_pointer = &value;
  int **last = &value_pointer;

  printf("Value address %d \n", &value);
  printf("Address %d \n", &value_pointer);
  printf("Adress new %d \n", *last);


  int *next = *last;

  printf("Check next address %d", &next);

  printf("Value of current value pointer before setting to NULL %d \n", value_pointer);
  *last = NULL;

  printf("Value of current value pointer %d \n", value_pointer);


  int a;
  int *b =  (int*)malloc(sizeof(int));

  printf("%d", b);
  printf("value of int %d", a);

  for (int i=0; i < 10000000; i++) {

  }


  printf("For Loop Is Also Done Running\n");

  time_t count;

  count = time(NULL);

  printf("Time is %d\n", count);
}
