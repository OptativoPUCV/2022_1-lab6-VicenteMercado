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

int is_valid(Node* n){
  int array[10];
  int i,j,k,m;
  
  for(i=0;i<9;i++) //FILAS
  { 
    for(k=0;k<10;k++){
      array[k]=0;
    }
    
    for(j=0;j<9;j++){
      if(n->sudo[i][j]!=0){
        if(array[n->sudo[i][j] ] == 1) return 0;
        else array[n->sudo[i][j]] = 1;
      }
    }
  }

  for(i=0;i<9;i++) //COLUMNAS
  { 
    for(k=0;k<10;k++){
      array[k]=0;
    }
    
    for(j=0;j<9;j++){
      if(n->sudo[j][i]!=0){
        if(array[n->sudo[j][i] ] == 1) return 0;
        else array[n->sudo[j][i]] = 1;
      }
    }
  }

  for(m=0;m<9;m++){ //SUBMATRICES
    for(k=0;k<10;k++){
      array[k]=0;
    }
    for(int p=0;p<9;p++){
      int r = 3*(m/3)+(p/3);
      int q = 3*(m%3)+(p%3);
      if(n->sudo[r][q]!=0){
        if(array[n->sudo[r][q] ] == 1) return 0;
        else array[n->sudo[r][q]] = 1;
      }
    }
  }  
    return 1;
}


List* get_adj_nodes(Node* n){
    List* list=createList();
    int i,j,k;
    for(i=0;i<9;i++){
      for(j=0;j<9;j++){
        if(n->sudo[i][j]==0){
          for(k=1;k<10;k++){
            n->sudo[i][j]=k;
            if(is_valid(n)){
              Node*adj=copy(n);
              pushBack(list,adj);
            }
          }
          n->sudo[i][j]=0;
          return list;
        }
      }
    }
    return list;
}


int is_final(Node* n){
  int i,j;
  for(i=0;i<9;i++){
    for(j=0;j<9;j++){
      if(n->sudo[i][j] == 0) return 0;
    }
  }
  return 1;
}

Node* DFS(Node* initial, int* cont){
  Stack* pila = createStack();
  push(pila,initial);
  int tamanyoP = get_size(pila);
  while(tamanyoP >0){
    Node* nodo = first(pila);
    popFront(pila);
    if (is_final(nodo)) continue;

    List* adj = get_adj_nodes(nodo);
    Node* aux = first(adj);

    while(aux){
      push(pila,aux);
      aux=next(adj);
    }

    free(aux);

  }
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/