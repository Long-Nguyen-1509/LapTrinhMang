#include <stdio.h>

int main(int argc, char *argv[])
{
   FILE *fp;
   char str[60];

   /* mo file de doc */
   fp = fopen(argv[1] , "r");
   if(fp == NULL) 
   {
      perror("Xay ra loi trong khi doc file");
      return(-1);
   }
   if( fgets (str, 60, fp)!=NULL ) 
   {
      /* Ghi noi dung len stdout */
      puts(str);
   }
   fclose(fp);
   
   return(0);
}