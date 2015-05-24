#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "main.h"

struct list_cell
{
  celestial_object object;
  struct list_cell *next;
};

typedef struct list_cell* list;


list new_list();
list push(celestial_object obj, list L);

bool is_empty(list L);
celestial_object head(list L);
list tail(list L);
void list_free(list *L);
void delete(list celest_obj, list *L);

#endif
