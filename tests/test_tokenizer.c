#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/minishell.h"

// Déclaration externe des fonctions à tester
extern t_token *tokenisation(char *line);
extern t_token *add_token(t_token **lst, t_token_type type, char *content, int quoted, int expandable);
extern void free_token(t_token *token);

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
 * @brief Test de la fonctionnalité de tokenisation
 * 
 * Vérifie que la tokenisation d'une chaîne d'entrée crée correctement
 * les tokens avec les types et contenus attendus.
 * 
 * @return int Nombre de tests échoués
 */
int test_tokenizer(void)
{
    int failed_tests = 0;
    int total_tests = 0;
    
    // Test de base : commande simple
    {
        char *input = "echo hello";
        t_token *tokens = tokenisation(input);
        
        ASSERT("Tokenisation de 'echo hello'", tokens != NULL);
        if (tokens) {
            ASSERT("Premier token est WORD", tokens->type == WORD);
            ASSERT("Premier token contenu", strcmp(tokens->content, "echo") == 0);
            ASSERT("Premier token suivant existe", tokens->next != NULL);
            
            if (tokens->next) {
                ASSERT("Deuxième token est WORD", tokens->next->type == WORD);
                ASSERT("Deuxième token contenu", strcmp(tokens->next->content, "hello") == 0);
                ASSERT("Deuxième token suivant est NULL", tokens->next->next == NULL);
            }
            free_token(tokens);
        }
    }
    
    // Test avec pipe
    {
        char *input = "ls | grep test";
        t_token *tokens = tokenisation(input);
        
        ASSERT("Tokenisation avec pipe", tokens != NULL);
        if (tokens) {
            ASSERT("Premier token est WORD", tokens->type == WORD);
            ASSERT("Premier token contenu", strcmp(tokens->content, "ls") == 0);
            
            if (tokens->next) {
                ASSERT("Deuxième token est PIPE", tokens->next->type == PIPE);
                
                if (tokens->next->next) {
                    ASSERT("Troisième token est WORD", tokens->next->next->type == WORD);
                    ASSERT("Troisième token contenu", strcmp(tokens->next->next->content, "grep") == 0);
                    
                    if (tokens->next->next->next) {
                        ASSERT("Quatrième token est WORD", tokens->next->next->next->type == WORD);
                        ASSERT("Quatrième token contenu", strcmp(tokens->next->next->next->content, "test") == 0);
                    }
                }
            }
            free_token(tokens);
        }
    }
    
    // Test avec redirections
    {
        char *input = "cat < input.txt > output.txt";
        t_token *tokens = tokenisation(input);
        
        ASSERT("Tokenisation avec redirections", tokens != NULL);
        if (tokens) {
            ASSERT("Premier token est WORD", tokens->type == WORD);
            ASSERT("Premier token contenu", strcmp(tokens->content, "cat") == 0);
            
            if (tokens->next) {
                ASSERT("Deuxième token est REDIR_IN", tokens->next->type == REDIR_IN);
                
                if (tokens->next->next) {
                    ASSERT("Troisième token est WORD", tokens->next->next->type == WORD);
                    ASSERT("Troisième token contenu", strcmp(tokens->next->next->content, "input.txt") == 0);
                }
            }
            
            // Continuer à vérifier les autres tokens si nécessaire
            free_token(tokens);
        }
    }
    
    // Test avec guillemets
    {
        char *input = "echo \"quoted string\" 'single quoted'";
        t_token *tokens = tokenisation(input);
        
        ASSERT("Tokenisation avec guillemets", tokens != NULL);
        if (tokens) {
            ASSERT("Premier token est WORD", tokens->type == WORD);
            ASSERT("Premier token contenu", strcmp(tokens->content, "echo") == 0);
            
            if (tokens->next) {
                ASSERT("Deuxième token est WORD", tokens->next->type == WORD);
                ASSERT("Deuxième token contenu", strcmp(tokens->next->content, "quoted string") == 0);
                ASSERT("Deuxième token est quoté", tokens->next->quoted == 1);
                
                if (tokens->next->next) {
                    ASSERT("Troisième token est WORD", tokens->next->next->type == WORD);
                    ASSERT("Troisième token contenu", strcmp(tokens->next->next->content, "single quoted") == 0);
                    ASSERT("Troisième token est quoté", tokens->next->next->quoted == 1);
                }
            }
            free_token(tokens);
        }
    }
    
    // Résumé
    printf("\nTotal: %d tests, %d réussis, %d échoués\n", 
           total_tests, total_tests - failed_tests, failed_tests);
    
    return failed_tests;
}