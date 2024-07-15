//#include "header.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListItem {
	struct ListItem* successor;
	char* data;
} ListItem;

typedef struct List {
	int data_size;
	struct ListItem* root;
} List;





List*     createList          (int data_size);
List*     createListFromItem  (int data_size, void* data);
List*     createListFromArray (int data_size, void* data, int num_of_data_points);
ListItem* createListItem      (void* data, int data_size);\

List*     cloneList           (List* original_list);

ListItem* getListItem         (List* list, int pos);
void      removeListItem      (List* list, int pos);
void      insert              (List* list, void* data, int pos);
void      setListItem         (List* list, void* data, int pos);
void      append              (List* list, void* data);
void      extendByArray       (List* list, void* data, int num_of_data_points);
void      extendByList        (List* list_one, List* list_two, int delete_second_list);
void      copyListItem        (List* list_one, int pos_one, List* list_two, int pos_two);
void      swapListItems       (List* list_one, int pos_one, List* list_two, int pos_two);

void      printList           (List* list, char* datatype);
int       listSize            (List* list);
void      freeList            (List* list);

int       listIsEmpty         (List* list);

void      printType           (void* pointer, int length, char* datatype);





List* createList(int data_size) {
	List* list = (List*) malloc (sizeof(data_size) + sizeof(NULL));
	list->data_size = data_size;
	list->root = NULL;
	return list;
}

List* createListFromItem(int data_size, void* data) {
	List* list = createList(data_size);
	append(list, data);
	return list;
}

List* createListFromArray(int data_size, void* data, int num_of_data_points) {
	List* list = (List*) malloc (sizeof(data_size) + sizeof(NULL));
	list->data_size = data_size;
	list->root = NULL;

	extendByArray(list, data, num_of_data_points);
	return list;
}

ListItem* createListItem(void* data, int data_size) {
	if(data == NULL) {
		printf("Error at createListItem: the data pointer is null.");
		exit(1);
	}
	ListItem* new_item = (ListItem*) malloc (sizeof(ListItem));
	new_item->successor = NULL;

	new_item->data = (char*) malloc (data_size);
	for(int i=0; i<data_size; i++) {
		new_item->data[i] = *(char*) (data + i);
	}
	return new_item;
}




List* cloneList (List* original_list) {
	List* cloned_list = (List*) malloc (sizeof(List*));
	cloned_list->data_size = original_list->data_size;
	if( listIsEmpty(original_list) ) return cloned_list;

	ListItem* item_to_clone = original_list->root;
	while(item_to_clone->successor != NULL) {
		append(cloned_list, item_to_clone->data);
		item_to_clone = item_to_clone->successor;
	}
	append(cloned_list, item_to_clone->data); /*the last, unlinked element*/

	return cloned_list;
}




ListItem* getListItem (List* list, int pos) {
	if (listIsEmpty(list)) {
		printf("Error at getListItem(). Cannot recover item from empty list.\n");
		return NULL;
	}

	pos %= listSize(list);
	if(pos < 0) pos += listSize(list);

	ListItem* current_item = list->root;
	while(pos != 0 && current_item->successor != NULL) { /*this ensures that if -1 (or any negative number) is given as pos argument, it takes the last one*/
		current_item = current_item->successor;
		pos--;
	}

	if(pos > 0) {
		printf("Error at getListItem(). Tried to retrieve item at position %d, while the list is only %d long.\n", pos+listSize(list), listSize(list));
		return NULL;
	} else {
		return current_item;
	}
}

void removeListItem (List* list, int pos) {
	pos %= listSize(list);
	if(pos < 0) pos += listSize(list);

	if (pos == 0) {
		ListItem* root = list->root;
		if(root != NULL) {
			list->root = root->successor;
			free(root);
			return;
		} else {
			printf("Error at removeListItem. Cannot remove item from empty list.\n");
			return;
		}
	}

	ListItem* item_before_pos = getListItem(list, pos-1);
	if(item_before_pos == NULL) {
		printf("Error at removeListItem(). getListItem() returned NULL.");
		return;
	}

	if(item_before_pos->successor == NULL) {
		printf("Error at removeListItem(). Tried to remove the item at the position right after the last item.");
		return;
	}

	ListItem* item_after_pos = item_before_pos->successor->successor;
	free (item_before_pos->successor);
	item_before_pos->successor = item_after_pos;
}

void insert (List* list, void* data, int pos) {
	if( listIsEmpty(list) ) {
		list->root = (ListItem*) {createListItem(data, list->data_size)};
		return;
	}


	ListItem* new_item = createListItem(data, list->data_size);

	pos %= listSize(list);
	if(pos < 0) pos += listSize(list);
	if(pos == 0) {
		new_item->successor = list->root;
		list->root = new_item;
		return;
	}


	ListItem* item_before_pos = getListItem(list, pos-1);
	if(item_before_pos == NULL) {
		printf("Error at insert(). getListItem() returned NULL.");
		return;
	}


	new_item->successor = item_before_pos->successor;
	item_before_pos->successor = new_item;
}

void setListItem (List* list, void* data, int pos) {
	if (pos >= listSize(list)) {
		printf("Error at setListItem(): tried to change position %d of the list, while the list is only %d long.", pos, listSize(list));
		return;
	}

	ListItem* item_to_set = getListItem(list, pos);
	for(int i=0; i<list->data_size; i++) {
		item_to_set->data[i] = ((char*) data)[i];
	}
}

void append (List* list, void* data) {
	if (listIsEmpty(list)) {
		list->root = (ListItem*){createListItem(data, list->data_size)};
	} else {
		ListItem* last_item = getListItem(list, -1);
		last_item->successor = (ListItem*){createListItem(data, list->data_size)};
	}
	return;
}

void extendByArray (List* list, void* data, int num_of_data_points) {
	for(int i=0; i<num_of_data_points; i++) append(list, data + i*(list->data_size));
}

void extendByList (List* list_one, List* list_two, int free_second_list) {
	if (list_one->data_size != list_two->data_size) {
		printf("Error at extendByList(): datatypes incompatible. The first list has data of size %d, and the second list of size %d.", list_one->data_size, list_two->data_size);
		return;
	}

	if( listIsEmpty(list_two) ) {
		if(free_second_list) freeList(list_two);
		return;
	}


	if(free_second_list) {
		if (listIsEmpty(list_one)) list_one                 ->root      = list_two->root;
		else                       getListItem(list_one, -1)->successor = list_two->root;
		free(list_two);
		return;
	} else {
		List* clone = cloneList(list_two);
		extendByList(list_one, clone, 1);
		return;
	}
}

void copyListItem (List* list_one, int pos_one, List* list_two, int pos_two) {
	if(list_one->data_size != list_two->data_size) {
		printf("Error at extendByList(): datatypes incompatible. The first list has data of size %d, and the second list of size %d.", list_one->data_size, list_two->data_size);
		return;
	}
	setListItem(list_two, getListItem(list_one, pos_one)->data, pos_two);
	return;
}

void swapListItems (List* list_one, int pos_one, List* list_two, int pos_two) {
	if(list_one->data_size != list_two->data_size) {
		printf("Error at extendByList(): datatypes incompatible. The first list has data of size %d, and the second list of size %d.", list_one->data_size, list_two->data_size);
		return;
	}
	char data_of_second_item[list_two->data_size];
	for(int i=0; i<list_two->data_size; i++) data_of_second_item[i] = (getListItem(list_two, pos_two)->data)[i];
	copyListItem(list_one, pos_one, list_two, pos_two);
	setListItem (list_one, data_of_second_item, pos_one);
	return;
}




void printList (List* list, char* datatype) {

	if (listIsEmpty(list)) {
		printf("{}\n");
		return;
	}

	int write_as_string = 0;
	if (strcmp(datatype, "str") == 0) write_as_string = 1;

	if (!write_as_string) printf("{");

	int list_size = listSize(list);
	ListItem* current_item = list->root;

	while (current_item->successor != NULL) {
		printType (current_item->data, list->data_size, datatype);
		current_item = current_item->successor;
		if (!write_as_string) printf(", ");
	}
	printType (current_item->data, list->data_size, datatype);

	if (!write_as_string) printf("}");
	printf("\n");
	return;
}

int listSize (List* list) {
	if (listIsEmpty(list)) return 0;

	int counter = 1;
	ListItem* current_item = list->root;

	while(current_item->successor != NULL) {
		current_item = current_item->successor;
		counter ++;
	}

	return counter;
}

void freeList (List* list) {
	while (list->root != NULL) removeListItem(list, -1);
	free(list);
}




int listIsEmpty (List* list) {
	return (list->root == NULL);
}



void printType (void* pointer, int length, char* datatype) {
	/* str, char, int, hex */
	/*-1 ~ datatype incorrect. 0 ~ no error. 1 ~ incorrect size*/
	int warning = -1;


	if (strcmp(datatype, "char") == 0 || strcmp(datatype, "str") == 0) {
		for(int i=0; i<length; i+=1) {
			printf("%c", *(char*) (pointer + i));
		}
		warning = 0;

	} else if (strcmp(datatype, "num_char") == 0) {
		for(int i=0; i<length-1; i+=1) {
			printf("%d ", *(char*) (pointer + i));
		}
		printf("%d", *(char*) (pointer + length-1)); /*so the space doesn't appear after the last one :þ*/
		warning = 0;

	} else if (strcmp(datatype, "int") == 0) {
		for(int i=0; i<length; i+=4) {
			printf("%d", *(int*)  pointer + i);
		}
		warning = 0;
		if(length % 4 != 0) warning = 1;

	} else if (strcmp(datatype, "hex") == 0) {
		if(length % 4 != 0) warning = 1;
		for(int i=0; i<length; i+=4) {
			printf("%x", *(int*)  pointer + i);
		}
		warning = 0;
		if(length % 4 != 0) warning = 1;
	}

	if(warning != 0) {
		if(warning == -1) printf("Warning at printType(): datatype %s not supported.", datatype);
		if(warning ==  1) printf("Warning at printType(): data of incorrect size; %d does not split into %ss.", length, datatype);
	}
	return;
}
