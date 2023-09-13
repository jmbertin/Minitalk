SRCS_S	=	server.c utils.c \
			ft_printf/ft_printf.c \
			ft_printf/ft_printf_utils.c \

SRCS_C	=	client.c \
			utils.c \
			ft_printf/ft_printf.c \
			ft_printf/ft_printf_utils.c \

NAME_S	= server
NAME_C	= client

OBJS_S	= ${SRCS_S:.c=.o}
OBJS_C	= ${SRCS_C:.c=.o}

CC = gcc
FLAGS = -Wall -Wextra -Werror
INCLUDE = -I includes/

all : ${NAME_S} ${NAME_C}

${NAME_S}	: ${OBJS_S}
				@${CC} -o ${NAME_S} ${OBJS_S}
				@echo "\033[0;92m${NAME_S} successfully compiled.\033[0;39m"

${NAME_C}	: ${OBJS_C}
				@${CC}  -o ${NAME_C} ${OBJS_C}
				@echo "\033[0;92m${NAME_C} successfully compiled.\033[0;39m"

.c.o	:
				@${CC}  -c $< -o $@ ${INCLUDE}
				@echo "\033[0;93mCompiling : $< \033[0;39m"

clean :
				@rm -f ${OBJS_C} ${OBJS_S}
				@echo "\033[0;92m${NAME_C} and ${NAME_S} objects files cleaned.\033[0;39m"

fclean : clean
				@rm -f ${NAME_C} ${NAME_S}
				@echo "\033[0;92m${NAME_C} and ${NAME_S} cleaned.\033[0;39m"

re : fclean all
				@echo "\033[0;92m${NAME_C} and ${NAME_S} cleaned and rebuilded.\033[0;39m"
