/*
Main program of calculator example.
Simply invoke the parser generated by bison, and then display the output.
*/

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "decl.h"
#include "expr.h"
#include "stmt.h"
#include "symbol.h"
#include "type.h"
#include "param_list.h"
#include "scope.h"

/* Clunky: Declare the parse function generated from parser.bison */
extern int yyparse();

extern FILE* yyin;

/* Clunky: Declare the result of the parser from parser.bison */
extern struct decl * parser_result;



int main( int argc, char *argv[] )
{
    decl_has_error = 0;
    int opt;
    static struct option long_options[] = {
	       {"print", 1, 0, 'p'},
        {"resolve", 1, 0, 's'},
        {"typecheck", 1, 0, 't'}
    };
    int long_index = 0;
    opt = getopt_long_only (argc, argv, "",
		long_options, &long_index);
    switch (opt) {
		case 'p':
			yyin = fopen( optarg, "r" );
      if (!yyin) {
        printf("file not opened!\n");
        exit(1);
      }
 			do {
 				if (yyparse() == 0 && yyin == 0) {
 					decl_print(parser_result, 0);
 					exit(0);
 				} else {
 					exit(1);
 				}
 			} while (1);
  		break;
    case 's':
      yyin = fopen( optarg, "r" );
      if (!yyin) {
          printf("file not opened!\n");
          exit(1);
      }
      do {
        if (yyparse() == 0 && yyin == 0) {
          decl_resolve(parser_result, SYMBOL_GLOBAL);
          exit(0);
        } else {
          exit(1);
        }
      } while (1);
      break;
    case 't':
       yyin = fopen( optarg, "r" );
      if (!yyin) {
          printf("file not opened!\n");
          exit(1);
      }
      do {
        if (yyparse() == 0 && yyin == 0) {
          decl_resolve(parser_result, SYMBOL_GLOBAL);
          decl_typecheck(parser_result);
          if (decl_has_error) {
            exit(1);
          } else {
            exit(0);           
          }
        } else {
          exit(1);
        }
      } while (1);
      break;     
		default: 
			exit(1);
     }
}
