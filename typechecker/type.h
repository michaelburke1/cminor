#ifndef TYPE_H
#define TYPE_H

#include "param_list.h"
#include "stdlib.h"
#include "expr.h"

typedef enum {
	TYPE_BOOLEAN,
	TYPE_CHARACTER,
	TYPE_INTEGER,
	TYPE_STRING,
	TYPE_ARRAY,
	TYPE_FUNCTION,
	TYPE_VOID
} type_kind_t;

struct type {
	type_kind_t kind;
	struct param_list *params;
	struct type *subtype;
	struct expr *num_subtype;
};

struct type * type_create( type_kind_t kind, struct param_list *params, struct type *subtype );
void          type_print( struct type *t );
void type_delete( struct type *t );

struct type * type_copy( struct type * t );
int type_compare( struct type *a, struct type *b );
void type_delete( struct type *t );

#endif
