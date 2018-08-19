SRC=			    ./download.c \
			        ./get_list_info.c \
			        ./main.c \
			        ./utilities.c \

OBJ=			    $(SRC:.c=.o)

NAME=			    a.out

CCFLAGS=		    -Wall -Wextra -Werror -ansi -pedantic

LFLAGS=			    -lpthread -lcurl

all:			$(NAME)

debug: CCFLAGS +=   --finstrument-functions -g3 -DTRACE_DEBUG
debug: LFLAGS +=    -DTRACE_DEBUG
debug: $(NAME)

$(NAME):		$(OBJ)
	gcc -o $(NAME) $(OBJ) $(LFLAGS)

clean:
	rm -f $(OBJ)

fclean:			clean
	rm -f $(NAME)

re:			fclean all

.PHONY:	all clean fclean re
