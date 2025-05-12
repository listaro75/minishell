#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/minishell.h"

// Déclaration externe des fonctions à tester
extern t_token *tokenisation(char *line);
extern void free_token(t_token *token);
extern int check_possible_token(t_token *token);
extern int check_end_line(t_token *token);
extern int check_between_token(t_token *token);
extern int check_parenthesis(t_token *token);

// Fichier de log pour les erreurs
FILE *error_log = NULL;

// Macro pour les assertions de test améliorée
#define ASSERT(test_name, condition) do { \
    printf("  - %-40s: ", test_name); \
    if (condition) { \
        printf("\033[0;32m[OK]\033[0m\n"); \
    } else { \
        printf("\033[0;31m[ÉCHEC]\033[0m\n"); \
        if (error_log) { \
            fprintf(error_log, "ERREUR: %s\n", test_name); \
            fprintf(error_log, "  Fichier: %s\n", __FILE__); \
            fprintf(error_log, "  Ligne: %d\n", __LINE__); \
            fprintf(error_log, "  Fonction: %s\n", __func__); \
            fprintf(error_log, "  Date/Heure: %s\n", get_current_time()); \
            fprintf(error_log, "---------------------------------------\n"); \
        } \
        failed_tests++; \
    } \
    total_tests++; \
} while(0)

/**
 * @brief Récupère l'heure courante formatée
 * @return Chaîne contenant la date et l'heure
 */
char *get_current_time(void) {
    static char buffer[100];
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tm_info);
    return buffer;
}

/**
 * @brief Initialise le fichier de log
 */
void init_error_log(void) {
    error_log = fopen("../tests/error_log.txt", "a");
    if (error_log) {
        fprintf(error_log, "\n=== NOUVELLE SESSION DE TEST (%s) ===\n\n", get_current_time());
    }
}

/**
 * @brief Ferme le fichier de log
 */
void close_error_log(void) {
    if (error_log) {
        fclose(error_log);
        error_log = NULL;
    }
}

/**
 * @brief Teste les fonctions de vérification de validité des tokens
 * 
 * Vérifie que les fonctions de validation détectent correctement
 * les erreurs de syntaxe dans les commandes.
 * 
 * @return int Nombre de tests échoués
 */
int test_parser(void)
{
    int failed_tests = 0;
    int total_tests = 0;
    
    // Initialisation du fichier de log
    init_error_log();
    
    // Test de commandes valides
    {
        char *valid_commands[] = {
            "echo hello",
            "ls -la | grep test",
            "cat < input.txt > output.txt",
            "(echo hello && echo world)",
            "echo hello || echo world",
            NULL
        };
        
        for (int i = 0; valid_commands[i] != NULL; i++) {
            t_token *tokens = tokenisation(valid_commands[i]);
            ASSERT(valid_commands[i], check_possible_token(tokens) == 0);
            if (error_log && !(check_possible_token(tokens) == 0)) {
                fprintf(error_log, "  Commande testée: \"%s\"\n", valid_commands[i]);
                fprintf(error_log, "  Attendu: Commande valide (0)\n");
                fprintf(error_log, "  Obtenu: Commande invalide (non-0)\n\n");
            }
            free_token(tokens);
        }
    }
    
    // Test de commandes invalides
    {
        char *invalid_commands[] = {
            "echo |",
            "| echo hello",
            "echo hello &&",
            "echo hello ||",
            "echo hello > ",
            NULL
        };
        
        for (int i = 0; invalid_commands[i] != NULL; i++) {
            t_token *tokens = tokenisation(invalid_commands[i]);
            ASSERT(invalid_commands[i], check_possible_token(tokens) != 0);
            if (error_log && !(check_possible_token(tokens) != 0)) {
                fprintf(error_log, "  Commande testée: \"%s\"\n", invalid_commands[i]);
                fprintf(error_log, "  Attendu: Commande invalide (non-0)\n");
                fprintf(error_log, "  Obtenu: Commande valide (0)\n\n");
            }
            free_token(tokens);
        }
    }
    
    // Test de check_end_line
    {
        t_token *tokens = tokenisation("echo hello |");
        ASSERT("check_end_line avec pipe final", check_end_line(tokens) != 0);
        free_token(tokens);
        
        tokens = tokenisation("echo hello");
        ASSERT("check_end_line sans erreur", check_end_line(tokens) == 0);
        free_token(tokens);
    }
    
    // Test de check_between_token
    {
        t_token *tokens = tokenisation("echo | | grep");
        ASSERT("check_between_token avec pipes consécutifs", check_between_token(tokens) != 0);
        free_token(tokens);
        
        tokens = tokenisation("echo | grep");
        ASSERT("check_between_token sans erreur", check_between_token(tokens) == 0);
        free_token(tokens);
    }
    
    // Test de check_parenthesis
    {
        char *tokens [] = {
            "(echo hello",
            "echo hello)",
            "(echo hello)",
			")(",
			"((ls)",
            NULL
        };
        ASSERT("check_parenthesis non fermée", check_unclosed_paren(tokens[0]) != 0);
        ASSERT("check_parenthesis mal fermée", check_unclosed_paren(tokens[1]) != 0);
        ASSERT("check_parenthesis sans erreur", check_unclosed_paren(tokens[2]) == 0);
        ASSERT("check invers parenthesis", check_unclosed_paren(tokens[3]) != 0);
        ASSERT("check unclosed parenthesis", check_unclosed_paren(tokens[4]) != 0);

    }
    
// Test de check_parenthesis (lignes incorrectes)
	{
		char *invalid_parenthesis[] = {
			"(cat |)",
			"()",
			"(| )",
			"((ls))",
			"(ls(ls)ls)",
			"(ls | (ls) ls)",
			"((grep | ls))",
			NULL
		};
		
		for (int i = 0; invalid_parenthesis[i] != NULL; i++) {
			t_token *tokens = tokenisation(invalid_parenthesis[i]);
			ASSERT(invalid_parenthesis[i], check_parenthesis(tokens) != 0);
			if (error_log && !(check_parenthesis(tokens) != 0)) {
				fprintf(error_log, "  Commande testée: \"%s\"\n", invalid_parenthesis[i]);
				fprintf(error_log, "  Attendu: Parenthèses invalides (non-0)\n");
				fprintf(error_log, "  Obtenu: Parenthèses valides (0)\n\n");
			}
			free_token(tokens);
		}
	}

	// Test de check_parenthesis (lignes correctes)
	{
		char *valid_parenthesis[] = {
			"(echo inside)",
			"(echo hello) > file.txt",
			"(ls | wc -l)",
			"(echo 42) && echo ok",
			"(echo start && (echo mid || echo fail)) && echo end",
			"(cat < file.txt) | grep something",
			"export VAR=hello",
			"(echo $VAR)",
			"((echo first && echo second) || echo fallback) && echo done",
			"(ls)",
			"(ls | (ls) | ls)",
			"(cat | ok)",
			"((grep) | (ls))",
			"(ls | (ls | ls) | ls)",
			NULL
		};
		
		for (int i = 0; valid_parenthesis[i] != NULL; i++) {
			t_token *tokens = tokenisation(valid_parenthesis[i]);
			ASSERT(valid_parenthesis[i], check_parenthesis(tokens) == 0);
			if (error_log && !(check_parenthesis(tokens) == 0)) {
				fprintf(error_log, "  Commande testée: \"%s\"\n", valid_parenthesis[i]);
				fprintf(error_log, "  Attendu: Parenthèses valides (0)\n");
				fprintf(error_log, "  Obtenu: Parenthèses invalides (non-0)\n\n");
			}
			free_token(tokens);
		}
	}

    // Résumé
    printf("\nTotal: %d tests, %d réussis, %d échoués\n", 
           total_tests, total_tests - failed_tests, failed_tests);
    
    // Fermeture du fichier de log
    if (error_log) {
        fprintf(error_log, "\n=== FIN DE SESSION - %d erreurs détectées ===\n", failed_tests);
        fprintf(error_log, "======================================\n\n");
    }
    close_error_log();
    
    return failed_tests;
}













	//	"()
	//	"(| )"
	//	"()""
	//	"(| )"
	//	"((ls)",
	//	"((ls))",
	// 	"(ls(ls)ls)",
	// 	"(ls | (ls) ls)",
	// 	"((grep | ls))",


// 	(echo inside)
// (echo hello) > file.txt
// (ls | wc -l)
// (echo 42) && echo ok
// (echo start && (echo mid || echo fail)) && echo end
// (cat < file.txt) | grep something
// export VAR=hello
// (echo $VAR)
// ((echo first && echo second) || echo fallback) && echo done
//	"(ls)"
// 	"(ls | (ls) | ls)",
//	"(cat | ok)"
// 	"((grep) | (ls))",
// 	"(ls | (ls | ls) | ls)",
