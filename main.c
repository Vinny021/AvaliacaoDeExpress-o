#include <stdio.h> 
#include <string.h> 
#include <ctype.h> 
#include <stdlib.h> 

// Estrutura da pilha
struct pilha 
{ 
	int index_topo; 
	int qtd_char; 
	int* elemento; 
}; 

typedef struct pilha Pilha;
 
Pilha* cria_pilha( int qtd_char ) 
{ 
	Pilha* pi = (Pilha*) malloc(sizeof(Pilha)); 

	if (!pi) return NULL; 

	pi->index_topo = -1; 
	pi->qtd_char = qtd_char; 
	pi->elemento = (int*) malloc(pi->qtd_char * sizeof(int)); 

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

//Retira elemento da pilha e retorna ele para ser utilizado
char remove_elemento(Pilha* pi) 
{ 
	if (!esta_vazio(pi)) 
		return pi->elemento[pi->index_topo--] ; 
	return '$'; 
} 

//Recebem uma operação e retorna o resultado
void resolve_conta(Pilha* pi, char op) 
{ 
	pi->elemento[++pi->index_topo] = op; 
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
} 
 
int main() 
{ 
  char exp[100];
  
  printf("Digite a expressão: ");
	scanf("%s", exp);

	printf ("Resultado: %d\n", avalia_expressao(exp)); 
	return 0; 
} 
