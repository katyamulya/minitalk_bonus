# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/15 11:44:07 by kdvarako          #+#    #+#              #
#    Updated: 2024/05/16 15:30:18 by kdvarako         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minitalk

N_SERVER = server

N_CLIENT = client

SERVER_SRC = server.c

CLIENT_SRC = client.c

SERVER_OBJ = ${SERVER_SRC:.c=.o}
CLIENT_OBJ = ${CLIENT_SRC:.c=.o}

CC = cc

CFlAGS = -Wall -Wextra -Werror

LIBFT = ./libft/libft.a

HEADER = minitalk.h


all:	${NAME}

${SERVER_OBJ}: ${SERVER_SRC}
	${CC} ${CFlAGS} -c ${SERVER_SRC}

${CLIENT_OBJ}: ${CLIENT_SRC}
	${CC} ${CFlAGS} -c ${CLIENT_SRC}

$(LIBFT):
	$(MAKE) -C ./libft

${N_SERVER}:	${SERVER_OBJ} ${LIBFT}
	${CC} ${CFlAGS} ${SERVER_OBJ} ${LIBFT} -o server

${N_CLIENT}:	${CLIENT_OBJ} ${LIBFT}
	${CC} ${CFlAGS} ${CLIENT_OBJ} ${LIBFT} -o client

${NAME}:	${N_SERVER} ${N_CLIENT}

clean:
	rm -f ${SERVER_OBJ} ${CLIENT_OBJ}
	$(MAKE) clean -C ./libft

fclean:	clean
	rm -f ${N_SERVER} ${N_CLIENT}
	$(MAKE) fclean -C ./libft

re:	fclean all

.PHONY: all clean fclean re