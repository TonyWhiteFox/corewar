# ------------  PROJECT  ----------------------------------------------------- #
NAME	=		corewar

# ------------  DIRECTORIES  ------------------------------------------------- #
SRC_DIR	=		src/$(NAME)
HDR_DIR	=		includes/$(NAME)
OBJ_DIR	=		obj
OBJ_DIR_NAME =	obj/$(NAME)

# ------------  MLX  --------------------------------------------------------- #
MLX		=		libmlx.a
MLX_DIR	=		miniLibX
MHS_DIR	=		$(MLX_DIR)

# ------------  LIBFT  ------------------------------------------------------- #
LFT		=		libft.a
LFT_DIR	=		libft
LHS_DIR	=		$(LFT_DIR)/includes

# ------------  SOURCE FILES  ------------------------------------------------ #
SRC_FLS	=       new_pos_vm.c \
                check_vm.c \
                create_gamer_and_fill_him_2_vm.c \
                create_gamer_and_fill_him_vm.c \
                execute_cl_vm.c \
                extermination_serfs.c \
                fill_decor_array_vm.c \
                find_players_vm.c \
                g_arg_quantity_usage_vm.c \
                g_dir_usage_vm.c \
                g_spell_time_usage.c \
                gamer_swap_vm.c \
                heat_visual_vm.c \
                hide_show_run_vm.c \
                init_start_params_vm.c \
                let_the_show_begin_vm.c \
                make_1_vm.c \
                make_2_vm.c \
                make_3_vm.c \
                make_additional_vm.c \
                new_main_vm.c \
                send_gamers_vm.c \
                winner_is_vm.c \

HEADERS =		$(HDR_DIR)/corewar.h

# ------------  FILEPATHS  --------------------------------------------------- #
SRCS	=		$(addprefix $(SRC_DIR)/, $(SRC_FLS))
OBJS	=		$(addprefix $(OBJ_DIR_NAME)/, $(SRC_FLS:%.c=%.o))
DEPS	=		$(OBJS:.o=.d)

# ------------  FLAGS  ------------------------------------------------------- #
CC		=		gcc
RM		=		rm -rf
CFLGS	=		-Wall -Werror -Wextra -g
IFLGS	=		-I $(HDR_DIR) -I $(LHS_DIR) -I $(MHS_DIR)
LFLGS	=		-L $(LFT_DIR) -lft -L $(MLX_DIR) -l mlx -framework OpenCL \
				-framework OpenGL -framework AppKit -lm
DFLGS	=		-MMD -MP
DEBUG	=		-g -pg -fsanitize=address

# ------------  RULES  ------------------------------------------------------- #
.PHONY: all clean fclean re FORCE

all: $(OBJ_DIR) $(OBJ_DIR_NAME) $(NAME)

FORCE: ;

$(MLX_DIR)/$(MLX): FORCE
	$(MAKE) -C $(MLX_DIR)

$(LFT_DIR)/$(LFT): FORCE
	$(MAKE) -C $(LFT_DIR)

-include $(DEPS)

$(OBJS): $(OBJ_DIR_NAME)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	$(CC) $(CFLGS) $(DFLGS) -c -o $@ $< $(IFLGS)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR_NAME): $(OBJ_DIR)
	mkdir -p $(OBJ_DIR_NAME)

$(NAME): $(LFT_DIR)/$(LFT) $(MLX_DIR)/$(MLX) $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LFLGS)

clean:
	$(MAKE) -C $(LFT_DIR) clean
	$(RM) $(OBJ_DIR_NAME)

fclean: clean
	$(MAKE) -C $(LFT_DIR) fclean
	$(RM) $(NAME)

re: fclean all
