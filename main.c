#include <stdio.h> 
#include <string.h> 
#include <ctype.h> 
#include <stdlib.h>

#include "pilha.h"
 
int main() 
{ 
  int op;
  char* exp;
  char *posfix;
  
  do{
    printf("=== Avaliação de Expressões ===\n");
    printf("1 - Avaliar expressão\n");
    printf("2 - Sair\n");
    printf("Sua escolha: ");
    scanf("%d", &op);
    if(op == 1){
      printf("Digite a expressão: ");
	    scanf("%s", exp);

      posfix = codificador(exp);

	    printf ("\nResultado: %d\n\n", avalia_expressao(posfix));
    }  
  }while(op != 2);
  printf("Até mais!\n");
   
	return 0; 
} 
