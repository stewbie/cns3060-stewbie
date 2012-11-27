#include <pthread.h>
#include <stdio.h>

int count = 0;

void* incrementCounter( void* m ) 
{ 

  int i; 
  for (i = 0; i < 10; ++i) 
  { 
    int tempValue = count; 
    sleep(1); 
    tempValue = tempValue + 1; 
    count = tempValue; 
  }
  
  return NULL; 
}

int main (char argc, char* argv[])
{

  pthread_t thrd1, thrd2, thrd3, thrd4;
  
  pthread_create(&thrd1, NULL, incrementCounter, NULL);
  pthread_create(&thrd2, NULL, incrementCounter, NULL);
  pthread_create(&thrd3, NULL, incrementCounter, NULL);
  pthread_create(&thrd4, NULL, incrementCounter, NULL);
  
  printf("%d\n", count);

  return 0;
}
