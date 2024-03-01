#include<"parserDef.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void create_parse_table() {
    PT = (ParseTable*)malloc(sizeof(ParseTable));
    if (PT == NULL) {
        fprintf(stderr, "Memory allocation failed for parse table.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < NTC; i++) {
        for (int j = 0; j < TC; j++) {
            PT->table[i][j] = NULL;
        }
    }
}

void initiate_parse_table() {
    for (int i = 0; i < NTC; i++) {
        LHSNode* current_lhs = G->rules[i];
        while (current_lhs != NULL) {
            ProductionRule* current_rule = current_lhs->rules;
            while (current_rule != NULL) {
                RHSNode* rhs_node = current_rule->head;=
                if (rhs_node->isT) {
                    PT->table[i][rhs_node->value.t] = current_rule;
                } else {
                    terminal_node* first_terminal = first_follow_sets[rhs_node->value.non_t]->first_set->head;
                    while (first_terminal != NULL) {
                        PT->table[i][first_terminal->t] = current_rule;
                        first_terminal = first_terminal->next;
                    }
                }
                current_rule = current_rule->next_rule;
            }
            
            current_lhs = current_lhs->next;
        }
    }
}
void print_parse_table() {
    printf("Parse Table:\n");
    printf("Non-terminals/Terminals\t");
    for (int j = 0; j < TC; j++) {
        printf("%d\t", j);
    }
    printf("\n");

    for (int i = 0; i < NTC; i++) {
        printf("%d\t", i);
        for (int j = 0; j < TC; j++) {
            if (PT->table[i][j] != NULL) {
                printf("%d\t", PT->table[i][j]); // Print the pointer value
            } else {
                printf("NULL\t");
            }
        }
        printf("\n");
    }
}
