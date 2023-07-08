%{
#include "y.tab.h"
extern yylval;
%}

%%
[0-9]+ {yylval=atoi(yytext);return num;}
[\+\-\*\/] {return yytext[0];}
[)] {return yytext[0];}
[(] {return yytext[0];}
. {;}
\n {return 0;}
%%

lab1b.y - PROGRAM

%{
#include<stdio.h>
#include<stdlib.h>
%}
%token num
%left '+' '-'
%left '*' '/'

%%
input:exp{printf("%d\n",$$);exit(0);}
exp:exp'+'exp{$$=$1+$3;}
|exp'-'exp{$$=$1-$3;}
|exp'*'exp{$$=$1*$3;}
|exp'/'exp{ if($3==0){printf("Divide by Zero error\n");exit(0);}
   else  $$=$1/$3;}
|'('exp')'{$$=$2;}
|num{$$=$1;};
%%

int yyerror()
{
 printf("error");
 exit(0);
}

int main()
{
 printf("Enter an expression:\n");
 yyparse();
}

/*
output
gedit 1b.l
gedit 1b.y
lex 1b.l
yacc -d 1b.y
cc lex.yy.c y.tab.c -ll
./a.out


Enter th expr: 
6+9
15

*/