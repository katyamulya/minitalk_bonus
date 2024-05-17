# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/15 11:44:07 by kdvarako          #+#    #+#              #
#    Updated: 2024/05/17 16:02:03 by kdvarako         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minitalk

N_SERVER = server

N_CLIENT = client

SERVER_SRC = server.c

CLIENT_SRC = client.c

SERVER_OBJ = ${SERVER_SRC:.c=.o}
CLIENT_OBJ = ${CLIENT_SRC:.c=.o}

B_SERVER = server_bonus

B_CLIENT = client_bonus

SERVER_SRC_B = server_bonus.c

CLIENT_SRC_B = client_bonus.c

SERVER_OBJ_B = ${SERVER_SRC_B:.c=.o}
CLIENT_OBJ_B = ${CLIENT_SRC_B:.c=.o}

CC = cc

CFlAGS = -Wall -Wextra -Werror

LIBFT = ./libft/libft.a


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

${SERVER_OBJ_B}: ${SERVER_SRC_B}
	${CC} ${CFlAGS} -c ${SERVER_SRC_B}

${CLIENT_OBJ_B}: ${CLIENT_SRC_B}
	${CC} ${CFlAGS} -c ${CLIENT_SRC_B}

${B_SERVER}:	${SERVER_OBJ_B} ${LIBFT}
	${CC} ${CFlAGS} ${SERVER_OBJ_B} ${LIBFT} -o server_bonus

${B_CLIENT}:	${CLIENT_OBJ_B} ${LIBFT}
	${CC} ${CFlAGS} ${CLIENT_OBJ_B} ${LIBFT} -o client_bonus

bonus:	${B_SERVER} ${B_CLIENT}

clean:
	rm -f ${SERVER_OBJ} ${CLIENT_OBJ} ${SERVER_OBJ_B} ${CLIENT_OBJ_B}
	$(MAKE) clean -C ./libft

fclean:	clean
	rm -f ${N_SERVER} ${N_CLIENT} ${B_SERVER} ${B_CLIENT}
	$(MAKE) fclean -C ./libft

re:	fclean all

.PHONY: all clean fclean re bonus