/// commands.h
/// the commands for the terminal
/// @author Russell Lee rl2939

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// add parent name, child name search for the parent and add the child to their offspring. If the arguments are missing, print a usage message and reissue the command prompt.
// @param node the node of the tree
// @param parent the name of the parent node
// @param child the child to be added
void add(NTree_S * node, char *parent, char *child);

// find - Search  from  the  tree  root  for  the  name,  and  print  the  name  and  its children list. If the name is not given, substitute the empty string. If the name is not found, report that it was not in the tree.
// @param node the node of the tree
// @param name the name to find
// @return the address of the node, or NULL if it could not be found.
NTree_S *find(NTree_S * node, char* name);

//  Print a breadth  rst traversal of all the o spring from the named person down. If the name is not given, use the name of the root person.
// @param node the node of the tree
// @param name the name to start print from 
void print(NTree_S * node, char* name);

// Compute and print the count of all members in the tree from the named person down. If the name is not given, use the name of the root person. If the name is not found, print the size of a non-existent tree as the value 0.
// @param node the root of the tree
// @param name the name of the person to be found
void size(NTree_S * node, char *name);

// Prints ofut the height of the branch
// @param node the root of the tree
// @param name the name of the person to search
void height(NTree_S * node, char *name);

// Calculates the height of the branch
// @param node the node of the tree
// @return an integer representing the current height
int calc_height(NTree_S * node);

// Delete the current tree and re-initialize the offspring tree as an empty tree
// @param node the root of the tree
void init(NTree_S * node);

// deletes the branch of the tree
// @param node the node of the tree
void tree_deleter(NTree_S * node);

// prints help
void help(void);

// frees up everything, and exits program
// @param node the node to free
void quit(NTree_S * node);
