##
## EPITECH PROJECT, 2023
## B-PSU-400-REN-4-1-strace-martin.boucault
## File description:
## Makefile
##

NO_PRINT 	= 	--no-print-directory
OPTI		=	-Ofast -march=native
CC 			= 	gcc
NAME 		=	strace
CFLAGS		=	$(OPTI) -I ./includes
SRC_DIR 	= 	src/

SRC			=   $(SRC_DIR)handle_command.c	\
				$(SRC_DIR)loop.c			\
				$(SRC_DIR)casting.c			\

MAIN		=	$(SRC_DIR)core.c

OBJ			=	$(SRC:.c=.o) $(MAIN:.c=.o)


$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

all: $(NAME)

clean:
	@$(RM) $(OBJ)
	@$(RM) *~
	@$(RM) *#

fclean:	clean
	@$(RM) $(NAME)
	@$(RM) *.gcda
	@$(RM) *.gcno
	@$(RM) vgcore.*

re: fclean all

debug:	CFLAGS += -g3
debug:	fclean $(OBJ)
	@$(CC) -Og $(OBJ) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
