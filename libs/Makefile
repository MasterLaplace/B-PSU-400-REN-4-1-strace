##
## EPITECH PROJECT, 2023
## B-PSU-400-REN-4-1-ftrace-martin.boucault
## File description:
## Makefile
##

SRC_MY =	$(wildcard my/*.c)
SRC_LINK =	$(wildcard link/*.c)

OBJ_MY =	$(SRC_MY:.c=.o)
OBJ_LINK =	$(SRC_LINK:.c=.o)

NAME_MY =	libmy.a
NAME_LINK =	liblink.a

INCLUDE_MY =	-I my/include
INCLUDE_LINK =	-I link/include

CC =	gcc

CFLAGS =	-Wall $(INCLUDE_MY) $(INCLUDE_LINK)

all:	$(NAME_MY) $(NAME_LINK)

$(NAME_MY):	$(OBJ_MY)
	@ar rc $(NAME_MY) $(OBJ_MY)

$(NAME_LINK):	$(OBJ_LINK)
	@ar rc $(NAME_LINK) $(OBJ_LINK)

clean:
	@rm -f $(OBJ_MY)
	@rm -f $(OBJ_LINK)

fclean:	clean
	@rm -f $(NAME_MY)
	@rm -f $(NAME_LINK)

re:	fclean all

debug:	CFLAGS += -g3
debug:	re

%.o: %.c
	@$(CC) -c -o $@ $< $(CFLAGS)

.PHONY:	all clean fclean re
