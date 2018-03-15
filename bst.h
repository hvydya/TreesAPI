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
typedef int(*compare) (void *, void *);
typedef struct leaf {
	void * data;
	struct leaf * left;
	struct leaf * right;
}leaf;
typedef struct BSTHead{
	leaf * root;
	compare compare;
	print_type print_helper;
}BSTHead;

const int size_of_leaf = sizeof(leaf);
const int size_of_BSTHead = sizeof(BSTHead);

leaf * create_leaf(size_t bytes) {
	leaf * new_node = (leaf *)malloc(size_of_leaf);
	if (new_node == NULL) return NULL;
	new_node->data = (void *)malloc(bytes);
	new_node->left = NULL;
	new_node->right = NULL;
	return new_node;
}
BSTHead * create_head_bst() {
	BSTHead * head = (BSTHead *)malloc(size_of_BSTHead);
	head->compare = NULL;
	head->root = NULL;
	head->print_helper = NULL;
	return head;
}

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

int compare_int(void * a, void * b) {
	int ret_val = (*(int *)a - *(int *)b);
	if (ret_val > 0) return LEFT;
	else return RIGHT;
}
int compare_float(void * a, void * b) {
	if ((*(float *)a - *(float *)b) > 0) return LEFT;
	else return RIGHT;
}
int compare_char(void * a, void * b) {
	int ret_val = (*(char *)a - *(char *)b);
	if (ret_val > 0) return LEFT;
	else return RIGHT;
}
int compare_string(void * a, void * b) {
	char * str1 = (char *)a;
	char * str2 = (char *)b;

	int i;
	for (i = 0; str1[i] && str2[i]; i++)
	{
		if (str1[i] > str2[i]) return LEFT;
		else if (str1[i] < str2[i]) return RIGHT;
	}
	if (str2[i] == 0 && str1[i] != 0) return LEFT;
	return RIGHT;
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

BSTHead * create_bst_int(void * data) {
	size_t bytes = get_int_size(data);
	BSTHead * head = create_head_bst();
	head->root = create_leaf(bytes);
	if (memcpy(head->root->data, data, bytes) == NULL) {
		return NULL;
	}
	head->compare = compare_int;
	head->print_helper = print_int;
	return head;
}
BSTHead * create_bst_char(void * data) {
	size_t bytes = get_char_size(data);
	BSTHead * head = create_head_bst();
	head->root = create_leaf(bytes);
	if (memcpy(head->root->data, data, bytes) == NULL) {
		return NULL;
	}
	head->compare = compare_char;
	head->print_helper = print_char;
	return head;
}
BSTHead * create_bst_float(void * data) {
	size_t bytes = get_float_size(data);
	BSTHead * head = create_head_bst();
	head->root = create_leaf(bytes);
	if (memcpy(head->root->data, data, bytes) == NULL) {
		return NULL;
	}
	head->compare = compare_float;
	head->print_helper = print_float;
	return head;
}
BSTHead * create_bst_string(void * data) {
	size_t bytes = get_string_size(data);
	BSTHead * head = create_head_bst();
	head->root = create_leaf(bytes);
	if (memcpy(head->root->data, data, bytes) == NULL) {
		return NULL;
	}
	head->compare = compare_string;
	head->print_helper = print_string;
	return head;
}

int insert_node_bst(void * data, get_size get_size, BSTHead ** head) {

	if (*head == NULL) return FAIL;
	if ((*head)->root == NULL) return FAIL;

	size_t bytes = get_size(data);
	leaf * temp = (*head)->root;
	leaf * prev = NULL;
	compare fun = (*head)->compare;

	int l_or_r = 0;

	while (temp != NULL)
	{
		prev = temp;
		if (fun(temp->data, data) == 1) {
			temp = temp->left;
			l_or_r = 1;
		}
		else {
			temp = temp->right;
			l_or_r = 2;
		}
	}

	temp = create_leaf(bytes);
	if (memcpy(temp->data, data, bytes) == NULL) {
		return NULL;
	}
	if (l_or_r == 1) {
		prev->left = temp;
	}
	else {
		prev->right = temp;
	}

	return SUCCESS;
}

int insert_char_bst(char data, BSTHead ** head) {
	(*head)->compare = &compare_char;
	return insert_node_bst((char *)&data, &get_char_size, head);
}
int insert_int_bst(int data, BSTHead ** head) {

	return insert_node_bst((int *)&data, &get_int_size,  head);
}
int insert_float_bst(float data, BSTHead ** head) {
	return insert_node_bst((float *)&data, &get_float_size, head);
}
int insert_string_bst(char * data, BSTHead ** head) {
	return insert_node_bst((char *)data, &get_string_size, head);
}

int display_nodes(leaf * root, print_type print) {//INORDER
	if (root == NULL) return 0;

	leaf * temp = root;

	if (temp->left != NULL) display_nodes((temp->left), print);

	print(temp->data);

	if (temp->right != NULL) display_nodes((temp->right), print);

	return SUCCESS;
}
int display_tree(BSTHead * head) {
	return display_nodes(head->root, head->print_helper);
}

int height_tree(leaf * root) {//TEST

	if (root == NULL) return -1;

	int l_ht = height_tree(root->left);
	int r_ht = height_tree(root->right);

	if (l_ht > r_ht) return (l_ht + 1);
	else return (r_ht + 1);
}
