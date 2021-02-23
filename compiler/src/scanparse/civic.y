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
 node               *node;
}

%token PARENTHESIS_L PARENTHESIS_R BRACKET_L BRACKET_R COMMA SEMICOLON CURLY_L CURLY_R
%token MINUS PLUS STAR SLASH PERCENT LE LT GE GT EQ NE OR AND NEG
%token TRUEVAL FALSEVAL LET INT FLOAT BOOL VOID
%token EXTERN EXPORT RETURN
%token IF ELSE DO WHILE FOR

%token <cint> NUM
%token <cflt> FLOAT
%token <id> ID

%type <node> intval floatval boolval constant expr
%type <node> stmts stmt assign varlet program 
%type <node> return exprstmt binop exprs monop 
%type <node> vardecl fundef funbody block ifelse
%type <node> decl decls globdef for dowhile
%type <node> param while

%start program

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
          $$ = TBmakeGlobalDef($1, STRcpy($2), NULL, NULL);
        }
      | type ID LET expr SEMICOLON
        {
          $$ = TBmakeGlobalDef($1, STRcpy($2), NULL, $4);
        }
      | EXPORT type ID SEMICOLON
        {
          $$ = TBmakeGlobalDef($2, STRcpy( $3), NULL, NULL);
          GLOBALDEF_ISEXPORT($$) = 1;
        }
      | EXPORT type ID LET expr SEMICOLON
        {
          $$ = TBmakeGlobalDef($2, STRcpy( $3), NULL, $5);
          GLOBALDEF_ISEXPORT($$) = 1;
        }
      | EXTERN type ID SEMICOLON
        {
          $$ = TBmakeGlobalDef($2, STRcpy( $3), NULL, NULL);
          GLOBALDEF_ISEXTERN($$) = 1;
        }
      ;

assign: varlet LET expr SEMICOLON
        {
          $$ = TBmakeAssign( $1, $3);
        }
        ;

varlet: ID
        {
          $$ = TBmakeVarlet( STRcpy( $1), NULL, NULL);
        }
        ;


expr: constant
      {
        $$ = $1;
      }
    | ID
      {
        $$ = TBmakeVar( STRcpy( $1), NULL, NULL);
      }
    | BRACKET_L expr binop expr BRACKET_R
      {
        $$ = TBmakeBinop( $3, $2, $4);
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

floatval: FLOAT
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

binop: PLUS      { $$ = BO_add; }
     | MINUS     { $$ = BO_sub; }
     | STAR      { $$ = BO_mul; }
     | SLASH     { $$ = BO_div; }
     | PERCENT   { $$ = BO_mod; }
     | LE        { $$ = BO_le; }
     | LT        { $$ = BO_lt; }
     | GE        { $$ = BO_ge; }
     | GT        { $$ = BO_gt; }
     | EQ        { $$ = BO_eq; }
     | OR        { $$ = BO_or; }
     | AND       { $$ = BO_and; }
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

