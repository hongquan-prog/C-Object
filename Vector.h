#ifndef VECTOR_H
#define VECTOR_H

#include <stdbool.h>
#include <stdlib.h>
#include "List.h"

typedef void Vector;
typedef void *VectorNode;

Vector *vector_create(int length);
bool vector_insert(Vector *list, int i, const VectorNode node);
VectorNode vector_remove(Vector *list, int i);
int vector_find(Vector *list, const VectorNode node);
bool vector_get(Vector *list, int i, VectorNode *node);
bool vector_set(Vector *list, int i, const VectorNode node);
int vector_length(Vector *list);
void vector_destroy(Vector *list);

void vector_begin(Vector *list);
void vector_next(Vector *list);
bool vector_end(Vector *list);
VectorNode vector_current(Vector *list);

#endif