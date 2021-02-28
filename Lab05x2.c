#include <stdio.h>
void readFile(int dim)//100 line file (101, but 101 is empty line)//each line has decimal fill space value
{
FILE *infile;
float read;
float prev;
float peak;
int k;
char str[] = "./Lab05Data/oo0xoo0.txt";//{'.','/','L','a','b','0','5','D','a','t','a','/',(char)(dim/10), (char)dim%10, '0','x',(char)(dim/10),(char)dim%10,'0','.','t','x','t','\0'}; 
str[13] =(char) (dim/10);
str[14] =(char) (dim%10);
str[17] =(char) (dim/10);
str[18] =(char) (dim%10);
infile = fopen(str, "r");
printf("file opened\n");
fscanf(infile, "%f", &prev);
fscanf(infile, "%f", &prev);
printf("first scan success\n");
for(k=0; k<99; k++)
{
   fscanf(infile, "%f", &read);
printf("%i",fscanf(infile, "%f", &read));
if(read>=prev)
{
   if(read>=peak)
      peak = read;
   else
      printf("read is less than peak and greater than prev\n");
}
else //if(read<prev)
{
   if(read>peak)
      printf("read is less than prev and greater than peak\n");
}
prev = read;
}
printf("%i0 by %i0 peak is: %f\n", dim, dim, peak);
}
void main()
{
   for(int j = 1; j<26; j++)
readFile(j);
}