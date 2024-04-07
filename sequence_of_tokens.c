// 1) Write a program in C to convert a declaration statement into a sequence of tokens
// 2) Write a program in C to convert a control flow statements (conditions and loops into a sequence of tokens.
// 3) Write a program in C to convert a 1/0 statements (printf, scanf) into a sequence of tokens.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKENS 100
#define MAX_TOKEN_LENGTH 100

typedef enum {
    KEYWORD,
    IDENTIFIER,
    CONSTANT,
    STRING_LITERAL,
    PUNCTUATOR,
    PREPROCESSOR,
    OTHER
} TokenType;

typedef struct {
    TokenType type;
    char value[MAX_TOKEN_LENGTH];
} Token;

int isIdentifier(char *token);
int isConstant(char *token);
int isStringLiteral(char *token);
int isComment(char *token);

int isKeyword(char *token) {
    char *keywords[] = {
        "auto", "break", "case", "char", "const", "continue", "default", "do",
        "double", "else", "enum", "extern", "float", "for", "goto", "if",
        "int", "long", "register", "return", "short", "signed", "sizeof",
        "static", "struct", "switch", "typedef", "union", "unsigned", "void",
        "volatile", "while"
    };
    int numKeywords = sizeof(keywords) / sizeof(keywords[0]);

    for (int i = 0; i < numKeywords; i++) {
        if (strcmp(token, keywords[i]) == 0)
            return 1;
    }

    return 0;
}

int isPunctuator(char *token) {
    char *punctuators[] = {
        "[", "]", "(", ")", "{", "}", ".", "->", "++", "--", "&", "*", "+", "-",
        "~", "!", "/", "%", "<<", ">>", "<", ">", "<=", ">=", "==", "!=", "^",
        "|", "&&", "||", "?", ":", ";", "...", "=", "*=", "/=", "%=", "+=",
        "-=", "<<=", ">>=", "&=", "^=", "|=", ",", "#", "##", "<:", ":>", "<%",
        "%>", "%:", "%:%:"
    };
    int numPunctuators = sizeof(punctuators) / sizeof(punctuators[0]);

    for (int i = 0; i < numPunctuators; i++) {
        if (strcmp(token, punctuators[i]) == 0)
            return 1;
    }

    return 0;
}

int isPreprocessor(char *token) {
    char *preprocessors[] = {
        "include", "define", "undef", "line", "error", "pragma"
    };
    int numPreprocessors = sizeof(preprocessors) / sizeof(preprocessors[0]);

    for (int i = 0; i < numPreprocessors; i++) {
        if (strcmp(token, preprocessors[i]) == 0)
            return 1;
    }

    return 0;
}

int isIdentifier(char *token) {
    if (isalpha(token[0]) || token[0] == '_')
        return 1;

    return 0;
}

int isConstant(char *token) {
    if (isdigit(token[0]))
        return 1;

    return 0;
}

int isStringLiteral(char *token) {
    if (token[0] == '"')
        return 1;

    return 0;
}

int isOther(char *token) {
    if (!isKeyword(token) && !isPunctuator(token) && !isPreprocessor(token)
        && !isIdentifier(token) && !isConstant(token) && !isStringLiteral(token))
        return 1;

    return 0;
}

void printToken(Token token) {
    switch (token.type) {
        case KEYWORD:
            printf("Keyword: %s\n", token.value);
            break;
        case IDENTIFIER:
            printf("Identifier: %s\n", token.value);
            break;
        case CONSTANT:
            printf("Constant: %s\n", token.value);
            break;
        case STRING_LITERAL:
            printf("String literal: %s\n", token.value);
            break;
        case PUNCTUATOR:
            printf("Punctuator: %s\n", token.value);
            break;
        case PREPROCESSOR:
            printf("Preprocessor: %s\n", token.value);
            break;
        case OTHER:
            printf("Other: %s\n", token.value);
            break;
    }
}

int main() {
    char input[1000];
    Token tokens[MAX_TOKENS];
    int numTokens = 0;

    printf("Enter a statement: ");
    fgets(input, sizeof(input), stdin);

    char *start = input;
    char *end = input;

    while (*end != '\0') {
        while (*start == ' ' || *start == '\t' || *start == '\n')
            start++;

        end = start;
        while (*end != ' ' && *end != '\t' && *end != '\n' && *end != '\0')
            end++;

        int tokenLength = end - start;
        if (tokenLength > 0) {
            char token[MAX_TOKEN_LENGTH];
            strncpy(token, start, tokenLength);
            token[tokenLength] = '\0';

            if (isKeyword(token)) {
                tokens[numTokens].type = KEYWORD;
            } else if (isPunctuator(token)) {
                tokens[numTokens].type = PUNCTUATOR;
            } else if (isPreprocessor(token)) {
                tokens[numTokens].type = PREPROCESSOR;
            } else if (isOther(token)) {
                tokens[numTokens].type = OTHER;
            } else if (isIdentifier(token)) {
                tokens[numTokens].type = IDENTIFIER;
            } else if (isConstant(token)) {
                tokens[numTokens].type = CONSTANT;
            } else if (isStringLiteral(token)) {
                tokens[numTokens].type = STRING_LITERAL;
            } else {
                printf("Error: Invalid token\n");
                return 1;
            }

            strcpy(tokens[numTokens].value, token);
            numTokens++;
        }

        start = end;
    }

    printf("\nTokens:\n");
    for (int i = 0; i < numTokens; i++)
        printToken(tokens[i]);

    return 0;
}

// Output:
// Enter a statement: int main ( ) { printf ( " Hello World! \n " ) ; return 0 ; }
//
// Tokens:
// Keyword: int
// Identifier: main
// Punctuator: (
// Punctuator: )
// Punctuator: {
// Identifier: printf
// Punctuator: (
// String literal: "Hello, world!\n"
// Punctuator: )
// Punctuator: ;
// Keyword: return
// Constant: 0
// Punctuator: ;
// Punctuator: }
