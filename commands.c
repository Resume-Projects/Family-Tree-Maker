/// commands.c
/// commands for the offspring program
/// @author Russell Lee rl2939@g.rit.edu

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "trimit.h"
#include "tree.h"
#include "queueADT.h"

// find - Search  from  the  tree  root  for  the  name,  and  print  the  name  and  its children list. If the name is not given, substitute the empty string. If the name is not found, report that it was not in the tree.
// @param node the node of the tree
// @param name the name to find
// @return the address of the node, or NULL if it could not be found.
NTree_S *find(NTree_S *node, char* name){
	//printf("hi");
	QueueADT queue = que_create(NULL);
	que_insert(queue,(void *) node);
	while( !que_empty(queue) ){
		node = (NTree_S *) que_remove( queue );
		if(strcmp(node -> name, name) == 0){
			que_clear(queue);
			que_destroy(queue);
			return node;
		}else{
			for(unsigned int i = 0; i < node->child_count; i++){
				que_insert(queue, (void *) node->children[i]);
			}
		}
	}
	que_clear(queue);
	que_destroy(queue);
	return NULL;
}

// add parent name, child name search for the parent and add the child to their offspring. If the arguments are missing, print a usage message and reissue the command prompt.
// @param node the node of the tree
// @param parent the name of the parent node
// @param child the child to be added
void add(NTree_S * node, char *parent, char *child){
	char * t_child = trim(child);
	char * t_parent = trim(parent);
	NTree_S * found_node = NULL;
	if((strcmp(t_child,"") == 0 || strcmp(t_parent,"") == 0)){
		printf("Usage: 'add parent name , child name'\n");
		return;
	}else if(node != NULL){
		found_node = find(node, t_parent);
		//printf("foundnode = %s\n", found_node->name);
	}
	if(found_node == NULL && node != NULL){
		printf("Name not in tree\n");
	
	}else if(node == NULL){
		NTree_S * parent_node = create_node(t_parent);
		node = parent_node;
		NTree_S * child_node = create_node(t_child);
		add_child_to_parent(child_node, parent_node);
	}else{
		NTree_S * child_node = create_node(t_child);
		add_child_to_parent(child_node, found_node);
	}
	return;
}

//  Print a breadth  rst traversal of all the o spring from the named person down. If the name is not given, use the name of the root person.
// @param node the node of the tree
// @param name the name to start print from 
void print(NTree_S * node, char* name){
	char * trimmed_name = trim(name);
	NTree_S * found_node = NULL;
	if(strcmp(trimmed_name,"") == 0){
		found_node = node;
	}else{
		found_node = find(node, trimmed_name);
		//printf("foundnode = %s\n", found_node->name);
	}
	if(found_node == NULL){
		printf("'%s' not found.\n", name);
		return;
	}
	QueueADT queue = que_create(NULL);
	que_insert(queue,(void *) found_node);
	while( !que_empty(queue) ){
		node = (NTree_S *) que_remove( queue );
		if(node->child_count == 0){
			printf("\n%s had no offspring.",node->name) ;		
		}else{	
			printf("\n%s had ", node->name) ;
		}
		for(unsigned int i = 0; i < node->child_count; i++){
			printf("%s", node->children[i]->name);
			if(i == node->child_count-1){
				printf(".");
			}else if(i == node->child_count-2){
					printf(" and ");
			}else{
				printf(", ");				
			}
			que_insert(queue, (void *) node->children[i]);
		}

	}
	putchar('\n');
	que_clear(queue);
	que_destroy(queue);
	return;
}

// Compute and print the count of all members in the tree from the named person down. If the name is not given, use the name of the root person. If the name is not found, print the size of a non-existent tree as the value 0.
// @param node the root of the tree
// @param name the name of the person to be found
void size(NTree_S * node, char *name){
	int counter = 0;
	char * trimmed_name = trim(name);
	NTree_S * found_node = NULL;
	counter++; // count the first node
	if(strcmp(trimmed_name,"") == 0){
		found_node = node;
	}else{
		found_node = find(node, trimmed_name);
		//printf("foundnode = %s\n", found_node->name);
	}
	if(found_node == NULL){
		printf("size: 0\n");
		return;
	}
	QueueADT queue = que_create(NULL);
	que_insert(queue,(void *) found_node);
	while( !que_empty(queue) ){
		node = (NTree_S *) que_remove( queue );
		for(unsigned int i = 0; i < node->child_count; i++){
			//printf("%s\n", node->children[i]->name);
			counter++;
			que_insert(queue, (void *) node->children[i]);
		}
	}
	printf("size: %d\n", counter);
	que_clear(queue);
	que_destroy(queue);
	return;
}

// Calculates the height of the branch
// @param node the node of the tree
// @return an integer representing the current height
int calc_height(NTree_S * node){
	int current_max_depth = 0;
	//printf("search %s at node %s\n", name, node->name);
	if(node == NULL){
		return 0;
	}else{
		//printf("recursive call\n");
		for(unsigned int i = 0; i < node->child_count; i++){
			int temp = calc_height(node->children[i]);
			if(temp > current_max_depth){
				current_max_depth = temp;				
			}
		}
	}
	// printf("about to return\n");
	return current_max_depth+1;
}

// Prints ofut the height of the branch
// @param node the root of the tree
// @param name the name of the person to search
void height(NTree_S * node, char * name){
	char * trimmed_name = trim(name);
	NTree_S * found_node = NULL;
	if(strcmp(trimmed_name,"") == 0){
		found_node = node;
	}else{
		found_node = find(node, trimmed_name);
		//printf("foundnode = %s\n", found_node->name);
	}
	if(found_node == NULL){
		printf("height: -1\n");
		return;
	}
	int total_height = calc_height(found_node) - 1;
	printf("height: %d\n", total_height);
	return;
}

// deletes the branch of the tree
// @param node the node of the tree
void tree_deleter(NTree_S * node){
	if(node != NULL){
		for(unsigned int i = 0; i < node->child_count; i++){
			tree_deleter(node->children[i]);
			//free(node->children[i]);
		}
		//printf("freeing %s\n", node->name);
		free(node->name);
		free(node->children);
		//free(node->child_count);
		//free(node->capacity);
		free(node);
		
	}	
}
// Delete the current tree and re-initialize the offspring tree as an empty tree
// @param node the root of the tree
void init(NTree_S * node){

	if(node != NULL){
		for(unsigned int i = 0; i < node->child_count; i++){
			tree_deleter(node->children[i]);
			//free(node->children[i]);
		}
		//printf("freeing %s\n", node->name);
		free(node->name);
		free(node->children);
		//free(node->child_count);
		//free(node->capacity);
		node = NULL;
	}	
}

// prints help
void help(void){
	printf("User Commands for offspring:\n");
	printf("add parent-name, child-name # find parent and add child.\n");
	printf("find name     # search and print ");
	printf("name and children if name is found.\n");
	printf("print [name]  # breadth first traversal of offspring from name.\n");
	printf("size [name]   # count members in the [sub]tree.\n");
	printf("height [name] # return the height of [sub]tree.\n");
	printf("init          # delete current tree ");
	printf("and restart with an empty tree.\n");
	printf("help          # print this information.\n");
	printf("quit          # delete current tree and end program.\n");
}

// frees up everything, and exits program
// @param node the node to free
void quit(NTree_S * node){
	if(node != NULL){
		init(node);
		free(node);
	}
	exit(0);
}

