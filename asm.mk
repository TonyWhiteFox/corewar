# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    asm.mk                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldonnor- <ldonnor-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/08 14:08:10 by mmanhack          #+#    #+#              #
#    Updated: 2020/07/11 13:12:37 by ldonnor-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ------------  PROJECT  ----------------------------------------------------- #
NAME	=		asm

# ------------  DIRECTORIES  ------------------------------------------------- #
SRC_DIR	=		src/$(NAME)
HDR_DIR	=		includes/$(NAME)
OBJ_DIR	=		obj
OBJ_DIR_NAME =	obj/$(NAME)

# ------------  LIBFT  ------------------------------------------------------- #
LFT		=		libft.a
LFT_DIR	=		libft
LHS_DIR	=		$(LFT_DIR)/includes

# ------------  SOURCE FILES  ------------------------------------------------ #
SRC_FLS = 		asm.c op.c \
				lexer.c lexer_parse.c \
				output.c output_code.c output_utils.c \
				parser.c parser_args.c parser_tokens.c \
				utils.c utils_2.c utils_3.c
HEADERS =		$(HDR_DIR)/asm.h $(HDR_DIR)/op.h

# ------------  FILEPATHS  --------------------------------------------------- #
SRCS	=		$(addprefix $(SRC_DIR)/, $(SRC_FLS))
OBJS	=		$(addprefix $(OBJ_DIR_NAME)/, $(SRC_FLS:%.c=%.o))
DEPS	=		$(OBJS:.o=.d)

# ------------  FLAGS  ------------------------------------------------------- #
CC		=		gcc
RM		=		rm -rf
CFLGS	=		-Wall -Werror -Wextra -g
IFLGS	=		-I $(HDR_DIR) -I $(LHS_DIR)
LFLGS	=		-L $(LFT_DIR) -lft
DFLGS	=		-MMD -MP
DEBUG	=		-g -pg -fsanitize=address

# ------------  RULES  ------------------------------------------------------- #
.PHONY: all clean fclean re FORCE

all: $(OBJ_DIR) $(OBJ_DIR_NAME) $(NAME)

FORCE: ;

$(LFT_DIR)/$(LFT): FORCE
	$(MAKE) -C $(LFT_DIR)

-include $(DEPS)

$(OBJS): $(OBJ_DIR_NAME)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	$(CC) $(CFLGS) $(DFLGS) -c -o $@ $< $(IFLGS)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR_NAME): $(OBJ_DIR)
	mkdir -p $(OBJ_DIR_NAME)

$(NAME): $(LFT_DIR)/$(LFT) $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LFLGS)

clean:
	$(MAKE) -C $(LFT_DIR) clean
	$(RM) $(OBJ_DIR_NAME)

fclean: clean
	$(MAKE) -C $(LFT_DIR) fclean
	$(RM) $(NAME)

re: fclean all
