#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define tablesize 10000000
#define NTC 54
#define TC 59
#define KC 28

/*
GROUP_NO_39
Dhruv Kamra - 2021A7PS0713P
Navneet Singla - 2021A7PS1450P
Tauqeer Akthar- 2021A7PS1628P
Archisha Mehta - 2020B3A70779P
Saloni Bhandari - 2020B1A71602P 
*/
typedef enum{
    program, mainFunction, otherFunctions, function, input_par, output_par, parameter_list, dataType, 
    primitiveDatatype, constructedDatatype, A, stmts, remaining_list, typeDefinitions, typeDefinition, fieldDefinitions, 
    fieldDefinition, fieldtype, moreFields, declarations, declaration, global_or_not, otherStmts, stmt, 
    assignmentStmt, singleOrRecId, option_single_constructed, oneExpansion, moreExpansions, funCallStmt, outputParameters, inputParameters, 
    iterativeStmt, conditionalStmt, elsePart, ioStmt, arithmeticExpression, expPrime, term, 
    termPrime, factor, highPrecedenceOperators, lowPrecedenceOperators, booleanExpression, var, 
    logicalOp, relationalOp, returnStmt, optionalReturn, idList, more_ids, definetypestmt, actualOrRedefined
}non_terminals;

typedef enum{
    TK_GT, TK_LT, TK_ASSIGNOP, TK_COMMENT, TK_EQ, TK_PLUS, TK_NE, TK_LE, TK_GE, 
    TK_SQR, TK_SQL, TK_OR, TK_NOT, TK_AND, TK_ID, TK_FIELDID, TK_DIV, TK_MUL, 
    TK_MINUS, TK_FUNID, TK_DOT, TK_CL, TK_OP, TK_COLON, TK_SEM, TK_RUID, 
    TK_COMMA, TK_NUM, TK_RNUM, TK_MAIN, TK_AS, TK_CALL, TK_DEFINETYPE, 
    TK_ELSE, TK_END, TK_ENDIF, TK_ENDWHILE, TK_ENDRECORD, TK_ENDUNION, 
    TK_GLOBAL, TK_IF, TK_INPUT, TK_OUTPUT, TK_INT, TK_REAL, TK_LIST, 
    TK_PARAMETERS, TK_PARAMETER, TK_READ, TK_WRITE, TK_RECORD, TK_UNION, 
    TK_RETURN, TK_THEN, TK_TYPE, TK_WHILE, TK_WITH, EPS, END_OF_INPUT
}terminals;

char* terms[]={
    "TK_GT", "TK_LT", "TK_ASSIGNOP", "TK_COMMENT", "TK_EQ", "TK_PLUS", "TK_NE", "TK_LE", 
    "TK_GE", "TK_SQR", "TK_SQL", "TK_OR", "TK_NOT", "TK_AND", "TK_ID", "TK_FIELDID", 
    "TK_DIV", "TK_MUL", "TK_MINUS", "TK_FUNID","TK_DOT", "TK_CL", "TK_OP", "TK_COLON",
    "TK_SEM", "TK_RUID", "TK_COMMA", "TK_NUM", "TK_RNUM", "TK_MAIN", "TK_AS", "TK_CALL", 
    "TK_DEFINETYPE", "TK_ELSE", "TK_END", "TK_ENDIF", "TK_ENDWHILE", "TK_ENDRECORD", 
    "TK_ENDUNION", "TK_GLOBAL", "TK_IF", "TK_INPUT", "TK_OUTPUT", "TK_INT", "TK_REAL", 
    "TK_LIST", "TK_PARAMETERS", "TK_PARAMETER", "TK_READ", "TK_WRITE", "TK_RECORD", 
    "TK_UNION", "TK_RETURN", "TK_THEN", "TK_TYPE", "TK_WHILE", "TK_WITH", "EPS", "END_OF_INPUT"
};

char* non_terms[]={
    "program", "mainFunction", "otherFunctions", "function", "input_par", "output_par", "parameter_list", "dataType", 
    "primitiveDatatype", "constructedDatatype", "A", "stmts", "remaining_list", "typeDefinitions", "typeDefinition", "fieldDefinitions", 
    "fieldDefinition", "fieldtype", "moreFields", "declarations", "declaration", "global_or_not", "otherStmts", "stmt", 
    "assignmentStmt", "singleOrRecId", "option_single_constructed", "oneExpansion", "moreExpansions", "funCallStmt", "outputParameters", "inputParameters", 
    "iterativeStmt", "conditionalStmt", "elsePart", "ioStmt", "arithmeticExpression", "expPrime", "term", 
    "termPrime", "factor", "highPrecedenceOperators", "lowPrecedenceOperators", "booleanExpression", "var", 
    "logicalOp", "relationalOp", "returnStmt", "optionalReturn", "idList", "more_ids", "definetypestmt"
};
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
	char firstBuffer[BUFFER_SIZE];
	char secondBuffer[BUFFER_SIZE];
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
bool LoadfirstBuffer = true;
bool LoadsecondBuffer = true;
twinBuff twinBuffer;


typedef struct TokenNode 
{
    terminals token; 
    char* lexeme;
    int lineNo;
    struct TokenNode* next;
} TokenNode;

