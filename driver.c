#include "parser.h"
#include "lexer.h"
#include <time.h>
int counter = 1;
int main(int argc, char *argv[])
{
    char *inputfile = argv[1];
    char *outputfile = ("parsetree%d.txt", counter);
    counter++;
    int nTokens = 0;
    int exit = 0;
    FILE *fp;

    printf("Group number - 39");
    printf("Group members:\n");
    printf("Dhruv Kamra - 2021A7PS0713P\n Navneet Singla - 2021A7PS1450P\n Tauqeer Akthar- 2021A7PS1628P\n Archisha Mehta - 2020B3A70779P\n Saloni Bhandari - 2020B1A71602P\n");
    printf("lexer module developed\n");
    printf("lexer module correctly working properly with test case 1, 2, 3, 4, 5, 6");
    printf("first and follow set is automated");
    printf("parse table implemented");
    printf("all files can be compiled");
    printf("first follow set is giving segmentation error after 30th rule");

    while (exit == 0)
    {
        int choice;
        printf("Choose a option.\n\t 0-->Exit\n\t 1-->Remove Comments\n\t 2-->Lexical Errors + Print Tokens\n\t 3-->Print Parse Tree 4--> Time to run the entire code\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 0:
            exit = 1;
            printf("Exiting...\n");
            break;
        case 1:
            printf("Removing Comments...\n");
            FILE *ip = fopen(inputfile, "r");
            FILE *op = fopen(("cleaned%d.txt", counter), "w");
            removeComments(ip, op);
            fclose(ip);
            fclose(op);

            FILE *file = fopen(op, "r");
            if (file == NULL)
            {
                fprintf(stderr, "Error in opening file\n", op);
                return 1;
            }

            char buffer[100000];

            while (fgets(buffer, sizeof(buffer), file) != NULL)
            {
                printf("%s", buffer);
            }

            fclose(file);

            break;
        case 2:
            printf("Lexical Analysis Started...\n");
            printf("\tLexeme\t\tToken\t\tLineCount");

            FILE *fp = initialise(inputfile, BUFFER_SIZE);
            if (!fp)
            {
                fprintf(stderr, "Failed to initialize lexer with file: %s\n", fp);
                return 1;
            }

            SymbolItem currToken;
            int tokenCount = 0;
            while (!isEnd)
            {
                currToken = getToken(fp);

                // Check if a valid token is fetched
                if (currToken.lexeme != NULL)
                {
                    printf("LineNo: %d , Token: %s, Lexeme: %s\n", currToken.lineCount, terms[currToken.token], currToken.lexeme);
                    tokenCount++;

                    // Assuming dynamic memory allocation for lexeme, it should be freed after use
                    free(currToken.lexeme);
                }
            }

            printf("Total number of tokens: %d\n", tokenCount);

            // Close the file and clean up if necessary
            fclose(fp);
            break;
        case 3:
            print("Parsing Started...\n");
            FILE *fp = initialise(inputfile, BUFFER_SIZE);
            if (!fp)
            {
                fprintf(stderr, "Failed to initialize lexer with file: %s\n", fp);
                return 1;
            }

            TokenNode *head = NULL;
            appendTokenNode(&head, END_OF_INPUT, NULL, -1);
            printTokens(head);
            freeTokenList(head);
            addRule();
            addGrammarRules();
            create_parse_table();
            initiate_parse_table();
            print_parse_table();
            compute_firsts();
            compute_follows();
            if(createParseTree(head)){
                printParseTree(root,0); 
            }else{
                printf("Parse Tree not printed due to errors.\n");
            }
            break;
        case 4:

            clock_t start_time, end_time;

            double total_CPU_time, total_CPU_time_in_seconds;

            start_time = clock();

            //Calculating only lexer
            FILE *fp = initialise(inputfile, BUFFER_SIZE);
            if (!fp)
            {
                fprintf(stderr, "Failed to initialize lexer with file: %s\n", fp);
                return 1;
            }
            lineCount = 1; 
            TokenNode *head = NULL;
            lineCount = 1; 
            appendTokenNode(&head, END_OF_INPUT, NULL, -1);
            printTokens(head);
            freeTokenList(head);

            end_time = clock();

            total_CPU_time = (double)(end_time - start_time);

            total_CPU_time_in_seconds = total_CPU_time / CLOCKS_PER_SEC;
            printf("Time taken by lexer in seconds %lf.\n", total_CPU_time_in_seconds);
        default:
            printf("Please enter a valid input\n");
            break;
        }
    }
    return 0;
}
