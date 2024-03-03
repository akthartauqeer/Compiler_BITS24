#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#define tablesize 10000000
#define NTC 54
#define TC 58
#define KC 28

typedef enum{
    program, mainFunction, otherFunctions, function, input_par, output_par, parameter_list, dataType, 
    primitiveDatatype, constructedDatatype, A, stmts, remaining_list, typeDefinitions, typeDefinition, fieldDefinitions, 
    fieldDefinition, dataType1, moreFields, declarations, declaration, colon_or_not, global_or_not, otherStmts, stmt, 
    assignmentStmt, singleOrRecId, singleOrRecId1, singleOrRecId2, funCallStmt, outputParameters, inputParameters, 
    iterativeStmt, conditionalStmt, conditionalStmt1, ioStmt, arithmeticExpression, operator_arithmetic1, arithmeticExpression1,
    operator_arithmetic2, arithmeticExpression2, operator1, operator2, booleanExpression, not_expression, not_expression2, var, 
    logicalOp, relationalOp, returnStmt, optionalReturn, idList, more_ids, definetypestmt
}non_terminals;

typedef enum{
    TK_GT, TK_LT, TK_ASSIGNOP, TK_COMMENT, TK_EQ, TK_PLUS, TK_NE, TK_LE, TK_GE, 
    TK_SQR, TK_SQL, TK_OR, TK_NOT, TK_AND, TK_ID, TK_FIELDID, TK_DIV, TK_MUL, TK_MINUS, TK_FUNID, TK_DOT, TK_CL, TK_OP, TK_COLON, 
    TK_SEM, TK_RUID, TK_COMMA, TK_NUM, TK_RNUM, TK_MAIN, TK_AS, TK_CALL, TK_DEFINETYPE, TK_ELSE, TK_END, TK_ENDIF, TK_ENDWHILE, 
    TK_ENDRECORD, TK_ENDUNION, TK_GLOBAL, TK_IF, TK_INPUT, TK_OUTPUT, TK_INT, TK_REAL, TK_LIST, TK_PARAMETERS, TK_PARAMETER, 
    TK_READ, TK_WRITE, TK_RECORD, TK_UNION, TK_RETURN, TK_THEN, TK_TYPE, TK_WHILE, TK_WITH
}terminals;

//Item of a symbol table
typedef struct sitem {
    char *lexeme;
    terminals token;
    char *type;
    int iVal;
    int lineCount;
    int eof;
    float fVal;
    int scpst;
    int scpend;
    char **parameter;
    struct sitem *next;
} SymbolItem;

typedef struct {
    SymbolItem *data[tablesize];
    int currentsize;
} Symboltable;

#define BUFFER_SIZE (1<<20)

//Twin Buffering
typedef struct {
	char firstBuf[BUFFER_SIZE];
	char secondBuf[BUFFER_SIZE];
} twinBuff;

typedef struct keyword{
    char* key;
    terminals token;
}keyword;

keyword* keywords[KC];

Symboltable * table;

FILE *fp;
char *forwardPtr, *beginPtr;
bool firstFlag, secondFlag;
int lineCount;
bool isEnd;
bool firstBufLoadable = true;
bool secondBufLoadable = true;
twinBuff twinBuffer;
