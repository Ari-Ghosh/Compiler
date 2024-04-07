// Write a program in C to determine the First and Follow Sets from a set of Production Rules.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_PRODUCTIONS 10
#define MAX_SYMBOLS 20

struct ProductionRule {
    char nonTerminal;
    char productions[MAX_PRODUCTIONS][MAX_SYMBOLS];
    int numProductions;
};
struct Set {
    char elements[MAX_SYMBOLS];
    int count;
};

void findFirst(char nonTerminal, struct ProductionRule *rules, int numRules, struct Set *firstSet);
void findFollow(char nonTerminal, struct ProductionRule *rules, int numRules, struct Set *followSet, struct Set *firstSets, int numNonTerminals);
int containsEpsilon(char *production);

int main() {
    int numRules, numNonTerminals = 0;

    struct ProductionRule rules[MAX_PRODUCTIONS];
    struct Set firstSets[MAX_PRODUCTIONS];
    struct Set followSets[MAX_PRODUCTIONS];

    printf("Enter the number of production rules: ");
    scanf("%d", &numRules);

    printf("Enter the production rules in the form A->alpha (non-terminal symbol A, string alpha) with '|' as OR:\n");

    for (int i = 0; i < numRules; i++) {
        printf("Rule %d: ", i + 1);
        scanf(" %c->", &rules[i].nonTerminal);

        char production[MAX_SYMBOLS];
        scanf("%s", production);

        char *token = strtok(production, "|");
        int index = 0;

        while (token != NULL) {
            strcpy(rules[i].productions[index], token);
            index++;
            token = strtok(NULL, "|");
        }
        rules[i].numProductions = index;
    }
    
    for (int i = 0; i < numRules; i++) {
        findFirst(rules[i].nonTerminal, rules, numRules, &firstSets[i]);
    }
    
    for (int i = 0; i < numRules; i++) {
        findFollow(rules[i].nonTerminal, rules, numRules, &followSets[i], firstSets, numNonTerminals);
    }
    
    printf("\nFirst Sets:\n");

    for (int i = 0; i < numRules; i++) {
        printf("First(%c) = { ", rules[i].nonTerminal);

        for (int j = 0; j < firstSets[i].count; j++) {
            printf("%c, ", firstSets[i].elements[j]);
        }

        printf("}\n");
    }
    
    printf("\nFollow Sets:\n");

    for (int i = 0; i < numRules; i++) {
        printf("Follow(%c) = { ", rules[i].nonTerminal);
        
        for (int j = 0; j < followSets[i].count; j++) {
            printf("%c, ", followSets[i].elements[j]);
        }
        printf("}\n");
    }
    return 0;
}
void findFirst(char nonTerminal, struct ProductionRule *rules, int numRules, struct Set *firstSet) {
    firstSet->count = 0;

    for (int i = 0; i < numRules; i++) {
        if (rules[i].nonTerminal == nonTerminal) {
            for (int j = 0; j < rules[i].numProductions; j++) {
                char firstSymbol = rules[i].productions[j][0];

                if (islower(firstSymbol) || firstSymbol == '#') {
                    firstSet->elements[firstSet->count++] = firstSymbol;
                } 
                else {
                    findFirst(firstSymbol, rules, numRules, firstSet);
                }
            }
        }
    }
}
void findFollow(char nonTerminal, struct ProductionRule *rules, int numRules, struct Set *followSet, struct Set *firstSets, int numNonTerminals) {
    followSet->count = 0;

    if (rules[0].nonTerminal == nonTerminal) {
        followSet->elements[followSet->count++] = '$';
    }

    for (int i = 0; i < numRules; i++) {
        for (int j = 0; j < rules[i].numProductions; j++) {
            char *ptr = strchr(rules[i].productions[j], nonTerminal);

            while (ptr != NULL) {
                ptr++;
                if (*ptr != '\0') {
                    char nextSymbol = *ptr;

                    if (isupper(nextSymbol)) {
                        for (int k = 0; k < numNonTerminals; k++) {
                            if (rules[k].nonTerminal == nextSymbol) {
                                struct Set *firstSetNext = &firstSets[k];
                                for (int l = 0; l < firstSetNext->count; l++) {
                                    if (firstSetNext->elements[l] != '#') {
                                        followSet->elements[followSet->count++] = firstSetNext->elements[l];
                                    }
                                }
                                if (containsEpsilon(rules[k].productions[0])) {
                                    findFollow(rules[i].nonTerminal, rules, numRules, followSet, firstSets, numNonTerminals);
                                }
                            }
                        }
                    } 
                    else {
                        followSet->elements[followSet->count++] = nextSymbol;
                    }

                    if (*(ptr + 1) != '\0') {
                        for (int k = 0; k < numNonTerminals; k++) {
                            if (rules[k].nonTerminal == rules[i].nonTerminal) {
                                struct Set *firstSetCurrent = &firstSets[k];
                                
                                for (int l = 0; l < firstSetCurrent->count; l++) {
                                    if (firstSetCurrent->elements[l] != '#') {
                                        followSet->elements[followSet->count++] = firstSetCurrent->elements[l];
                                    }
                                }
                            }
                        }
                    }
                }
                ptr = strchr(ptr, nonTerminal);
            }
        }
    }
}
int containsEpsilon(char *production) {
    return (production[0] == '#' && production[1] == '\0');
}


// Output
// Enter the number of production rules: 3
// Enter the production rules in the form A->alpha (non-terminal symbol A, string alpha):
// Rule 1: S->AB
// Rule 2: A->aA|#
// Rule 3: B->b
// First Sets:
// First(S) = { a }
// First(A) = { a, # }
// First(B) = { b }
// Follow Sets:
// Follow(S) = { $ }
// Follow(A) = { b }
// Follow(B) = { $ }
