#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define fragmentLength 4

struct LineFragment {
	char text[fragmentLength+1];
	struct LineFragment* next_fragment;
};

void append();

struct LineFragment* createLine (char text[]) {
	struct LineFragment* root = (struct LineFragment*) malloc (sizeof(struct LineFragment));
	strncpy(root->text, text, fragmentLength);


	int number_of_fragments = strlen(text) / fragmentLength + (strlen(text) % fragmentLength != 0); //ceil
	for(int i=1; i<number_of_fragments; i++) {
		char new_line_string[fragmentLength];
		strncpy(new_line_string, text + i*fragmentLength, fragmentLength); //because text is a pointer, and we just add a bit to that to start further in the string
		append(root, new_line_string);
	}


	return root;
}




void printLine (struct LineFragment* line) {
	while (line->next_fragment != 0) {
		printf("%s", line->text);
		line = line->next_fragment;
	}

	printf("%s", line->text);
}


void debugPrintLine (struct LineFragment* line) {
	while (line->next_fragment != 0) {
		printf("%s | ", line->text);
		line = line->next_fragment;
	}

	printf("%s", line->text);
}


void append (struct LineFragment* root, char new_text[]) {
	while (root->next_fragment != NULL) root = root->next_fragment;

	struct LineFragment* new_fragment = (struct LineFragment*) malloc (sizeof(struct LineFragment));
	strncpy(new_fragment->text, new_text, fragmentLength);
	new_fragment->next_fragment = NULL;

	root->next_fragment = new_fragment;
}


void insert (struct LineFragment* root, char new_character, int pos) {
	/*inserts a character at a certain position. If pos==-1, at the end.*/

	if (pos == -1) {
		/*we start by finding the last pos*/
		while(root->next_fragment != NULL) root = root->next_fragment;
		pos = strlen(root->text);
	}



	// /*shift to make room for the new character*/
	// insert(root->next_fragment, root->text[fragmentLength-1])

	while(pos > fragmentLength) {
		root = root->next_fragment;
		pos -= fragmentLength;
	}

	if(pos == fragmentLength) {

			if(root->next_fragment == NULL) {
				append(root, &new_character); /*pretty sure making it a pointer to a char makes it basically a string??*/
			} else {
				insert(root->next_fragment, new_character, 0);
			}


	} else { /*in which case: pos < fragmentLength*/



		/*making sure the last character of the fragment is put at the beginning of the next
		  the problem is that there might not be a next one *yet*, in which case we add an extra case to handle that*/
		if(strlen(root->text) == fragmentLength) {
			if(root->next_fragment == NULL) {
				append(root, &root->text[fragmentLength-1]); /*pretty sure making it a pointer to a char makes it basically a string??*/
			} else {
				insert(root->next_fragment, root->text[fragmentLength-1], 0);
			}
		}

		/*then shifting the rest along*/
		for(int i=fragmentLength-1; i>pos; i--) {
			root->text[i] = root->text[i-1];
		}
		root->text[pos] = new_character;
	}

}



int main(){

	// struct LineFragment root = {"test", NULL};
	// append(&root, " succ");
	// append(&root, "eeded");
	// printLine(&root);

	// struct LineFragment* line = createLine("the test has succeeded");
	// insert(line, 'a', 0);
	// printLine(line);


	// struct LineFragment* line = createLine("test");
	// insert(line, 'i', 2);
	// insert(line, 'i', 2);
	// insert(line, 'i', 2);
	// insert(line, 'i', 2);
	// insert(line, 'i', 2);
	// insert(line, 'i', 2);
	// insert(line, 'i', 2);
	// debugPrintLine(line);

	// struct LineFragment* line = createLine("testng");
	// insert(line, 'i', 4);
	// debugPrintLine(line);

	// struct LineFragment* line = createLine("test");
	// insert(line, ' ', -1);
	// insert(line, 's', -1);
	// insert(line, 'u', -1);
	// insert(line, 'c', -1);
	// insert(line, 'c', -1);
	// insert(line, 'e', -1);
	// insert(line, 'e', -1);
	// insert(line, 'd', -1);
	// insert(line, 'e', -1);
	// insert(line, 'd', -1);
	// debugPrintLine(line);


	return 0;
}

