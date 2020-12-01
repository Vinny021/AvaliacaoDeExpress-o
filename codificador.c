#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


struct pilha 
{ 
	int index_topo; 
	int qtd_char; 
	int* elemento;
  char* caracter; 
}; 

typedef struct pilha Pilha;

//Alteração
Pilha* cria_pilha( int qtd_char ) 
{ 
	Pilha* pi = (Pilha*) malloc(sizeof(Pilha)); 

	if (!pi) return NULL; 

	pi->index_topo = -1; 
	pi->qtd_char = qtd_char; 
	pi->elemento = (int*) malloc(pi->qtd_char * sizeof(int));
  pi->caracter = (char*) malloc(pi->qtd_char * sizeof(char)); 

	if (!pi->elemento) return NULL; 

	return pi; 
} 

void resolve_conta(Pilha* pi, char op) 
{ 
	pi->elemento[++pi->index_topo] = op; 
} 

//Novo
void adiciona_caracter(Pilha* pi, char item)
{
  pi->caracter[++pi->index_topo] = item;
}

//Novo
char remove_caracter(Pilha* pi) 
{  
	return pi->caracter[pi->index_topo--];
} 

//Novo
int precedencia(char item)
{
  if(item == '*' || item == '/'){
    return 2;
  }

  else if(item == '+' || item == '-'){
    return 1;
  }

  else{
    return 0;
  }
}

int main(){
  char infix[100];
  int index;
  int i = 0;
  Pilha* B;
  Pilha* A;
  scanf("%s", infix);

  index = strlen(infix);

  B = cria_pilha(index);
  A = cria_pilha(index);

  do{
    if(isdigit(infix[i])){
      adiciona_caracter(B, infix[i]);
    }
    else{

      if(infix[i] == '(')
      {
        adiciona_caracter(A, infix[i]);
      }
      else
      {
        if(infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/')
        {
          if(precedencia(infix[i]) <= precedencia(A->caracter[A->index_topo]))
          {
            do
            {
              char aux = remove_caracter(A);
              adiciona_caracter(B, aux);
            }while(A->index_topo != -1 || precedencia(infix[i]) <= precedencia(A->caracter[A->index_topo]));
          }
          adiciona_caracter(A, infix[i]);
        }
        else
        {
          if(infix[i] == ')')
          {
            do
            {
              char aux = remove_caracter(A);
              adiciona_caracter(B, aux);
            }while(infix[i] == '(');
          }
        }
      }    
    }
    i++;
  }while(i < index);

  do
  {
    char aux = remove_caracter(A);
    adiciona_caracter(B, aux);
  }while(A->index_topo != -1);

  printf("%s\n", B->caracter);
  printf("%s\n", A->caracter);
}