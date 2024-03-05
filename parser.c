#include "parser.h"
#include "lexerDef.h"

gitems *createNonTerminal(non_terminals nt)
{
    gitems *item = (gitems *)malloc(sizeof(gitems));
    item->isTer = false;
    item->v.non_t = nt;
    return item;
}
// Function to create and populate a gitem for terminal
gitems *createTerminal(terminals t)
{
    gitems *item = (gitems *)malloc(sizeof(gitems));
    item->isTer = true;
    item->v.t = t;
    return item;
}

void populateitems()
{
    itemList = (gitems **)malloc((TC + NTC) * sizeof(gitems *));
    itemList[0] = createTerminal(TK_GT);
    itemList[1] = createTerminal(TK_LT);
    itemList[2] = createTerminal(TK_ASSIGNOP);
    itemList[3] = createTerminal(TK_COMMENT);
    itemList[4] = createTerminal(TK_EQ);
    itemList[5] = createTerminal(TK_PLUS);
    itemList[6] = createTerminal(TK_NE);
    itemList[7] = createTerminal(TK_LE);
    itemList[8] = createTerminal(TK_GE);
    itemList[9] = createTerminal(TK_SQR);
    itemList[10] = createTerminal(TK_SQL);
    itemList[11] = createTerminal(TK_OR);
    itemList[12] = createTerminal(TK_NOT);
    itemList[13] = createTerminal(TK_AND);
    itemList[14] = createTerminal(TK_ID);
    itemList[15] = createTerminal(TK_FIELDID);
    itemList[16] = createTerminal(TK_DIV);
    itemList[17] = createTerminal(TK_MUL);
    itemList[18] = createTerminal(TK_MINUS);
    itemList[19] = createTerminal(TK_FUNID);
    itemList[20] = createTerminal(TK_DOT);
    itemList[21] = createTerminal(TK_CL);
    itemList[22] = createTerminal(TK_OP);
    itemList[23] = createTerminal(TK_COLON);
    itemList[24] = createTerminal(TK_SEM);
    itemList[25] = createTerminal(TK_RUID);
    itemList[26] = createTerminal(TK_COMMA);
    itemList[27] = createTerminal(TK_NUM);
    itemList[28] = createTerminal(TK_RNUM);
    itemList[29] = createTerminal(TK_MAIN);
    itemList[30] = createTerminal(TK_AS);
    itemList[31] = createTerminal(TK_CALL);
    itemList[32] = createTerminal(TK_DEFINETYPE);
    itemList[33] = createTerminal(TK_ELSE);
    itemList[34] = createTerminal(TK_END);
    itemList[35] = createTerminal(TK_ENDIF);
    itemList[36] = createTerminal(TK_ENDWHILE);
    itemList[37] = createTerminal(TK_ENDRECORD);
    itemList[38] = createTerminal(TK_ENDUNION);
    itemList[39] = createTerminal(TK_GLOBAL);
    itemList[40] = createTerminal(TK_IF);
    itemList[41] = createTerminal(TK_INPUT);
    itemList[42] = createTerminal(TK_OUTPUT);
    itemList[43] = createTerminal(TK_INT);
    itemList[44] = createTerminal(TK_REAL);
    itemList[45] = createTerminal(TK_LIST);
    itemList[46] = createTerminal(TK_PARAMETERS);
    itemList[47] = createTerminal(TK_PARAMETER);
    itemList[48] = createTerminal(TK_READ);
    itemList[49] = createTerminal(TK_WRITE);
    itemList[50] = createTerminal(TK_RECORD);
    itemList[51] = createTerminal(TK_UNION);
    itemList[52] = createTerminal(TK_RETURN);
    itemList[53] = createTerminal(TK_THEN);
    itemList[54] = createTerminal(TK_TYPE);
    itemList[55] = createTerminal(TK_WHILE);
    itemList[56] = createTerminal(TK_WITH);
    itemList[57] = createNonTerminal(EPS);
    itemList[58] = createNonTerminal(END_OF_INPUT);
    itemList[59] = createNonTerminal(program);
    itemList[60] = createNonTerminal(mainFunction);
    itemList[61] = createNonTerminal(otherFunctions);
    itemList[62] = createNonTerminal(function);
    itemList[63] = createNonTerminal(input_par);
    itemList[64] = createNonTerminal(output_par);
    itemList[65] = createNonTerminal(parameter_list);
    itemList[66] = createNonTerminal(dataType);
    itemList[67] = createNonTerminal(primitiveDatatype);
    itemList[68] = createNonTerminal(constructedDatatype);
    itemList[69] = createNonTerminal(A);
    itemList[70] = createNonTerminal(stmts);
    itemList[71] = createNonTerminal(remaining_list);
    itemList[72] = createNonTerminal(typeDefinitions);
    itemList[73] = createNonTerminal(typeDefinition);
    itemList[74] = createNonTerminal(fieldDefinitions);
    itemList[75] = createNonTerminal(fieldDefinition);
    itemList[76] = createNonTerminal(fieldtype);
    itemList[77] = createNonTerminal(moreFields);
    itemList[78] = createNonTerminal(declarations);
    itemList[79] = createNonTerminal(declaration);
    itemList[80] = createNonTerminal(global_or_not);
    itemList[81] = createNonTerminal(otherStmts);
    itemList[82] = createNonTerminal(stmt);
    itemList[83] = createNonTerminal(assignmentStmt);
    itemList[84] = createNonTerminal(singleOrRecId);
    itemList[85] = createNonTerminal(option_single_constructed);
    itemList[86] = createNonTerminal(oneExpansion);
    itemList[87] = createNonTerminal(moreExpansions);
    itemList[88] = createNonTerminal(funCallStmt);
    itemList[89] = createNonTerminal(outputParameters);
    itemList[90] = createNonTerminal(inputParameters);
    itemList[91] = createNonTerminal(iterativeStmt);
    itemList[92] = createNonTerminal(conditionalStmt);
    itemList[93] = createNonTerminal(elsePart);
    itemList[94] = createNonTerminal(ioStmt);
    itemList[95] = createNonTerminal(arithmeticExpression);
    itemList[96] = createNonTerminal(expPrime);
    itemList[97] = createNonTerminal(term);
    itemList[98] = createNonTerminal(termPrime);
    itemList[99] = createNonTerminal(factor);
    itemList[100] = createNonTerminal(highPrecedenceOperators);
    itemList[101] = createNonTerminal(lowPrecedenceOperators);
    itemList[102] = createNonTerminal(booleanExpression);
    itemList[103] = createNonTerminal(var);
    itemList[104] = createNonTerminal(logicalOp);
    itemList[105] = createNonTerminal(relationalOp);
    itemList[106] = createNonTerminal(returnStmt);
    itemList[107] = createNonTerminal(optionalReturn);
    itemList[108] = createNonTerminal(idList);
    itemList[109] = createNonTerminal(more_ids);
    itemList[110] = createNonTerminal(definetypestmt);
}

void addRule(int index, non_terminals nt, int size, gitems *value)
{
    LHSNode *lhsNode;
    if (G->rules[index - 1] == NULL)
    {
        lhsNode = (LHSNode *)malloc(sizeof(LHSNode));
        lhsNode->rules = NULL;
        lhsNode->lhs = nt;
    }
    ProductionRule *currentrulehead = lhsNode->rules;
    ProductionRule *newRule = (ProductionRule *)malloc(sizeof(ProductionRule));
    newRule->head = NULL;
    newRule->next_rule = NULL;
    if (currentrulehead == NULL)
    {
        lhsNode->rules = newRule;
    }
    else
    {
        while (currentrulehead->next_rule != NULL)
            currentrulehead = currentrulehead->next_rule;
    }
    // Create and add RHS nodes for the production rule
    RHSNode *rhshead = (RHSNode *)malloc(sizeof(RHSNode));
    RHSNode *rhsptr = rhshead;
    rhshead->v = value[0].v;
    rhshead->isT = value[0].isTer;
    for (int i = 1; i < size; i++)
    {
        // Create a new RHSNode
        RHSNode *rhsNode = (RHSNode *)malloc(sizeof(RHSNode));
        rhshead->v = value[i].v;
        rhshead->isT = value[i].isTer;
        rhsptr->next = rhsNode;
        rhsNode->ptr = NULL; // You might need to set this depending on your needs
        // Add the RHSNode to the production rule
        rhsptr = rhsptr->next;
    }

    // Link the new production rule to the LHSNode
    newRule->head = rhshead;
    currentrulehead->next_rule = newRule;
    // Add the LHSNode to the grammar
    G->rules[index] = lhsNode;
}

void addGrammarRules()
{
    addrule(1, program, 2, {otherFunctions, mainFunction});
    addrule(2, mainFunction, 3, {TK_MAIN, stmts, TK_END});
    addrule(3, otherFunctions, 2, {function, otherFunctions});
    addrule(3, otherFunctions, 1, {EPS});
    addrule(4, function, 6, {TK_FUNID, input_par, output_par, TK_SEM, stmts, TK_END});
    addrule(5, input_par, 6, {TK_INPUT, TK_PARAMETER, TK_LIST, TK_SQL, parameter_list, TK_SQR});
    addrule(6, output_par, 6, {TK_OUTPUT, TK_PARAMETER, TK_LIST, TK_SQL, parameter_list, TK_SQR});
    addrule(6, output_par, 1, {EPS});
    addrule(7, parameter_list, 3, {dataType, TK_ID, remaining_list});
    addrule(8, dataType, 1, {primitiveDatatype});
    addrule(8, dataType, 1, {constructedDatatype});
    addrule(9, primitiveDatatype, 1, {TK_INT});
    addrule(9, primitiveDatatype, 1, {TK_REAL});
    addrule(10, constructedDatatype, 2, {TK_RECORD, TK_RUID});
    addrule(10, constructedDatatype, 2, {TK_UNION, TK_RUID});
    addrule(10, constructedDatatype, 1, {TK_RUID});
    addrule(11, remaining_list, 2, {TK_COMMA, parameter_list});
    addrule(11, remaining_list, 1, {EPS});
    addrule(12, stmts, 4, {typeDefinitions, declarations, otherStmts, returnStmt});
    addrule(13, typeDefinitions, 2, {typeDefinition, typeDefinitions});
    addrule(13, typeDefinitions, 1, {EPS});
    addrule(14, typeDefinition, 4, {TK_RECORD, TK_RUID, fieldDefinitions, TK_ENDRECORD});
    addrule(15, typeDefinition, 4, {TK_UNION, TK_RUID, fieldDefinitions, TK_ENDUNION});
    addrule(16, fieldDefinitions, 3, {fieldDefinition, fieldDefinition, moreFields});
    addrule(17, fieldDefinition, 5, {TK_TYPE, fieldType, TK_COLON, TK_FIELDID, TK_SEM});
    addrule(18, fieldtype, 1, {primitiveDatatype});            // 17a
    addrule(18, fieldtype, 1, {TK_RUID});                      // 17a
    addrule(19, moreFields, 2, {fieldDefinition, moreFields}); // 18
    addrule(19, moreFields, 1, {EPS});
    addrule(20, declarations, 2, {declaration, declarations}); // 19
    addrule(20, declarations, 1, {EPS});
    addrule(21, declaration, 6, {TK_TYPE, dataType, TK_COLON, TK_ID, global_or_not, TK_SEM}); // 20
    addrule(22, global_or_not, 2, {TK_COLON, TK_GLOBAL});                                     // 21
    addrule(22, global_or_not, 1, {EPS});
    addrule(23, otherStmts, 2, {stmt, otherStmts}); // 22
    addrule(23, otherStmts, 1, {EPS});
    addrule(24, stmt, 1, {assignmentStmt}); // 23
    addrule(24, stmt, 1, {iterativeStmt});
    addrule(24, stmt, 1, {conditionalStmt});
    addrule(24, stmt, 1, {ioStmt});
    addrule(24, stmt, 1, {funCallStmt});
    addrule(25, assignmentStmt, 4, {SingleOrRecId, TK_ASSIGNOP, arithmeticExpression, TK_SEM}); // 24
    addrule(26, singleOrRecId, 2, {TK_ID, option_single_constructed});                          // 25e
    addrule(27, option_single_constructed, 2, {oneExpansion, moreExpansions});                  // 25F
    addrule(27, option_single_constructed, 1, {EPS});
    addrule(28, oneExpansion, 2, {TK_DOT, TK_FIELDID});
    addrule(29, moreExpansions, 2, {oneExpansion, moreExpansions}); // 25d
    addrule(29, moreExpansions, 1, {EPS});
    addrule(30, funCallStmt, 7, {outputParameters, TK_CALL, TK_FUNID, TK_WITH, TK_PARAMETERS, inputParameters, TK_SEM}); // 26
    addrule(31, outputParameters, 4, {TK_SQL, idList, TK_SQR, TK_ASSIGNOP});                                             // 27
    addrule(31, outputParameters, 1, {EPS});
    addrule(32, inputParameters, 3, {TK_SQL, idList, TK_SQR});                                                      // 28
    addrule(33, iterativeStmt, 7, {TK_WHILE, TK_OP, booleanExpression, TK_CL, stmt, otherStmts, TK_ENDWHILE});      // 29
    addrule(34, conditionalStmt, 8, {TK_IF, TK_OP, booleanExpression, TK_CL, TK_THEN, stmt, otherStmts, elsePart}); // 30a
    addrule(35, elsePart, 4, {TK_ELSE, stmt, otherStmts, TK_ENDIF});                                                // 31a
    addrule(35, elsePart, 1, {TK_ENDIF});
    addrule(36, ioStmt, 5, {TK_READ, TK_OP, var, TK_CL, TK_SEM});       // 32
    addrule(36, ioStmt, 5, {TK_WRITE, TK_OP, var, TK_CL, TK_SEM});      // 32
    addrule(37, arithmeticExpression, 2, {term, expPrime});             // B1
    addrule(38, expPrime, 3, {lowPrecedenceOperators, term, expPrime}); // B2
    addrule(38, expPrime, 3, {EPS});
    addrule(39, term, 2, {factor, termPrime});
    addrule(40, termPrime, 3, {highPrecedenceOperators, factor, termPrime});
    addrule(40, termPrime, 1, {EPS});
    addrule(41, factor, 3, {TK_OP, arithmeticExpression, TK_CL}); // B5
    addrule(41, factor, 1, {var});                                // B5
    addrule(42, highPrecedenceOperators, 1, {TK_MUL});
    addrule(42, highPrecedenceOperators, 1, {TK_DIV});
    addrule(43, lowPrecedenceOperators, 1, {TK_PLUS});
    addrule(43, lowPrecedenceOperators, 1, {TK_MINUS});
    addrule(44, booleanExpression, 7, {TK_OP, booleanExpression, TK_CL, logicalOp, TK_OP, booleanExpression, TK_CL}); // 36
    addrule(45, booleanExpression, 3, {var, relationOP, var});
    addrule(46, booleanExpression, 4, {TK_NOT, TK_OP, booleanExpression, TK_CL}); // 38a
    addrule(47, var, 1, {singleOrRecId});                                         // 39a
    addrule(47, var, 1, {TK_NUM});                                                // 39a
    addrule(47, var, 1, {TK_RNUM});                                               // 39a
    addrule(48, logicalOp, 1, {TK_AND});                                          // 40
    addrule(48, logicalOp, 1, {TK_OR});                                           // 40
    addrule(49, relationalOp, 1, {TK_LT});                                        // 41
    addrule(49, relationalOp, 1, {TK_LE});                                        // 41
    addrule(49, relationalOp, 1, {TK_EQ});                                        // 41
    addrule(49, relationalOp, 1, {TK_GT});                                        // 41
    addrule(49, relationalOp, 1, {TK_GE});                                        // 41
    addrule(49, relationalOp, 1, {TK_NE});                                        // 41
    addrule(50, returnStmt, 3, {TK_RETURN, optionalReturn, TK_SEM});              // 42
    addrule(51, optionalReturn, 3, {TK_SQL, idList, TK_SQR});                     // 43
    addrule(51, optionalReturn, 1, {EPS});
    addrule(52, idList, 2, {TK_ID, more_ids});                                   // 44
    addrule(53, more_ids, 2, {TK_COMMA, idList});                                // 45
    addrule(53, more_ids, 1, {EPS});                                             // 45
    addrule(54, definetypestmt, 5, {TK_DEFINETYPE, A, TK_RUID, TK_AS, TK_RUID}); // 46
    addrule(55, A, 1, {TK_RECORD});                                              // 47
    addrule(55, A, 1, {TK_UNION});                                               // 47
}

void create_parse_table()
{
    PT = (ParseTable *)malloc(sizeof(ParseTable));
    if (PT == NULL)
    {
        fprintf(stderr, "Memory allocation failed for parse table.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < NTC; i++)
    {
        for (int j = 0; j < TC; j++)
        {
            PT->table[i][j] = NULL;
        }
    }
}

void initiate_parse_table()
{
    for (int i = 0; i < NTC; i++)
    {
        LHSNode *current_lhs = G->rules[i]->rules;
        while (current_lhs != NULL)
        {
            ProductionRule *current_rule = current_lhs->rules;
            while (current_rule != NULL)
            {
                RHSNode *rhs_node = current_rule->head;
                if (rhs_node->isT)
                {
                    PT->table[i][rhs_node->v.t] = current_rule;
                }
                else
                {
                    terminal_node *first_terminal = first_follow_sets[rhs_node->v.non_t].first_set->head;
                    while (first_terminal != NULL)
                    {
                        PT->table[i][first_terminal->t] = current_rule;
                        first_terminal = first_terminal->next;
                    }
                }
                current_rule = current_rule->next_rule;
            }

            current_lhs = current_lhs->rules;
        }
    }
}

void print_parse_table()
{
    printf("Parse Table:\n");
    printf("Non-terminals/Terminals\t");
    for (int j = 0; j < TC; j++)
    {
        printf("%d\t", j);
    }
    printf("\n");

    for (int i = 0; i < NTC; i++)
    {
        printf("%d\t", i);
        for (int j = 0; j < TC; j++)
        {
            if (PT->table[i][j] != NULL)
            {
                printf("%d\t", PT->table[i][j]); // Print the pointer value
            }
            else
            {
                printf("NULL\t");
            }
        }
        printf("\n");
    }
}

void add_terminal_tolist(terminal_list *list, terminals t)
{

    if (list->head == NULL)
    {
        list->head = (terminal_node *)malloc(sizeof(terminal_node));
        list->head->t = t;
        list->head->next = NULL;
    }
    else
    {
        terminal_node *cur = list->head;
        terminal_node *prev = NULL;

        while (cur != NULL)
        {
            if (cur->t == t)
            {
                return;
            }

            prev = cur;
            cur = cur->next;
        }

        terminal_node *newnode = (terminal_node *)malloc(sizeof(terminal_node));

        newnode->t = t;
        newnode->next = NULL;

        if (prev != NULL)
        {
            prev->next = newnode;
        }
    }
}

void join_terminal_list(terminal_list *l1, terminal_list *l2)
{
    if (l1 == NULL || l2 == NULL || l2->head == NULL)
    {
        return;
    }

    terminal_node *cur = l2->head;

    while (cur != NULL)
    {
        terminal_node *search = l1->head;
        bool found = false;

        while (search != NULL)
        {
            if (search->t == cur->t)
            {
                found = true;
                break;
            }
            search = search->next;
        }

        if (!found)
        {
            terminal_node *newnode = (terminal_node *)malloc(sizeof(terminal_node));

            if (newnode == NULL)
            {
                fprintf(stderr, "memory allocation failed\n");
                exit(EXIT_FAILURE);
            }

            newnode->t = cur->t;
            newnode->next = NULL;

            if (l1->head == NULL)
            {
                l1->head = newnode;
            }
            else
            {
                terminal_node *last = l1->head;
                while (last->next != NULL)
                {
                    last = last->next;
                }
                last->next = newnode;
            }
        }

        cur = cur->next;
    }
}

void initialise_list(terminal_list *list)
{

    if (list != NULL)
    {
        list->head = NULL;
    }
}

bool contains_epsilon(terminal_list *given_list)
{
    terminal_node *temp = given_list->head;

    while (temp != NULL)
    {
        if (temp->t == EPS)
        {
            return true;
        }

        temp = temp->next;
    }

    return false;
}

void remove_epsilon(terminal_list *given_list)
{
    terminal_node *temp = given_list->head;
    terminal_node *prev = NULL;
    if (temp != NULL && temp->t == EPS)
    {
        given_list->head = temp->next;
        free(temp);
        return;
    }
    while ((temp != NULL) && (temp->next->t != EPS))
    {
        prev = temp;
        temp = temp->next;
    }
    if (temp = NULL)
        return;
    prev->next = temp->next;
    free(temp);
    return;
}

void compute_first(non_terminals given_nt)
{

    if (first_follow_sets[given_nt].first_set == NULL)
    {
        first_follow_sets[given_nt].first_set = (terminal_list *)malloc(sizeof(terminal_list));
        initialise_list(first_follow_sets[given_nt].first_set);
    }
    ////
    else if (first_follow_sets[given_nt].first_set->head != NULL)
    {
        return;
    }

    LHSNode *lhs = G->rules[given_nt];
    for (ProductionRule *rule = lhs->rules; rule != NULL; rule = rule->next_rule)
    {
        compute_first_for_rhsnode(rule->head, first_follow_sets[given_nt].first_set);
    }
}

terminal_list *compute_first_for_rhsnode(RHSNode *rhs, terminal_list *firstset)
{

    if (rhs == NULL)
    {
        return firstset;
    }

    if (rhs->isT)
    {
        add_terminal_tolist(firstset, rhs->v.t);
    }
    else
    {
        compute_first(rhs->v.non_t);
        join_terminal_list(firstset, first_follow_sets[rhs->v.non_t].first_set);

        if (contains_epsilon(first_follow_sets[rhs->v.non_t].first_set) && rhs->next != NULL)
        {
            remove_epsilon(first_follow_sets[rhs->v.non_t].first_set);
            join_terminal_list(firstset, compute_first_for_rhsnode(rhs->next, firstset));
        }
    }
    return firstset;
}

void compute_firsts()
{
    for (int i = 0; i < NTC; i++)
    {
        compute_first(i);
    }
}

void populate_occ_follow()

{
    for (int i = 0; i < NTC; i++)
    {
        LHSNode *lhsNode = G->rules[i];
        ProductionRule *rule = lhsNode->rules;

        while (rule)
        {
            RHSNode *rhs = rule->head;

            while (rhs)
            {
                if (!rhs->isT && rhs->v.non_t != lhsNode->lhs)
                {
                    followDS *newFollow = (followDS *)malloc(sizeof(followDS));

                    if (newFollow)
                    {
                        newFollow->occurrence = rhs;
                        newFollow->parent_nt = lhsNode->lhs;
                        newFollow->next = follow_occurrence[rhs->v.non_t];
                        follow_occurrence[rhs->v.non_t] = newFollow;
                    }
                }
                rhs = rhs->next;
            }
            rule = rule->next_rule;
        }
    }
}

void find_followset(non_terminals nt)
{
    if (first_follow_sets[nt].follow_set == NULL)
    {
        first_follow_sets[nt].follow_set = (terminal_list *)malloc(sizeof(terminal_list));
        initialise_list(first_follow_sets[nt].follow_set);
    }

    else if (first_follow_sets[nt].follow_set->head != NULL)
    {
        return;
    }

    if (nt == program)
    {
        add_terminal_tolist(first_follow_sets[nt].follow_set, END_OF_INPUT);
    }

    followDS *followNode = follow_occurrence[nt];

    while (followNode)
    {
        RHSNode *occurence = followNode->occurrence;
        RHSNode *nextSymbol = occurence->next;

        if (nextSymbol)
        {
            if (nextSymbol->isT)
            {
                add_terminal_tolist(first_follow_sets[nt].follow_set, nextSymbol->v.t);
            }
            else
            {
                terminal_list *firstsetOfNext = first_follow_sets[nextSymbol->v.non_t].first_set;
                join_terminallist_exc_eps(first_follow_sets[nt].follow_set, firstsetOfNext);

                if (contains_epsilon(firstsetOfNext))
                {
                    join_terminal_list(first_follow_sets[nt].follow_set, first_follow_sets[followNode->parent_nt].follow_set);
                }
            }
        }

        else
        {
            join_terminal_list(first_follow_sets[nt].follow_set, first_follow_sets[followNode->parent_nt].follow_set);
        }

        followNode = followNode->next;
    }
}

void join_terminallist_exc_eps(terminal_list *l1, terminal_list *l2)
{
    if (l1 == NULL || l2 == NULL || l2->head == NULL)
    {
        return;
    }

    terminal_node *cur = l2->head;

    while (cur != NULL)
    {
        terminal_node *search = l1->head;
        bool found = false;

        while (search != NULL)
        {
            if ((search->t == cur->t) && (search->t != EPS))
            {
                found = true;
                break;
            }
            search = search->next;
        }

        if (!found)
        {
            terminal_node *newnode = (terminal_node *)malloc(sizeof(terminal_node));

            if (newnode == NULL)
            {
                fprintf(stderr, "memory allocation failed\n");
                exit(EXIT_FAILURE);
            }

            newnode->t = cur->t;
            newnode->next = NULL;

            if (l1->head == NULL)
            {
                l1->head = newnode;
            }
            else
            {
                terminal_node *last = l1->head;
                while (last->next != NULL)
                {
                    last = last->next;
                }
                last->next = newnode;
            }
        }
        cur = cur->next;
    }
}

void compute_follow()
{
    if (first_follow_sets[program].follow_set == NULL)
    {
        first_follow_sets[program].follow_set = (terminal_list *)malloc(sizeof(terminal_list));
        initialise_list(first_follow_sets[program].follow_set);
    }

    add_terminal_tolist(first_follow_sets[program].follow_set, END_OF_INPUT);

    populate_occ_follow();

    for (int i = 0; i < NTC; i++)
    {
        find_followset(i);
    }
}

bool createParseTree(SymbolItem *head)
{
    helperStack *Stack = (helperStack *)malloc(sizeof(helperStack));
    if (Stack == NULL){
        fprintf(stderr, "Memory allocation failed for Stack.\n");
        exit(EXIT_FAILURE);
    }

    ProductionRule *startRule = PT->table[program][head->type];
    if (startRule == NULL)
    {
        fprintf(stderr, "No production rule found for the start symbol.\n");
        exit(EXIT_FAILURE);
    }

    StackNode *startNode = (StackNode *)malloc(sizeof(StackNode));
    if (startNode == NULL)
    {
        fprintf(stderr, "Memory allocation failed for StackNode.\n");
        exit(EXIT_FAILURE);
    }
    startNode->isT = false;
    startNode->value.non_t = program;
    startNode->next = NULL;
    Stack->top = startNode;
    Stack->size = 1;

    token *currentToken = head;
    treeNode *root = NULL;
    treeNode *currentParent = NULL;

    root = (treeNode *)malloc(sizeof(treeNode));
    if (root == NULL)
    {
        printf("Memory allocation failed for root node.\n");
        exit(EXIT_FAILURE);
    }
    root->parent = NULL;
    root->firstChild = NULL;
    root->rightSibling = NULL;
    root->token_ptr = NULL;
    root->isT = false;
    root->v.non_t = program;
    currentParent = root;

    while (currentToken != NULL)
    {
        if (Stack->top == NULL)
        {
            fprintf(stderr, "Error: Stack underflow.\n");
            exit(EXIT_FAILURE);
        }
        bool is_terminal = Stack->top->isT;
        value currentSymbol = Stack->top->value;

        if (is_terminal)
        {
            if (currentSymbol.t == currentToken->type)
            {
                treeNode *newNode = (treeNode *)malloc(sizeof(treeNode));
                if (newNode == NULL)
                {
                    printf("Memory allocation failed for tree node.\n");
                    exit(EXIT_FAILURE);
                }
                newNode->parent = currentParent;
                newNode->firstChild = NULL;
                newNode->rightSibling = NULL;
                newNode->token_ptr = currentToken;
                newNode->isT = true;
                newNode->v.t = currentToken->type;
                if (currentParent->firstChild == NULL)
                {
                    // If the parent node doesn't have a child yet
                    currentParent->firstChild = newNode;
                }
                else
                {
                    treeNode *sibling = currentParent->firstChild;
                    while (sibling->rightSibling != NULL)
                    {
                        sibling = sibling->rightSibling;
                    }
                    sibling->rightSibling = newNode;
                }
                StackNode *temp = Stack->top;
                Stack->top = Stack->top->next;
                free(temp);
                // Move to the next token
                currentToken = currentToken->next;
            }
            else
            {
                // Error: Mismatched terminal symbol
                printf("Error: Unexpected token '%s' at line %d\n", getTokenName(currentToken->type), currentToken->line);
                return false;
            }
        }

        else
        {

            // Handle non-terminal symbol
            ProductionRule *productionRule = PT->table[currentSymbol.non_t][currentToken->type];
            if (productionRule == NULL)
            {
                // Error: No production rule found in the parsing table
                printf("Error: No production rule found for non-terminal '%s' and token '%s' at line %d\n",
                       getNonTerminalName(currentSymbol.non_t), getTokenName(currentToken->type), currentToken->line);
                return false;
            }
            else
            {
                // Apply the production rule

                // Pop the stack
                StackNode *temp = Stack->top;
                Stack->top = Stack->top->next;
                free(temp);

                // Iterate through the RHS of the production rule in reverse
                RHSNode *currentRHS = productionRule->tail; // Assuming tail points to the last RHSNode
                while (currentRHS != productionRule->head)
                {
                    // Create a new stack node for each RHS symbol
                    StackNode *rhsNode = (StackNode *)malloc(sizeof(StackNode));
                    if (rhsNode == NULL)
                    {
                        printf("Memory allocation failed for StackNode.\n");
                        exit(EXIT_FAILURE);
                    }
                    // Initialize the new stack node
                    rhsNode->isT = currentRHS->isT;
                    if (currentRHS->isT)
                    {
                        rhsNode->value.t = currentRHS->v.t;
                    }
                    else
                    {
                        rhsNode->value.non_t = currentRHS->v.non_t;
                    }
                    // Push the RHS symbol onto the stack
                    rhsNode->next = Stack->top;
                    Stack->top = rhsNode;

                    // Move to the previous RHS symbol
                    currentRHS = currentRHS->prev;
                }
            }
        }
    }
}

bool createParseTree(SymbolItem *head)
{
    helperStack *Stack = (helperStack *)malloc(sizeof(helperStack));
    if (Stack == NULL)
    {
        fprintf(stderr, "Memory allocation failed for Stack.\n");
        exit(EXIT_FAILURE);
    }

    StackNode *startNode = (StackNode *)malloc(sizeof(StackNode));
    if (startNode == NULL)
    {
        fprintf(stderr, "Memory allocation failed for StackNode.\n");
        exit(EXIT_FAILURE);
    }
    startNode->isT = false;
    startNode->value.non_t = program;
    startNode->next = NULL;
    Stack->top = startNode;
    Stack->size = 1;

    treeNode *root = (treeNode *)malloc(sizeof(treeNode));
    if (root == NULL)
    {
        fprintf(stderr, "Memory allocation failed for root node.\n");
        exit(EXIT_FAILURE);
    }
    root->parent = NULL;
    root->firstChild = NULL;
    root->rightSibling = NULL;
    root->isT = false;
    root->v.non_t = program;
    treeNode *currentParent = root;

    token *currentToken = head;

    while (currentToken != NULL)
    {
        if (Stack->top == NULL)
        {
            fprintf(stderr, "Error: Stack underflow.\n");
            exit(EXIT_FAILURE);
        }
        bool is_terminal = Stack->top->isT;
        value currentSymbol = Stack->top->value;

        if (is_terminal)
        {
            if (currentSymbol.t == currentToken->type)
            {
                treeNode *newNode = (treeNode *)malloc(sizeof(treeNode));
                if (newNode == NULL)
                {
                    fprintf(stderr, "Memory allocation failed for tree node.\n");
                    exit(EXIT_FAILURE);
                }
                newNode->parent = currentParent;
                newNode->firstChild = NULL;
                newNode->rightSibling = NULL;
                newNode->isT = true;
                newNode->v.t = currentToken->type;
                if (currentParent->firstChild == NULL)
                {
                    currentParent->firstChild = newNode;
                }
                else
                {
                    treeNode *sibling = currentParent->firstChild;
                    while (sibling->rightSibling != NULL)
                    {
                        sibling = sibling->rightSibling;
                    }
                    sibling->rightSibling = newNode;
                }
                StackNode *temp = Stack->top;
                Stack->top = Stack->top->next;
                free(temp);
                currentToken = currentToken->next;
            }
            else
            {
                fprintf(stderr, "Error: Unexpected token '%s' at line %d\n", getTokenName(currentToken->type), currentToken->line);
                return false;
            }
        }
        else
        {
            ProductionRule *productionRule = PT->table[currentSymbol.non_t][currentToken->type];
            if (productionRule == NULL)
            {
                fprintf(stderr, "Error: No production rule found for non-terminal '%s' and token '%s' at line %d\n",
                        getNonTerminalName(currentSymbol.non_t), getTokenName(currentToken->type), currentToken->line);
                return false;
            }
            else
            {
                StackNode *temp = Stack->top;
                Stack->top = Stack->top->next;
                free(temp);

                RHSNode *currentRHS = productionRule->tail;
                while (currentRHS != NULL)
                {
                    StackNode *rhsNode = (StackNode *)malloc(sizeof(StackNode));
                    if (rhsNode == NULL)
                    {
                        fprintf(stderr, "Memory allocation failed for StackNode.\n");
                        exit(EXIT_FAILURE);
                    }
                    rhsNode->isT = currentRHS->isT;
                    if (currentRHS->isT)
                    {
                        rhsNode->value.t = currentRHS->v.t;
                    }
                    else
                    {
                        rhsNode->value.non_t = currentRHS->v.non_t;
                    }
                    rhsNode->next = Stack->top;
                    Stack->top = rhsNode;
                    currentRHS = currentRHS->prev;
                }

                currentRHS = productionRule->head;
                while (currentRHS != NULL)
                {
                    treeNode *newNode = (treeNode *)malloc(sizeof(treeNode));
                    if (newNode == NULL)
                    {
                        fprintf(stderr, "Memory allocation failed for tree node.\n");
                        exit(EXIT_FAILURE);
                    }
                    newNode->parent = currentParent;
                    newNode->firstChild = NULL;
                    newNode->rightSibling = NULL;
                    newNode->isT = currentRHS->isT;
                    if (currentRHS->isT)
                    {
                        newNode->v.t = currentRHS->v.t;
                    }
                    else
                    {
                        newNode->v.non_t = currentRHS->v.non_t;
                    }
                    if (currentParent->firstChild == NULL)
                    {
                        currentParent->firstChild = newNode;
                    }
                    else
                    {
                        treeNode *sibling = currentParent->firstChild;
                        while (sibling->rightSibling != NULL)
                        {
                            sibling = sibling->rightSibling;
                        }
                        sibling->rightSibling = newNode;
                    }
                    currentParent = newNode;
                    currentRHS = currentRHS->next;
                }
            }
        }
    }

    printf("Parsing successful.\n");
    return true;
}

void printParseTree(treeNode *node, int depth)
{
    if (node == NULL)
    {
        return;
    }
    // Print current node
    for (int i = 0; i < depth; i++)
    {
        printf("  "); // Indent according to depth
    }

    if (node->isT)
    {
        printf("Terminal: %s\n", terms[node->v.t]); // define function getTokenName This function takes a token type (enumeration value) as input and returns a string representing the name or description of that token
    }
    else
    {
        printf("Non-terminal: %s\n", non_terms[node->v.non_t]);
    }

    // Print children recursively
    printParseTree(node->firstChild, depth + 1);
    printParseTree(node->rightSibling, depth); // Print right sibling at same depth
}

int main()
{
    G = (Grammar *)malloc(sizeof(Grammar));
    // Initialize rules for each non-terminal
    for (int i = 0; i < NTC; i++)
    {
        G->rules[i] = (LHSNode *)malloc(sizeof(LHSNode));
        G->rules[i]->rules = NULL;           // Assuming the rules are initialized elsewhere
        G->rules[i]->lhs = (non_terminals)i; // Assuming non-terminals are assigned corresponding values
    }
    compute_firsts();
    compute_follow();

    // Print the computed first sets for each non-terminal
    printf("First Sets:\n");
    for (int i = 0; i < NTC; i++)
    { // Assuming NTC is the count of non-terminals
        printf("First set for non-terminal %d: ", i);
        terminal_node *current = first_follow_sets[i].first_set->head;
        while (current != NULL)
        {
            printf("%c ", current->t);
            current = current->next;
        }
        printf("\n");
    }

    // Print the computed follow sets for each non-terminal
    printf("\nFollow Sets:\n");
    for (int i = 0; i < NTC; i++)
    {
        printf("Follow set for non-terminal %d: ", i);
        terminal_node *current = first_follow_sets[i].follow_set->head;
        while (current != NULL)
        {
            if (current->t == END_OF_INPUT)
            {
                printf("$ ");
            }
            else
            {
                printf("%c ", current->t);
            }
            current = current->next;
        }
        printf("\n");
    }
}
