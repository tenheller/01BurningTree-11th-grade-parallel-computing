//Kristen Heller 9/17/2019
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define R 30
#define C 40
#define P 0.6
#define T 1000

char grid[R][C];

double ran();//returns a random number
int fill( double ); //returns total number of slots on
void show();
int countInColumn(int, char[][C]); //returns the number of slots on in a column, starting at zero RISK: NO END OF ARRAY CHECK
int burnOut();//returns number of steps it takes to burn out
void lightAdj(int, int); 
int contains(char);//returns 1 or 0; 1 is true, 0 is false

void main()
{
   long long int randseed;
   int totalOn, k, current; 
   double totalp;
   randseed = time(NULL); //switch with student id
   srand(randseed);
   fill(P);
   show();
   printf("\n");
   burnOut();
   
}

int burnOut()
{

   for(int j=0; j<R; j++)
   {
      grid[j][0] = '*';
   }
int r, c;
   do 
   {
      for(r = 0; r<R; r++)
      {
         for(c = 0; c<C; c++)
         {
            if(grid[r][c] == '*') 
            {
               lightAdj(r, c);
               grid[r][c] = 't';
            }
         }
      }
      show();
      printf("\n");
   }while(contains('*')==1);
}
int contains(char cha)
{
   for(int r=0; r<R; r++)
   {
   for(int c=0; c<C; c++)
   {
      if(grid[r][c] == cha) return 1;
   }
   }
   return 0;
}
void lightAdj(int row, int col)
{
   if(row > 0)
   {
      if(grid[row-1][col] == 'T')
      {
         grid[row-1][col] = '*';
      }
   }
   
   if(row < R-1)
   {
      if(grid[row+1][col] == 'T')
      {
         grid[row+1][col] = '*';
      }
   }
   if(col > 0)
   {
      if(grid[row][col-1] == 'T')
      {
         grid[row][col-1] = '*';
      }
   }
   if(col <C-1)
   {
      if(grid[row][col+1] == 'T')
      {
         grid[row][col+1] = '*';
      }
   }

}

double ran()
{
   return rand()*1.0/RAND_MAX;
}

int fill(double p)
{
   int j,k,total;
   total=0;
   for(j=0;j<R;j++)
   {
      for(k=0;k<C;k++)
      {
         if(ran()<p)
         {
            grid[j][k] = 'T';
            total++;
         }
         else
         {
            grid[j][k] = ' ';
         }
      }
   }
   return total;
}   
void show()
{
   int j,k;
   for(j=0;j<R;j++)
   {
      for(k=0; k<C; k++)
      {
         printf("%c", grid[j][k]);
      }
      printf("%s", "\n");
   }
}
int countAdjPrevCol(int col, char grid[][C])
{
   int count, j;
   count=0;
   for(j=0;j<R;j++)
   {
      if(grid[j][col] == 'T')
      {
         if(grid[j][col-1] == 'T')
         {
            count++;
         }
      }
   }
   return count;
}
int countInColumn(int col, char grid[][C])
{
   int count,j;
   count=0;
   for(j=0; j<R; j++)
   {
      if(grid[j][col] == 'T')
      {
         count++;
      }
   }
   return count;
}
