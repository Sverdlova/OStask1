#include <stdio.h>

#include <pthread.h>


int size;

int* m;



typedef struct task* task_t;



struct task

{
	
  int start;
	
  int end;

};



void* sort(void* par) {
   task_t t = (task_t)par;
	
   int start = t->start;
	
   int end = t->end;
	
   printf("%d %d\n", start, end);  
   int tmp, i, j, pos;
 
   for(i = start; i < end; ++i){ 
       
     pos = i; 

     tmp = m[i];
    
     for(j = i + 1; j < end; ++j) {
        
        if (m[j] < tmp){
    
          pos = j; 
     
          tmp = m[j]; 
        
        }
    
    }
      
    m[pos] = m[i]; 
     
    m[i] = tmp; 
   
  }

}



void start_sort(){
	
   int midle = size / 2;

   pthread_t th_1, th_2;
	
   task_t t1 = malloc(sizeof(struct task));

   task_t t2 = malloc(sizeof(struct task));
	
   printf("Middle = %d\n", midle);

   t1->start = 0;

   t1->end = midle;
	
   t2->start = midle;
	
   t2->end = size;

 
   int i = pthread_create(&th_1, NULL, &sort, (void*)t1);
 
   i = pthread_create(&th_2, NULL, &sort, (void*)t2);

   pthread_join(th_1, NULL); 
	
   pthread_join(th_2, NULL);
	
   free(t1);
   free(t2);

}



void mergemass(int *dest, int second) {
	
   int c1 = 0, c2 = second;
	
   for (int i = 0; i < size; i++){
		
      if (c1 <= second && c2 <= size){
			
         dest[i] = m[c1] > m[c2] ? m[c2++] : m[c1++];

      }
		
      if (c1 > second && c2 < size) {
			
         dest[i] = m[c2++];
	
      }
		
      if (c1 < second && c2 > size){
	
         dest[i] = m[c1++];
	
      }
	
   }

}



int main(){
	
   scanf("%d", &size);

   printf("Size = %d\n", size);

   m=malloc(sizeof(int) * size);
	
   for (int i=0; i<size; i++){

      scanf("%d", m + i);
	
   }
	
   printf("%s\n");


	
   start_sort();
	
   int *final = malloc(sizeof(int) * size);

   mergemass(final, size / 2);



   for (int i=0; i<size; i++){
		
      printf("%d ", *(m + i));

   }
	
   printf("\n");	

   for (int i=0;i<size;i++){
		
      printf("%d ", *(final + i));
	
   }
	
   printf("\n");
	
   free(m);
	
   free(final);
	
   return 0;


}


