%{
#include <string.h>
%}

NUM [0-9]+\.?[0-9]*
VARS [a-z]+[0-9]*

FIM "fim"
INICIO "inicio"

IF "if"
ELSE "else"
WHILE "while"

PRINTI "printi<<"
PRINTS "prints<<"
PRINTF "printf<<"

SCANINT "lerin>>"
SCANSTRING "lerstr>>"
SCANFLOAT "lerf>>"

STRING "string"
FLOAT "float"
INT "int"
COMENTARIO "#"
TEXTO ["][^"]*["]
	
%%
{FIM} {return FIM;}
{INICIO} {return INICIO;}
{COMENTARIO}.* {;}

{IF} {return IF;}
{ELSE} {return ELSE;}
{WHILE} {return WHILE;}

{PRINTS} {return PRINTS;}
{PRINTI} {return PRINTI;}
{PRINTF} {return PRINTF;}

{SCANINT} {return SCANINT;}
{SCANSTRING} {return SCANSTRING;}
{SCANFLOAT} {return SCANFLOAT;}

{FLOAT} {return FLOAT;}
{INT} {return INT;}
{STRING} {return STRING;}

{VARS} {
	strcpy(yylval.str,yytext);
	return VARS;
	}

{TEXTO} {
	char aux[50];
	strncpy(aux, &yytext[1], strlen(yytext)-2); 
	aux[strlen(yytext)-2]='\0';
	strcpy (yylval.str, aux);

	return TEXTO;
	}

{NUM} {
	yylval.flo = atof(yytext);
	return NUM;
	}

[-+()=/*^{}$] {return *yytext;}
			

">" {yylval.fn = 1; return CMP; }
"<" {yylval.fn = 2; return CMP; }
"!=" {yylval.fn = 3; return CMP; }
"==" {yylval.fn = 4; return CMP; }
">=" {yylval.fn = 5; return CMP; }
"<=" {yylval.fn = 6; return CMP; }

[\ \n\t;]*	{;}
. {printf("(%s) Ingonrado\n",yytext);}
%%
