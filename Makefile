# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ngda-sil <marvin@42lausanne.ch>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/06 19:44:57 by ngda-sil          #+#    #+#              #
#    Updated: 2022/06/14 14:33:30 by ngda-sil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ------------------------------------------------------------------------------

NAME		= minishell
CC			= gcc
CFLAGS 		= -g3 -Wall -Wextra -Werror
LFTDIR 		= ./Libft
LIBFT		= $(LFTDIR)/libft.a
RL_DIR		= -I/usr/local/opt/readline/include
RL_LIB   	= -lreadline -L/usr/local/opt/readline/lib 
SRC_PATH 	= ./src/
SRC 		= $(addprefix $(SRC_PATH), $(FILES))
OBJ			= $(SRC:.c=.o)
FILES 		= main.c 			\
			  signal.c 			\
			  prompt.c 			\
			  env_into_list.c	\
			  parsing.c			\
			  quotes.c			\
			  quotes_list.c		\
			  reset_shell.c		\
			  execution.c		\
			  echo_builtin.c	\
			  cd_builtin.c		\
			  exit_builtin.c	\
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
