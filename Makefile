##
## EPITECH PROJECT, 2023
## B-PSU-400-REN-4-1-strace-martin.boucault
## File description:
## Makefile
##



# TAGS


NO_PRINT 	= 	--no-print-directory
OPTI		=	-Ofast -march=native
CC 			= 	gcc
NAME 		=	ftrace
CFLAGS		=	$(OPTI) -I ./includes
CFLAGS 		+=	-L ./libs -lmy -llink
CFLAGS 		+= -I includes -I ./libs/my/include -I ./libs/link/include

SRC	=	$(wildcard src/*.c) \
		$(wildcard src/*/*.c)

OBJ	=	$(SRC:.c=.o)



# ALL


all: lib $(NAME)

$(NAME): $(OBJ)
	@$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	@make clean -C ./libs $(NO_PRINT)
	@$(RM) $(OBJ)
	@$(RM) *~
	@$(RM) *#
	@$(RM) $(OBJ_TEST)

fclean:	clean
	@make fclean -C ./libs $(NO_PRINT)
	@$(RM) $(NAME)
	@$(RM) *.gcda
	@$(RM) *.gcno
	@$(RM) vgcore.*
	@$(RM) *.gcov
	@$(RM) $(NAME_TEST)
	@$(RM) unit_tests

re: fclean all



# LIB


lib:
	@make all -C ./libs $(NO_PRINT)
	@echo -e $(BOLD) $(GREEN)"\n► LIB !"$(DEFAULT)



# DEBUG


debug:	CFLAGS += -g3
debug:	fclean all



# TESTS


TEST 		= 	tests/unit_test.c

NAME_TEST = asm_test
ASM = nasm
SRC_TEST = tests/main.S
OBJ_TEST = $(SRC_TEST:.S=.o)


.S.o:
	@$(ASM) -felf64 $< -o $@

build_test: $(OBJ_TEST)
	@gcc $(OBJ_TEST) -o $(NAME_TEST) -fno-builtin

tests_run: re build_test
	@gcc -o unit_tests $(TEST) $(OBJ) $(CFLAGS) --coverage -lcriterion
	@./unit_tests
	@$(RM) unit_tests

coverage:
	@gcovr --exclude tests/

coverage_b:
	@gcovr -b --exclude tests/


%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
