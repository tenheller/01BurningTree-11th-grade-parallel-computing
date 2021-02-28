//Kristen Heller 9/24/2019
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define R 30 
#define C 40 
//#define P 0.6
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
   int length; //empty=0 not_empty>=2 single_node=1
}List;

double ran();//returns a random number
int fill( double ); //returns total number of slots on
void show();
int countInColumn(int, char[][C]); //returns the number of slots on in a column, starting at zero RISK: NO END OF ARRAY CHECK
int burnOut();//returns number of steps it takes to burn out
void lightAdj(Node*, List*); // returns Nodes of the trees that have been lit around the given Node
void add(List*, int, int); //appends new Node to the end of the list with coordinates inputted (r, c)
void removal(List*); //removes the head of the list

void main()
{
   double P;
   long long int randseed;
   int totalOn, k, current; 
   double total;
   randseed = time(NULL); //switch with student id
   srand(randseed);
   //fill(P);
   //show();
   //printf("\n");
   for(P=0; P<1; P = P+.01)
   {
   total = 0;
      for(k=0;k<T;k++)
      {
         fill(P);
         total+=burnOut()/(C*1.0);//normalization by dividing by the width
      }
      //printf("Normalized average over %i trials on a %i by %i grid when P=%f: %f\n", T, R, C, P, total/T);
      printf("%f          %f\n",P,total/T);
   }
   printf("Seed: %lli\nM: %i\nN: %i\nT: %i\ndeltaP: %f",randseed,R,C,T,0.01);
}

int burnOut()
{
   List* current;
   List* next;
   current = (List*) malloc(sizeof(List));
   next = (List*) malloc(sizeof(List));

   current->length = 0;
   next->length = 0;

   int roundcount = 0;
   
   //printf("round 0\n");

   for(int j = 0; j<R; j++)
   {
      if(grid[j][0] == 'T')
      {
         add(current, j, 0);
         grid[j][0] = '*';
      }
   }
   //show();
   //printf("\n");
   while(current->length > 0)
   {
      roundcount++;
      //printf("round %i\n", roundcount);
      while(current->length > 0)
      { 
         grid[current->head->r][current->head->c] = 't';
         lightAdj(current->head, next);
         removal(current);
         //show();
      }
      current = next;
      next = (List*) malloc(sizeof(List));
      next -> length = 0 ;
      //printf("\n");
   }
   //show();
   return roundcount;
}
void removal(List* list)
{
   Node* sto;
   sto = list->head;
   if(list->length == 1)
   {
      list->head = NULL;
   }
   else
   {
      list->head = list->head->next;
   }
   list->length = list->length-1;
   free(sto);
}

void add(List* list, int row, int col)
{
   Node* n = (Node*) malloc(sizeof(Node));
   n->r = row;
   n->c = col;
   if(list->length == 0) //0 is empty
   {
      list->head = n;
   }
   else if(list->length == 1) // 1 is single node list
   {
      list->head->next = n;
      list->end = n;
   }
   else
   {
      list->end->next = n;
      list->end = n;
   }
   list->length++;
}
void lightAdj(Node* cur, List* nxt)
{
   if(cur->r > 0)
   {
      if(grid[cur->r-1][cur->c] == 'T')
      {
         add(nxt, cur->r-1, cur->c);
         grid[cur->r-1][cur->c] = '*';
      }
   }
   
   if(cur->r < R-1)
   {
      if(grid[cur->r+1][cur->c] == 'T')
      {
         add(nxt, cur->r+1, cur->c);
         grid[cur->r+1][cur->c] = '*';
      }
   }
   if(cur->c > 0)
   {
      if(grid[cur->r][cur->c-1] == 'T')
      {
         add(nxt, cur->r, cur->c-1);
         grid[cur->r][cur->c-1] = '*';
      }
   }
   if(cur->c <C-1)
   {
      if(grid[cur->r][cur->c+1] == 'T')
      {
         add(nxt, cur->r, cur->c+1);
         grid[cur->r][cur->c+1] = '*';
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
