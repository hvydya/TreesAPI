#include "binary_tree.h"
#pragma warning(disable : 4996)

int main() {
	char str[30] = "Tree";
	int sample_int = 13;
	float sample_float = 12.08;
	void * s = str;
	bt_head * b = create_tree_string(s);
	insert_leaf_bt_int(sample_int, &b);
	strcpy(str, "PI");
	insert_leaf_bt_string(str, &b);
	char sample_char = 'c';
	insert_leaf_bt_char(sample_char, &b);
	insert_leaf_bt_float(sample_float, &b);
	sample_float = 3.14;
	insert_leaf_bt_float(sample_float, &b);
	display_tree(&b->root);
	printf("\n");
	printf("%d\n", height_tree(b->root));
	system("pause");
	return 0;
}