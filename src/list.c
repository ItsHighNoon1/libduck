#include <duck/list.h>

#include <stdlib.h>

#include "inline.h"

export duck_list* duck_list_create() {
	duck_list* list = (duck_list*)malloc(sizeof(duck_list));
	if (list) {
		list->length = 0;
		list->size = 10;
		list->data = (void**)malloc(sizeof(void*) * list->size);
		if (list->data == NULL) {
			free(list);
			list = NULL;
		}
	}
	return list;
}

export void* duck_list_get(duck_list* list, int index) {
	return list->data[index];
}

export void duck_list_append(duck_list* list, void* element) {
	duck_list_insert(list, list->length, element);
}

export void duck_list_insert(duck_list* list, int index, void* element) {
	if (list->length >= list->size) {
		list->size *= 2;
		list->data = realloc(list->data, sizeof(void*) * list->size);
	}
	for (int move_to = list->length - 1; move_to > index; move_to--) {
		list->data[move_to] = list->data[move_to - 1];
	}
	list->data[index] = element;
	list->length++;
}

export void* duck_list_replace(duck_list* list, int index, void* element) {
	void* old_element = list->data[index];
	list->data[index] = element;
	return old_element;
}

export void* duck_list_remove(duck_list* list, int index) {
	void* old_element = list->data[index];
	for (int move_to = index; move_to < list->length - 1; move_to++) {
		list->data[move_to] = list->data[move_to + 1];
	}
	return old_element;
}

export int duck_list_find(duck_list* list, void* element, int (*compare)(void*, void*)) {
	for (int search_idx = 0; search_idx < list->length; search_idx++) {
		if ((*compare)(list->data[search_idx], element) == 0) {
			return search_idx;
		}
	}
	return -1;
}

export void duck_list_free(duck_list* list) {
	free(list->data);
	free(list);
}
