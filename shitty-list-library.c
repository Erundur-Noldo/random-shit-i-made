#include <stdio.h>
#include <stdlib.h>





struct listitem {
	int value;
	struct listitem *successor;
};


//BAD
void changeValue (struct listitem *item, int newValue) {
	(*item).value = newValue;
}



struct list {
	struct listitem *root;
};


int len(struct list l) {
	int output = 1;
	for (struct listitem currentItem = *l.root; currentItem.successor != 0; currentItem = *currentItem.successor) {
		output ++;
	}

	return output;
}

void readList (struct list l) {
	printf("{");

	struct listitem currentItem = *l.root;

	while(currentItem.successor != 0) {
		printf("%d, ", currentItem.value);
		currentItem = *currentItem.successor;
	}

	printf("%d}\n", currentItem.value);
}




void append(struct list *l, int value) {
	//find the last item in the list
	struct listitem *finalItem = (*l).root;
	while ((*finalItem).successor != 0) {
		finalItem = (*finalItem).successor;
	}


	//allocate memory for the new thingy
	struct listitem *ptr = (struct listitem*) malloc(sizeof(value) + sizeof(0));
	(*ptr).value = value;
	(*ptr).successor = 0;

	//change the successor of the final item
	(*finalItem).successor = ptr;
}


void extend(struct list *l1, struct list *l2) {
	output = *l1;

	//find the last item in the list
	struct listitem finalItem = *output.root;
	while (finalItem.successor != 0) {
		finalItem = *finalItem.successor;
	}

	(*finalItem).successor = (*l2).root;
}








int main(){

	struct listitem root;
	root.value = 5;
	root.successor = 0;

	struct list l = {&root};

	add(&l, 1);

	for (int i=0; i<10; i++){
		add(&l, value(l, len(l)-1)*2);
	}



	struct listitem root2;
	root2.value = 2;
	root.successor = 0;

	struct list l2 = {&root2};

	add(&l, 3);
	add(&l, 4);
	add(&l, 5);

	readList(l);
	readList(l2);

	extend(l, l2);
	readList(l);


	return 0;
}

