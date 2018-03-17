#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#define SUCCESS 1
#define FAIL 0
#define LEFT 1
#define RIGHT -1

typedef void(*print_type) (void *);
typedef size_t(*get_size) (void *);
typedef struct leaf {
	void * data;
	struct leaf * left;
	struct leaf * right;
	print_type print_helper;
}leaf;
typedef struct bt_head {
	struct leaf * root;
	int elements;
	int level;
}bt_head;

const int size_of_leaf = sizeof(leaf);
const int size_of_tree = sizeof(bt_head);

void print_int(void * a) {
	printf("%d ", *(int *)a);
}
void print_string(void * a) {
	printf("%s ", (char *)a);
}
void print_char(void * a) {
	printf("%c ", *(char *)a);
}
void print_float(void * a) {
	printf("%0.2f ", *(float *)a);
}

size_t get_int_size(void *data) {
	return sizeof(int);
}
size_t get_float_size(void *data) {
	return sizeof(float);
}
size_t get_char_size(void *data) {
	return sizeof(char);
}
size_t get_string_size(void *data) {
	size_t size = strlen((char *)data) + 1;
	return size;
}

bt_head * create_root() {
	bt_head * root = (bt_head *)malloc(sizeof(bt_head));
	root->root = NULL;
	root->level = 0;
	root->elements = 0;
	return root;
}
leaf * create_empty_leaf(size_t bytes) {
	leaf * new_leaf = (leaf *)malloc(size_of_leaf);
	if (new_leaf == NULL) return NULL;
	new_leaf->data = (void *)malloc(bytes);
	new_leaf->left = NULL;
	new_leaf->right = NULL;
	new_leaf->print_helper = NULL;
	return new_leaf;
}
leaf * create_leaf(void * data, get_size size, print_type print_helper) {
	size_t bytes = size(data);
	leaf * new_leaf = create_empty_leaf(bytes);
	if (memcpy(new_leaf->data, data, bytes) == NULL) {
		return NULL;
	}
	new_leaf->print_helper = print_helper;
	return new_leaf;
}

bt_head * create_tree_int(void * data) {
	size_t bytes = get_int_size(data);
	bt_head * head = create_root();
	head->root = create_empty_leaf(bytes);
	if (memcpy(head->root->data, data, bytes) == NULL) {
		return NULL;
	}
	head->root->print_helper = print_int;
	head->elements = 1;
	head->level = 1;
	return head;
}
bt_head * create_tree_char(void * data) {
	size_t bytes = get_char_size(data);
	bt_head * head = create_root();
	head->root = create_empty_leaf(bytes);
	if (memcpy(head->root->data, data, bytes) == NULL) {
		return NULL;
	}
	head->root->print_helper = print_char;
	head->elements = 1;
	head->level = 1;
	return head;
}
bt_head * create_tree_float(void * data) {
	size_t bytes = get_float_size(data);
	bt_head * head = create_root();
	head->root = create_empty_leaf(bytes);
	if (memcpy(head->root->data, data, bytes) == NULL) {
		return NULL;
	}
	head->root->print_helper = print_float;
	head->elements = 1;
	head->level = 1;
	return head;
}
bt_head * create_tree_string(void * data) {
	size_t bytes = get_string_size(data);
	bt_head * head = create_root();
	head->root = create_empty_leaf(bytes);
	
	if (memcpy(head->root->data, data, bytes) == NULL) {
		return NULL;
	}
	head->root->print_helper = print_string;
	head->elements = 1;
	head->level = 1;
	
	return head;
}

int get_max_elements(int level) {
	int i;
	int max = 0;
	for (i = 0; i <= level ; i++)
	{
		max += (int)pow(2, i);
	}
	return max;
}

leaf * get_next_empty_leaf(int level, int * side, leaf ** root, leaf ** prev) {//WORKING
	leaf * ans;

	if (level < 0) return NULL;

	if ((*root)->left != NULL) {
		ans = get_next_empty_leaf(level - 1, side, &(*root)->left, root);
	}
	else {
		*side = LEFT;
		return (*root);
	}

	if (ans != NULL) return ans;

	if ((*root)->right != NULL && ans == NULL) {
		ans = get_next_empty_leaf(level - 1, side, &(*root)->right, root);
	}
	else {
		*side = RIGHT;
		return (*root);
	}

	return ans;
}
int insert_leaf_bt(void * data, get_size size, print_type print_helper, bt_head ** head) {
	int side = 0;
	int current_level = (*head)->level;
	int max = get_max_elements(current_level);
	leaf * new_leaf = get_next_empty_leaf(current_level - 1, &side, &(*head)->root, NULL);

	if (new_leaf == NULL) {
		printf("FAILED TO INSERT\n");
		return FAIL;
	}

	if (side == LEFT)
	{
		new_leaf->left = create_leaf(data, size, print_helper);
	}
	else
	{
		new_leaf->right = create_leaf(data, size, print_helper);
	}

	if (++((*head)->elements) == max)
	{
		((*head)->level)++;
	}

	return SUCCESS;
}

int insert_leaf_bt_int(int data, bt_head ** head) {
	return insert_leaf_bt((void *)&data, &get_int_size, &print_int, head);
}
int insert_leaf_bt_char(char data, bt_head ** head) {
	return insert_leaf_bt((void *)&data, &get_char_size, &print_char, head);
}
int insert_leaf_bt_float(float data, bt_head ** head) {
	return insert_leaf_bt((void *)&data, &get_float_size, &print_float, head);
}
int insert_leaf_bt_string(char * data, bt_head ** head) {
	return insert_leaf_bt((void *)data, &get_string_size, &print_string, head);
}

int display_tree(leaf ** head) {//INORDER
	if (*head == NULL) return 0;

	leaf * temp = (*head);

	if (temp->left != NULL) display_tree(&(temp->left));

	temp->print_helper(temp->data);

	if (temp->right != NULL) display_tree(&(temp->right));

	return SUCCESS;
}

int height_tree(leaf * head) {//TEST

	if (head == NULL) return 0;

	int l_ht = height_tree(head->left);
	int r_ht = height_tree(head->right);

	if (l_ht > r_ht) return (l_ht + 1);
	else return (r_ht + 1);
}

