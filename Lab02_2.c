//Kristen Heller 9/3/2019
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define R 15 //30
#define C 15 //40
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
   int length; //empty=0 not_empty>=2 single_node=1
}List;

double ran();//returns a random number
int fill( double ); //returns total number of slots on
void show();
int countInColumn(int, char[][C]); //returns the number of slots on in a column, starting at zero RISK: NO END OF ARRAY CHECK
int burnOut();//returns number of steps it takes to burn out
void lightAdj(Node*, List*); // returns Nodes of the trees that have been lit around the given Node
void add(List*, int, int); //appends new Node to the end of the list with coordinates inputted (r, c)
void process(List*, List*); //changes head of first List from burning to burned, calls lightAdj
void removal(List*); //removes the head of the list
//void transfer(List*, List*);

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
   printf("\n");
   
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
   List* current;
   List* next;
   current = (List*) malloc(sizeof(List));
   next = (List*) malloc(sizeof(List));

   current->length = 0;
   next->length = 0;

   int roundcount = 1;
   
   printf("round 1\n");

   for(int j = 0; j<R; j++)
   {
      if(grid[j][0] == 'T')
      {
         add(current, j, 0);
         grid[j][0] = '*';
      }
   }
   show();
   printf("\n");
   while(current->length > 0)
   {
      roundcount++;
      printf("round %i\n", roundcount);
      while(current->length > 0)
      { // change burning to burned and adjacent to burning
         grid[current->head->r][current->head->c] = 't';
         lightAdj(current->head, next);
         //printf("current length is %i\n", current->length);
         removal(current);
         //printf("current length is %i\n", current->length);
         show();
         //printf("(%i,%i)\n", current->head->r, current->head->c);
      }
      //printf("outed\n");
      //printf("row: %i\ncol: %i\n",current->head->r, current->head->c);
      current = next; //transfer(current, next);//current = next;
      next = (List*) malloc(sizeof(List));
      next -> length = 0 ;
      printf("\n");
   }
}
void process(List* list, List* nxt)//changes head of first List from burning to burned, calls lightAdj
{ //no longer needed
   grid[list->head->r][list->head->c] = 't';
   lightAdj(list->head, nxt); 
}

void removal(List* list) // ERROR
{
   if(list->length == 1)
   {
      printf("removing last node\n");
      list->head = NULL;
   }
   else
   {
      printf("(%i,%i)\n", list->head->next->r, list->head->next->c);
      list->head = list->head->next;
      printf("(%i,%i)\n", list->head->r, list->head->c);
   }
   list->length = list->length-1;
   //free(sto);
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
   printf("added node to list of length %i: ( %i, %i)\n", list->length, n->r, n->c);
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
         printf("(%i, %i)\n", cur->r-1, cur->c);
      }
   }
   
   if(cur->r < R-1)
   {
      if(grid[cur->r+1][cur->c] == 'T')
      {
         add(nxt, cur->r+1, cur->c);
         grid[cur->r+1][cur->c] = '*';
         printf("(%i, %i)\n", cur->r+1, cur->c);
      }
   }
   if(cur->c > 0)
   {
      if(grid[cur->r][cur->c-1] == 'T')
      {
         add(nxt, cur->r, cur->c-1);
         grid[cur->r][cur->c-1] = '*';
         printf("(%i, %i)\n",cur->r, cur->c-1);
      }
   }
   if(cur->c <C-1)
   {
      if(grid[cur->r][cur->c+1] == 'T')
      {
         add(nxt, cur->r, cur->c+1);
         grid[cur->r][cur->c+1] = '*';
         printf("(%i, %i)\n", cur->r, cur->c+1);
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
