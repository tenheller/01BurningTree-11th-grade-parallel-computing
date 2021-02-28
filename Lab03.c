//Kristen Heller 9/26/2019
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define M 150
#define N 150
#define T 1000
#define deltaP 0.01
char grid[M][N];

typedef struct Node
{
   int r, c, num;
   struct Node* next;
}Node;

typedef struct List
{
   Node* head, *end;
   int length;
}List;
double ran();
int fill(double);
void show();
int burnOut();
void lightAdj(Node*,List*);
void add(List*, int, int);
void removal(List*);
void main()
{
   double P;
   long long int randseed;
   int totalOn, k;
   double total;
   randseed = time(NULL);
   srand(randseed);
   for(P=0;P<1;P=P+deltaP)
   {
      total=0;
      for(k=0;k<T;k++)
      {
         fill(P);
         total+=burnOut()/(N*1.0);
      }
      //printf("%f\t%f\n",P,total/T);
      printf("%f\n", total/T);
   }
   printf("Random Seed = %lli\nM = %i\nN = %i\nT = %i\ndelta P = %f\n",randseed,M,N,T,deltaP);
}
int burnOut()
{
   List* current, *next;
   current = (List*) malloc(sizeof(List));
   next = (List*) malloc(sizeof(List));
   current->length = 0;
   next->length = 0;
   int roundcount = 0;
   for(int j=0; j<M; j++)
      if(grid[j][0] == 'T')
      {
         add(current, j, 0);
         grid[j][0] = '*';
      }
   while(current->length >0)
   {
      roundcount++;
      while(current->length >0)
      {
         grid[current->head->r][current->head->c] = 't';
         lightAdj(current->head, next);
         removal(current);
      }
      free(current);
      current = next;
      next = (List*) malloc(sizeof(List));
      next->length = 0;
   }
   return roundcount;
}
void removal(List* list)
{
   Node* sto;
   sto = list->head;
   if(list->length == 1)
      list->head = NULL;
   else
      list->head = list->head->next;
   list->length = list->length-1;
   free(sto);
}
void add(List* list, int row, int col)
{
   Node* n = (Node*) malloc(sizeof(Node));
   n->r = row;
   n->c = col;
   if(list->length == 0)
   {
      list->head = n;
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
   if(cur->r>0 && grid[cur->r-1][cur->c] == 'T')
   {
      add(nxt, cur->r-1, cur->c);
      grid[cur->r-1][cur->c] = '*';
   }
   if(cur->r < M-1 && grid[cur->r+1][cur->c] == 'T')
   {
      add(nxt, cur->r+1, cur->c);
      grid[cur->r+1][cur->c] = '*';
   }
   if(cur->c > 0 && grid[cur->r][cur->c-1] == 'T')
   {
      add(nxt, cur->r, cur->c-1);
      grid[cur->r][cur->c-1]='*';
   }
   if(cur->c < N-1 && grid[cur->r][cur->c+1] =='T')
   {
      add(nxt, cur->r, cur->c+1);
      grid[cur->r][cur->c+1] = '*';
   }
}
double ran()
{
   return rand()*1.0/RAND_MAX;
}
int fill(double p)
{
   int j, k, total;
   total = 0;
   for(j=0;j<M;j++)
      for(k=0;k<N;k++)
         if(ran()<p)
         {
            grid[j][k] = 'T';
            total++;
         }
         else
            grid[j][k]=' ';
   return total;
}
void show()
{
   int j, k;
   for(j=0; j<M; j++)
   {
      for(k=0; k<N; k++)
         printf("%c", grid[j][k]);
      printf("%s", "\n");
   }
}