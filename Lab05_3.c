#include <stdio.h>
void readFile()//1000 line file (1001, but 1001 is empty line)
{
FILE *infile;
float read;
float prev;
float peak;
int k;
infile = fopen("./Lab05.txt", "r");
printf("file opened\n");
fscanf(infile, "%f", &prev);
printf("first scan success\n");
for(k=0; k<999; k++)
{
fscanf(infile, "%f", &read);
if(read>=prev)
{
   if(read>=peak)
      peak = read;
   else
      printf("read is less than peak and greater than prev");
}
else //if(read<prev)
{
   if(read>peak)
      printf("read is less than prev and greater than peak");
}
prev = read;
}
printf("peak is: %f\n", peak);
}
void main()
{
readFile();
}