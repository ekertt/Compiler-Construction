%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <memory.h>

#include "types.h"
#include "tree_basic.h"
#include "str.h"
#include "dbug.h"
#include "ctinfo.h"
#include "free.h"
#include "globals.h"

static node *parseresult = NULL;
extern int yylex();
static int yyerror( char *errname);

%}

%union {
 nodetype            nodetype;
 char               *id;
 int                 cint;
 float               cflt;
 binop               cbinop;
 monop              cmonop;
 type                ctype;
 node               *node;
}

%token PARENTHESIS_L PARENTHESIS_R BRACKET_L BRACKET_R COMMA SEMICOLON CURLY_L CURLY_R
%token MINUS PLUS STAR SLASH PERCENT LE LT GE GT EQ NE OR AND NEG
%token TRUEVAL FALSEVAL LET INT BOOL VOID FLOAT
%token EXTERN EXPORT RETURN
%token IF ELSE DO WHILE FOR

%token <cint> NUM
%token <cflt> FLOATVAL
%token <id> ID

%type <node> intval floatval boolval constant expr
%type <node> stmts stmt assign varlet program 
%type <node> return exprstmt binop exprs monop 
%type <node> vardecl fundef funbody block ifelse
%type <node> decl decls globdef for dowhile
%type <node> param while

%type <ctype> type

%start program

%left OR
%left AND
%left EQ NE
%left LT GT LET LE GE
%left PLUS MINUS
%left STAR SLASH PERCENT
%right NEG CAST

%nonassoc ID
%nonassoc PARENTHESIS_L
%nonassoc PARENTHESIS_R
%nonassoc ELSE

%%

program: decls 
         {
           parseresult = TBmakeProgram($1, NULL);
         }
         ;

decls: decl decls
        {
          $$ = TBmakeDecls( $1, $2);
        }
      | decl
        {
          $$ = TBmakeDecls( $1, NULL);
        }
        ;

decl: fundef
       {
         $$ = $1;
       }
      | globdef
        {
         $$ = $1;
        }
       ;

globdef: type ID SEMICOLON
        {
          $$ = TBmakeGlobdef($1, STRcpy($2), NULL, NULL);
        }
      | type ID LET expr SEMICOLON
        {
          $$ = TBmakeGlobdef($1, STRcpy($2), NULL, $4);
        }
      | EXPORT type ID SEMICOLON
        {
          $$ = TBmakeGlobdef($2, STRcpy( $3), NULL, NULL);
          GLOBDEF_ISEXPORT($$) = 1;
        }
      | EXPORT type ID LET expr SEMICOLON
        {
          $$ = TBmakeGlobdef($2, STRcpy( $3), NULL, $5);
          GLOBDEF_ISEXPORT($$) = 1;
        }
      | EXTERN type ID SEMICOLON
        {
          $$ = TBmakeGlobdef($2, STRcpy( $3), NULL, NULL);
          GLOBDEF_ISEXTERN($$) = 1;
        }
      ;

fundef: type ID PARENTHESIS_L PARENTHESIS_R  CURLY_L funbody CURLY_R
        {
            $$ = TBmakeFundef( $1, STRcpy( $2), $6, NULL);
        }
    |   type ID PARENTHESIS_L param PARENTHESIS_R CURLY_L funbody CURLY_R
        {
            $$ = TBmakeFundef( $1, STRcpy( $2), $7, $4);
        }
    |   EXPORT type ID PARENTHESIS_L PARENTHESIS_R CURLY_L funbody CURLY_R
        {
            $$ = TBmakeFundef( $2, STRcpy( $3), $7, NULL);
            FUNDEF_ISEXPORT($$) = 1;
        }
    |   EXPORT type ID PARENTHESIS_L param PARENTHESIS_R CURLY_L funbody CURLY_R
        {
            $$ = TBmakeFundef( $2, STRcpy( $3), $8, $5);
            FUNDEF_ISEXPORT($$) = 1;
        }
    |   EXTERN type ID PARENTHESIS_L PARENTHESIS_R SEMICOLON
        {
            $$ = TBmakeFundef( $2, STRcpy( $3), NULL, NULL);
            FUNDEF_ISEXTERN($$) = 1;

        }
    |   EXTERN type ID PARENTHESIS_L param PARENTHESIS_R SEMICOLON
        {
            $$ = TBmakeFundef( $2, STRcpy( $3), NULL, $5);
            FUNDEF_ISEXTERN($$) = 1;

        }
    ;

param: type ID
        {
          $$ = TBmakeParam(STRcpy($2), $1, NULL, NULL);
        }
      | type ID COMMA param
        {
          $$ = TBmakeParam(STRcpy($2), $1, NULL, $4);
        }
      ;

funbody: vardecl stmts
        {
          $$ = TBmakeFunbody($1, NULL, $2);
        }
      | vardecl
        {
          $$ = TBmakeFunbody($1, NULL, NULL);
        }
      | stmts
        {
          $$ = TBmakeFunbody(NULL, NULL, $1);
        }
      |
        {
          $$ = TBmakeFunbody(NULL, NULL, NULL);
        }
      ;

vardecl: type ID LET expr SEMICOLON
        {
          $$ = TBmakeVardecl( STRcpy( $2), $1, NULL, $4, NULL);
        }
      | type ID SEMICOLON
        {
          $$ = TBmakeVardecl( STRcpy( $2), $1, NULL, NULL, NULL);
        }
      | type ID SEMICOLON vardecl
        {
            $$ = TBmakeVardecl( STRcpy( $2), $1, NULL, NULL, $4);
        }
      | type ID LET expr SEMICOLON vardecl
        {
            $$ = TBmakeVardecl( STRcpy( $2), $1, NULL, $4, $6);
        }
      ;

stmts: stmt stmts
        {
            $$ = TBmakeStmts( $1, $2);
        }
    |   stmt
        {
            $$ = TBmakeStmts( $1, NULL);
        }
    ;

stmt: assign
       {
         $$ = $1;
       }
      | dowhile
        {
          $$ = $1;
        }
      | ifelse
        {
          $$ = $1;
        }
      | for
        {
          $$ = $1;
        }
      | return
        {
          $$ = $1;
        }
      | exprstmt
        {
          $$ = $1;
        }
      | while
        {
          $$ = $1;
        }
       ;

assign: varlet LET expr SEMICOLON
        {
          $$ = TBmakeAssign( $1, $3);
        }
        ;

dowhile: DO block WHILE PARENTHESIS_L expr PARENTHESIS_R SEMICOLON
        {
          $$ = TBmakeDowhile( $5, $2);
        }
        ;

ifelse: IF PARENTHESIS_L expr PARENTHESIS_R block
        {
          $$ = TBmakeIfelse( $3, $5, NULL);
        }
      | IF PARENTHESIS_L expr PARENTHESIS_R block ELSE block
        {
          $$ = TBmakeIfelse( $3, $5, $7);
        }
        ;

for: FOR PARENTHESIS_L INT ID LET expr COMMA expr PARENTHESIS_R block
        {
          $$ = TBmakeFor( STRcpy( $4), $6, $8, NULL, $10);
        }
      |   FOR PARENTHESIS_L INT ID LET expr COMMA expr COMMA expr PARENTHESIS_R block
        {
          $$ = TBmakeFor( STRcpy( $4), $6, $8, $10, $12);
        }
        ;

return: RETURN expr SEMICOLON
        {
          $$ = TBmakeReturn( $2);
        }
      |   RETURN SEMICOLON
        {
          $$ = TBmakeReturn( NULL);
        }
        ;

exprstmt: expr SEMICOLON
        {
          $$ = TBmakeExprstmt( $1);
        }
        ;

while: WHILE PARENTHESIS_L expr PARENTHESIS_R block
        {
          $$ = TBmakeWhile($3, $5);
        }
        ;

varlet: ID
        {
          $$ = TBmakeVarlet( STRcpy( $1), NULL, NULL);
        }
        ;

exprs: expr COMMA exprs
        {
          $$ = TBmakeExprs($1, $3);
        }
      | expr
        {
          $$ = TBmakeExprs($1, NULL);
        }
        ;

block: CURLY_L stmts CURLY_R
        {
          $$ = $2;
        }
      | CURLY_L CURLY_R
        {
          $$ = NULL;
        }
      | stmt
        {
          $$ = TBmakeStmts($1, NULL);
        }
        ;

constant: floatval
          {
            $$ = $1;
          }
        | intval
          {
            $$ = $1;
          }
        | boolval
          {
            $$ = $1;
          }
        ;

floatval: FLOATVAL
           {
             $$ = TBmakeFloat( $1);
           }
         ;

intval: NUM
        {
          $$ = TBmakeNum( $1);
        }
      ;

boolval: TRUEVAL
         {
           $$ = TBmakeBool( TRUE);
         }
       | FALSEVAL
         {
           $$ = TBmakeBool( FALSE);
         }
       ;

expr:
    PARENTHESIS_L expr PARENTHESIS_R
        {
          $$ = $2;
        }
      | PARENTHESIS_L type PARENTHESIS_R expr
        {
          $$ = TBmakeCast( $2, $4);
        }
      | constant
        {
          $$ = $1;
        }
      | ID
        {
          $$ = TBmakeVar( STRcpy( $1), NULL, NULL);
        }
      | binop 
        {
          $$ = $1;
        }
      | monop 
        {
          $$ = $1;
        }
      | BRACKET_L type BRACKET_R expr %prec CAST 
        {
        $$ = TBmakeCast($2, $4);
        }
      | ID PARENTHESIS_L PARENTHESIS_R 
        {
          $$ = TBmakeFuncall( STRcpy( $1), NULL, NULL);
        }
      | ID PARENTHESIS_L exprs PARENTHESIS_R 
        {
          $$ = TBmakeFuncall( STRcpy( $1), NULL, $3);
        }
    ;

monop: MINUS expr
        {
          $$ = TBmakeMonop( MO_minus, $2);
        }
      | NEG expr
        {
          $$ = TBmakeMonop( MO_neg, $2);
        }
      ;

binop: expr PLUS expr      
        { 
          $$ = TBmakeBinop( BO_add,$1, $3); 
        }
      | expr MINUS expr    
        { 
          $$ = TBmakeBinop( BO_sub,$1, $3); 
        }
      | expr STAR expr    
        { 
          $$ = TBmakeBinop( BO_mul,$1, $3); 
        }
      | expr SLASH expr    
        { 
          $$ = TBmakeBinop( BO_div,$1, $3); 
        }
      | expr PERCENT expr   
        { 
          $$ = TBmakeBinop( BO_mod,$1, $3); 
        }
      | expr LE expr      
        { 
          $$ = TBmakeBinop( BO_le,$1, $3);
        }
      | expr LT expr        
        { 
          $$ = TBmakeBinop( BO_lt,$1, $3);
        }
      | expr GE expr        
        { 
          $$ = TBmakeBinop( BO_ge,$1, $3);
        }
      | expr GT expr       
        { 
          $$ = TBmakeBinop( BO_gt,$1, $3);
        }
      | expr EQ expr       
        { 
          $$ = TBmakeBinop( BO_eq,$1, $3);
        }
      | expr OR expr       
        { 
          $$ = TBmakeBinop( BO_or,$1, $3);
        }
      | expr AND expr       
        { 
          $$ = TBmakeBinop( BO_and,$1, $3);
        }
      | expr NE expr 
        { 
          $$ = TBmakeBinop( BO_ne,$1, $3);
        }
     ;

type: INT      
        { 
          $$ = T_int; 
        }
      | FLOAT     
        { 
          $$ = T_float; 
        }
      | BOOL      
        { 
          $$ = T_bool; 
        }
      | VOID     
        { 
          $$ = T_void; 
        }
      ;
   
%%

static int yyerror( char *error)
{
  CTIabort( "line %d, col %d\nError parsing source code: %s\n", 
            global.line, global.col, error);

  return( 0);
}

node *YYparseTree( void)
{
  DBUG_ENTER("YYparseTree");

  yyparse();

  DBUG_RETURN( parseresult);
}

