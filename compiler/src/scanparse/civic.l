%{

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "types.h"
#include "node_basic.h"
#include "str.h"
#include "free.h"
#include "civic.tab.h"
#include "globals.h"
#include "ctinfo.h"


#define FILTER(token) \
  global.col += yyleng;  \
  return( token);

#define LINEBUF_SIZE 256
#define YY_NO_UNPUT
#define YY_NO_INPUT


%}

%p 6000
%e 2000
%option noyywrap
%option nounput


%%

"("                        { FILTER( PARENTHESIS_L); }
")"                        { FILTER( PARENTHESIS_R); }
","                        { FILTER( COMMA); }
";"                        { FILTER( SEMICOLON); }
"{"                        { FILTER( CURLY_L); }
"}"                        { FILTER( CURLY_R); }
"["                        { FILTER( BRACKET_L); }
"]"                        { FILTER( BRACKET_R); }

"-"                        { FILTER( MINUS); }
"+"                        { FILTER( PLUS);  }
"*"                        { FILTER( STAR);  } 
"/"                        { FILTER( SLASH);  } 
"%"                        { FILTER( PERCENT);  } 

"<="                       { FILTER( LE);    }
"<"                        { FILTER( LT);    } 
">="                       { FILTER( GE);    }
">"                        { FILTER( GT);    }
"=="                       { FILTER( EQ);    }
"!="                       { FILTER( NE);    }
"&&"                       { FILTER( AND);    }
"||"                       { FILTER( OR);    }

"="                        { FILTER( LET);    }

"!"                        { FILTER( NEG);    }

"extern"                   { FILTER( EXTERN); }
"export"                   { FILTER( EXPORT); }
"return"                   { FILTER( RETURN); }

"if"                       { FILTER( IF); }
"else"                     { FILTER( ELSE); }
"do"                       { FILTER( DO); }
"while"                    { FILTER( WHILE); }
"for"                      { FILTER( FOR); }

"int"                      { FILTER( INT); }
"float"                    { FILTER( FLOAT); }
"bool"                     { FILTER( BOOL); }
"void"                     { FILTER( VOID); }

"true"                     { FILTER( TRUEVAL); }
"false"                    { FILTER( FALSEVAL); }

[A-Za-z][A-Za-z0-9_]*      { yylval.id = STRcpy(yytext);
                             FILTER( ID);
                           }

[0-9]+                      {
                            if (strtol(yytext, 0, 10) > 2147483649) {
                              CTIerror("Integer %s out of range", yytext);
                            }
                            yylval.cint=atoi(yytext);
                            FILTER( NUM);
                          }

[0-9]*[.][0-9]+            { yylval.cflt = atof(yytext);  
                             FILTER( FLOATVAL);
                           }

\n.*                       { global.line += 1;
                             global.col = 0;
                             yyless(1);
                           }

"/*"((\*+[^/*])|([^*]))*\**"*/"           { /* none */ }
[/][*]                                    { yy_fatal_error("Comment isn't closed"); } 
[ \t\n]+                                  { /* none */ }
"//".*                                    { /* none */ }

[ \t]                      { global.col += yyleng;
                           } 

