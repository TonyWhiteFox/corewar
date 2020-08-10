# ------------  PROJECT  ----------------------------------------------------- #
ASM = asm
DISASM = dasm
COREWAR = corewar

# ------------  DIRECTORIES  ------------------------------------------------- #

# ------------  LIBFT  ------------------------------------------------------- #

# ------------  SOURCE FILES  ------------------------------------------------ #

ASM_MAKE =      asm.mk
DASM_MAKE =     dasm.mk
CW_MAKE =       corewar.mk

# ------------  FILEPATHS  --------------------------------------------------- #

# ------------  FLAGS  ------------------------------------------------------- #
CC		=		gcc
RM		=		rm -rf
CFLGS	=		-Wall -Werror -Wextra -g
IFLGS	=		-I $(HDR_DIR) -I $(LHS_DIR)
LFLGS	=		-L $(LFT_DIR) -lft
DFLGS	=		-MMD -MP
DEBUG	=		-g -pg -fsanitize=address

# ------------  RULES  ------------------------------------------------------- #
.PHONY: all clean fclean re $(ASM) $(DISASM) $(COREWAR)

all: $(ASM) $(DISASM) $(COREWAR)

FORCE: ;

$(ASM): FORCE
	make -f $(ASM_MAKE)

$(DISASM): FORCE
	make -f $(DASM_MAKE)

$(COREWAR): FORCE
	make -f $(CW_MAKE)

clean:
	$(MAKE) -f $(ASM_MAKE) clean
	$(MAKE) -f $(DASM_MAKE) clean
	$(MAKE) -f $(CW_MAKE) clean
	$(RM) $(OBJ_DIR)

fclean: clean
	$(MAKE) -f $(ASM_MAKE) fclean
	$(MAKE) -f $(DASM_MAKE) fclean
	$(MAKE) -f $(CW_MAKE) fclean
	$(RM) $(NAME)

re: fclean all
