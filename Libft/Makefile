# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/17 13:38:57 by keramos-          #+#    #+#              #
#    Updated: 2024/06/10 02:11:01 by keramos-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

# **************************************************************************** #
#                                 variables                                    #
# **************************************************************************** #


LIBFT = Libft/libft.a

CC = cc

CCFLAGS = -Wall -Wextra -Werror

ARNAME = ar crs $(NAME)

INCLUDES = -I inclu

RM = rm -f

MKDIR_P = mkdir -p

#                         Color and Checkmark Definitions                      #

LILAC=\033[38;5;183m
PINK=\033[38;5;213m
BLUE=\033[1;34m
CHECK = \033[0;34m✔\033[0m
RT = \033[0m

#                                 Print Function                               #

define print_status
	@echo "${LILAC}====> ${1}${NC}"
endef

#                                   Flag File                                  #

COMPILATION_FLAG_FILE=.compilation_started

#                                    LIBFT                                     #

SRC_DIR = src/

OBJS_DIR = objs/

LIBFT_FILES = isalpha isdigit isalnum \
		isascii isprint atoi \
		bzero calloc itoa \
		memchr memcmp memcpy \
		memmove memset \
		putchar_fd putendl_fd putnbr_fd \
		putstr_fd split strchr \
		strdup striteri strjoin \
		strlcat strlcpy strlen \
		strmapi strncmp strnstr \
		strrchr strtrim substr \
		tolower toupper\
		lstnew lstadd_front lstsize \
		lstlast lstadd_back lstdelone \
		lstclear lstiter lstmap \
		strcmp strtoke strndup \
		strcdup

SRC = $(addprefix $(SRC_DIR)ft_, $(addsuffix .c, $(LIBFT_FILES)))

OBJS := $(addprefix $(OBJS_DIR)ft_, $(addsuffix .o, $(LIBFT_FILES)))

#                                    PRINTF                                    #

PRINTF_SRC_DIR = $(SRC_DIR)printf

PRINTF_OBJS_DIR = $(OBJS_DIR)printf/

PRINTF_FILES = printf put_chars put_dig \
		put_hexa put_add

PRINTF_SRC = $(addprefix $(PRINTF_SRC_DIR)ft_, $(addsuffix .c, $(PRINTF_FILES)))

PRINTF_OBJS := $(addprefix $(PRINTF_OBJS_DIR)ft_, $(addsuffix .o, $(PRINTF_FILES)))

#                                       GNL                                    #

GNL_SRC_DIR = $(SRC_DIR)gnl

GNL_OBJS_DIR = $(OBJS_DIR)gnl/

GNL_FILES = get_next_line get_next_line_utils

GNL_SRC = $(addprefix $(GNL_SRC_DIR), $(addsuffix .c, $(GNL_FILES)))

GNL_OBJS := $(addprefix $(GNL_OBJS_DIR), $(addsuffix .o, $(GNL_FILES)))

# **************************************************************************** #
#                                 LIBFT RULES                                  #
# **************************************************************************** #

all: libft_std printf gnl

libft_std: $(NAME)

$(NAME): directories $(OBJS)
	$(call print_status,"Creating library $(NAME)...")
	@$(ARNAME) $(OBJS) > /dev/null
	@echo "${CHECK} Library $(NAME) created"
	@$(RM) $(COMPILATION_FLAG_FILE)

$(OBJS_DIR)%.o: $(SRC_DIR)%.c
	@if [ ! -f $(COMPILATION_FLAG_FILE) ]; then \
		echo "${PINK}====> Compiling library${NC}"; \
		touch $(COMPILATION_FLAG_FILE); \
	fi
	@$(CC) $(INCLUDES) $(CCFLAGS) -c $< -o $@ > /dev/null
	@echo "${CHECK} Compiled $<"

$(OBJS_DIR):
	@$(MKDIR_P) $(OBJS_DIR)

# **************************************************************************** #
#                                PRINTF RULES                                  #
# **************************************************************************** #

printf: $(NAME) $(PRINTF_OBJS)
	$(call print_status,"Adding Printf to $(NAME)...")
	@$(ARNAME) $(PRINTF_OBJS) > /dev/null
	@echo "${CHECK} Library $(NAME) created"
	@$(RM) $(COMPILATION_FLAG_FILE)

$(PRINTF_OBJS_DIR): $(OBJS_DIR)
	@$(MKDIR_P) $(PRINTF_OBJS_DIR)


$(PRINTF_OBJS_DIR)%.o: $(PRINTF_SRC_DIR)%.c
	@$(CC) $(INCLUDES) $(CCFLAGS) -c $< -o $@ > /dev/null
	@echo "${CHECK} Compiled $<"

# **************************************************************************** #
#                                  GNL RULES                                   #
# **************************************************************************** #

gnl: $(NAME) $(GNL_OBJS)
	$(call print_status,"Adding GNL to $(NAME)...")
	@$(ARNAME) $(GNL_OBJS) > /dev/null
	@echo "${CHECK} Library $(NAME) created"
	@$(RM) $(COMPILATION_FLAG_FILE)

$(GNL_OBJS_DIR): $(OBJS_DIR)
	@$(MKDIR_P) $(GNL_OBJS_DIR)

$(GNL_OBJS_DIR)%.o: $(GNL_SRC_DIR)%.c
	@$(CC) $(INCLUDES) $(CCFLAGS) -c $< -o $@ > /dev/null
	@echo "${CHECK} Compiled $<"

# **************************************************************************** #
#                                    RULES                                     #
# **************************************************************************** #

directories: $(OBJS_DIR) $(GNL_OBJS_DIR) $(PRINTF_OBJS_DIR)

clean:
	$(call print_status,"Cleaning up object files...")
	@$(RM) $(OBJS) $(OBJS_PRINTF) $(OBJS_GNL) $(COMPILATION_FLAG_FILE)
	@rm -rf $(OBJS_DIR)
	@echo "${CHECK} Cleanup complete"

fclean: clean
	$(call print_status,"Full clean - Removing library...")
	@$(RM) $(NAME)
	@echo "${CHECK} Full cleanup complete"

re: fclean all

.PHONY: all printf gnl libft_std directories clean fclean re
