#include <stdlib.h>

#ifndef TREE_H
#define TREE_H

typedef struct treeNode{
	void* data;
	struct treeNode* children;
	unsigned int nChildren;
}treeNode;

typedef struct {
	treeNode* root;
}tree;

tree* create_tree(void* data);
treeNode* tree_add(treeNode* parent, void* data);
void destroy_tree(tree* t);

#endif