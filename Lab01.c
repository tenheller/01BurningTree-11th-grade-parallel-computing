//Kristen Heller 9/3/2019
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define R 30
#define C 40
#define P 0.6
#define T 1000

char grid[R][C];

typedef struct Node
{
   int r, c, num;
   struct Node* next;
}Node;
typedef struct List
{
   Node* head;
   Node* end;
}List;

double ran();//returns a random number
int fill( double ); //returns total number of slots on
void show();
int countInColumn(int, char[][C]); //returns the number of slots on in a column, starting at zero RISK: NO END OF ARRAY CHECK
int burnOut();//returns number of steps it takes to burn out
Node *lightAdj(Node*, int); // returns Nodes of the trees that have been lit around the given Node


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
   
   
   //totalOn = fill(P);
   //show();
   /*for(k=0; k<T; k++)
   {
      current = fill(P);
      totalp = totalp+current;
   }
   printf("Total percent: %f\nAverage Percent: %f", totalp, totalp/(R*C*T));*/
   //printf("%lli\n", randseed);
   //printf("%s","Total On:");
   //printf("%d\n", totalOn);
   //printf("%s", "On in column: ");
   //printf("%d\n", countInColumn(1, grid));
   
}

int burnOut()
{
   Node* curptr;
   Node* nxtptr;
   Node* sto;
   //curptr = (Node*) malloc(sizeof(Node));
   //nxtptr = (Node*) malloc(sizeof(Node));

//add left column trees to curptr and change them from 'T' to '*'
   curptr = nxtptr = (Node*) malloc(sizeof(Node));
   int j, loopnum;
   int first = 1;
   loopnum =1;
   for(j=0; j<R; j++)
   {
      if(grid[j][0] == 'T')
      {
         if(first==1)
         {
            first = 0;
            curptr = sto = (Node*) malloc(sizeof(Node));
            sto->next = nxtptr;
         }
         else
            sto = (Node*) malloc(sizeof(Node));
         (*sto).r = j;
         (*sto).c = 0;
         (*sto).num = loopnum;
         nxtptr->next = sto;
         nxtptr = nxtptr->next;
         grid[j][0] = '*';
      }
   }
   show();
   printf("\n");
   while(curptr != NULL)
   {
      do 
      {
         sto = lightAdj(curptr, loopnum); //append to nxtptr
         nxtptr->next = sto;
         while((*nxtptr).next != NULL) nxtptr = nxtptr->next; //end of append
      
         grid[(*curptr).r][(*curptr).c] = ' ';
         curptr = (*curptr).next;
         show();
         printf("\n");
      }while( curptr != NULL && loopnum==curptr->num);
      show();
      printf("loop: %i\n", loopnum);
      loopnum++;
   }
   show();
   printf("\n");
//while curptr still has Nodes go through each node, 
//    add its adjacent nodes that are 'T' to nxtptr, 
//    then remove the node from curptr and change it from '*' to ' '
//
}
Node *lightAdj(Node* ptr, int loopnum)
{
   Node* sto;
   Node* start;
   Node* end;
   if((*ptr).r > 0)
   {
      if(grid[(*ptr).r-1][(*ptr).c] == 'T')
      {
         sto = (Node*) malloc(sizeof(Node));
         (*sto).r = (*ptr).r-1;
         (*sto).c = (*ptr).c;
         (*sto).num = loopnum;
         grid[(*ptr).r-1][(*ptr).c] = '*';
         printf("(%i, %i)\n", sto->r-1, sto->c);
         if(start == NULL)
            start = end = sto;
         else {
            end->next = sto;
            end = end->next;}
      }
   }
   
   if((*ptr).r < R-1)
   {
      if(grid[(*ptr).r+1][(*ptr).c] == 'T')
      {
         sto = (Node*) malloc(sizeof(Node));
         (*sto).r = (*ptr).r+1;
         (*sto).c = (*ptr).c;
         (*sto).num = loopnum;
         grid[(*ptr).r+1][(*ptr).c] = '*';
         printf("(%i, %i)\n",sto->r+1, sto->c);
         if(start == NULL)
            start = end = sto;
         else {
            end->next = sto;
            end = end->next;}
      }
   }
   if((*ptr).c > 0)
   {
      if(grid[(*ptr).r][(*ptr).c-1] == 'T')
      {
         sto = (Node*) malloc(sizeof(Node));
         (*sto).r = (*ptr).r;
         (*sto).c = (*ptr).c-1;
         grid[(*ptr).r][(*ptr).c-1] = '*';
         printf("(%i, %i)\n",sto->r, sto->c-1);
         if(start == NULL)
            start = end = sto;
         else {
            end->next = sto;
            end = end->next;}
      }
   }
   if((*ptr).c <C-1)
   {
      if(grid[(*ptr).r][(*ptr).c+1] == 'T')
      {
         sto = (Node*) malloc(sizeof(Node));
         (*sto).r = (*ptr).r;
         (*sto).c = (*ptr).c+1;
         grid[(*ptr).r][(*ptr).c+1] = '*';
         printf("(%i, %i)\n",sto->r, sto->c+1);
         if(start == NULL)
            start = end = sto;
         else {
            end->next = sto;
            end = end->next;}
      }
   }
   printf("%lli\n%lli\n", &start, &sto);
   return start;
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
