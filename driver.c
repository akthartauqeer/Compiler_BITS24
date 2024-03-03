#include"parser.h"
#include"lexer.h"
int counter=1;
int main(int argc, char*argv[]){
    char * inputfile = argv[1];
    char * outputfile = ("parsetree%d.txt",counter);
    counter++;
    int nTokens=0;
    int exit=0;
    FILE* fp;
    while(exit==0){
        int choice;
        printf("Choose a option.\n\t 0-->Exit\n\t 1-->Remove Comments\n\t 2-->Lexical Errors + Print Tokens\n\t 3-->Print Parse Tree\n");
        scanf("%d", &choice);
        switch(choice){
            case 0: 
                exit=1;
                printf("Exiting...\n");
                break;
            case 1:
                printf("Removing Comments...\n");
                FILE* ip = fopen(inputfile,"r");
                FILE* op = fopen(("cleaned%d.txt",counter), "w");
                removeComments(ip,op);
                fclose(ip);
                fclose(op);
                break;
            case 2:
                printf("Lexical Analysis Started...\n");
                printf("\tLexeme\t\tToken\t\tLineCount");
                FILE* fp = initialise(inputfile);
                SymbolItem sitem;
                while(!isEnd){
                    sitem=getToken(fp);
                    if((sitem.lexeme=NULL) ||(sitem.token==TK_COMMENT)){
                        continue;
                    }
                    nTokens++;
                    printf("\t%s\t\t%s\t\t%d\n", sitem.lexeme, terms[sitem.token], sitem.lineCount);
                }
                break;
            case 3:
                print("Parsing Started...\n");
                if(nTokens==0){
                    fp = initialise(inputfile);
                    SymbolItem sitem;
                    while(!isEnd){
                        sitem=getToken(fp);
                        if((sitem.lexeme=NULL) ||(sitem.token==TK_COMMENT)){
                            continue;
                        }
                        nTokens++;
                    }
                }
                nTokens++;
                SymbolItem* sitems=(SymbolItem* )malloc(sizeof(SymbolItem)*nTokens);
                int i=0;
                while(!isEnd){
                        sitem=getToken(ip);
                        if((sitem.lexeme=NULL) ||(sitem.token==TK_COMMENT)){
                            continue;
                        }
                        sitems[i]=sitem;
                        i++;
                }
                SymbolItem sitem;
                sitem.lexeme=NULL;
                sitem.lineCount=0;
                sitem.token=NULL;
                sitem.iVal=0;
                sitem.fVal=0.0;
                sitems[nTokens-1]=sitem;
                initializeParser(sitems, nTokens);
                treeNode* parsetree = createParseTree(inputfile);
                printParseTree(parsetree, outputfile);
                if(errFlag){
                    printf("Test file has some syntactic errors\n");
                }else{
                    printf("No errors. Compilation done successfully\n");
                }
                break;
            default: 
                printf("Please enter a valid input\n");
                break;
        }
    }
    return 0;
}
