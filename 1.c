#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#define tablesize 10000000
typedef enum gitem {
    program, mainFunction, otherFunctions, function, input_par, output_par, parameter_list, dataType, 
    primitiveDatatype, constructedDatatype, A, stmts, remaining_list, typeDefinitions, typeDefinition, fieldDefinitions, 
    fieldDefinition, dataType1, moreFields, declarations, declaration, colon_or_not, global_or_not, otherStmts, stmt, 
    assignmentStmt, singleOrRecId, singleOrRecId1, singleOrRecId2, funCallStmt, outputParameters, inputParameters, 
    iterativeStmt, conditionalStmt, conditionalStmt1, ioStmt, arithmeticExpression, operator_arithmetic1, arithmeticExpression1,
    operator_arithmetic2, arithmeticExpression2, operator1, operator2, booleanExpression, not_expression, not_expression2, var, 
    logicalOp, relationalOp, returnStmt, optionalReturn, idList, more_ids, definetypestmt,TK_GT, TK_LT, TK_ASSIGNOP, TK_COMMENT, 
    TK_SQR, TK_SQL, TK_OR, TK_NOT, TK_AND, TK_ID, TK_FIELDID, TK_DIV, TK_MUL, TK_MINUS, TK_FUNID, TK_DOT, TK_CL, TK_OP, TK_COLON, 
    TK_SEM, TK_RUID, TK_COMMA, TK_NUM, TK_RNUM, TK_MAIN, TK_AS, TK_CALL, TK_DEFINETYPE, TK_ELSE, TK_END, TK_ENDIF, TK_ENDWHILE, 
    TK_ENDRECORD, TK_ENDUNION, TK_GLOBAL, TK_IF, TK_INPUT, TK_OUTPUT, TK_INT, TK_REAL, TK_LIST, TK_PARAMETERS, TK_PARAMETER, 
    TK_READ, TK_WRITE, TK_RECORD, TK_UNION, TK_RETURN, TK_THEN, TK_TYPE, TK_WHILE, TK_WITH
} grammerItem;
typedef struct sitem{
    char *lexeme;
    grammerItem token;
    char *type;
    int scpst;
    int scpend;
    char **parameter;
    SymbolItem * next;
} SymbolItem;

typedef struct Stable{
    SymbolItem *data[tablesize];
    int currentsize;
} SymbolTable;
SymbolTable* table;
SymbolTable* initializeSymbolTable() {
   table= (SymbolTable* )(malloc(sizeof(SymbolTable)));
    for(int i=0;i<tablesize;i++){
        table->data[i]=NULL;
    }
    table->currentsize=0;
    return table;
}
int hash(char *lexeme) {
    unsigned long hash = 5381;
    int c;
    while ((c = *lexeme++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash % tablesize;
}
void insert(char *lexeme, grammerItem token) {
    int index = hash(lexeme);

    // Check if the lexeme already exists
    if (!lookup(lexeme)) {
        // Lexeme doesn't exist, create a new SymbolItem
        SymbolItem *newItem = (SymbolItem *)malloc(sizeof(SymbolItem));
        newItem->lexeme = strdup(lexeme); // Make a copy of lexeme
        newItem->token = token;
        newItem->next = NULL; // Initialize next pointer

        // Insert newItem into the symbol table
        if (table->data[index] == NULL) {
            // No collision, insert newItem directly
            table->data[index] = newItem;
        } else {
            // Collision occurred, append newItem to the existing linked list
            SymbolItem *current = table->data[index];
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newItem;
        }
        table->currentsize++;
    } else {
        // Lexeme already exists, handle as needed
        printf("Lexeme %s already exists in the symbol table.\n", lexeme);
    }
}
bool lookup(char *lexeme) {
    int index = hash(lexeme);

    // Traverse the linked list at index to find the lexeme
    SymbolItem *current = table->data[index];
    while (current != NULL) {
        if (strcmp(current->lexeme, lexeme) == 0) {
            // Lexeme found in the symbol table
            return true;
        }
        current = current->next;
    }
    // Lexeme not found in the symbol table
    return false;
}