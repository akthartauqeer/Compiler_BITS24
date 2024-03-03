#include"lexerDef.h"
// Function prototypes
FILE *initialise(char *inputFile, long long int buff_size);
void initializeSymbolTable();
int hash(char *lexeme);
void insert(char *lexeme, terminals token);
bool lookup(char *lexeme);
void initializeKeywords();
SymbolItem errorHandle(int err, char *lex, int line);
char *getLexeme();
FILE *getstream(FILE *fp);
void removeComments(char* testFile, char* cleanFile);
char getNextCharacter(FILE *fp);
terminals findKeyword(char *lexeme);
SymbolItem tokenize(char *lex, terminals g, int line);
SymbolItem getToken(FILE *fp);
