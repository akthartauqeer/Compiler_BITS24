#include "lexer.h"

// initialising lexer
FILE *initialise(char *inputFile, long long int buff_size)
{
    memset(twinBuffer.firstBuf, 0, sizeof(twinBuffer.firstBuf));
    memset(twinBuffer.secondBuf, 0, sizeof(twinBuffer.secondBuf));
    FILE *fileptr = fopen(inputFile, "r");
    if (fileptr == NULL)
    {
        printf("ERROR! File not opened.\n");
    }
    int size = fread(twinBuffer.firstBuf, sizeof(char), BUFFER_SIZE, fp);
    if (size < BUFFER_SIZE)
    {
        twinBuffer.firstBuf[size] = EOF;
    }

    firstBufLoadable = false;
    secondBufLoadable = true;
    lineCount = 1;
    isEnd = false;
    beginPtr = twinBuffer.firstBuf;
    forwardPtr = twinBuffer.firstBuf;
    initializeSymbolTable();
    return fp;
}

// Function to initialize SymbolTable
void initializeSymbolTable()
{
    table = (Symboltable *)malloc(sizeof(Symboltable));
    if (table == NULL)
    {
        fprintf(stderr, "Memory allocation failed for SymbolTable.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < tablesize; i++)
    {
        table->data[i] = NULL;
    }
    table->currentsize = 0;
    initializeKeyWords();
    // Insert keywords into the symbol table
    for (int i = 0; i < KC; i++)
    {
        insert(keywords[i]->key, keywords[i]->token);
    }
    return;
}

// Function to calculate hash
int hash(char *lexeme)
{
    unsigned long hash = 5381;
    int c;
    while ((c = *lexeme++))
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash % tablesize;
}

// Function to insert into SymbolTable
void insert(char *lexeme, terminals token)
{
    int index = hash(lexeme);

    // Check if the lexeme already exists
    if (!lookup(lexeme))
    {
        // Lexeme doesn't exist, create a new SymbolItem
        SymbolItem *newItem = (SymbolItem *)malloc(sizeof(SymbolItem));
        if (newItem == NULL)
        {
            fprintf(stderr, "Memory allocation failed for SymbolItem.\n");
            exit(EXIT_FAILURE);
        }
        newItem->lexeme = strdup(lexeme); // Make a copy of lexeme
        if (newItem->lexeme == NULL)
        {
            fprintf(stderr, "Memory allocation failed for lexeme.\n");
            exit(EXIT_FAILURE);
        }
        newItem->token = token;
        newItem->next = NULL; // Initialize next pointer

        // Insert newItem into the symbol table
        if (table->data[index] == NULL)
        {
            // No collision, insert newItem directly
            table->data[index] = newItem;
        }
        else
        {
            // Collision occurred, append newItem to the existing linked list
            SymbolItem *current = table->data[index];
            while (current->next != NULL)
            {
                current = current->next;
            }
            current->next = newItem;
        }
        table->currentsize++;
    }
    else
    {
        // Lexeme already exists, handle as needed
        printf("Lexeme %s already exists in the symbol table.\n", lexeme);
    }
}

// Function to lookup a lexeme in SymbolTable
bool lookup(char *lexeme)
{
    int index = hash(lexeme);

    // Traverse the linked list at index to find the lexeme
    SymbolItem *current = table->data[index];
    while (current != NULL)
    {
        if (strcmp(current->lexeme, lexeme) == 0)
        {
            // Lexeme found in the symbol table
            return true;
        }
        current = current->next;
    }
    // Lexeme not found in the symbol table
    return false;
}

void initializeKeywords()
{
    keywords = {
        {"_main", TK_MAIN},
        {"as", TK_AS},
        {"call", TK_CALL},
        {"definetype", TK_DEFINETYPE},
        {"else", TK_ELSE},
        {"end", TK_END},
        {"endif", TK_ENDIF},
        {"endrecord", TK_ENDRECORD},
        {"endunion", TK_ENDUNION},
        {"endwhile", TK_ENDWHILE},
        {"global", TK_GLOBAL},
        {"if", TK_IF},
        {"input", TK_INPUT},
        {"int", TK_INT},
        {"list", TK_LIST},
        {"output", TK_OUTPUT},
        {"parameters", TK_PARAMETERS},
        {"parameter", TK_PARAMETER},
        {"read", TK_READ},
        {"real", TK_REAL},
        {"record", TK_RECORD},
        {"return", TK_RETURN},
        {"then", TK_THEN},
        {"type", TK_TYPE},
        {"union", TK_UNION},
        {"while", TK_WHILE},
        {"with", TK_WITH},
        {"write", TK_WRITE},
    };
    for (int i = 0; i < KC; i++)
    {
        keywords[i]->key = table[i][0];
        keywords[i]->token = table[i][1];
    }
}

// error handling
SymbolItem errorHandle(int err, char *lex, int line)
{
    SymbolItem nextSymbolItem;
    nextSymbolItem.token.value = 0;
    nextSymbolItem.lexeme = NULL;
    nextSymbolItem.iVal = 0;
    nextSymbolItem.fVal = 0.00;
    nextSymbolItem.lineCountf = line;
    if (err == -2)
        printf("Identified lexical error at line %d. Type: Unknown character %s\n", line, lex);
    else if (err == -3)
        printf("Identified lexical error at line %d. Type: Length of variable identifier more than 20 in %s\n", line, lex);
    else if (err == -4)
        printf("Identified lexical error at line %d. Type: Length of function identifier more than 30 in %s\n", line, lex);
    else
        printf("Identified lexical error at line %d. Type: Wrong sequence of characters in %s\n", line, getLexeme());
    beginPtr = forwardPtr;
    return nextSymbolItem;
}

// get lexeme
char *getLexeme()
{
    char *lexeme;
    bool begin = (beginPtr < (twinBuffer.firstBuf + BUFFER_SIZE) && beginPtr >= twinBuffer.firstBuf);
    bool forward = (forwardPtr < (twinBuffer.firstBuf + BUFFER_SIZE) && forwardPtr >= twinBuffer.firstBuf);
    int sizeInFirst, sizeInSecond, size;
    if ((begin && forward) || (!begin && !forward))
    {
        size = (forwardPtr - beginPtr);
        lexeme = (char *)malloc(size * sizeof(char));
        strncpy(lexeme, beginPtr, size);
    }
    else if (begin && !forward)
    {
        sizeInFirst = ((twinBuffer.firstBuf + BUFFER_SIZE - 1) - beginPtr) + 1;
        sizeInSecond = (forwardPtr - twinBuffer.secondBuf);
        size = sizeInFirst + sizeInSecond;
        lexeme = (char *)malloc(sizeof(char) * size);
        strncpy(lexeme, beginPtr, sizeInFirst);
        strncpy(lexeme + sizeInFirst, twinBuffer.secondBuf, sizeInSecond);
    }
    else
    {
        sizeInFirst = (forwardPtr - twinBuffer.firstBuf);
        sizeInSecond = ((twinBuffer.secondBuf + BUFFER_SIZE - 1) - beginPtr) + 1;
        size = sizeInFirst+sizeInSecond;
        lexeme = (char *) malloc(size * sizeof(char));
        strncpy(lexeme, beginPtr, sizeInSecond);
        strncpy(lexeme + sizeInSecond, twinBuffer.firstBuf, sizeInFirst);
    }
    return lexeme;
}

FILE *getstream(FILE *fp)
{
    // If the buffer is completed, load character stream to next buffer from file
    if (forwardPtr == twinBuffer.firstBuf + BUFFER_SIZE - 1)
    {
        if (secondBufLoadable)
        {
            size_t size = fread(twinBuffer.secondBuf, sizeof(char), BUFFER_SIZE, fp);
            if (size < BUFFER_SIZE)
            {
                twinBuffer.secondBuf[size] = EOF;
            }
        }
        firstBufLoadable = true;
        forwardPtr = twinBuffer.secondBuf;
        secondBufLoadable = false;
    }
    else if (forwardPtr == twinBuffer.secondBuf + BUFFER_SIZE - 1)
    {
        if (firstBufLoadable)
        {
            size_t size = fread(twinBuffer.firstBuf, sizeof(char), BUFFER_SIZE, fp);
            if (size < BUFFER_SIZE)
            {
                twinBuffer.firstBuf[size] = EOF;
            }
        }
        secondBufLoadable = true;
        forwardPtr = twinBuffer.firstBuf;
        firstBufLoadable = false;
    }
    else
    {
        forwardPtr++;
    }
    return fp;
}

// removing the comments
void removeComments(char *testFile, char *cleanFile)
{
    FILE *test = fopen(testFile, "r");
    FILE *clean = fopen(cleanFile, "w");

    if (!test || !clean)
    {
        printf("File opening failed!\n");
        return;
    }

    int openFlag = 0;
    int commentFlag = 0;
    char c = getc(test);
    while (c != EOF)
    {
        if (c == '\n')
        {
            openFlag = 1;
            putc('\n', clean);
        }
        c = getc(test);
        if (openFlag == 1)
        {
            if (c == '%')
            {
                commentFlag = 1;
            }
            else
            {
                openFlag = 0;
                putc(c, clean);
            }
        }
        if (commentFlag == 1)
        {
            if (c == '\n')
            {
                commentFlag = 0;
                putc('\n', clean);
            }
        }
        else
        {
            putc(c, clean);
        }
    }
    fclose(test);
    fclose(clean);
}

// DFA Handle....
char getNextCharacter(FILE *fp)
{
    char ch = *forwardPtr;
    if (ch == EOF)
    {
        isEnd = true;
    }
    getstream(fp);
    return ch;
}

// FINDING KEYWORDS
terminals findKeyword(char *lexeme)
{
    for (int i = 0; i < KC; i++)
    {
        if (lexeme == keywords[i]->key)
        {
            return keywords[i]->key;
        }
    }
    return NULL;
}
// tokenize
SymbolItem tokenize(char *lex, terminals g, int line)
{
    SymbolItem nextSymbolItem;
    nextSymbolItem.lexeme = lex;
    nextSymbolItem.lineCount = line;
    nextSymbolItem.token = g;
    nextSymbolItem.iVal = 0;
    nextSymbolItem.fVal = 0.0;
    switch (g)
    {
    case TK_NUM:
        nextSymbolItem.iVal = atoi(lex);
        break;
    case TK_RNUM:
        nextSymbolItem.fVal = atof(lex);
        break;
    case TK_FIELDID:
        nextSymbolItem.token = findKeyword(nextSymbolItem.lexeme);
        if (nextSymbolItem.token == NULL)
        {
            nextSymbolItem.token = TK_FIELDID;
        }
    case TK_ID:
        if (strlen(nextSymbolItem.lexeme) > 20)
        {
            return errorHandle(-3, lex, line);
        }
        break;
    case TK_FUNID:
        if (strlen(nextSymbolItem.lexeme) > 30)
        {
            return errorHandle(-4, lex, line);
        }
        break;
    }
    beginPtr = forwardPtr;
    return nextSymbolItem;
}
SymbolItem getToken(FILE *fp)
{
    beginPtr = forwardPtr;
    char ch = getNextCharacter(fp);
    int dfastate = 0;
    SymbolItem newSymbolItem;
    int lineCount;

    while (dfastate >= 0)
    {

        if (isEnd)
        {
            newSymbolItem.eof = true;
            newSymbolItem.lexeme = NULL;
            newSymbolItem.lineCount = lineCount;
            return newSymbolItem;
        }

        switch (dfastate)
        {
        case 0:
            switch (ch)
            {
            case '\t':
                beginPtr = forwardPtr;
                ch = getNextCharacter(fp);
                break;
            case ' ':
                beginPtr = forwardPtr;
                ch = getNextCharacter(fp);
                break;
            case '\n':
                beginPtr = forwardPtr;
                lineCount++;
                ch = getNextCharacter(fp);
                break;
            case '+':
                dfastate = 30;
                break;
            case '/':
                dfastate = 33;
                break;
            case '-':
                dfastate = 31;
                break;
            case '*':
                dfastate = 32;
                break;
            case ')':
                dfastate = 29;
                break;
            case ';':
                dfastate = 25;
                break;
            case ':':
                dfastate = 26;
                break;
            case '.':
                dfastate = 27;
                break;
            case '(':
                dfastate = 28;
                break;
            case ',':
                dfastate = 24;
                break;
            case '~':
                dfastate = 40;
                break;
            case '@':
                dfastate = 37;
                break;
            case '[':
                dfastate = 41;
                break;
            case ']':
                dfastate = 42;
                break;
            case '%':
                dfastate = 56;
                break;
            case '_':
                dfastate = 7;
                break;
            case '#':
                dfastate = 11;
                break;
            case '&':
                dfastate = 34;
                break;
            case '=':
                dfastate = 43;
                break;
            case '<':
                dfastate = 47;
                break;
            case '>':
                dfastate = 53;
                break;
            case '!':
                dfastate = 45;
                break;
            default:
                if (ch >= 'b' && ch <= 'd')
                {
                    dfastate = 1;
                }

                else if ((ch == 'a' || ch >= 'e'))
                {
                    dfastate = 5;
                }

                else if (ch >= '0' && ch <= '9')
                {
                    dfastate = 14;
                }
                else
                {
                    dfastate = -2;
                }
            }

        case 1:
            ch = getNextCharacter(fp);

            if (ch >= '2' && ch <= '7')
            {
                dfastate = 2;
            }
            else if (ch >= 'a' && ch <= 'z')
            {
                dfastate = 5;
            }
            else
            {
                dfastate = -5;
            }
            break;

        case 2:

            ch = getNextCharacter(fp);

            if (ch >= 'b' && ch <= 'd')
            {
                dfastate = 2;
            }
            else if (ch >= '2' && ch <= '7')
            {
                dfastate = 3;
            }
            else
            {
                dfastate = 4;
            }
            break;

        case 3:
            ch = getNextCharacter(fp);

            if (ch >= '2' && ch <= '7')
            {
                dfastate = 3;
            }
            else
            {
                dfastate = 4;
            }
            break;

        case 4:
            return tokenize(getLexeme(), TK_ID, lineCount);
            break;

        case 5:
            ch = getNextCharacter(fp);
            if (ch >= 'a' && ch <= 'z')
            {
                dfastate = 5;
            }
            else
            {
                dfastate = 6;
            }
            break;

        case 6:
            return tokenize(getLexeme(), TK_FIELDID, lineCount);
            break;
        case 7:
            ch = getNextCharacter(fp);

            if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
            {
                dfastate = 8;
            }
            else
            {
                dfastate = -5;
            }

            break;

        case 8:
            ch = getNextCharacter(fp);

            if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
            {
                dfastate = 8;
            }
            else if (ch >= '0' && ch <= '9')
            {
                dfastate = 9;
            }
            else
            {
                dfastate = 10;
            }
            break;

        case 9:
            ch = getNextCharacter(fp);

            if (ch >= '0' && ch <= '9')
            {
                dfastate = 9;
            }
            else
            {
                dfastate = 10;
            }
            break;

        case 10:
            return tokenize(getLexeme(), TK_FUNID, lineCount);
            break;

        case 11:

            ch = getNextCharacter(fp);

            if (ch >= 'a' && ch <= 'z')
            {
                dfastate = 12;
            }
            else
            {
                dfastate = -5;
            }
            break;

        case 12:

            ch = getNextCharacter(fp);

            if (ch >= 'a' && ch <= 'z')
            {
                dfastate = 12;
            }
            else
            {
                dfastate = 13;
            }
            break;

        case 13:
            return tokenize(getLexeme(), TK_RUID, lineCount);
            break;

        case 14:

            ch = getNextCharacter(fp);

            if (ch == '.')
            {
                dfastate = 15;
            }
            else if (ch >= '0' && ch <= '9')
            {
                dfastate = 14;
            }
            else
            {
                dfastate = 22;
            }

            break;

        case 15:

            ch = getNextCharacter(fp);

            if (ch >= '0' && ch <= '9')
            {
                dfastate = 16;
            }
            else
            {
                dfastate = -5;
            }
            break;

        case 16:
            ch = getNextCharacter(fp);

            if (ch >= '0' && ch <= '9')
            {
                dfastate = 17;
            }
            else
            {
                dfastate = -5;
            }
            break;

        case 17:
            ch = getNextCharacter(fp);

            if (ch == 'E')
            {
                dfastate = 18;
            }
            else
            {
                dfastate = 23;
            }
            break;

        case 18:
            ch = getNextCharacter(fp);

            if (ch == '+' || ch == '-')
            {
                dfastate = 19;
            }
            else if (ch >= '0' && ch <= '9')
            {
                dfastate = 20;
            }
            else
            {
                dfastate = -5;
            }
            break;

        case 19:
            ch = getNextCharacter(fp);

            if (ch >= '0' && ch <= '9')
            {
                dfastate = 20;
            }
            else
            {
                dfastate = -5;
            }
            break;

        case 20:
            ch = getNextCharacter(fp);

            if (ch >= '0' && ch <= '9')
            {
                dfastate = 21;
            }
            else
            {
                dfastate = -5;
            }
            break;
        case 21:
            forwardPtr++;
            dfastate = 23;
            break;
        case 22:
            return tokenize(getLexeme(), TK_NUM, lineCount);
            break;

        case 23:
            return tokenize(getLexeme(), TK_RNUM, lineCount);
            break;

        case 24:
            forwardPtr++;
            return tokenize(getLexeme(), TK_COMMA, lineCount);
            break;

        case 25:
            forwardPtr++;
            return tokenize(getLexeme(), TK_SEM, lineCount);
            break;

        case 26:
            forwardPtr++;
            return tokenize(getLexeme(), TK_COLON, lineCount);
            break;

        case 27:
            forwardPtr++;
            return tokenize(getLexeme(), TK_DOT, lineCount);
            break;

        case 28:
            forwardPtr++;
            return tokenize(getLexeme(), TK_OP, lineCount);
            break;

        case 29:
            forwardPtr++;
            return tokenize(getLexeme(), TK_CL, lineCount);
            break;

        case 30:
            forwardPtr++;
            return tokenize(getLexeme(), TK_PLUS, lineCount);
            break;

        case 31:
            forwardPtr++;
            return tokenize(getLexeme(), TK_MINUS, lineCount);
            break;

        case 32:
            forwardPtr++;
            return tokenize(getLexeme(), TK_MUL, lineCount);
            break;

        case 33:
            forwardPtr++;
            return tokenize(getLexeme(), TK_DIV, lineCount);
            break;

        case 34:
            ch = getNextCharacter(fp);

            if (ch == '&')
            {
                dfastate = 35;
            }
            else
            {
                dfastate = -5;
            }
            break;

        case 35:
            ch = getNextCharacter(fp);

            if (ch == '&')
            {
                dfastate = 36;
            }
            else
            {
                dfastate = -5;
            }
            break;

        case 36:
            forwardPtr++;
            return tokenize(getLexeme(), TK_AND, lineCount);
            break;

        case 37:
            ch = getNextCharacter(fp);

            if (ch == '@')
            {
                dfastate = 38;
            }
            else
            {
                dfastate = -5;
            }
            break;

        case 38:
            ch = getNextCharacter(fp);

            if (ch == '@')
            {
                dfastate = 39;
            }
            else
            {
                dfastate = -5;
            }
            break;

        case 39:
            forwardPtr++;
            return tokenize(getLexeme(), TK_OR, lineCount);
            break;

        case 40:
            forwardPtr++;
            return tokenize(getLexeme(), TK_NOT, lineCount);
            break;

        case 41:
            forwardPtr++;
            return tokenize(getLexeme(), TK_SQL, lineCount);
            break;

        case 42:
            forwardPtr++;
            return tokenize(getLexeme(), TK_SQR, lineCount);
            break;

        case 43:
            ch = getNextCharacter(fp);

            if (ch == '=')
            {
                dfastate = 44;
            }
            else
            {
                dfastate = -5;
            }
            break;

        case 44:
            forwardPtr++;
            return tokenize(getLexeme(), TK_EQ, lineCount);
            break;

        case 45:
            ch = getNextCharacter(fp);

            if (ch == '=')
            {
                dfastate = 46;
            }
            else
            {
                dfastate = -5;
            }
            break;

        case 46:
            forwardPtr++;
            return tokenize(getLexeme(), TK_NE, lineCount);
            break;

        case 47:

            ch = getNextCharacter(fp);

            if (ch == '-')
            {
                dfastate = 50;
            }
            else if (ch == '=')
            {
                dfastate = 49;
            }
            else
            {
                dfastate = 48;
            }
            break;

        case 48:
            forwardPtr++;
            return tokenize(getLexeme(), TK_LT, lineCount);
            break;

        case 49:
            forwardPtr++;
            return tokenize(getLexeme(), TK_LE, lineCount);
            break;

        case 50:
            ch = getNextCharacter(fp);

            if (ch == '-')
            {
                dfastate = 51;
            }
            else
            {
                dfastate = -5;
            }
            break;

        case 51:
            ch = getNextCharacter(fp);

            if (ch == '-')
            {
                dfastate = 52;
            }
            else
            {
                dfastate = -5;
            }
            break;

        case 52:
            forwardPtr++;
            return tokenize(getLexeme(), TK_ASSIGNOP, lineCount);
            break;

        case 53:
            ch = getNextCharacter(fp);

            if (ch == '=')
            {
                dfastate = 55;
            }
            else
            {
                dfastate = 54;
            }
            break;

        case 54:
            forwardPtr++;
            return tokenize(getLexeme(), TK_GT, lineCount);
            break;

        case 55:
            forwardPtr++;
            return tokenize(getLexeme(), TK_GE, lineCount);
            break;

        case 56:
            ch = getNextCharacter(fp);

            if (ch == '/n')
            {
                dfastate = 57;
            }
            else
            {
                dfastate = 56;
            }
            break;

        case 57:
            forwardPtr++;
            return tokenize(getLexeme(), TK_COMMENT, lineCount);
            break;
        }
        if (dfastate == -2)
        {
            return errorHandle(-2, getLexeme(), lineCount);
        }

        if (dfastate == -5)
        {
            return errorHandle(-5, getLexeme(), lineCount);
        }
    }
    newSymbolItem.lexeme = NULL;
    newSymbolItem.lineCount = -1;
    newSymbolItem.token = NULL;
    newSymbolItem.iVal = 0;
    newSymbolItem.fVal = 0.0;
    return newSymbolItem;
}
