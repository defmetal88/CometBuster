#include "list.h"

list new_list()
{
  return NULL;
}

list push(celestial_object obj, list L)
{
  list new = new_list();

  new = (list) malloc(sizeof(struct list_cell));
  new->object = obj;
  new->next = L;
  return new;
}

bool is_empty(list L)
{
  if (L == NULL)
    return true;
  return false;
}

celestial_object head(list L)
{
  return L->object;
}

list tail(list L)
{
  if (is_empty(L))
    return NULL;
  return L->next;
}


/* delete del_elmt from list L */
void delete(list del_elmt, list *L)
{
  list tmp;
  list to_delete;
  tmp = *L;

  /* The list is not empty */
  if (!is_empty(tmp)) {
    /* if  the first element is the one to delete */
    if (tmp == del_elmt) {
      to_delete = *L;
      *L = tail(*L);
      free(to_delete);
    }
    /* else we browse the list to find del_elmt */
    else {
      while (tmp->next != del_elmt && tmp->next != NULL) {
	tmp = tail(tmp);
      }
      if (tmp->next != NULL) {
	to_delete = tmp->next;
	tmp->next = tmp->next->next;
	free(to_delete);
      }
    }
  }
}

void list_free(list *L)
{
  list tmp;
  while (!is_empty(*L)) {
    tmp = *L;
    *L = tail(*L);
    free(tmp);
  }
}
