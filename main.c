#include <stdio.h> 
#include <string.h> 
#include <ctype.h> 
#include <stdlib.h>

#include "pilha.h"
 
int main() 
{ 
  int op;
  char* exp;
  
  do{
    printf("=== Avaliação de Expressões ===\n");
    printf("1 - Avaliar expressão\n");
    printf("2 - Sair\n");
    printf("Sua escolha: ");
    scanf("%d", &op);
    if(op == 1){
      printf("Digite a expressão: ");
	    scanf("%s", exp);

	    printf ("Resultado: %d\n", avalia_expressao(exp));
    }  
  }while(op != 2);
  printf("Até mais!\n");
   
	return 0; 
} 
