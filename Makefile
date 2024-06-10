# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/07 17:06:07 by keramos-          #+#    #+#              #
#    Updated: 2024/06/10 02:30:20 by keramos-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

# **************************************************************************** #
#                                 variables                                    #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

LIBFT = ./Libft/libft.a

INCLUDES = -I inc \
			-I Libft/inclu

RL_LIB = -lreadline -lhistory -L $(READLINE_DIR)/lib -lreadline

RM = rm -rf

#                         Color and Checkmark Definitions                      #

LILAC=\033[1;38;5;183m
PINK=\033[1;38;5;213m
BABY_BLUE = \033[1;38;5;153m
ORG =\033[38;5;216m
BLUE=\033[1;34m
AQUA=\033[1;38;5;79m
AQUA_L=\033[38;5;51m
CHECK = \033[0;34m✔\033[0m
RT = \033[0m

#                                 Print Function                               #

define print_libs
	@echo "${BABY_BLUE}====> ${1}${RT}"
endef

define print_status
	@echo "${LILAC}====> ${1}${RT}"
endef

define norm_check
	@echo "${AQUA}====> ${1}${RT}"
endef

#                                    Flag File                                 #

#COMPILATION_FLAG_FILE=.compilation_started

# **************************************************************************** #
#                                 SOURCES                                      #
# **************************************************************************** #

SRCS = minishell.c \
	utils/input.c utils/intro_art.c utils/utils.c utils/checks.c \
	utils/erro.c utils/free.c \
	parsing/ast.c parsing/token.c \
	built/built_cd.c built/built_echo.c built/built_pwd.c built/built_exit.c \
	built/built_env.c \
	src/cmd_execute.c src/execute.c src/process.c src/path.c src/setup_pipe.c \
	src/var_exp.c

OBJS = $(SRCS:.c=.o)


# **************************************************************************** #
#                                  RULES                                       #
# **************************************************************************** #

all: Start $(NAME) End

Start :
	@if [ -f $(NAME) ]; then \
		echo "${LILAC}Checking if build is necessary...${RT}"; \
	else \
		echo "${PINK}Compiling Minishell...${RT}"; \
		echo "Starting the build process...!"; \
	fi

$(LIBFT):
	$(call print_libs,"Compiling Libft...")
	@make -C Libft > /dev/null
	@echo "${CHECK} Libft compiled                 ✅"

$(NAME): $(OBJS) $(LIBFT)
	$(call print_status,"Creating Minishell...")
	@$(CC) $(INCLUDES) $(OBJS) $(LIBFT) $(RL_LIB) -o $@ > /dev/null
	@echo "${CHECK} Compiling utilities and sources"

%.o: %.c
	@${CC} $(INCLUDES) ${CFLAGS} -c $< -o $@ > /dev/null

End :
	@echo "${PINK}Minishell...${RT}";
	@echo "${CHECK} successfully compiled!         🎉$(RT)";

# **************************************************************************** #
#                                NORMINETTE                                    #
# **************************************************************************** #

norm:
	$(call print_libs,"Norminette check started...")
	@for file in $$(find Libft src inc -type f -name '*.c' -o -name '*.h'); do \
		dirname=$$(basename $$(dirname $$file)); \
		if [ "$$prev_dir" != "$$dirname" ]; then \
			echo "${AQUA_L}Checking Directory: $$dirname${RT}"; \
			prev_dir=$$dirname; \
		fi; \
		basefile=$$(basename $$file); \
		result=$$(norminette $$file); \
		echo "$$result" | awk '/Error|Warning/ {print "${ORG}" $$0 "${RT}"}'; \
		if ! echo "$$result" | grep -q "Error\|Warning"; then \
			echo "✅            $$basefile ${AQUA} OK${RT}"; \
		fi; \
	done

# **************************************************************************** #
#                                clean RULES                                   #
# **************************************************************************** #

clean:
	@echo "${ORG}==> Cleaning up object files...${1}${RT}"
	@$(MAKE) clean -C Libft > /dev/null
	@$(RM) $(OBJS)
	@echo "${CHECK} Cleanup complete               🧹"

fclean: clean
	@echo "${ORG}==> Full clean - Removing executables...${1}${RT}"
	@$(MAKE) fclean -C Libft > /dev/null
	@$(RM) $(NAME)
	@echo "${CHECK} Full cleanup complete          🧹"

re: fclean all

.PHONY: all clean fclean re
