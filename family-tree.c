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

Node* find(Node* node, Data* data, Node* skip);
int equal(char* str1, char* str2);
Tree init();
void printTree(Tree t);
char* strnew(char* str);

int main(int ac, char** av) {
	Tree t = init();
	printTree(t);
	return 0;
}

void printTree(Tree t) {
	if (t == NULL) return;
	printf("name: %20s\n", t->data->name);
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
	printf("Begin construct tree\n");
	for (i = 0; i < 10; i++) {
		m = members[i];
		printf("%2d: %s => %s\n", i, m.name, m.parent);
		fflush(NULL);

		int len;
		Node* parent;
		Node* n = (Node *)malloc(sizeof(Node));
		Data* data = (Data *)malloc(sizeof(Data));
		data->age = 0;
		data->name = strnew(m.name);
		n->data = data;
		if (equal(m.parent, "")) {
			t = n;
			continue;
		}

		Data* parentData = (Data *)malloc(sizeof(Data));
		parentData->age = 0;
		parentData->name = strnew(m.parent);
		parent = find(t, parentData, NULL);
		free(parentData->name);
		free(parentData);

		if (parent == NULL) {
			printf("can not find: %s->%s (skiped)\n", m.name, m.parent);
			continue;
		}

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

char* strnew(char* str) {
	int len;
	len = strlen(str);
	char *new = (char*)malloc(len+1);
	strcpy(new, str);
	new[len] = '\0';
	return new;
}

Node* find(Node* node, Data* data, Node* skip ){
	if(node ==NULL) return NULL;
	if(0==strcmp(node->data->name,data->name)) return node;
	Node* n;
	Node* pN[4] = {node->parent, node->left, node->right, node->child};
	int i;
	for(i=0; i<4; i++) {
		if (pN[i] ==  skip) continue;
		if(pN[i]!=NULL) {
			if(NULL != (n=find(pN[i], data, node))) return n;
		}
	}
	return NULL;
}
