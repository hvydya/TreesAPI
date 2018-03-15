#include "bst.h"
#pragma warning(disable : 4996)

int main() {
	BSTHead * cur = NULL;
	char b[100] = "llama";
	cur = create_bst_string(b);
	strcpy(b, "bbbbbb");
	insert_string_bst(b, &cur);
	strcpy(b, "ccccccc");
	insert_string_bst(b, &cur);
	strcpy(b, "aaaaa");
	insert_string_bst(b, &cur);
	strcpy(b, "smart");
	insert_string_bst(b, &cur);
	strcpy(b, "panting");
	insert_string_bst(b, &cur);
	strcpy(b, "smarty");
	insert_string_bst(b, &cur);
	strcpy(b, "smarxy");
	insert_string_bst(b, &cur);
	strcpy(b, "panting");
	insert_string_bst(b, &cur);
	strcpy(b, "smaert");
	insert_string_bst(b, &cur);
	strcpy(b, "smacrt");
	insert_string_bst(b, &cur);
	display_tree(cur);
	printf("\n");
	printf("%d\n", height_tree(cur->root));
	system("pause");
	return 0;
}
