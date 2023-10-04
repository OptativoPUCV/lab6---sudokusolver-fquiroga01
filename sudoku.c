#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n)
{
    int filaVerificada[9][9] = {0};
    int columnaVerificada[9][9] = {0};

    for (int i = 0 ; i < 9 ; i++)
      {
        for (int j = 0 ; j < 9 ; j++)
          {
            int numero = n->sudo[i][j];
            if (numero != 0)
            {
              if (filaVerificada[i][numero] == 1)
              {
                return 0;
              }
              filaVerificada[i][numero] = 1;
              if (columnaVerificada[j][numero] == 1)
              {
                return 0;
              }
              columnaVerificada[j][numero] = 1;
            }
          }
      }
    return 1;
}


List* get_adj_nodes(Node* n)
{
    List* list=createList();

    for (int i = 0 ; i < 9 ; i++)
      {
        for (int j = 0 ; j < 9 ; j++)
          {
            if (n->sudo[i][j] == 0)
            {
              Node* adj_node = copy(n);
              adj_node->sudo[i][j] = i;
              if (is_valid(adj_node))
              {
                pushBack(list, adj_node);
              }
              else
              {
                free(adj_node);
              }
            }
          }
      }
    return list;
}


int is_final(Node* n)
{
    for (int i = 0 ; i < 9 ; i++)
      {
        for (int j = 0 ; j < 9 ; j++)
          {
            if (n->sudo[i][j] == 0)
            {
              return 0;
            }
          }
      }
  return 1;
}

Node* DFS(Node* initial, int* cont)
{
  Stack * stack = createStack();
  push(stack, initial);

  while (!is_empty(stack))
    {
      Node* nodoActual = top(stack);
      pop(stack);
      (*cont)++;
      if (is_final(nodoActual))
      {
        free(stack);
        return nodoActual;
      }
      List* adj_nodes = get_adj_nodes(nodoActual);
      while (!is_empty(adj_nodes))
        {
          Node* adj_node = front(adj_nodes);
          popFront(adj_nodes);
          push(stack, adj_nodes);
        }
      free(adj_nodes);
      free(nodoActual);
    }
  
  
  return NULL;
}


int main( int argc, char *argv[] )
{

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}