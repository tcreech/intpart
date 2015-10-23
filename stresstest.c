#include "intpart.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <omp.h>

void printout(int *intpart, float *floatpart, int l){
   int i;
   printf("intpart = {");
   for(i=0; i<l; i++){
      printf("%d",intpart[i]);
      if(i<l-1)
         printf(", ");
   }
   printf("};\n");

   printf("floatpart = {");
   for(i=0; i<l; i++){
      printf("%02.2f",floatpart[i]);
      if(i<l-1)
         printf(", ");
   }
   printf("};\n");
}

int main(void){
    float total_mtests = 0;

#pragma omp parallel
   {
      unsigned int seed;
      double last_print = omp_get_wtime();
      unsigned testcount = 0;
      unsigned lasttestcount = testcount;
      seed = time(NULL);
      float *floatpart = malloc(0);
      int *intpart = malloc(0);
      float my_mtests = 0;

      unsigned j;
      for(j=0; j<1024*1024*1024; j++){

         int n = (rand_r(&seed) % 64) + 1;
         int len = (rand_r(&seed) % n) + 1;
         if(len/4 > 0 && n / (len/4) > 0)
            len = len / 4;
         int chunk = (rand_r(&seed) % (n / len)) + 1;
         floatpart = realloc(floatpart, sizeof(float)*len);
         intpart = realloc(intpart, sizeof(int)*len);
         int i;
         for(i=0; i<len; i++){
            floatpart[i] = 1e-9 + ((double)rand_r(&seed) / (double)RAND_MAX) * len;
         }

         int ret;
         ret = intpart_from_floatpart_chunked_normalized(n, intpart, floatpart, chunk, 0, len);
         if(ret != 0)
            printf("len=%d, n=%d, chunk=%d, returned %d.\n",
                  len, n, chunk, ret);
         testcount++;
         double now = omp_get_wtime();
         if(now - last_print > 4.0){
#pragma omp critical
            {
               total_mtests -= my_mtests;
               my_mtests = (double)(testcount-lasttestcount)/(double)(now - last_print)*1e-6;
               total_mtests += my_mtests;

               printf("Thread %d: %1.3f Mtests/s. Total: %1.3f Mtests/s.\n", omp_get_thread_num(), my_mtests, total_mtests);
               lasttestcount = testcount;
               last_print = now;

               printf("len=%d, chunk=%d, n=%d\n", len, chunk, n);
               printout(intpart, floatpart, len);
               printf("\n");
            }
         }
      }
   }

}
