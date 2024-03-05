#include"lexerDef.h"

/*
GROUP_NO_39
Dhruv Kamra - 2021A7PS0713P
Navneet Singla - 2021A7PS1450P
Tauqeer Akthar- 2021A7PS1628P
Archisha Mehta - 2020B3A70779P
Saloni Bhandari - 2020B1A71602P 
*/

FILE *initialise(char *inputFile, long long int buff_size);
void initializeSymbolTable();
int hash(char *lexeme);
void insert(char *lexeme, terminals token);
bool lookup(char *lexeme);
void initializeKeywords();
SymbolItem error_helper(int error, char *lex, int line);
char *getLexeme();
FILE *getstream(FILE *fp);
void removeComments(char* testFile, char* cleanFile);
char getNextCharacter(FILE *fp);
terminals findKeyword(char *lexeme);
SymbolItem tokenize(char *lex, terminals g, int line);
SymbolItem getToken(FILE *fp);
TokenNode* createTokenNode(terminals token, char* lexeme, int lineNo);
void appendTokenNode(TokenNode** head, terminals token, char* lexeme, int lineNo);
void printTokens(TokenNode* head);
void freeTokenList(TokenNode* head);
