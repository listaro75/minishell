# ════════════════════════════════════════════════ #
#                   🎨 STYLING                    #
# ════════════════════════════════════════════════ #
RED     = \033[31m
GREEN   = \033[32m
WHITE   = \033[37m
BROWN   = \033[33m
YELLOW  = \033[93m
RESET   = \033[0m
BLUE    = \033[34m
CYAN    = \033[36m
GRAY    = \033[90m
MAGENTA = \033[35m


# ════════════════════════════════════════════════ #
#                 🔧 VARIABLES                    #
# ════════════════════════════════════════════════ #
NAME = minishell

# Libft
LIBFT_DIR = libft
LIBFT_A = $(LIBFT_DIR)/libft.a

# Répertoires
SRC_DIR = src
OBJ_DIR = obj
INCLUDE_DIR = include
LIBS = -lreadline

# Commandes
CC = cc
CFLAGS = -Wall -Werror -Wextra -I$(INCLUDE_DIR) -I$(LIBFT_DIR)/include_libft -g3
RM = rm -f

# Fichiers
SRC_FILES = $(shell find $(SRC_DIR) -name "*.c")
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))
TOTAL = $(words $(SRC_FILES))

# Log
LOG = logs
TMP_LOG = .tmp_log
TMP_NORM = .tmp_norm
# ════════════════════════════════════════════════ #
#              🛠️ COMPILATION RULES               #
# ════════════════════════════════════════════════ #
all: banner $(NAME)

banner:
	@echo "$(CYAN)"
	@echo "══════════════════════════════════════════════════════════════════════════════════════════"
	@echo "$(MAGENTA)"
	@echo "|  ███╗   ███╗ █████╗ ██╗  ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     ██╗   ██╗███████╗|"
	@echo "|  ████╗ ████║██╔══██╗╚██╗██╔╝██║██╔════╝██║  ██║██╔════╝██║     ██║     ██║   ██║██╔════╝|"
	@echo "|  ██╔████╔██║███████║ ╚███╔╝ ██║███████╗███████║█████╗  ██║     ██║     ██║   ██║███████╗|"
	@echo "|  ██║╚██╔╝██║██╔══██║ ██╔██╗ ██║╚════██║██╔══██║██╔══╝  ██║     ██║     ██║   ██║╚════██║|"
	@echo "|  ██║ ╚═╝ ██║██║  ██║██╔╝ ██╗██║███████║██║  ██║███████╗███████╗███████╗╚██████╔╝███████║|"
	@echo "|  ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝ ╚═════╝ ╚══════╝|"
	@echo "|                                    M I N I S H E L L                                    |"
	@echo "$(CYAN)"
	@echo "═════════════════════════════════════════════════════════════════════════════════════════"
$(NAME): $(LIBFT_A) $(OBJ_FILES)
	
	@$(CC) $(CFLAGS) $(OBJ_FILES) $(LIBFT_A) $(LIBS) -o $@
	@printf "\r["
	@for i in $(shell seq 1 30); do printf "$(CYAN)▮$(RESET)"; done
	@printf "] 100%% - $(GREEN)✅ [OK]$(GREEN) Executable created: $(CYAN)$@ $(CYAN)🚀✔️ $(RESET)\n"
	@echo "🚀$(GREEN) $(NAME) ready!$(RESET)"

# ══ Compilation avec barre de progression stylisée ══ #
define PROGRESS_BAR
BAR_WIDTH=30 ; \
PCT=$$(expr 100 \* $(1) / $(TOTAL)) ; \
FILLED=$$(expr $(1) \* $$BAR_WIDTH / $(TOTAL)) ; \
EMPTY=$$(expr $$BAR_WIDTH - $$FILLED) ; \
BAR=$$(printf "%0.s$(CYAN)▮$(RESET)" $$(seq 1 $$FILLED)) ; \
BAR=$$BAR$$(printf "%0.s$(BLUE)▯$(RESET)" $$(seq 1 $$EMPTY)) ; \
printf "\r[$$BAR] $$PCT%% - Compiling $(YELLOW)$(<F)$(RESET) ... "
endef

INDEX = 0

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@$(eval INDEX := $(shell expr $(INDEX) + 1))
	@$(call PROGRESS_BAR,$(INDEX))
	@$(CC) $(CFLAGS) -c $< -o $@ 2> .tmp_log \
	&& printf "$(GREEN)✔️ $(RESET)" \
	|| (mkdir -p $(LOG) && cat .tmp_log >> $(LOG)/compile_errors.log && printf "\
	$(RED)❌$(RESET)\n" && echo "$(RED)[!] Compilation failed for:$(RESET) $(<F)" && exit 1)
	@rm -f .tmp_log


$(OBJ_DIR):
	@mkdir -p $@

# ════════════════════════════════════════════════ #
#                 📚 LIBFT RULE                   #
# ════════════════════════════════════════════════ #
$(LIBFT_A):
	@$(MAKE) -s -C $(LIBFT_DIR)
	@printf "$(GREEN)📚 Libft ready!$(RESET)\n"

# ════════════════════════════════════════════════ #
#                🧼 CLEANING RULES                #
# ════════════════════════════════════════════════ #
clean:
	@$(MAKE) -s -C $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR) rm -rf $(LOG) $(RM) $(TMP_LOG) $(RM) $(TMP_NORM)
	@printf "$(BROWN)🧹 Cleaning project...\n$(RESET)"
	@printf "$(YELLOW)🗑️  Removed object directory   $(WHITE)➤ $(GRAY)$(OBJ_DIR) $(NAME)$(RESET)\n"
	@printf "$(YELLOW)🗑️  Removed Lib obj directory  $(WHITE)➤ $(GRAY)obj libft.a$(RESET)\n"

fclean: clean
	@$(MAKE) -s -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)
	@printf "$(YELLOW)🗑️  Removed executable         $(WHITE)➤ $(GRAY)$(NAME)$(RESET)\n"
	@printf "$(GREEN)✨ Full cleanup done!$(RESET)\n"

re: clear
	@printf "$(BROWN)🔄 Rebuilding project from scratch...\n$(RESET)"
	@$(MAKE) --no-print-directory fclean
	@$(MAKE) --no-print-directory all

# ════════════════════════════════════════════════ #
#                   🧹 LOG RULE                    #
# ════════════════════════════════════════════════ #
log:
	@echo "$(CYAN)📄 Last compile errors:$(RESET)"
	@cat logs/compile_errors.log || echo "$(YELLOW)(no errors yet)$(RESET)"

# ════════════════════════════════════════════════ #
#                   🧹 NORM RULE                   #
# ════════════════════════════════════════════════ #
norm:
	@echo "$(CYAN)🔍 Checking norm...$(RESET)"
	@mkdir -p logs 2>/dev/null || true
	@norminette . | grep -v '^Norme: OK!' | grep -v ': OK!' | grep -v 'tests/' > .tmp_norm || true
	@if grep -q 'Error:' .tmp_norm; then \
		cat .tmp_norm; \
		cp .tmp_norm logs/norm_errors.log; \
		echo "$(RED)❌ Norm errors found. Log saved to logs/norm_errors.log$(RESET)"; \
	else \
		echo "$(GREEN)✅ All files passed norm check!$(RESET)"; \
	fi
	@rm -f .tmp_norm

# ════════════════════════════════════════════════ #
#                   🧹 CLEAR RULE                  #
# ════════════════════════════════════════════════ #
clear:
	@clear
	@echo "$(CYAN)"
	@echo "══════════════════════════════════════════════════════════════════════════════════════════"
	@echo "$(MAGENTA)"
	@echo "|                      ██████╗██╗     ███████╗ █████╗ ██████╗                            |"
	@echo "|                     ██╔════╝██║     ██╔════╝██╔══██╗██╔══██╗                           |"
	@echo "|                     ██║     ██║     █████╗  ███████║██████╔╝                           |"
	@echo "|                     ██║     ██║     ██╔══╝  ██╔══██║██╔══██╗                           |"
	@echo "|                     ╚██████╗███████╗███████╗██║  ██║██║  ██║                           |"
	@echo "|                      ╚═════╝╚══════╝╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝                           |"
	@echo "$(CYAN)"
	@echo "══════════════════════════════════════════════════════════════════════════════════════════"
	@echo "$(RESET)"

# ════════════════════════════════════════════════ #
#                   🆘 HELP RULE                   #
# ════════════════════════════════════════════════ #
help:
	@echo "$(CYAN)═══════════════════════════════════════════════════════$(RESET)"
	@echo "$(YELLOW)                    🛠️  $(NAME) Commands Help                     $(RESET)"
	@echo "$(CYAN)═══════════════════════════════════════════════════════$(RESET)"
	@echo "$(GREEN)make$(RESET)         ➤ Compile le projet"
	@echo "$(GREEN)make re$(RESET)      ➤ Recompile tout proprement"
	@echo "$(GREEN)make clean$(RESET)   ➤ Supprime les fichiers objets et logs"
	@echo "$(GREEN)make fclean$(RESET)  ➤ Supprime aussi l'exécutable"
	@echo "$(GREEN)make clear$(RESET)   ➤ Nettoie visuellement ton terminal 🧹"
	@echo "$(GREEN)make log$(RESET)     ➤ Affiche les dernières erreurs de compilation"
	@echo "$(GREEN)make norm$(RESET)    ➤ Vérifie la norme avec Norminette"
	@echo "$(GREEN)make help$(RESET)    ➤ Affiche cette aide"
	@echo "$(CYAN)═══════════════════════════════════════════════════════$(RESET)"


.PHONY: all clean fclean re log norm help banner
