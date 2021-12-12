%{

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/* int - 0
 float - 1
 string - 2
*/

// estrutura de uma variável 
typedef struct vars { 
    int nodetype;     // Qual o tipo de nó está na árvore
    char name[50];
    double valor;
    char valors[1000];
    double *vet;
    struct vars *prox;
} VARI;

//nova variável FLOAT
VARI *ins_float(VARI *l, char n[]) {
  VARI *neww = (VARI *)malloc(sizeof(VARI)); 
  
  strcpy(neww->name, n);
  neww->prox = l;
  neww->nodetype = 1;

  return neww;
}

// nova variável INT
VARI *ins_int(VARI *l, char n[]) {
  VARI *new = (VARI *)malloc(sizeof(VARI)); 
  
  strcpy(new->name, n);
  new->prox = l;
  new->nodetype = 0;
  
  return new;
}

// nova variável STRING
VARI *ins_string(VARI *l, char n[]) {
  VARI *new = (VARI *)malloc(sizeof(VARI)); 

  strcpy(new->name, n);
  new->prox = l;
  new->nodetype = 2;
  
  return new;
}

// busca uma variável na lista de variáveis
VARI *srch(VARI *l, char n[]) {
  VARI *aux = l;

  while(aux != NULL) {
    if(strcmp(n, aux->name) == 0)
      return aux;
    aux = aux->prox;
  }

  return aux;
}

typedef struct ast {
  int nodetype;
  struct ast *l;
  struct ast *r;
} Ast;

// Estrutura de um número
typedef struct numval {
  int nodetype;   //para dizer que é um número
  double valor;
} Numval;

// Estrutura de um nome de variável, nesse exemplo uma variável é um número no vetor var[50]
typedef struct varval {
  int nodetype;
  char var[50];
  int size;
  Ast *length;
} Varval;

// Estrutura de um texto
typedef struct texto {
  int nodetype;
  char txt[50];
} TXT;

// Estrutura de um desvio (if/else/while)
typedef struct flow {     //Estrutura de um fluxo
  int nodetype;
  Ast *cond; // Ponteiro p/ condição como se fosse IF(condição)
  Ast *tl;   // then, ou seja, verdade/ guarda o que for verdade... faça isso...
  Ast *el;   // else/ guarda o que não for entender a condição.
} Flow;

// Estrutura para um nó de atribuição. Para atrubuir o valor de v em s
typedef struct symasgn {    //quando tiver uma atribuição guardar nesta estrutura
  int nodetype;
  char s[50];
  Ast *v;
  int pos;
  Ast *indice;
} Symasgn;

// Variáveis
VARI *l1; 
VARI *aux;

// Função para criar um nó recebendo parâmetros da estrutura AST
Ast *newast(int nodetype, Ast *l, Ast *r) { 
  Ast *a = (Ast *)malloc(sizeof(Ast));

  if (!a) {
    printf("out of space");
    exit(0);
  }
  a->nodetype = nodetype;
  a->l = l;
  a->r = r;

  return a;
}

// Função de que cria uma nova variável
Ast *newvari(int nodetype, char nome[50]) {
  Varval *a = (Varval *)malloc(sizeof(Varval));

  if (!a) {
    printf("out of space");
    exit(0);
  }
  a->nodetype = nodetype;
  strcpy(a->var, nome);

  return (Ast *)a;
}

// Função de que cria um novo número
Ast *newnum(double d) {
  Numval *a = (Numval *)malloc(sizeof(Numval));

  if(!a) {
    printf("out of space");
    exit(0);
  }
  a->nodetype = 'K'; //Se o nodetype for K, então ele é um número
  a->valor = d;

  return (Ast *)a;
}

// Função que cria um nó de if/else/while. Quando aparecer uma mudança de fluxo
Ast *newflow(int nodetype, Ast *cond, Ast *tl, Ast *el) {  //passa tipo, condição, ponteiro p/verdade e p/falso. Passa o nodetype e o ponteiro como parametro
  Flow *a = (Flow *)malloc(sizeof(Flow));

  if(!a) {
      printf("out of space");
      exit(0);
  }
  a->nodetype = nodetype;
  a->cond = cond;
  a->tl = tl;
  a->el = el;

  return (Ast *)a;
}

// Função que cria um nó para testes
Ast *newcmp(int cmptype, Ast *l, Ast *r) { //fluxo comparação/ cmptype -> tipo símbolos (<>+)
  Ast *a = (Ast *)malloc(sizeof(Ast));
  
  if(!a) {
      printf("out of space");
      exit(0);
  }
  a->nodetype = '0' + cmptype;
  a->l = l;
  a->r = r;
  
  return a;
}

// Função para um nó de atribuição
Ast *newasgn(char s[50], Ast *v) { //parâmetros vão receber nome da variável s[50] e o valor da atribuição *v e o nodetype é o “=”)
  Symasgn *a = (Symasgn *)malloc(sizeof(Symasgn));
  if(!a) {
    printf("out of space");
    exit(0);
  }
  a->nodetype = '=';
  strcpy(a->s, s);
  a->v = v; // Valor
  
  return (Ast *)a;
}

// Função para um nó de atribuição
Ast *newasgnString(char s[50], Ast *v) {  // Declaração de string asgn
  Symasgn *a = (Symasgn *)malloc(sizeof(Symasgn));
  if (!a) {
    printf("out of space");
    exit(0);
  }
  a->nodetype = 'a';
  strcpy(a->s, s);
  a->v = v; 
 
  return (Ast *)a;
}

// Função que recupera o nome/referência de uma variável, neste caso o número
Ast *newValorVal(char s[]) { // quando precisa recuperar um valor da variável
  Varval *a = (Varval *)malloc(sizeof(Varval));
  
  if(!a) {
    printf("out of space");
    exit(0);
  }
  a->nodetype = 'N';
  strcpy(a->var, s);

  return (Ast *)a;
}
// Função que recupera o nome/referência de uma variável, neste caso o número
Ast *recupera_Nome_ref_vari_str(char s[50]) { 
  Varval *a = (Varval *)malloc(sizeof(Varval));

  if(!a) {
    printf("out of space");
    exit(0);
  }
  a->nodetype = 'Q';
  strcpy(a->var, s);

  return (Ast *)a;
}

Ast *searchVar(int nodetype, char s[50]) {
  Symasgn *a = (Symasgn *)malloc(sizeof(Symasgn));

  if (!a) {
    printf("out of space");
    exit(0);
  }
  a->nodetype = nodetype;
  strcpy(a->s, s);

  return (Ast *)a;
}

// Função que executa operações a partir de um nó
char *eval2(Ast *a) { // é chamada executando só um nó da árvore (start) depois disso começa a execução
  VARI *aux1;
  char *v2;

  switch(a->nodetype) { // para pegar o nodetype do nó (ex: Q)
    case 'Q':
      aux1 = srch(l1, ((Varval *)a)->var);
      return aux1->valors;
      break;

    default:
      printf("internal error: bad node %c\n", a->nodetype);
      break;
  }

  return v2;
}
//Função que avalia o nó da árvore com a operação
double evalAux(Ast *a) {
  double v;
  double value;
  char v1[50];
  char *v2;
  VARI *aux1;

  if(!a) {
    printf("internal error, null eval");
    return 0.0;
  }

  switch(a->nodetype) {
    case 'K': // Recupera um número
      v = ((Numval *)a)->valor;
      break; 
    case 'N':
      aux1 = srch(l1, ((Varval *)a)->var);
      v = aux1->valor;
      break;

    case 'n':
      aux1 = srch(l1, ((Varval *)a)->var);
      v = aux1->vet[((Varval *)a)->size];
      break;

    case '+': v = evalAux(a->l) + evalAux(a->r); break; 
    case '-': v = evalAux(a->l) - evalAux(a->r); break; 
    case '*': v = evalAux(a->l) * evalAux(a->r); break; 
    case '/': v = evalAux(a->l) / evalAux(a->r); break;
    case '%': v = (int) evalAux(a->l) % (int) evalAux(a->r); break;
    case '^': v = pow(evalAux(a->l), evalAux(a->r)); break;
    case '~': v = pow(evalAux(a->l), (1 / evalAux(a->r))); break;
    case 'M': v = -evalAux(a->l); break;
	// Operações lógicas. "árv esq   >   árv dir"  Se verdade 1, falso 0 
    case '1': v = (evalAux(a->l) > evalAux(a->r)) ? 1 : 0; break; // sig. se o valor da esq > direita
    case '2': v = (evalAux(a->l) < evalAux(a->r)) ? 1 : 0; break;
    case '3': v = (evalAux(a->l) != evalAux(a->r)) ? 1 : 0; break;
    case '4': v = (evalAux(a->l) == evalAux(a->r)) ? 1 : 0; break;
    case '5': v = (evalAux(a->l) >= evalAux(a->r)) ? 1 : 0; break;
    case '6': v = (evalAux(a->l) <= evalAux(a->r)) ? 1 : 0; break;
   
    default:
      printf("EVAL1: internal error: bad node %c\n", a->nodetype);
      break;
  }

  return v;
}

char *recupera_decStrg(Ast *a) { // recuperar uma decl string
  char *v = (char *)malloc(1000 * sizeof(char));
  double value;
  VARI *aux1;

  if(!a) {
    printf("internal error, null eval");
    return NULL;
  }

  switch(a->nodetype) {
    case '$':
      return ((TXT *)a->l)->txt;
      break;
    case '7':
      value = evalAux(a->l);
      sprintf(v, "%.2lf", value);
      break;
    case '8':
      value = evalAux(a->l);
      sprintf(v, "%.0lf", value);
      break;
    case '9':
      aux1 = srch(l1, ((Symasgn *)(a->l))->s);
      if (aux1->nodetype == 2)
        return aux1->valors;
      else
        printf("Variável não é do tipo String %c\n", a->nodetype);
      break;
    default:
      printf("STRING: internal error: bad node %c\n", a->nodetype);
      break;
  }

  return v;
}

// Função que executa operações a partir de um nó
double eval(Ast *a) {
  double v;
  double value;
  char v1[50];
  char *v2;
  VARI *aux1;

  if(!a) {
    printf("internal error, null eval");
    return 0.0;
  }

  switch(a->nodetype) {
    case 'K':
      v = ((Numval *)a)->valor;
      break; /*Recupera um número*/
    case 'N':
      aux1 = srch(l1, ((Varval *)a)->var);  //faz a conversão de varval, pegando o var e busca na lista de variaveis
      v = aux1->valor;
      break;
    case 'n':
      aux1 = srch(l1, ((Varval *)a)->var);
      value = eval(((Varval *)a)->length);
      v = aux1->vet[(int)value];
      break;

    case '+': v = eval(a->l) + eval(a->r); break;   // adição chama eval p/ esquerda + eval p/ direita
    case '-': v = eval(a->l) - eval(a->r); break;
    case '*': v = eval(a->l) * eval(a->r); break;
    case '/': v = eval(a->l) / eval(a->r); break;
    case '%': v = (int)eval(a->l) % (int)eval(a->r); break;
    case '^': v = pow(eval(a->l), eval(a->r)); break;
    case '~': v = pow(eval(a->l), (1 / eval(a->r))); break;
    case 'M': v = -eval(a->l); break;

    case '1': v = (eval(a->l) > eval(a->r)) ? 1 : 0; break;   //saber se o valor da esq é maior que o da direita(verdade 1/ falso 0)
    case '2': v = (eval(a->l) < eval(a->r)) ? 1 : 0; break;
    case '3': v = (eval(a->l) != eval(a->r)) ? 1 : 0; break;
    case '4': v = (eval(a->l) == eval(a->r)) ? 1 : 0; break;
    case '5': v = (eval(a->l) >= eval(a->r)) ? 1 : 0; break;
    case '6': v = (eval(a->l) <= eval(a->r)) ? 1 : 0; break;

    case '=':     //atribuição
      v = eval(((Symasgn *)a)->v); /*Recupera o valor*/
      aux = srch(l1, ((Symasgn *)a)->s);
      aux->valor = v;
      break;

    case 'a':
      //v = eval(((Symasgn *)a)->v); /*Recupera o valor*/
      strcpy(v1,  recupera_decStrg(((Symasgn *)a)->v));
      aux = srch(l1, ((Symasgn *)a)->s);
      strcpy(aux->valors, v1);
      break;
      
    case 'I': /*CASO IF*/
      if(eval(((Flow *)a)->cond) != 0) { // executa a condição / teste se for verdade exucuta o if
        if (((Flow *)a)->tl)            // Se existir árvore e tiver algo dentro
          v = eval(((Flow *)a)->tl);    // Verdade
        else
          v = 0.0;
      } else {
        if(((Flow *)a)->el) {         // caso não tenha chama do else 
          v = eval(((Flow *)a)->el); /*Falso*/
        } else
          v = 0.0;
      }
      break;

    case 'W':                     // while
      v = 0.0;                    
      if(((Flow *)a)->tl) {       // se a condição for verdade, chama o tl
        while(eval(((Flow *)a)->cond) != 0) {   //verificação dentro do while
          v = eval(((Flow *)a)->tl);            // se a condição for verdade, executa
        }
      }
      break;

    case 'L':
      eval(a->l);
      v = eval(a->r);
      break; // Lista de operções em um bloco IF/ELSE/WHILE. Assim o analisador não se perde entre os blocos

    case 'P':
      v = eval(a->l); // Imprime um FLOAT
      printf("%.2f\n", v);
      break;

    case 'S':
      fflush(stdin);
      scanf("%lf", &v);
      fflush(stdin);
      aux1 = srch(l1, ((Varval *)a)->var);
      aux1->valor = v;
      break;

    case 'T':
      fflush(stdin);
      scanf("%s", v1);
      fflush(stdin);
      aux1 = srch(l1, ((Varval *)a)->var);
      strcpy(aux1->valors, v1);
      break;

    case 'Y':
      v2 = eval2(a->l); /*Recupera um valor STR*/
      printf("%s\n", v2);
      break; /*Função que imprime um valor (string)*/

    /** =========  Função que imprime um valor (string) ============ */
    // subdivisao do float
    case 'q':
      eval(a->r);
      eval(a->l);
      /*Recupera um valor STR*/
      break; /*Função que imprime um valor (string)*/
    case 'p':
      value = eval(a->l); /*Recupera um valor STR*/
      printf("%.2lf\n", value);
      break;

    // subdivisao do int
    case 'v':
      eval(a->r);
      eval(a->l); // Recupera um valor STR
      break; // Função que imprime um valor (string)
    case 'u':
      value = eval(a->l);
      printf("%d\n", (int)value);
      break;

    case 'z':
      aux1 = srch(l1, ((Varval *)a)->var);
      if (aux1->nodetype == 2)
        printf("%s\n", aux1->valors);
      else
        printf("Variável não é do tipo String %c\n", a->nodetype);
      break;

    case 'Z':
      printf("%s\n", ((TXT*)a->l)->txt);
      break;

    case 'V': //armazena um float
      l1 = ins_float(l1, ((Varval *)a)->var);
      break;
    case 'U': //armazena um int
      l1 = ins_int(l1, ((Varval *)a)->var);
      break;
    case 'X': //armazena um string
      l1 = ins_string(l1, ((Varval *)a)->var);
      break;

    case 'D': //declarar e inserir float
      v = eval(a->r);
      l1 = ins_float(l1, ((Symasgn *)(a->l))->s);
      l1->valor = v;
      break;
    case 'd': //declarar varios float
      l1 = ins_float(l1, ((Symasgn *)(a->l))->s);
      eval(a->r);
      break;

    case 'G': //declarar e inserir int
      v = eval(a->r);
      l1 = ins_int(l1, ((Symasgn *)(a->l))->s);
      l1->valor = v;
      break;
    case 'g': //declarar varios int
      l1 = ins_int(l1, ((Symasgn *)(a->l))->s);
      eval(a->r);
      break;

    case 'H': //declarar e inserir string
      l1 = ins_string(l1, (((Symasgn *)(a->l))->s));
      strcpy(l1->valors, ((Varval *)a->r)->var);
      break;
    case 'h': //declarar varios string
      l1 = ins_string(l1, ((Symasgn *)(a->l))->s);
      eval(a->r);
      break;
    case '@':
      v2 = recupera_decStrg(((Symasgn *)a)->v);
      aux1 = srch(l1, ((Symasgn *)a)->s);
      
      if (aux1->nodetype == 2)
        strcpy(aux1->valors, v2);
      else
        printf("Variável %s não é do tipo String \n", ((Symasgn *)a)->s);
      break;
    case '#':
      v2 = recupera_decStrg(((Symasgn *)a)->v);
      aux1 = srch(l1, ((Symasgn *)a)->s);
      if (aux1->nodetype == 2)
        strcat(aux1->valors, v2);
      else
          printf("Variável %s não é do tipo String \n", ((Symasgn *)a)->s);
      break;
    default:
      printf("EVAL1: internal error: bad node %c\n", a->nodetype);
      break;
  }
  
  return v;
}

	int yylex();
	void yyerror (char *s) {
		printf("%s\n", s);
	}

%}

%union {
	float flo;
	int fn;
	char str[50];
	Ast *a;
}

%token <flo>NUM
%token <str>VARS
%token <str>TEXTO
%token INICIO FIM 
%token IF ELSE WHILE
%token STRING INT FLOAT
%token PRINTF PRINTS PRINTI
%token SCANINT SCANFLOAT SCANSTRING
%token <fn> CMP

%right '='
%left '+' '-'
%left '*' '/' '%'
%right '^' '$'
%left CMP

%type <a> exp list stmt prog aString

%nonassoc IFX VARPREC VARPREC2 NEG VET declint declfloat declstring

%%

val: INICIO prog FIM
	;

prog: stmt { eval($1); }
	| prog stmt { eval($2); }
	;
	
	
stmt: 
	IF '(' exp ')' '{' list '}' %prec IFX { $$ = newflow('I', $3, $6, NULL); }
	| IF '(' exp ')' '{' list '}' ELSE '{' list '}' { $$ = newflow('I', $3, $6, $10); }
	| WHILE '(' exp ')' '{' list '}' { $$ = newflow('W', $3, $6, NULL); }

	| VARS '=' exp %prec VARPREC { $$ = newasgn($1,$3); }
	| VARS '=' TEXTO %prec VARPREC2 { $$ = newasgnString($1, newast('$', recupera_Nome_ref_vari_str($3), NULL)); }

	| INT VARS %prec declint { $$ = newvari('U',$2); }
	| FLOAT VARS %prec declfloat { $$ = newvari('V',$2); }
	| STRING VARS %prec declstring { $$ = newvari('X',$2); }

	| INT VARS '=' exp { $$ = newast('G', newvari('U',$2) , $4); }
	| FLOAT VARS '=' exp { $$ = newast('D', newvari('V',$2) , $4); }
	| STRING VARS '=' TEXTO { $$ = newast('H', newvari('X',$2) , recupera_Nome_ref_vari_str($4)); }

	| SCANFLOAT VARS {  $$ = newvari('S', $2); }
	| SCANINT  VARS  {  $$ = newvari('S', $2); }
	| SCANSTRING  VARS  {  $$ = newvari('T', $2); }

	| PRINTF  exp { $$ = newast('p', $2, NULL); }
	| PRINTI  exp { $$ = newast('u', $2, NULL); }
	| PRINTS  aString { $$ = $2; }
	;

aString: VARS { $$ = searchVar('z', $1); }
	| TEXTO { $$ = newast('Z', recupera_Nome_ref_vari_str($1), NULL); }
	;

list: stmt { $$ = $1; }
		| list stmt { $$ = newast('L', $1, $2);	}
		;
	
exp: 
	exp '+' exp { $$ = newast('+', $1, $3); }
	| exp '-' exp { $$ = newast('-', $1, $3); }
	| exp '*' exp { $$ = newast('*', $1, $3); }
	| exp '/' exp { $$ = newast('/', $1, $3); }
	| exp '%' exp { $$ = newast('%', $1, $3); }
	| '(' exp ')' { $$ = $2; }
	| exp '^' exp { $$ = newast('^', $1, $3);  }
	| '$' '(' exp ',' exp ')' { $$ = newast('~', $3, $5); }

	| exp CMP exp { $$ = newcmp($2, $1, $3); }
	| '-' exp %prec NEG { $$ = newast('M',$2,NULL); }
	| NUM { $$ = newnum($1); }
	| VARS	%prec VET { $$ = newValorVal($1); }
	;

;

%%

#include "lex.yy.c"

int main(){

	yyin = fopen("entrada.txt", "r");


	yyparse();
	yylex();
	fclose(yyin);
	
	return 0;
}
int yywrap(){
return 1;
}