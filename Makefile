# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ngda-sil <marvin@42lausanne.ch>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/06 19:44:57 by ngda-sil          #+#    #+#              #
#    Updated: 2022/06/15 16:36:52 by ngda-sil         ###   ########.fr        #
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
FILES 		= main.c 			\
			  signal.c 			\
			  prompt.c 			\
			  env_into_list.c	\
			  parsing.c			\
			  quotes.c			\
			  quotes_list.c		\
			  reset_shell.c		\
			  execution.c		\
			  builtins/echo_builtin.c	\
			  builtins/cd_builtin.c		\
			  builtins/exit_builtin.c	\
			  builtins/pwd_builtin.c	\
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
