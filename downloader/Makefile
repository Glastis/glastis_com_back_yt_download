SRC=			    ./download.c \
			        ./get_list_info.c \
			        ./main.c \
			        ./utilities.c \

SRC_NOTRACE=        ./trace.c \

OBJ=			    $(SRC:.c=.o)

OBJ_NOTRACE=	    $(SRC_NOTRACE:.c=.o)

NAME=			    a.out

CFLAGS=		        -Wall -Wextra -Werror -ansi -pedantic -std=c99

LFLAGS=			    -lpthread -lcurl

CC=                 gcc

TRACEFLAG=          -DDIRTY_WAY_WITH_UNREDONDANT_NAME

all: comp_trace $(NAME)

comp_trace:
	$(CC) -c $(SRC_NOTRACE) $(TRACEFLAG)

debug: TRACEFLAG +=-DTRACE_DEBUG
debug: fclean comp_trace
debug: CFLAGS += -finstrument-functions -g3 -DTRACE_DEBUG
debug: $(NAME)

$(NAME):		$(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(OBJ_NOTRACE) $(LFLAGS)

clean:
	rm -f $(OBJ) $(OBJ_NOTRACE)

fclean:			clean
	rm -f $(NAME)

re:			fclean all

.PHONY:	all clean fclean re
