#include <pthread.h>
#include <iostream>

using namespace std;

// Shared variable.
int a = 0 ;

// Thread 2 increments shared variable by 2.
void *thread2(void *dummy) 
{
  pthread_t mythid;
  
  // Local variable for thread 2.
  int b=0;
  
  // Getting thread ID.
  mythid = pthread_self();
  b = a;
  b=b+2;
  
  // Artificially slow down the thread.
  for (int i=0;i<10000000L;i++);
  
  // Write to shared variable.
  a = b;
  cout<<"Thread "<<mythid<<". Calculation result = "<<a<<endl;
  return NULL;
}

// Thread 3 increments shared variable by 3.
void *thread3(void *dummy) 
{
  pthread_t mythid;
  
  // Local variable for thread 3.
  int b=0;
  
  // Getting thread ID.
  mythid = pthread_self();
  b = a;
  b=b+3;
  
  // Artificially slow down the thread.
  for (int i=0;i<10000000L;i++);
  
  // Write to shared variable.
  a = b;
  cout<<"Thread "<<mythid<<". Calculation result = "<<a<<endl;
  return NULL;
}

// Main thread aka thread 1. Increments shared variable by 1.
int main() 
{
  pthread_t th1id, th2id, th3id;
  int result;
  
  // Create thread 2.
  result = pthread_create(&th2id, (pthread_attr_t *)NULL, thread2,NULL);
  if(result != 0)
  {
    cout<<"Error on thread create, return value = "<<result<<endl;
    return -1;
  }
  
  // Create thread 3.
  result = pthread_create(&th3id, (pthread_attr_t *)NULL, thread3,NULL);
  if(result != 0)
  {
    cout<<"Error on thread create, return value = "<<result<<endl;
    return -1;
  }
  
  // Local variable for thread 1.
  int c=0;
  
  // Getting thread ID.
  th1id = pthread_self();
  c=a; 
  c=c+1;
  
  // Artificially slow down the thread.
  for (int i=0;i<10000000L;i++);
  
  // Write to shared variable.
  a = c;
  cout<<"Thread "<<th1id<<". Calculation result = "<<a<<endl;
  
  // Whaiting to thread 2.
  pthread_join(th2id, (void **)NULL);
  
  // Whaiting to thread 3.
  pthread_join(th3id, (void **)NULL);
  return 0;
}