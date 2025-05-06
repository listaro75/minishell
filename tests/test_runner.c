#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/minishell.h"

// Déclarations des fonctions de test
extern int test_tokenizer(void);
extern int test_parser(void);
extern int test_utils(void);

/**
 * @brief Programme principal pour exécuter tous les tests
 * 
 * Exécute tous les tests unitaires et affiche un résumé des résultats.
 * 
 * @return int 0 si tous les tests passent, sinon le nombre de tests échoués
 */
int main(void)
{
    int failures = 0;
    
    printf("\n\033[1;36m╔════════════════════════════════════════╗\033[0m\n");
    printf("\033[1;36m║       MINISHELL - TESTS UNITAIRES       ║\033[0m\n");
    printf("\033[1;36m╚════════════════════════════════════════╝\033[0m\n\n");
    
    // Création du répertoire de logs s'il n'existe pas
    system("mkdir -p ../tests/logs");
    
    // Exécution des tests
    printf("\033[1;33m[TEST] Démarrage des tests utils...\033[0m\n");
    failures += test_utils();
    printf("\n");
    
    printf("\033[1;33m[TEST] Démarrage des tests tokenizer...\033[0m\n");
    failures += test_tokenizer();
    printf("\n");
    
    printf("\033[1;33m[TEST] Démarrage des tests parser...\033[0m\n");
    failures += test_parser();
    printf("\n");

    // Affichage du résultat final
    printf("\033[1;36m╔════════════════════════════════════════╗\033[0m\n");
    if (failures > 0) {
        printf("\033[1;31m║  %3d test(s) échoué(s)                  ║\033[0m\n", failures);
        printf("\033[1;31m║  Voir error_log.txt pour les détails    ║\033[0m\n");
        printf("\033[1;36m╚════════════════════════════════════════╝\033[0m\n");
        
        // Copier le fichier d'erreur dans le dossier logs avec date
        char cmd[256];
        sprintf(cmd, "cp ../tests/error_log.txt ../tests/logs/errors_%ld.txt", time(NULL));
        system(cmd);
        printf("\033[1;33mLog d'erreur sauvegardé dans logs/\033[0m\n");
        
        return 1;
    } else {
        printf("\033[1;32m║  Tous les tests ont réussi ! 🎉          ║\033[0m\n");
        printf("\033[1;36m╚════════════════════════════════════════╝\033[0m\n");
        return 0;
    }
}