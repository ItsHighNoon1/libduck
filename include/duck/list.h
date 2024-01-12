#pragma once

typedef struct {
	void** data;
	int length;
	int size;
} duck_list;

duck_list* duck_list_create();

void* duck_list_get(duck_list* list, int index);

void duck_list_append(duck_list* list, void* element);

void duck_list_insert(duck_list* list, int index, void* element);

void* duck_list_replace(duck_list* list, int index, void* element);

void* duck_list_remove(duck_list* list, int index);

int duck_list_find(duck_list* list, void* element, int (*compare)(void*, void*));

void duck_list_free(duck_list* list);
