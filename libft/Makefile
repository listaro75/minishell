# Couleurs ANSI
RED     = \033[31m
GREEN   = \033[32m
WHITE   = \033[37m
BROWN   = \033[33m
YELLOW  = \033[93m
RESET   = \033[0m
BLUE    = \033[34m
CYAN    = \033[36m
GRAY    = \033[90m

# Nom de la bibliothèque
NAME = libft.a

# Répertoires
SRC_DIR = src_libft
INCLUDE_DIR = include_libft
OBJDIR = obj_libft

# Commandes
CC = cc
FLAGS = -Wall -Wextra -Werror -I$(INCLUDE_DIR) -g3
AR = ar rcs
RM = rm -f

# Fichiers
SOURCES = $(shell find $(SRC_DIR) -name "*.c")
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJDIR)/%.o, $(SOURCES))
TOTAL = $(words $(SOURCES))

# Compilation principale
all: $(NAME)

$(NAME): $(OBJECTS)
	@printf "\r["
	@for i in $(shell seq 1 30); do printf "$(CYAN)▮$(RESET)"; done
	@printf "] 100%% - $(GREEN)✅ [OK]$(GREEN) Library created: $(CYAN)$(NAME) $(CYAN)📚$(RESET)\n"
	@$(AR) $@ $^

# Barre de progression
define PROGRESS_BAR
BAR_WIDTH=30 ; \
PCT=$$(expr 100 \* $(1) / $(TOTAL)) ; \
FILLED=$$(expr $(1) \* $$BAR_WIDTH / $(TOTAL)) ; \
EMPTY=$$(expr $$BAR_WIDTH - $$FILLED) ; \
BAR=$$(printf "%0.s$(CYAN)▮$(RESET)" $$(seq 1 $$FILLED)) ; \
BAR=$$BAR$$(printf "%0.s$(BLUE)▯$(RESET)" $$(seq 1 $$EMPTY)) ; \
printf "\r[$$BAR] $$PCT%% - Compiling $(YELLOW)$(<F)$(RESET) ... "
endef

# Compilation
INDEX = 0
$(OBJDIR)/%.o: $(SRC_DIR)/%.c | $(OBJDIR)
	@mkdir -p $(dir $@)
	@$(eval INDEX := $(shell expr $(INDEX) + 1))
	@$(call PROGRESS_BAR,$(INDEX))
	@$(CC) $(FLAGS) -c $< -o $@ \
	&& printf "$(GREEN)✔️ $(RESET)" \
	|| (printf "$(RED)❌$(RESET)\n" && exit 1)

# Création du dossier obj si besoin
$(OBJDIR):
	@mkdir -p $@

# Nettoyage stylisé
clean:
	@rm -rf $(OBJDIR)
	@printf "$(BROWN)🧹 Cleaning...\n$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@printf "$(YELLOW)🗑️  Removed object library     $(WHITE)➤ $(GRAY)$(NAME)$(RESET)\n"
	@printf "$(GREEN)✨ Cleanup complete!$(RESET)\n"

re:
	@printf "$(BROWN)🔄 Rebuilding project from scratch...\n$(RESET)"
	@$(MAKE) --no-print-directory fclean
	@$(MAKE) --no-print-directory all

.PHONY: all clean fclean re

