#include <duck/list.h>

int compare_voidptr_as_int(void* a, void* b) {
	return (long)a - (long)b;
}

int main() {
	duck_list* list = duck_list_create();
	for (long i = 0; i < 20; i++) {
		duck_list_append(list, (void*)i);
	}
	if (list->length != 20) {
		return 1;
	}
	if (duck_list_get(list, 7) != (void*)7) {
		return 2;
	}
	for (long i = 0; i < 10; i++) {
		if (duck_list_remove(list, 0) != (void*)i) {
			return 3;
		}
	}
	if (duck_list_find(list, (void*)12, compare_voidptr_as_int) != 2) {
		return 4;
	}
	if (duck_list_find(list, (void*)22, compare_voidptr_as_int) != -1) {
		return 5;
	}
	duck_list_insert(list, 5, (void*)50);
	if (duck_list_get(list, 5) != (void*)50) {
		return 6;
	}
	if (duck_list_get(list, 6) != (void*)15) {
		return 7;
	}
	duck_list_remove(list, 5);
	if (duck_list_get(list, 5) != (void*)15) {
		return 8;
	}
	if (duck_list_replace(list, 8, (void*)0) != (void*)18) {
		return 9;
	}
	if (duck_list_get(list, 8) != (void*)0) {
		return 10;
	}
	duck_list_free(list);
	return 0;
}
