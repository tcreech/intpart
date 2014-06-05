#include <intpart.h>
#include <stdio.h>

int main(void){
   float floatpart[3] = {1/3.0 + 1/20.0, 1/2.0 - 1/10.0, 1/6.0 + 1/20.0};
   int intpart[3];
   int n = 240;
   int chunksize = 4;

   printf("floatpart = {%f, %f, %f}\n",
         floatpart[0],
         floatpart[1],
         floatpart[2]
         );
   printf("n = %d\n", n);
   printf("chunksize = %d\n", chunksize);
   printf("\n");

   intpart_from_floatpart_chunked(n, intpart, floatpart, chunksize, 3);

   int sum = 0;
   int i;
   for(i=0; i<3; i++){ sum += intpart[i]; }
   printf("intpart = {%d, %d, %d}; sum = %d\n",
         intpart[0],
         intpart[1],
         intpart[2],
         sum
         );

   printf("equipartitioning gives:\n");
   intpart_equipartition_chunked(n, intpart, chunksize, 3);

   sum = 0;
   for(i=0; i<3; i++){ sum += intpart[i]; }
   printf("intpart = {%d, %d, %d}; sum = %d\n",
         intpart[0],
         intpart[1],
         intpart[2],
         sum
         );

   return 0;
}
