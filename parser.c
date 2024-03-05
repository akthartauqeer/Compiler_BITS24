// Group Number - 33
// 1. Shashank Khattar - 2020A7PS1509P
// 2. Omkar Gothankar - 2020A7PS0991P
// 3. Pulkit Sinha - 2020A7PS1678P
// 4. Soumya Vishnoi - 2020A7PS1512P
// 5. Tikesh Vaishnav - 2020A7PS0014P

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"parserDef.h"


char *nt_map[NT_COUNT_FULL] = {"program",
                               "moduleDeclarations",
                               "moduleDeclaration",
                               "otherModules",
                               "driverModule",
                               "module",
                               "ret",
                               "input_plist",
                               "N1",
                               "output_plist",
                               "N2",
                               "dataType",
                               "range_arrays",
                               "type",
                               "moduleDef",
                               "statements",
                               "statement",
                               "ioStmt",
                               "boolConstt",
                               "id_num_rnum",
                               "var_print",
                               "P1",
                               "simpleStmt",
                               "assignmentStmt",
                               "whichStmt",
                               "lvalueIDStmt",
                               "lvalueARRStmt",
                               "index_arr",
                               "new_index",
                               "sign",
                               "moduleReuseStmt",
                               "para_list_extension",
                               "actual_para_list_element",
                               "id_num_rnum_2",
                               "N_11",
                               "optional",
                               "idList",
                               "N3",
                               "expression",
                               "U",
                               "new_NT",
                               "var_id_num",
                               "unary_op",
                               "unary_op2",
                               "arithmeticOrBooleanExpr",
                               "N7",
                               "AnyTerm",
                               "N8",
                               "arithmeticExpr",
                               "N4",
                               "term",
                               "N5",
                               "factor",
                               "element_index_with_expressions",
                               "N_10",
                               "arrExpr",
                               "arr_N4",
                               "arrTerm",
                               "arr_N5",
                               "arrFactor",
                               "op1",
                               "op2",
                               "logicalOp",
                               "relationalOp",
                               "declareStmt",
                               "condionalStmt",
                               "caseStmts",
                               "N9",
                               "value",
                               "default",
                               "iterativeStmt",
                               "range_for_loop",
                               "index_for_loop",
                               "new_index_for_loop",
                               "sign_for_loop",
                               "undefined_nonterminal"};


char *t_map[T_COUNT] = {"INTEGER", "REAL", "BOOLEAN",
                        "OF", "ARRAY", "START",
                        "END", "DECLARE", "MODULE",
                        "DRIVER", "PROGRAM", "GET_VALUE",
                        "PRINT", "USE", "WITH",
                        "PARAMETERS", "TRUE", "FALSE",
                        "TAKES", "INPUT", "RETURNS",
                        "AND", "OR", "FOR",
                        "IN", "SWITCH", "CASE",
                        "BREAK", "DEFAULT", "WHILE",
                        "PLUS", "MINUS", "MUL",
                        "DIV", "LT", "LE",
                        "GE", "GT", "EQ",
                        "NE", "DRIVERDEF", "DRIVERENDDEF",
                        "DEF", "ENDDEF", "COLON",
                        "RANGEOP", "SEMICOL", "COMMA",
                        "ASSIGNOP", "SQBO", "SQBC",
                        "BO", "BC", "COMMENTMARK",
                        "ID", "NUM", "RNUM",
                        "$", "e", "undefined_terminal"};



char *trim(char *str)
{ // removes trailing and leading spaces
    int next = 0;
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] != ' ' && str[i] != '\t')
        {
            str[next] = str[i];
            next++;
        }
    }
    for (int i = next; i < strlen(str); i++)
    {
        str[i] = '\0';
    }

    return str;
}

// char *nt_format(char *str) {
//   str = trim(str);
//   for (int i = 0; i < strlen(str) - 2; i++) {
//     str[i] = str[i + 1];
//   }
//   str[strlen(str) - 1] = '\0';
//   str[strlen(str) - 1] = '\0';
//   return str;
// }

void break_rhs(node *n, char *str)
{                                 // loads RHS of every rule
    char *tok = strtok(str, "|"); // splitting RHS based on |
    ll *curr_rule;
    curr_rule = NULL;
    while (tok != NULL)
    {
        ll *prod_rule = (ll *)malloc(sizeof(ll)); // initializing a new production rule
        prod_rule->head = NULL;
        prod_rule->next_ll = NULL;
        new_node *curr_nn = NULL;
        for (int i = 0; i < strlen(tok); i++)
        {
            if (tok[i] == '<')
            { // checking for NT
                i++;
                char nonTerm[50] = {0};
                int nt_index = 0;
                while (tok[i] != '>')
                {
                    nonTerm[nt_index] = tok[i];
                    nt_index++;
                    i++;
                }
                for (int j = 0; j < NT_COUNT; j++)
                {
                    if (strcmp(nonTerm, nt_map[j]) == 0)
                    {
                        new_node *nn2 = (new_node *)malloc(sizeof(new_node)); // adding NT to RHS of production rule (the LL)
                        // nn2->grammar_ptr = G->non_terminal_rules[j];
                        nn2->isT = false;
                        nn2->next = NULL;
                        nn2->val.non_t = j;
                        if (prod_rule->head == NULL)
                        {
                            prod_rule->head = nn2;
                        }
                        if (curr_nn != NULL)
                        {
                            curr_nn->next = nn2;
                        }
                        curr_nn = nn2;
                        break;
                    }
                }
            }
            else if (tok[i] != ' ')
            { // checking for terminals in RHS
                char term[50] = {0};
                int ind = 0;
                while (i < strlen(tok) && tok[i] != ' ')
                {
                    term[ind] = tok[i];
                    ind++;
                    i++;
                }
                for (int j = 0; j < T_COUNT; j++)
                {
                    if (strcmp(term, t_map[j]) == 0)
                    {
                        new_node *nn2 = (new_node *)malloc(sizeof(new_node)); // adding T to RHS of production rule (the LL)
                        // nn2->grammar_ptr = NULL;
                        nn2->isT = true;
                        nn2->next = NULL;
                        nn2->val.t = j;
                        if (prod_rule->head == NULL)
                        {
                            prod_rule->head = nn2;
                        }
                        if (curr_nn != NULL)
                        {
                            curr_nn->next = nn2;
                        }
                        curr_nn = nn2;
                        break;
                    }
                }
            }
        }

        if (n->list_arr == NULL)
            n->list_arr = prod_rule;
        if (curr_rule != NULL)
            curr_rule->next_ll = prod_rule;
        curr_rule = prod_rule;
        tok = strtok(NULL, "|");
    }
}

// declarations
int *find_first_set(nonterminals nt);
int *find_follow_set(nonterminals nt);
// void break_lhs();

void init_set_arr(int *arr)
{ // initializing first and follow sets with -1
    for (int i = 0; i < SETBUFFERSIZE; i++)
    {
        arr[i] = -1;
    }
}

void join_int_sets(int *set1, int *set2)
{ // to take union of sets
    int temp[SETBUFFERSIZE];
    init_set_arr(temp);
    int temp_ind = 0;
    int i = 0;
    while (set2[i] != -1 && i < SETBUFFERSIZE)
    {
        bool isCommon = false;
        int j = 0;
        while (set1[j] != -1 && i < SETBUFFERSIZE)
        {
            if (set1[j] == set2[i])
            {
                isCommon = true;
                break;
            }
            j++;
        }
        if (!isCommon)
        {
            temp[temp_ind] = set2[i];
            temp_ind++;
        }
        i++;
    }
    int set1_ind = 0;
    while (set1[set1_ind] != undefined_terminal)
    {
        set1_ind++;
    }

    for (int i = 0; i < temp_ind; i++)
    {
        set1[set1_ind++] = temp[i];
    }
}

void findFirsts()
{ // iterates through all NT to find their first set
    for (int i = 0; i < NT_COUNT; i++)
    {
        find_first_set(i);
    }
}

int *find_first_helper(new_node *nn)
{ // finds first set of a given NT based on one production rule

    int *arr = calloc(SETBUFFERSIZE, sizeof(int));
    init_set_arr(arr);
    if (nn->isT)
    {
        arr[0] = nn->val.t;
        return arr;
    }

    int *nt_first_set = find_first_set(nn->val.non_t);
    int ind = 0;
    while (nt_first_set[ind] != undefined_terminal)
    {
        arr[ind] = nt_first_set[ind];
        ind++;
    }
    for (int i = 0; i < ind; i++)
    {
        if (arr[i] == e && nn->next != NULL)
        {
            int *next_set = find_first_helper(nn->next);
            int temp_ind = 0;
            for (int j = 0; j < SETBUFFERSIZE; j++)
            {
                if (arr[j] != e)
                {
                    arr[temp_ind] = arr[j];
                    temp_ind++;
                }
            }
            arr[temp_ind] = undefined_nonterminal;

            join_int_sets(arr, next_set);
        }
    }
    return arr;
}

int *find_first_set(nonterminals nt)
{ // calls find_first_helper on each RHS for a given NT
    if (first->set[nt][0] != undefined_terminal)
    {
        return first->set[nt];
    }

    node *n = G->non_terminal_rules[nt];
    ll *prod_rule = n->list_arr;
    int *final_set = calloc(SETBUFFERSIZE, sizeof(int));
    init_set_arr(final_set);
    while (prod_rule != NULL)
    {
        int *new_set = find_first_helper(prod_rule->head);
        join_int_sets(final_set, new_set);
        prod_rule = prod_rule->next_ll;
    }
    for (int i = 0; i < SETBUFFERSIZE; i++)
    {
        first->set[nt][i] = final_set[i];
    }

    return first->set[nt];
}

// Printing the grammar loaded into the data structure
void print_grammar()
{
    for (int i = 0; i < NT_COUNT; i++)
    {
        node *curr = G->non_terminal_rules[i];
        printf("<%s> -> ", nt_map[curr->val]);
        ll *rule = curr->list_arr;
        while (rule != NULL)
        {
            new_node *nn = rule->head;
            while (nn != NULL)
            {
                if (nn->isT)
                {
                    printf("%s ", t_map[nn->val.t]);
                }
                else
                {
                    printf("<%s> ", nt_map[nn->val.non_t]);
                }
                nn = nn->next;
            }
            if (rule->next_ll != NULL)
                printf("| ");
            rule = rule->next_ll;
        }
        printf("\n");
    }
}

void print_set(sets *printing_set)
{ // to print first or follow sets
    for (int i = 0; i < NT_COUNT; i++)
    {
        printf("%s => { ", nt_map[i]);
        for (int j = 0; j < SETBUFFERSIZE; j++)
        {
            if (printing_set->set[i][j] == undefined_terminal)
            {

                break;
            }
            else
            {
                if (j != 0)
                    printf(", ");
                printf("%s", t_map[printing_set->set[i][j]]);
            }
        }
        printf(" }\n");
    }
}

void populate_follow_occ()
{ // points to all occurences of all NTs on RHS of production rules
    for (int i = 0; i < NT_COUNT; i++)
    {
        node *curr = G->non_terminal_rules[i];
        ll *curr_ll = curr->list_arr;

        while (curr_ll != NULL)
        {
            new_node *curr_nn = curr_ll->head;
            while (curr_nn != NULL)
            {
                if (!curr_nn->isT)
                {
                    follow_ds *curr_fds = follow_occ[curr_nn->val.non_t];
                    follow_ds *new_fds = (follow_ds *)malloc(sizeof(follow_ds));
                    new_fds->next = curr_fds;
                    follow_occ[curr_nn->val.non_t] = new_fds;
                    new_fds->occ = curr_nn;
                    new_fds->parent_nt = i;
                }
                curr_nn = curr_nn->next;
            }
            curr_ll = curr_ll->next_ll;
        }
    }
}

// void print_followds(){
//   for(int i=0;i<NT_COUNT;i++){
//     printf("\n%s -> ", nt_map[i]);
//     follow_ds* curr = follow_occ[i];
//     while(curr!=NULL){
//       printf("In the rule of %s, ", nt_map[curr->parent_nt]);
//       curr=curr->next;
//     }
//   }
// }

int *find_follow_helper(new_node *occ, nonterminals parent_nt)
{ // finds follow elements based on given occurence of the NT (on RHS)

    int *arr = calloc(SETBUFFERSIZE, sizeof(int));
    init_set_arr(arr);
    new_node *nxt_nn = occ->next;
    int *n_first_set;
    if (nxt_nn != NULL)
    {

        if (nxt_nn->isT)
        {
            if (nxt_nn->val.t == e)
            {
                n_first_set = find_follow_set(parent_nt);
                join_int_sets(arr, n_first_set);
            }
            else
            {
                arr[0] = nxt_nn->val.t;
            }

            return arr;
        }

        n_first_set = first->set[nxt_nn->val.non_t];
        join_int_sets(arr, n_first_set);
        bool e_found = false;
        for (int i = 0; i < SETBUFFERSIZE && arr[i] != -1; i++)
        {
            if (arr[i] == e)
            {
                e_found = true;
                break;
            }
        }
        if (e_found)
        {
            int temp_ind = 0;
            for (int j = 0; j < SETBUFFERSIZE; j++)
            {
                if (arr[j] != e)
                {
                    arr[temp_ind] = arr[j];
                    temp_ind++;
                }
            }
            arr[temp_ind] = undefined_nonterminal;

            n_first_set = find_follow_helper(nxt_nn, parent_nt);

            join_int_sets(arr, n_first_set);
        }
    }

    else
    {
        if (!occ->isT)
        {
            if (occ->val.non_t != parent_nt)
            {

                n_first_set = find_follow_set(parent_nt);
                join_int_sets(arr, n_first_set);
            }
        }
    }
    return arr;
}

int *find_follow_set(nonterminals nt)
{ // calls find_follow_helper on every occurence of the NT on RHS
    if (follow->set[nt][0] != undefined_terminal)
    {
        return follow->set[nt];
    }

    follow_ds *curr_fds = follow_occ[nt];

    if (curr_fds == NULL)
    {
        follow->set[nt][0] = $;
        return follow->set[nt];
    }

    int *arr = calloc(SETBUFFERSIZE, sizeof(int));
    init_set_arr(arr);
    while (curr_fds != NULL)
    {
        int *temp = find_follow_helper(curr_fds->occ, curr_fds->parent_nt);
        // printf("here");
        join_int_sets(arr, temp);

        curr_fds = curr_fds->next;
        // printf("here");
    }
    for (int i = 0; i < SETBUFFERSIZE; i++)
    {
        follow->set[nt][i] = arr[i];
    }
    return follow->set[nt];
}

void findFollows()
{ // calls find_follow_set on every NT
    for (int i = 0; i < NT_COUNT; i++)
    {
        find_follow_set(i);
    }
}
void break_lhs()
{ // loading grammar LHS from text file to data structure (LL)
    char *line = (char *)malloc(BUFFERSIZE * sizeof(char));
    FILE *fp = fopen("grammar.txt", "r");

    int map_index = 0;

    while (fgets(line, BUFFERSIZE, fp))
    {
        line[strcspn(line, "\n\r")] = 0;
        node *curr_nt = NULL;
        // bool LHS_found = false;
        for (int i = 0; i < strlen(line); i++)
        {
            char nonTerm[50];
            if (line[i] == '<')
            {
                int nt_index = 0;
                i++;
                while (line[i] != '>')
                {
                    nonTerm[nt_index++] = line[i];

                    i++;
                }
                nonTerm[nt_index] = '\0';
                for (int j = map_index; j < NT_COUNT; j++)
                {
                    if (strcmp(nonTerm, nt_map[j]) == 0)
                    {
                        map_index = j;
                        curr_nt = G->non_terminal_rules[j];
                        break;
                    }
                }
            }

            if (line[i] == '=')
            {
                i++;
                int ind = 0;
                char rhs[200] = {0};
                for (; i < strlen(line); i++)
                {
                    rhs[ind] = line[i];
                    ind++;
                }
                break_rhs(curr_nt, rhs);
                break;
            }
        }
    }
    fclose(fp);
}


void populateParseTable(){
    for (int i = 0; i < NT_COUNT; i++)
    {
        
        ll* curr_ll =  G->non_terminal_rules[i]->list_arr;
        while (curr_ll !=NULL)
        {
            int* temp = find_first_helper(curr_ll->head);
            for (int j = 0; j < SETBUFFERSIZE && temp[j]!=undefined_terminal; j++)
            {
                if(temp[j]==e){
                    int* temp2 = follow->set[i];
                    // for(int k =0; k<SETBUFFERSIZE; k++){
                    //     printf("%s\n", t_map[temp2[k]]);
                    // }
                    ll* temp_ll = (ll*)malloc(sizeof(ll));
                    temp_ll->next_ll = NULL;
                    new_node* e_nn = (new_node*)malloc(sizeof(new_node));
                    e_nn->isT=true;
                    e_nn->val.t=58;
                    e_nn->next=NULL;
                    // printf("adding e to the %s for %s", nt_map[i], t_map[temp2[k]]);
                    temp_ll->head=e_nn;
                    int k=0;
                    while(temp2[k]!=undefined_terminal){
                        // printf("%s\n", t_map[temp2[k]]);
                        PT->table[i][temp2[k]] = temp_ll;
                        k++;
                    }

                }
                else
                    PT->table[i][temp[j]] = curr_ll;
            }
            
            curr_ll = curr_ll->next_ll;
        }
        
    }
    
}

void initialize()
{ // initializes the global variables
PT = (ParseTable*)malloc(sizeof(ParseTable));
    for (int i = 0; i < NT_COUNT; i++)
    {
        follow_occ[i] = NULL;
    }
    first = (sets *)malloc(sizeof(sets));
    follow = (sets *)malloc(sizeof(sets));
    for (int i = 0; i < NT_COUNT; i++)
    {
        for (int j = 0; j < SETBUFFERSIZE; j++)
        {
            first->set[i][j] = undefined_terminal;
            follow->set[i][j] = undefined_terminal;
        }
    }
    G = (Grammar *)malloc(sizeof(Grammar));
    for (int i = 0; i < NT_COUNT; i++)
    {
        node *temp = (node *)malloc(sizeof(node));
        temp->list_arr = NULL;
        temp->val = i;
        G->non_terminal_rules[i] = temp;
    }
    for (int i = 0; i < NT_COUNT; i++)
    {
        for (int j = 0; j < T_COUNT; j++)
        {
            PT->table[i][j]=NULL;
        }
    }
    
    break_lhs();
    // print_grammar();
    findFirsts();
    populate_follow_occ();
    findFollows();
    populateParseTable();
}



void print_one_rule(ll* rule){
    new_node* curr_nn = rule->head;

     while (curr_nn != NULL)
            {
                if (curr_nn->isT)
                {
                    printf("%s ", t_map[curr_nn->val.t]);
                }
                else
                {
                    printf("<%s> ", nt_map[curr_nn->val.non_t]);
                }
                curr_nn = curr_nn->next;
            }
            // printf("\n");


}

void printPT(){
    
    for (int i = 0; i < NT_COUNT; i++)
    {
        for (int j = 0; j < T_COUNT; j++)
        {
            printf("<%s>\t\t", nt_map[i]);
            printf("%s\t\t\t", t_map[j]);

            if(PT->table[i][j]!=NULL){
                print_one_rule(PT->table[i][j]);
            }
            else{
                printf("NULL");
            }
            printf("\n");
        }
        
    }
    
}

void push_stack(stack* s, new_node* nn){
    nn->next = s->head;
    s->head = nn;
}

new_node* pop_stack(stack* s){
    new_node* ret = s->head;
    s->head = ret->next;
    return ret;
}


void print_error(int line){
    printf("Syntax error at line %d\n", line);
}

bool createParseTree(token* head){
    Stack = (stack* )malloc(sizeof(stack));
    stack* temp_stack = (stack* )malloc(sizeof(stack));
    new_node* dllr = (new_node*)malloc(sizeof(new_node));
    new_node* start = (new_node*)malloc(sizeof(new_node));
    dllr->isT=true;
    dllr->val.t=57;
    // dllr->
    dllr->next=NULL;
    bool isCorrect = true;
    start->isT=false;
    start->val.non_t=program;
    start->next=dllr;
    int count=1;
    Stack->head = start;

    root=(tree_node*)malloc(sizeof(tree_node));
    root->isT=false;
    root->val.non_t=program;
    root->child=NULL;
    root->right=NULL;
    root->token_ptr=NULL;
    start->ptr = root;
    tree_node* curr_parent;

    token* curr_char = head;
    while(curr_char!=NULL){

        // if(Stack->head->isT){
        //     printf("Top of stack - %s, Ptr - %s\n", t_map[Stack->head->val.t], t_map[curr_char->type]);
        // }
        // else{
        //     printf("Top of stack - %s, Ptr - %s\n", nt_map[Stack->head->val.non_t], t_map[curr_char->type]);
        // }

        if(Stack->head->isT){
            if(curr_char->type == Stack->head->val.t){
                Stack->head->ptr->token_ptr=curr_char;
                new_node* popped = pop_stack(Stack);
                free(popped);
                curr_char = curr_char->next;
            }
            else{
                print_error(curr_char->line);
                isCorrect = false;
                return false;
                break;
            }
        }
        else{
            ll* rule = PT->table[Stack->head->val.non_t][curr_char->type];
            if(rule == NULL){
                print_error(curr_char->line);
                // printf("here\n");
                isCorrect=false;
                return false;
                break;
            }
            else{
                new_node* popped = pop_stack(Stack);             

                curr_parent=popped->ptr;

                free(popped);
                new_node* rule_itr = rule->head;
                // new_node* curr=NULL;// itr for tree
                while(rule_itr!=NULL){
                    new_node* new_st_ele = (new_node*)malloc(sizeof(new_node));
                    new_st_ele->isT = rule_itr->isT;
                    new_st_ele->val = rule_itr->val;

                    push_stack(temp_stack, new_st_ele);


                    rule_itr=rule_itr->next;
                }
                while(temp_stack->head!=NULL){
                    new_node* temp_nn = pop_stack(temp_stack);
                    tree_node* new_tree_ele = (tree_node*)malloc(sizeof(tree_node));
                    new_tree_ele->isT=temp_nn->isT;
                    new_tree_ele->val=temp_nn->val;
                    new_tree_ele->right = curr_parent->child;
                    curr_parent->child = new_tree_ele;
                    count++;
                    temp_nn->ptr = new_tree_ele;
                    // printf("%s\n", nt_map[new_tree_ele->val.non_t]);
                    if(!(temp_nn->isT && temp_nn->val.t==e)){
                        push_stack(Stack, temp_nn);
                    }
                    // printf("hwe\n");
                }
            }
        }
        // printf("%d\n", Stack->head->isT);
        if(Stack->head->isT){
            // printf("dfwfwef - %s\n", t_map[58]);
            if(Stack->head->val.t == 57){}
                // printf("correct\n");
        }
        // curr_char = curr_char->next;
    }

    // printf("Number of tokens %d\n", count);
    // printf("Number of tokens %d\n", Stack->head->val.t);
    if(curr_char==NULL){
        if(Stack->head->isT){
            if(Stack->head->val.t != $){
                print_error(-1);
                return false;
            }
            else{
                // printf("correct");
            }
        }
        else{
            while(!Stack->head->isT){
                int* first_temp = first->set[Stack->head->val.non_t];
                bool e_present=false;
                for(int k=0;k<SETBUFFERSIZE && first_temp[k]!=undefined_terminal;k++){
                    if(first_temp[k]==e){
                        e_present=true;
                        break;
                    }
                }
                if(e_present){
                    new_node* temp_nn = pop_stack(Stack);
                    curr_parent = temp_nn->ptr;
                    tree_node* new_tree_ele = (tree_node*)malloc(sizeof(tree_node));
                    new_tree_ele->isT=true;
                    new_tree_ele->val.t = e;
                    new_tree_ele->right = curr_parent->child;
                    curr_parent->child = new_tree_ele;
                    count++;
                    free(temp_nn);
                }
                else{
                    print_error(-1);
                    isCorrect=false;
                    return false;
                    break;
                }
            }
            if(isCorrect && Stack->head->val.t == $){
                printf("Syntactically correct code!\n");
                return true;
            }
        }

    }
    return isCorrect;
}

void print_tree(tree_node* root, bool goRight, FILE *fp){

    if(root==NULL){
        return;
        }
    if(root->isT){
        printf("%s ", t_map[root->val.t]);
        fprintf(fp, "%s ", t_map[root->val.t]);
        if(goRight) print_tree(root->right, true, fp);
    }
    else{
        print_tree(root->child, false, fp);
        printf("<%s> ", nt_map[root->val.non_t]);
        fprintf(fp, "<%s> ", nt_map[root->val.non_t]);
        if(root->child!=NULL)
            print_tree(root->child->right, true, fp);
        if(goRight) print_tree(root->right, true, fp);
        // print_tree(root->right, true);
    }
}


// int main()
// {
//     initialize();
//     // print_grammar();
//     // printf("**********************************************************\n");
//     // print_set(first);
//     // printf("**********************************************************\n");
//     print_set(follow);
//     // printf("**********************************************************\n");
//     // printPT();


//     return 0;
// }
