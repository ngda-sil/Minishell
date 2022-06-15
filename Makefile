# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ngda-sil <marvin@42lausanne.ch>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/06 19:44:57 by ngda-sil          #+#    #+#              #
#    Updated: 2022/06/15 15:19:51 by amuhleth         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ------------------------------------------------------------------------------

NAME		= minishell
CC			= gcc
CFLAGS 		= -g3 -Wall -Wextra -Werror
LFTDIR 		= ./Libft
LIBFT		= $(LFTDIR)/libft.a
RL_DIR		= -I ~/.brew/Cellar/readline/8.1.2/include
RL_LIB   	= -lreadline -L ~/.brew/Cellar/readline/8.1.2/lib
SRC_PATH 	= ./src/
SRC 		= $(addprefix $(SRC_PATH), $(FILES))
OBJ			= $(SRC:.c=.o)
FILES 		= main2.c 			\
			  signal.c 			\
			  prompt.c 			\
			  env_into_list.c	\
			  parsing.c			\
			  parsing2.c		\
			  quotes.c			\
			  quotes_list.c		\
			  reset_shell.c		\
			  dollar.c			\
			  cmd_list.c		\

# ==============================================================================


all : $(OBJ)
	$(MAKE) -C $(LFTDIR)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(RL_DIR) $(RL_LIB) -o $(NAME)

clean :
	$(MAKE) -C $(LFTDIR) clean
	rm -Rf $(OBJ)

fclean : clean
	$(MAKE) -C $(LFTDIR) fclean
	rm -Rf $(NAME)

re : fclean all

.PHONY: all clean fclean re
