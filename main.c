#include <stdio.h> 
#include <string.h> 
#include <ctype.h> 
#include <stdlib.h> 

// Pilha type 
struct pilha 
{ 
	int inicio; 
	unsigned qtd_char; 
	int* array; 
}; 

typedef struct pilha Pilha;

// Pilha Operations 
Pilha* cria_pilha( unsigned qtd_char ) 
{ 
	Pilha* stack = (Pilha*) malloc(sizeof(Pilha)); 

	if (!stack) return NULL; 

	stack->inicio = -1; 
	stack->qtd_char = qtd_char; 
	stack->array = (int*) malloc(stack->qtd_char * sizeof(int)); 

	if (!stack->array) return NULL; 

	return stack; 
} 

int isEmpty(Pilha* stack) 
{ 
	return stack->inicio == -1 ; 
} 

char peek(Pilha* stack) 
{ 
	return stack->array[stack->inicio]; 
} 

char pop(Pilha* stack) 
{ 
	if (!isEmpty(stack)) 
		return stack->array[stack->inicio--] ; 
	return '$'; 
} 

void push(Pilha* stack, char op) 
{ 
	stack->array[++stack->inicio] = op; 
} 


// The main function that returns value of a given postfix expression 
int evaluatePostfix(char* exp) 
{ 
	// Create a stack of qtd_char equal to expression size 
	Pilha* stack = cria_pilha(strlen(exp)); 
	int i; 

	// See if stack was created successfully 
	if (!stack) return -1; 

	// Scan all characters one by one 
	for (i = 0; exp[i]; ++i) 
	{ 
		// If the scanned character is an operand (number here), 
		// push it to the stack. 
		if (isdigit(exp[i])) 
			push(stack, exp[i] - '0'); 

		// If the scanned character is an operator, pop two 
		// elements from stack apply the operator 
		else
		{ 
			int val1 = pop(stack); 
			int val2 = pop(stack); 
			switch (exp[i]) 
			{ 
			case '+': push(stack, val2 + val1); break; 
			case '-': push(stack, val2 - val1); break; 
			case '*': push(stack, val2 * val1); break; 
			case '/': push(stack, val2/val1); break; 
			} 
		} 
	} 
	return pop(stack); 
} 

// Driver program to test above functions 
int main() 
{ 
  char exp[100];
  printf("Digite a expressão: ");
	scanf("%s", exp);

	printf ("Resultado: %d\n", evaluatePostfix(exp)); 
	return 0; 
} 
