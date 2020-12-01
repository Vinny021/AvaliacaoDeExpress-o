typedef struct pilha Pilha;

//Função para alocação de memoria para a pilha
Pilha* cria_pilha( int qtd_char );

//Função responsável por verificar se a pilha está vazia
int esta_vazio(Pilha* pi);

//Retorna o elemento do topo da pilha e remove ele
char remove_elemento(Pilha* pi); 

//Recebe uma operação e salva o valor no topo da pilha
void resolve_conta(Pilha* pi, char op);

//Função responsável por receber a expressão e chamar as outras funções
int avalia_expressao(char* exp);

//Função que vai codificar a expressão infixa para posfixa
char* codificador(char* infix);