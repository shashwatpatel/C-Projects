#include <stdio.h>
#include <stdlib.h>

int main(){
  FILE *ptr1, *ptr2; //Data is stored here
  char fname[50], f; //Array of 50 chars for a filename 
  printf("Enter the name of input filename: \n");
  scanf("%s", fname);

  ptr1 = fopen(fname, "r"); //Opens inputfile for reading contents
  //Check to see if the file eists
  if(ptr1 == NULL) {
     printf("File not found %s\n", fname );
     exit(0);
}

printf("Enter the file name you want to copy contents to: \n");
scanf("%s", fname);

ptr2 = fopen(fname, "w"); //Opens outputfile for writing contents
//Check to see if the file exists
if(ptr2 == NULL) {
   printf("File not found %s\n", fname );
   exit(0);
}
//Read from file, COURTESY OF: https://www.programmingsimplified.com/c-program-read-file
f = fgetc(ptr1);
//Check to see if we are at the end of file, if not then copy contents
while (f!= EOF) {
fputc(f, ptr2);
f = fgetc(ptr1);
}
printf("Contents were copied to %s \n", fname);
//Close both files
fclose(ptr1);
fclose(ptr2);
return 0;
}
