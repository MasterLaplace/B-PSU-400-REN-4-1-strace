##
## EPITECH PROJECT, 2023
## Laplace Library v1.0.0
## File description:
## Makefile
##

SRC_MY =	$(wildcard my/*.c)
SRC_LINK =	$(wildcard link/*.c)

SRC_TEST =	$(wildcard tests/*/*.c)

OBJ_MY =	$(SRC_MY:.c=.o)
OBJ_LINK =	$(SRC_LINK:.c=.o)

OBJ_TEST =	$(SRC_TEST:.c=.o)

NAME_MY =	libmy.a
NAME_LINK =	liblink.a

NAME_TEST =	unit_tests

INCLUDE_MY =	-I my/include
INCLUDE_LINK =	-I link/include

CC =	gcc

CFLAGS =	-Wall $(INCLUDE_MY) $(INCLUDE_LINK)
LDFLAGS =	-L. -lmy -llink

all:	$(NAME_MY) $(NAME_LINK)

$(NAME_MY):	$(OBJ_MY)
	@ar rc $(NAME_MY) $(OBJ_MY)

$(NAME_LINK):	$(OBJ_LINK)
	@ar rc $(NAME_LINK) $(OBJ_LINK)

clean:
	@rm -f $(OBJ_MY)
	@rm -f $(OBJ_LINK)
	@rm -f $(OBJ_TEST)
	@find -type f -name "*.gcda" -delete
	@find -type f -name "*.gcno" -delete

fclean:	clean
	@rm -f $(NAME_MY)
	@rm -f $(NAME_LINK)
	@rm -f $(NAME_TEST)
	@rm -rf *.gcda
	@rm -rf *.gcno

re:	fclean all

debug:	CFLAGS += -g3 -ggdb -pg
debug:	re

tests_run:	CFLAGS += --coverage -lcriterion
tests_run:	re $(OBJ_TEST)
	@$(CC) -o $(NAME_TEST) $(OBJ_TEST) $(CFLAGS) $(LDFLAGS)
	@./$(NAME_TEST)
	@gcovr --exclude tests/
	@gcovr --exclude tests/ --branches

%.o: %.c
	@$(CC) -c -o $@ $< $(CFLAGS)

.PHONY:	all clean fclean re debug tests_run
