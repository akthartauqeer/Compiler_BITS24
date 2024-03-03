#ifndef parserDef
#define parserDef
#include"lexerDef.h"

#endif

//First follow sets
typedef struct terminal_node {
    terminals t;
    struct terminal_node* next;
} terminal_node;

typedef struct terminal_list {
    terminal_node* head;
} terminal_list;

typedef struct non_terminal_sets {
    terminal_list* first_set;
    terminal_list* follow_set;
} non_terminal_sets;

//Nodes of Grammar Non-Terminals

typedef struct rhs_node {
    bool isT;  // Indicates whether it's a terminal or non-terminal
    union {
        terminals t;            // Terminal value
        non_terminals non_t;     // Non-terminal value
    } value;
    struct rhs_node* next;  // Pointer to the next node in the list
    treeNode* ptr;
} RHSNode;

// A linked list containing a production rule
typedef struct production_rule {
    RHSNode* head;          // Pointer to the head of the list
    struct production_rule* next_rule;  // Pointer to the next production rule
} ProductionRule;

// Node for RHS of production rule
typedef struct lhs_node {
    ProductionRule* rules;  // Pointer to linked list of production rules
    non_terminals lhs;       // LHS non-terminal value
} LHSNode;

typedef struct grammar {
    LHSNode* rules[NTC];
} Grammar; 

typedef struct parse_table {
    ProductionRule* table[NTC][TC];
} ParseTable;

//parse tree
typedef struct tree_node {
    treeNode* parent;  
    treeNode* firstChild;   
    treeNode* rightSibling;   
    token* token_ptr;          // Pointer to the token associated with the node
    bool isT;                  
    union {
        terminals t;           // Terminal value
        non_terminals non_t;    // Non-terminal value
    } val;
} treeNode;

//stack for maintaining non-terminals
typedef struct stack {
    LHSNode* top;
    int size;
} helperStack;

//follow for non-terminals initialized
typedef struct follow {
    RHSNode *occurrence;  
    non_terminals parent_nt;
    struct follow *next;  // Pointer to the next follow struct
} followDS;

followDS *follow_occurrence[NTC]; 
Grammar *G;
non_terminal_sets first_follow_sets[NTC]; 
ParseTable* PT;
helperStack* Stack;
treeNode* root; 
