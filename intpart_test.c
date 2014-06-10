#include <intpart.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv){
   int l = argc-1;
   if(l <= 0){
      printf("Need some floats!\n");
      return 1;
   }

   float* floatpart;
   int* intpart;

   floatpart = malloc(sizeof(float) * l);
   intpart = malloc(sizeof(int) * l);

   int argi;
   for(argi=1; argi<argc; argi++){
      floatpart[argi-1] = atof(argv[argi]);
   }

   int n = 240;
   int chunksize = 1;
   char *chunksizeenv = getenv("CHUNKSIZE");
   if(chunksizeenv)
      chunksize=atoi(chunksizeenv);
   if(!chunksize >= 1){
      printf("invalid chunksize! must be >= 1.\n");
      free(floatpart);
      free(intpart);
      return 1;
   }
   char *nenv = getenv("N");
   if(nenv)
      n = atoi(nenv);
   if(!n >= 1){
      printf("invalid n value! must be >= 1.\n");
      free(floatpart);
      free(intpart);
      return 1;
   }

   printf("floatpart = {%f, %f, %f}\n",
         floatpart[0],
         floatpart[1],
         floatpart[2]
         );
   printf("n = %d\n", n);
   printf("chunksize = %d\n", chunksize);
   printf("\n");

   intpart_from_floatpart_chunked(n, intpart, floatpart, chunksize, l);

   int sum = 0;
   int i;
   for(i=0; i<l; i++){ sum += intpart[i]; }
   printf("intpart = {");
   for(i=0; i<l; i++){
      printf("%d",intpart[i]);
      if(i<l-1)
         printf(", ");
   }
   printf("}; sum = %d\n\n", sum);

   printf("equipartitioning gives:\n");
   intpart_equipartition_chunked(n, intpart, chunksize, l);

   sum = 0;
   for(i=0; i<l; i++){ sum += intpart[i]; }
   printf("intpart = {");
   for(i=0; i<l; i++){
      printf("%d",intpart[i]);
      if(i<l-1)
         printf(", ");
   }
   printf("}; sum = %d\n", sum);

   float normweight = 0.0;
   printf("weighted with %02.2f gives:\n", normweight);
   intpart_from_floatpart_chunked_normalized(n, intpart, floatpart, chunksize, normweight, l);

   sum = 0;
   for(i=0; i<l; i++){ sum += intpart[i]; }
   printf("intpart = {");
   for(i=0; i<l; i++){
      printf("%d",intpart[i]);
      if(i<l-1)
         printf(", ");
   }
   printf("}; sum = %d\n", sum);

   free(floatpart);
   free(intpart);
   return 0;
}
