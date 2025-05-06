#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/minishell.h"

// Déclaration des fonctions testées
extern int is_operator(char c);
extern int is_token_operator(t_token_type type);
extern int check_unclosed_quotes(char *line);
extern int check_unclosed_paren(char *line);

// Macro pour les assertions de test
#define ASSERT(test_name, condition) do { \
    printf("  - %-40s: ", test_name); \
    if (condition) { \
        printf("\033[0;32m[OK]\033[0m\n"); \
    } else { \
        printf("\033[0;31m[ÉCHEC]\033[0m\n"); \
        failed_tests++; \
    } \
    total_tests++; \
} while(0)

/**
 * @brief Tests des fonctions utilitaires
 * 
 * Teste les fonctions de base comme is_operator, check_unclosed_quotes, etc.
 * 
 * @return int Nombre de tests échoués
 */
int test_utils(void)
{
    int failed_tests = 0;
    int total_tests = 0;

    // Tests pour is_operator
    ASSERT("is_operator('|')", is_operator('|') == 1);
    ASSERT("is_operator('&')", is_operator('&') == 1);
    ASSERT("is_operator('<')", is_operator('<') == 1);
    ASSERT("is_operator('>')", is_operator('>') == 1);
    ASSERT("is_operator('(')", is_operator('(') == 1);
    ASSERT("is_operator(')')", is_operator(')') == 1);
    ASSERT("is_operator('a')", is_operator('a') == 0);
    ASSERT("is_operator(' ')", is_operator(' ') == 0);

    // Tests pour is_token_operator
    ASSERT("is_token_operator(PIPE)", is_token_operator(PIPE) == 1);
    ASSERT("is_token_operator(AND)", is_token_operator(AND) == 1);
    ASSERT("is_token_operator(OR)", is_token_operator(OR) == 1);
    ASSERT("is_token_operator(WORD)", is_token_operator(WORD) == 0);
    ASSERT("is_token_operator(REDIR_IN)", is_token_operator(REDIR_IN) == 0);

    // Tests pour check_unclosed_quotes
    ASSERT("check_unclosed_quotes(\"text\")", check_unclosed_quotes("text") == 0);
    ASSERT("check_unclosed_quotes(\"'text'\")", check_unclosed_quotes("'text'") == 0);
    ASSERT("check_unclosed_quotes(\"\\\"text\\\"\")", check_unclosed_quotes("\"text\"") == 0);
    ASSERT("check_unclosed_quotes(\"'text\")", check_unclosed_quotes("'text") == 1);
    ASSERT("check_unclosed_quotes(\"\\\"text\")", check_unclosed_quotes("\"text") == 1);
    ASSERT("check_unclosed_quotes(\"text'\")", check_unclosed_quotes("text'") == 1);
    
    // Tests pour check_unclosed_paren
    ASSERT("check_unclosed_paren(\"text\")", check_unclosed_paren("text") == 0);
    ASSERT("check_unclosed_paren(\"(text)\")", check_unclosed_paren("(text)") == 0);
    ASSERT("check_unclosed_paren(\"(text\")", check_unclosed_paren("(text") == 1);
    ASSERT("check_unclosed_paren(\"text)\")", check_unclosed_paren("text)") == 1);
    ASSERT("check_unclosed_paren(\"((text))\")", check_unclosed_paren("((text))") == 0);

    // Résumé
    printf("\nTotal: %d tests, %d réussis, %d échoués\n", 
           total_tests, total_tests - failed_tests, failed_tests);
    
    return failed_tests;
}