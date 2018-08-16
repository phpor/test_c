#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

typedef struct Data {
	int age;
	char* name;
}Data;
typedef struct Node{
	 Data* data;
	 struct Node *parent,*child, *left, *right;
}Node,*Tree;
typedef struct Member{
	char* name;
	char* parent;
}Member;

Node* find(Node* node, Data* data );
int equal(char* str1, char* str2);
Tree init();
void printTree(Tree t);

int main(int ac, char** av) {
	Tree t = init();
	printTree(t);
	return 0;
}

void printTree(Tree t) {
	if (t == NULL) return;
	printf("name: %s\n", t->data->name);
	printTree(t->child);
	printTree(t->right);
}

Tree init() {
	Member members[10] = {
		{.name = "0", .parent = "" },
		{.name = "1", .parent = "0" },
		{.name = "2", .parent = "0" },
		{.name = "3", .parent = "1" },
		{.name = "4", .parent = "1" },
		{.name = "5", .parent = "2" },
		{.name = "6", .parent = "3" },
		{.name = "7", .parent = "6" },
		{.name = "8", .parent = "6" },
		{.name = "9", .parent = "7" },
	};
	int i = 0;
	Member m;
	Tree t;
	for (i = 0; i < 10; i++) {
		m = members[i];
		Node* parent;
		Node* n = (Node *)malloc(sizeof(Node));
		Data* data = (Data *)malloc(sizeof(Data));
		data->age = 0;
		data->name = (char*) malloc(strlen(m.name)+1);
		strcpy(data->name, m.name);
		n->data = data;
		if (equal(m.parent, "")) {
			t = n;
			continue;
		}

		Data* parentData = (Data *)malloc(sizeof(Data));
		parentData->age = 0;
		parentData->name = (char*) malloc(strlen(m.parent)+1);
		strcpy(parentData->name, m.parent);
		parent = find(t, parentData);
		Node* node;
		node = parent->child;
		if (node == NULL) {
			n->parent = parent;
			parent->child = n;
			continue;
		}

		for(;node->right != NULL;) {
			node = node->right;
		}
		node->right = n;
		n->left = node;
	}
	return t;
}

int equal(char* str1, char* str2) {
	return 0==strcmp(str1, str2)?1:0;
}

Node* find(Node* node, Data* data ){
	if(node ==NULL) return NULL;
	if(0==strcmp(node->data->name,data->name)) return node;
	Node* n;
	Node* pN[4] = {node->parent, node->left, node->right, node->child};
	int i;
	for(i=0; i<4; i++) {
		if(pN[i]!=NULL) {
			if(NULL != (n=find(pN[i],data))) return n;
		}
	}
	return NULL;
}
