/// tree.h
/// the header file for offspring.c
/// holds the tree data 
/// @author Russell Lee rl2939@g.rit.edu

/// NTree_S implementation for N-ary tree structure.
typedef struct NTree_S {
    char * name;           ///< name of the person.
    struct NTree_S ** children;   ///< collection of children.
    //struct NTree_S * children;   ///< collection of children.
	size_t child_count;          ///< current number of children.
    size_t capacity;             ///< capacity of children collection.
} NTree_S;

/// NTree_p is the "pointer to N-ary tree struct" type.
typedef struct NTree_S * NTree_p;

// Builds a single node in the tree
// @param person the persons name
// @return the node of the person
struct NTree_S * create_node(const char* person);

// Builds a tree for the family
//void build_tree(NTree_p ** root, const int elements[], const int count, const int capicity);

// counts the number of tokens
// @param input the input string
// @param delim the charcter to split the string with 
int token_count(char *input, char delim);

// Legacy version of the find command, do not use.
NTree_S *find_parent(char* name, NTree_S *node);

// adds a child to a parent
// @param child the child node
// @param parent the parent node
void add_child_to_parent(NTree_S *child, NTree_S *parent);

//Print children 
//@param parent the parent node
void print_children(NTree_S *parent);

