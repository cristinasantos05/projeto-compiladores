/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "aulaAST.y"


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


#line 647 "aulaAST.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    NUM = 258,
    VARS = 259,
    TEXTO = 260,
    INICIO = 261,
    FIM = 262,
    IF = 263,
    ELSE = 264,
    WHILE = 265,
    STRING = 266,
    INT = 267,
    FLOAT = 268,
    PRINTF = 269,
    PRINTS = 270,
    PRINTI = 271,
    SCANINT = 272,
    SCANFLOAT = 273,
    SCANSTRING = 274,
    CMP = 275,
    IFX = 276,
    VARPREC = 277,
    VARPREC2 = 278,
    NEG = 279,
    VET = 280,
    declint = 281,
    declfloat = 282,
    declstring = 283
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 578 "aulaAST.y"

	float flo;
	int fn;
	char str[50];
	Ast *a;

#line 732 "aulaAST.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);





#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  17
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   200

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  7
/* YYNRULES -- Number of rules.  */
#define YYNRULES  37
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  85

#define YYUNDEFTOK  2
#define YYMAXUTOK   283


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,    28,    26,     2,     2,
      37,    38,    24,    22,    41,    23,     2,    25,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    21,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    27,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    39,     2,    40,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    29,    30,    31,    32,
      33,    34,    35,    36
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   607,   607,   610,   611,   616,   617,   618,   620,   621,
     623,   624,   625,   627,   628,   629,   631,   632,   633,   635,
     636,   637,   640,   641,   644,   645,   649,   650,   651,   652,
     653,   654,   655,   656,   658,   659,   660,   661
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUM", "VARS", "TEXTO", "INICIO", "FIM",
  "IF", "ELSE", "WHILE", "STRING", "INT", "FLOAT", "PRINTF", "PRINTS",
  "PRINTI", "SCANINT", "SCANFLOAT", "SCANSTRING", "CMP", "'='", "'+'",
  "'-'", "'*'", "'/'", "'%'", "'^'", "'$'", "IFX", "VARPREC", "VARPREC2",
  "NEG", "VET", "declint", "declfloat", "declstring", "'('", "')'", "'{'",
  "'}'", "','", "$accept", "val", "prog", "stmt", "aString", "list", "exp", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,    61,    43,    45,    42,    47,    37,    94,    36,   276,
     277,   278,   279,   280,   281,   282,   283,    40,    41,   123,
     125,    44
};
# endif

#define YYPACT_NINF (-68)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       0,   181,     7,     8,   -26,    -7,    27,    29,    32,    72,
      -2,    72,    34,    42,    43,   165,   -68,   -68,    75,    72,
      72,    11,    35,    37,   -68,   -68,    72,    22,    72,    28,
     -68,   -68,   -68,    28,   -68,   -68,   -68,   -68,   -68,   -68,
      28,   102,   119,    55,    72,    72,   -68,    72,   127,    72,
      72,    72,    72,    72,    72,    72,    57,    58,   -68,    28,
      28,    94,   -68,   -68,    81,    81,   -15,   -15,   -15,   -15,
     181,   181,    72,   -68,     9,    53,   136,    85,   -68,   -68,
     -68,    60,   181,    73,   -68
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     3,     1,     0,     0,
       0,    12,    10,    11,    36,    37,     0,     0,     0,    19,
      22,    23,    21,    20,    17,    16,    18,     2,     4,     9,
       8,     0,     0,     0,     0,     0,    35,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    15,    13,
      14,     0,    31,    34,    26,    27,    28,    29,    30,    32,
       0,     0,     0,    24,     0,     0,     0,     5,    25,     7,
      33,     0,     0,     0,     6
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -68,   -68,   -68,    -1,   -68,   -67,   -10
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,    15,    73,    32,    74,    29
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      16,    33,    30,    31,    75,    49,     1,    17,    40,    41,
      42,    19,    55,     3,    38,    83,    46,     4,    48,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    18,
      20,    21,    43,    22,    59,    60,    23,    61,    34,    63,
      64,    65,    66,    67,    68,    69,    35,    36,    49,    77,
      50,    51,    52,    53,    54,    55,    44,     3,    45,    47,
      58,     4,    76,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    78,    78,    24,    25,     3,    24,    25,
      39,     4,    78,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    79,    81,    26,    70,    71,    26,    82,
      27,    49,     0,    27,     0,    52,    53,    54,    55,    28,
       0,     0,    28,    84,    49,     0,    50,    51,    52,    53,
      54,    55,    49,     0,    50,    51,    52,    53,    54,    55,
       0,     0,     0,     0,     0,    72,     0,     0,     0,    49,
      56,    50,    51,    52,    53,    54,    55,    49,     0,    50,
      51,    52,    53,    54,    55,     0,    49,    57,    50,    51,
      52,    53,    54,    55,     0,    62,     0,     0,     0,     3,
       0,     0,    37,     4,    80,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,     3,     0,     0,     0,     4,
       0,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14
};

static const yytype_int8 yycheck[] =
{
       1,    11,     4,     5,    71,    20,     6,     0,    18,    19,
      20,    37,    27,     4,    15,    82,    26,     8,    28,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    21,
      37,     4,    21,     4,    44,    45,     4,    47,     4,    49,
      50,    51,    52,    53,    54,    55,     4,     4,    20,    40,
      22,    23,    24,    25,    26,    27,    21,     4,    21,    37,
       5,     8,    72,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    74,    75,     3,     4,     4,     3,     4,
       5,     8,    83,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    40,     9,    23,    39,    39,    23,    39,
      28,    20,    -1,    28,    -1,    24,    25,    26,    27,    37,
      -1,    -1,    37,    40,    20,    -1,    22,    23,    24,    25,
      26,    27,    20,    -1,    22,    23,    24,    25,    26,    27,
      -1,    -1,    -1,    -1,    -1,    41,    -1,    -1,    -1,    20,
      38,    22,    23,    24,    25,    26,    27,    20,    -1,    22,
      23,    24,    25,    26,    27,    -1,    20,    38,    22,    23,
      24,    25,    26,    27,    -1,    38,    -1,    -1,    -1,     4,
      -1,    -1,     7,     8,    38,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,     4,    -1,    -1,    -1,     8,
      -1,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     6,    43,     4,     8,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    44,    45,     0,    21,    37,
      37,     4,     4,     4,     3,     4,    23,    28,    37,    48,
       4,     5,    46,    48,     4,     4,     4,     7,    45,     5,
      48,    48,    48,    21,    21,    21,    48,    37,    48,    20,
      22,    23,    24,    25,    26,    27,    38,    38,     5,    48,
      48,    48,    38,    48,    48,    48,    48,    48,    48,    48,
      39,    39,    41,    45,    47,    47,    48,    40,    45,    40,
      38,     9,    39,    47,    40
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    42,    43,    44,    44,    45,    45,    45,    45,    45,
      45,    45,    45,    45,    45,    45,    45,    45,    45,    45,
      45,    45,    46,    46,    47,    47,    48,    48,    48,    48,
      48,    48,    48,    48,    48,    48,    48,    48
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     3,     1,     2,     7,    11,     7,     3,     3,
       2,     2,     2,     4,     4,     4,     2,     2,     2,     2,
       2,     2,     1,     1,     1,     2,     3,     3,     3,     3,
       3,     3,     3,     6,     3,     2,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 3:
#line 610 "aulaAST.y"
           { eval((yyvsp[0].a)); }
#line 1978 "aulaAST.tab.c"
    break;

  case 4:
#line 611 "aulaAST.y"
                    { eval((yyvsp[0].a)); }
#line 1984 "aulaAST.tab.c"
    break;

  case 5:
#line 616 "aulaAST.y"
                                              { (yyval.a) = newflow('I', (yyvsp[-4].a), (yyvsp[-1].a), NULL); }
#line 1990 "aulaAST.tab.c"
    break;

  case 6:
#line 617 "aulaAST.y"
                                                        { (yyval.a) = newflow('I', (yyvsp[-8].a), (yyvsp[-5].a), (yyvsp[-1].a)); }
#line 1996 "aulaAST.tab.c"
    break;

  case 7:
#line 618 "aulaAST.y"
                                         { (yyval.a) = newflow('W', (yyvsp[-4].a), (yyvsp[-1].a), NULL); }
#line 2002 "aulaAST.tab.c"
    break;

  case 8:
#line 620 "aulaAST.y"
                                     { (yyval.a) = newasgn((yyvsp[-2].str),(yyvsp[0].a)); }
#line 2008 "aulaAST.tab.c"
    break;

  case 9:
#line 621 "aulaAST.y"
                                        { (yyval.a) = newasgnString((yyvsp[-2].str), newast('$', recupera_Nome_ref_vari_str((yyvsp[0].str)), NULL)); }
#line 2014 "aulaAST.tab.c"
    break;

  case 10:
#line 623 "aulaAST.y"
                                 { (yyval.a) = newvari('U',(yyvsp[0].str)); }
#line 2020 "aulaAST.tab.c"
    break;

  case 11:
#line 624 "aulaAST.y"
                                     { (yyval.a) = newvari('V',(yyvsp[0].str)); }
#line 2026 "aulaAST.tab.c"
    break;

  case 12:
#line 625 "aulaAST.y"
                                       { (yyval.a) = newvari('X',(yyvsp[0].str)); }
#line 2032 "aulaAST.tab.c"
    break;

  case 13:
#line 627 "aulaAST.y"
                           { (yyval.a) = newast('G', newvari('U',(yyvsp[-2].str)) , (yyvsp[0].a)); }
#line 2038 "aulaAST.tab.c"
    break;

  case 14:
#line 628 "aulaAST.y"
                             { (yyval.a) = newast('D', newvari('V',(yyvsp[-2].str)) , (yyvsp[0].a)); }
#line 2044 "aulaAST.tab.c"
    break;

  case 15:
#line 629 "aulaAST.y"
                                { (yyval.a) = newast('H', newvari('X',(yyvsp[-2].str)) , recupera_Nome_ref_vari_str((yyvsp[0].str))); }
#line 2050 "aulaAST.tab.c"
    break;

  case 16:
#line 631 "aulaAST.y"
                         {  (yyval.a) = newvari('S', (yyvsp[0].str)); }
#line 2056 "aulaAST.tab.c"
    break;

  case 17:
#line 632 "aulaAST.y"
                         {  (yyval.a) = newvari('S', (yyvsp[0].str)); }
#line 2062 "aulaAST.tab.c"
    break;

  case 18:
#line 633 "aulaAST.y"
                            {  (yyval.a) = newvari('T', (yyvsp[0].str)); }
#line 2068 "aulaAST.tab.c"
    break;

  case 19:
#line 635 "aulaAST.y"
                      { (yyval.a) = newast('p', (yyvsp[0].a), NULL); }
#line 2074 "aulaAST.tab.c"
    break;

  case 20:
#line 636 "aulaAST.y"
                      { (yyval.a) = newast('u', (yyvsp[0].a), NULL); }
#line 2080 "aulaAST.tab.c"
    break;

  case 21:
#line 637 "aulaAST.y"
                          { (yyval.a) = (yyvsp[0].a); }
#line 2086 "aulaAST.tab.c"
    break;

  case 22:
#line 640 "aulaAST.y"
              { (yyval.a) = searchVar('z', (yyvsp[0].str)); }
#line 2092 "aulaAST.tab.c"
    break;

  case 23:
#line 641 "aulaAST.y"
                { (yyval.a) = newast('Z', recupera_Nome_ref_vari_str((yyvsp[0].str)), NULL); }
#line 2098 "aulaAST.tab.c"
    break;

  case 24:
#line 644 "aulaAST.y"
           { (yyval.a) = (yyvsp[0].a); }
#line 2104 "aulaAST.tab.c"
    break;

  case 25:
#line 645 "aulaAST.y"
                            { (yyval.a) = newast('L', (yyvsp[-1].a), (yyvsp[0].a));	}
#line 2110 "aulaAST.tab.c"
    break;

  case 26:
#line 649 "aulaAST.y"
                    { (yyval.a) = newast('+', (yyvsp[-2].a), (yyvsp[0].a)); }
#line 2116 "aulaAST.tab.c"
    break;

  case 27:
#line 650 "aulaAST.y"
                      { (yyval.a) = newast('-', (yyvsp[-2].a), (yyvsp[0].a)); }
#line 2122 "aulaAST.tab.c"
    break;

  case 28:
#line 651 "aulaAST.y"
                      { (yyval.a) = newast('*', (yyvsp[-2].a), (yyvsp[0].a)); }
#line 2128 "aulaAST.tab.c"
    break;

  case 29:
#line 652 "aulaAST.y"
                      { (yyval.a) = newast('/', (yyvsp[-2].a), (yyvsp[0].a)); }
#line 2134 "aulaAST.tab.c"
    break;

  case 30:
#line 653 "aulaAST.y"
                      { (yyval.a) = newast('%', (yyvsp[-2].a), (yyvsp[0].a)); }
#line 2140 "aulaAST.tab.c"
    break;

  case 31:
#line 654 "aulaAST.y"
                      { (yyval.a) = (yyvsp[-1].a); }
#line 2146 "aulaAST.tab.c"
    break;

  case 32:
#line 655 "aulaAST.y"
                      { (yyval.a) = newast('^', (yyvsp[-2].a), (yyvsp[0].a));  }
#line 2152 "aulaAST.tab.c"
    break;

  case 33:
#line 656 "aulaAST.y"
                                  { (yyval.a) = newast('~', (yyvsp[-3].a), (yyvsp[-1].a)); }
#line 2158 "aulaAST.tab.c"
    break;

  case 34:
#line 658 "aulaAST.y"
                      { (yyval.a) = newcmp((yyvsp[-1].fn), (yyvsp[-2].a), (yyvsp[0].a)); }
#line 2164 "aulaAST.tab.c"
    break;

  case 35:
#line 659 "aulaAST.y"
                            { (yyval.a) = newast('M',(yyvsp[0].a),NULL); }
#line 2170 "aulaAST.tab.c"
    break;

  case 36:
#line 660 "aulaAST.y"
              { (yyval.a) = newnum((yyvsp[0].flo)); }
#line 2176 "aulaAST.tab.c"
    break;

  case 37:
#line 661 "aulaAST.y"
                          { (yyval.a) = newValorVal((yyvsp[0].str)); }
#line 2182 "aulaAST.tab.c"
    break;


#line 2186 "aulaAST.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 666 "aulaAST.y"


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
