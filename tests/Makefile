# ════════════════════════════════════════════════ #
#              🧪 TEST CONFIGURATION              #
# ════════════════════════════════════════════════ #

NAME = run_tests
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

# Chemin vers les répertoires principaux du projet
MAIN_DIR = ..
INCLUDE_DIR = $(MAIN_DIR)/include
SRC_DIR = $(MAIN_DIR)/src
LIBFT_DIR = $(MAIN_DIR)/libft

# Fichiers sources à tester
TEST_SRCS = test_runner.c \
            test_parser.c \
            test_tokenizer.c \
            test_utils.c

# Fichiers du projet principal nécessaires aux tests
MINISHELL_SRCS = $(SRC_DIR)/parsing/utils_tokenisation.c \
                $(SRC_DIR)/parsing/tokenisation.c \
                $(SRC_DIR)/parsing/check_token.c \
                $(SRC_DIR)/exit/exit_code.c

# Objets
TEST_OBJS = $(TEST_SRCS:.c=.o)
MINISHELL_OBJS = $(MINISHELL_SRCS:.c=.o)

# Couleurs pour l'affichage
GREEN = \033[0;32m
RED = \033[0;31m
YELLOW = \033[0;33m
CYAN = \033[0;36m
MAGENTA = \033[0;35m
RESET = \033[0m

# ════════════════════════════════════════════════ #
#                  🚀 RULES                       #
# ════════════════════════════════════════════════ #

all: banner $(NAME)

banner:
	@echo "$(CYAN)"
	@echo "═══════════════════════════════════════════════════════"
	@echo "$(MAGENTA)"
	@echo "  ████████╗███████╗███████╗████████╗███████╗"
	@echo "  ╚══██╔══╝██╔════╝██╔════╝╚══██╔══╝██╔════╝"
	@echo "     ██║   █████╗  ███████╗   ██║   ███████╗"
	@echo "     ██║   ██╔══╝  ╚════██║   ██║   ╚════██║"
	@echo "     ██║   ███████╗███████║   ██║   ███████║"
	@echo "     ╚═╝   ╚══════╝╚══════╝   ╚═╝   ╚══════╝"
	@echo "       M I N I S H E L L   T E S T S         "
	@echo "$(CYAN)"
	@echo "═══════════════════════════════════════════════════════"
	@echo "$(RESET)"

$(NAME): $(TEST_OBJS) $(MINISHELL_OBJS)
	@echo "$(YELLOW)🔗 Linking test executable...$(RESET)"
	@$(CC) $(CFLAGS) -o $@ $^ -L$(LIBFT_DIR) -lft
	@echo "$(GREEN)✅ Test executable ready! Run with ./$(NAME)$(RESET)"

%.o: %.c
	@echo "$(YELLOW)🔧 Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

clean:
	@echo "$(YELLOW)🧹 Cleaning test objects...$(RESET)"
	@rm -f $(TEST_OBJS)
	@echo "$(GREEN)✨ Tests cleaned!$(RESET)"

fclean: clean
	@echo "$(YELLOW)🧹 Removing test executable...$(RESET)"
	@rm -f $(NAME)
	@echo "$(GREEN)✨ Tests fully cleaned!$(RESET)"

re: fclean all

run: $(NAME)
	@echo "$(YELLOW)▶️ Running tests...$(RESET)"
	@./$(NAME)

# Ajout des commandes pour gérer les logs d'erreurs

logs: 
	@mkdir -p logs
	@echo "$(YELLOW)📊 Affichage des derniers logs d'erreurs :$(RESET)"
	@if [ -f "error_log.txt" ]; then \
		cat error_log.txt; \
	else \
		echo "$(RED)Aucun log d'erreur trouvé$(RESET)"; \
	fi

clean_logs:
	@echo "$(YELLOW)🧹 Nettoyage des logs...$(RESET)"
	@rm -f error_log.txt logs/*.txt
	@echo "$(GREEN)✨ Logs nettoyés!$(RESET)"

.PHONY: all clean fclean re run banner logs clean_logs