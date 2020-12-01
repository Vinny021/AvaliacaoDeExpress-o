#include <stdio.h> 
#include <string.h> 
#include <ctype.h> 
#include <stdlib.h>

#include "pilha.h"


// Estrutura da pilha
struct pilha 
{ 
	int index_topo; 
	int qtd_char; 
	int* elemento; 
  char* caracter;
}; 


//Função para criação da pilha
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

int esta_vazio(Pilha* pi) 
{ 
	return pi->index_topo == -1 ; 
} 

char retorna_topo(Pilha* pi) 
{ 
	return pi->elemento[pi->index_topo]; 
} 

//Função que adiciona um caracter em uma pilha
void adiciona_caracter(Pilha* pi, char item)
{
  pi->caracter[++pi->index_topo] = item;
}

//Função que remove o caracter do topo da pilha
char remove_caracter(Pilha* pi) 
{  
	return pi->caracter[pi->index_topo--];
} 

//Função que verifica a precedencia das funções
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

//Retira elemento da pilha e retorna ele para ser utilizado
char remove_elemento(Pilha* pi) 
{ 
	if (!esta_vazio(pi)) 
		return pi->elemento[pi->index_topo--];
	return '$'; 
} 

//Recebe uma operação e retorna o resultado
void resolve_conta(Pilha* pi, char op) 
{ 
	pi->elemento[++pi->index_topo] = op; 
} 

//Função que codifica a expreção infixa para posfixa
char* codificador(char* infix){
  int index;
  int i = 0;
  Pilha* B;
  Pilha* A;

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

  return B->caracter;
}

// Função principal que recebe um vetor char e realiza a resolução
int avalia_expressao(char* exp) 
{ 
	// Cria uma Pilha com base no tamanho da expressão 
	Pilha* pi = cria_pilha(strlen(exp)); 
	int i; 

	// Verifica se foi criada corretamente 
	if (!pi) return -1; 

	// Lê cada um dos caracteres 
	for (i = 0; exp[i]; i++) 
	{ 
		//Verifica se o caracter é um numero 
		if (isdigit(exp[i]))

      //Através da operação transforma em inteiro e adiciona na pilha 
			resolve_conta(pi, exp[i] - '0'); 
    
		//Caso em que o caracter é uma operação
		else
		{ 
      //Remove os dois numeros do topo e salva eles em variaveis
			int val1 = remove_elemento(pi); 
			int val2 = remove_elemento(pi); 

      //Analisa qual foi a operação requisitada e realiza ela
			switch (exp[i]) 
			{ 
			case '+': 
        resolve_conta(pi, val2 + val1);
        break; 
			case '-': 
        resolve_conta(pi, val2 - val1);
        break; 
			case '*': 
        resolve_conta(pi, val2 * val1); 
        break; 
			case '/': 
        resolve_conta(pi, val2/val1); 
        break; 
			} 
		} 
	}
  //Remove o ultimo elemento(Resultado) e retorna ele
	return remove_elemento(pi);
  free(pi); 
}