#include <pthread.h>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// Thread count.
const int n=3;

// Thread number in FIFO.
int number[n];

// Thread FIFO.
vector<bool> choosing;

// This procedure should be called before entering critical region.
void enter_region (int thread)
{
  int j;
  choosing[thread]=true;
  
  // Getting max thread number in FIFO.
  number[thread] =int(*max_element(choosing.begin(),choosing.end()))+1;//(choosing,[](bool a, bool b){return a<b;}) + 1;
  choosing[thread]=false;
  
  // WHAITING.
  for(j = 0; j < n; j++)
  {
    while(choosing[j]);
    while ((number[j] != 0) && ((number[j] < number[thread]) || ((number[j] == number[thread]) && (j <thread))));
  }
}

// This procedure should be called after leaving critical region.
void leave_region (int thread)
{
  number[thread] = 0;
}


// Shared variable.
int a = 0 ;

// Thread 2 increments shared variable by 2.
void *thread2(void *dummy) 
{
  // Thread id in FIFO.
  const int thread_id = 1;
  
  // Local variable for thread 2.
  int b=0;
  
  enter_region(thread_id);
  
  b = a;
  b=b+2;
  
  // Artificially slow down the thread.
  for (int i=0;i<10000000L;i++);
  
  // Write to shared variable.
  a = b;
  cout<<"Thread "<<thread_id<<". Calculation result = "<<a<<endl;
  leave_region(thread_id);
  return NULL;
}

// Thread 3 increments shared variable by 3.
void *thread3(void *dummy) 
{
  // Thread id in FIFO.
  const int thread_id = 2;
  
  // Local variable for thread 3.
  int b=0;
  
  enter_region(thread_id);

  b = a;
  b=b+3;
  
  // Artificially slow down the thread.
  for (int i=0;i<10000000L;i++);
  
  // Write to shared variable.
  a = b;
  cout<<"Thread "<<thread_id<<". Calculation result = "<<a<<endl;
  leave_region(thread_id);
  
  return NULL;
}

// Main thread aka thread 1. Increments shared variable by 1.
int main() 
{
  //for (int i=0;i<n;i++) choosing[i]=false;
  for (int i=0;i<n;i++) choosing.push_back(false);
  pthread_t th2id, th3id;
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
  
  // Thread id in FIFO.
  const int thread_id = 0;
  // Local variable for thread 1.
  int c=0;
  
  enter_region(thread_id);

  c=a; 
  c=c+1;
  
  // Artificially slow down the thread.
  for (int i=0;i<10000000L;i++);
  
  // Write to shared variable.
  a = c;
  cout<<"Thread "<<thread_id<<". Calculation result = "<<a<<endl;
  leave_region(thread_id);
  // Whaiting to thread 2.
  pthread_join(th2id, (void **)NULL);
  
  // Whaiting to thread 3.
  pthread_join(th3id, (void **)NULL);
  return 0;
}

/*
TASK

Модифицируйте программу из задания 1 для корректной работы с
помощью алгоритма булочной. Проверьте, что после нескольких запусков
ошибки в работе программы не возникают.
*/