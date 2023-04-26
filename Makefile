##
## EPITECH PROJECT, 2023
## B-PSU-400-REN-4-1-strace-martin.boucault
## File description:
## Makefile
##

NO_PRINT 	= 	--no-print-directory
OPTI		=	-Ofast -march=native
CC 			= 	gcc
NAME 		=	ftrace
CFLAGS		=	$(OPTI) -I ./includes
SRC_DIR 	= 	src/

SRC			=   $(SRC_DIR)handle_command.c	\
				$(SRC_DIR)loop.c			\
				$(SRC_DIR)casting.c			\
				$(SRC_DIR)utils.c			\

TEST 		= 	tests/unit_test.c

NAME_TEST = asm_test
ASM = nasm
SRC_TEST = tests/main.S
OBJ_TEST = $(SRC_TEST:.S=.o)

CFLAGS +=	-L ./libs -lmy -llink

CFLAGS += -I includes -I ../libs/my/include -I ../libs/link/include

all: lib $(NAME)

.S.o:
	@$(ASM) -felf64 $< -o $@

build_test: $(OBJ_TEST)
	@gcc $(OBJ_TEST) -o $(NAME_TEST) -fno-builtin


lib:
	@make all -C ./libs $(NO_PRINT)
	@echo -e $(BOLD) $(GREEN)"\n► LIB !"$(DEFAULT)

MAIN		=	$(SRC_DIR)core.c

OBJ			=	$(SRC:.c=.o) $(MAIN:.c=.o)


$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

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

debug:	CFLAGS += -g3
debug:	fclean $(OBJ)
	@$(CC) -Og $(OBJ) -o $(NAME)

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
