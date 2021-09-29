/// tree.c
/// Functions to help generate a family tree
/// @author Russell Lee

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "trimit.h"
#include "tree.h"

#define MORE_SIZE 5

// The node is called NTree_S

// Builds a single node in the tree
// @param person the persons name
// @return the node of the person
NTree_S * create_node( const char* person){
	NTree_S * node = (NTree_S*) malloc(sizeof(NTree_S));
	//if(node != NULL){
	//strncpy(node->name, person, 1024);
	node->name = malloc(strlen(person)+1);
	strcpy(node->name,person);
	//node->name = person;
	node->children = NULL;
	node->child_count = 0;
	node->capacity = 0;
	//}
	return node;
}

// counts the number of tokens
// @param input the input string
// @param delim the charcter to split the string with 
int token_count(char *input, char delim){
	int counter = 0;
	if(strcmp(trim(input),"")){
		return counter;
	}
	const char *p = input;
	do{
		if(*p == delim){
			counter++;
		}
	}while (*(p++));
	return counter + 1;
} 

// adds a child to a parent
// @param child the child node
// @param parent the parent node
void add_child_to_parent(NTree_S *child, NTree_S *parent){
	//make the capacity if needed
	if(parent->capacity == parent -> child_count){
		parent->children = realloc(parent->children,(parent->capacity+MORE_SIZE) * sizeof(NTree_S));
		parent-> capacity += MORE_SIZE;		
	}
	parent->children[parent->child_count] = child;

	parent->child_count++;

}

//Print children 
//@param parent the parent node
void print_children(NTree_S *parent){
	for(unsigned int i = 0; i < parent->child_count; i++){
		printf("the child is: %s\n",parent->children[i]->name);
	}
}

// Legacy version of the find command, do not use.
NTree_S *find_parent(char* name, NTree_S *node){
	NTree_S * found_node = NULL;

	printf("search %s at node %s\n", name, node->name);
	if(strcmp(node->name, name) == 0){
		printf("found node\n");
		found_node = node;
	}else{
		printf("recursive call\n");
		for(unsigned int i = 0; i < node->child_count; i++){
			
			found_node = find_parent(name, node->children[i]);
			if(found_node != NULL){
				break;
			}
		}
	}
	printf("about to return\n");
	return found_node;
}

