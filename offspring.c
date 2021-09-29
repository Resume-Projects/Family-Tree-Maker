/// offspring.c
/// builds and modifies a tree from one person
/// @author Russell Lee rl2939@g.rit.edu

# define _GNU_SOURCE
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include "trimit.h"
# include "tree.h"
# include "commands.h"
# include "queueADT.h" //"A future assignment in this course might need a queue. You are free to use this."

# define MAX 65535

// parses the file into a tree
// @param param[] the file to extract data from
// @param root the root node of the tree.
void file_parser(char param[], NTree_S** root){
		size_t n = 0;
		char *line = NULL;
		char *token = NULL;
		char *parent = NULL;
		char *child = NULL;
		NTree_S * parent_node;
		NTree_S * child_node;
		
		FILE *fileptr = fopen(param,"r");
		if(!fileptr){
			perror("file open failed\n");
			exit(1);
		}
		while(getline(&line, &n, fileptr) != -1){
			token = strtok(line,",");
			parent = trim(token);
			parent_node = NULL ;
			
			if(strcmp(parent,"")){
				//printf("\nParent: %s\n", parent);

				if(*root == NULL){
					//printf("No node found, creating node...\n");
					parent_node = create_node(parent);
					//printf("Parent node created! name is %s\n", parent_node->name);
					*root  = parent_node ;
				}else{
					// search for parent in tree and get the node where the node name = panrent value 
					
					//printf("Root is %s\n",(*root)->name);
					parent_node = find(*root, parent);
					if(parent_node == NULL){
						
					}			
				}
				if(parent_node == NULL){
					// check if named child is the root of the tree
					while(token != NULL){			
						token = strtok(NULL,",");
						child = trim(token);
						if(child == NULL){break;}	
						//printf("Root is %s\n",(*root)->name);
						//printf("child is %s\n",child);
						if(!strcmp(child,(*root)-> name)){
							//printf("adding name to node");
							NTree_S * new_parent = create_node(parent);
							add_child_to_parent((*root), new_parent);
							//break;
						}else{
							printf("error: '%s' is not in the tree and '%s' is not the root.\n", parent, child);
						}
					}
				}else{
					while(token != NULL){				
						token = strtok(NULL,",");
						child = trim(token);
						if(child != NULL ){
							//printf("Child: %s\n", child);
							child_node = create_node(child);
							add_child_to_parent(child_node, parent_node);
							//printf("added child");
						}
					} 
				}
			}
		}
		putchar('\n');
		fclose(fileptr);
		free(line);
}

// A command line 'menu' to put commands in.
void menu(NTree_S * tree){
	int exiting = 0;
	while(exiting == 0){
		char *token;
		//char *param;
		printf("> ");
		char input[MAX];
		fgets(input,MAX,stdin);
		if(strcmp(trim(input),"") == 0){
			continue;
		}
		//printf("input: %s\n", input);
		token = strtok(input," ");
		//printf("token: %s\n", token);
		
		if(strcmp(token,"add") == 0){
			char * parent;
			//fprintf(stdout,"hi\n");
			//fflush( stdout );
			token = strtok(NULL, ",");
			//fprintf(stdout,"hi\n");
			//fflush( stdout );
			parent = token;		
			token = strtok(NULL, "");
			//fprintf(stdout,"parent: %s, child: %s", parent, token);
			//fflush( stdout );
			if(parent == NULL){
				parent = "";
			}
			if(token == NULL){
				token = "";			
			}
			add(tree, parent, token);	
		}
		else if(strcmp(token,"find") == 0){
			token = strtok(NULL, "");
			if(token == NULL){
				token = "";			
			}		
			//fprintf(stdout,"%s\n", token);
			//fflush( stdout );	
			NTree_S * node = find(tree, token);
			if(node != NULL){
				if(node->child_count >= 1){
					printf("%s had ",node->name);
				}else{
					printf("%s is found, has no children\n", node->name);
					continue;
				}				
				for(unsigned int i = 0; i < node->child_count; i++){
					printf("%s", node->children[i]->name);
					if(i == node->child_count-1){
						printf(".\n");
					}else if(i == node->child_count-2){
							printf(" and ");
					}else{
						printf(", ");				
					}
				}
			}else{
				printf("error: '%s' not found\n", token);			
			}	
		}
		else if(strcmp(token,"print") == 0){
			token = strtok(NULL, "");			
			if(token == NULL){
				token = "";			
			}
			print(tree, token);		
		}
		else if(strcmp(token,"size") == 0){
			token = strtok(NULL, "");	
			if(token == NULL){
				token = "";			
			}		
			size(tree, token);	
		}
		else if(strcmp(token,"height") == 0){
			token = strtok(NULL, "");	
			if(token == NULL){
				token = "";			
			}		
			height(tree, token);	
		}
		else if(strcmp(token,"init") == 0){
			init(tree);
			tree = NULL;
		}
		else if(strcmp(token,"help") == 0){
			help();		
		}
		else if(strcmp(token,"quit") == 0){
			exiting = 1;	
			quit(tree);
		}
		else{
			printf("Invalid command\n");
		}		
	}
	
}


// The main function of this program
// @param argc the number of arguments
// @param argv the arguments placed in
// @return a number
int main(int argc, char *argv[]){
	/*printf("argc: %d\n", argc); */
	//printf("argv: %s\n", argv[0]);
	//printf("argv: %s\n", argv[1]);

	NTree_S *root = NULL;
	if(argc == 2){
		file_parser(argv[1], &root);
	}
	menu( root );
	return 0;
}
