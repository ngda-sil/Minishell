#**************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ngda-sil <marvin@42lausanne.ch>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/06 19:44:57 by ngda-sil          #+#    #+#              #
#    Updated: 2022/07/27 20:08:22 by ngda-sil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ------------------------------------------------------------------------------

NAME		= minishell
CC			= gcc
CFLAGS 		= -g3 -Wall -Wextra -Werror
LFTDIR 		= ./Libft
LIBFT		= $(LFTDIR)/libft.a

# to compile on Intel Macs (x86)
#RL_DIR		= -I ~/.brew/Cellar/readline/8.1.2/include
#RL_LIB   	= -lreadline -L ~/.brew/Cellar/readline/8.1.2/lib

# to compile on M1 Macs (arm)
RL_DIR		= -I /opt/homebrew/Cellar/readline/8.1.2/include
RL_LIB		= -lreadline -L/opt/homebrew/Cellar/readline/8.1.2/lib

SRC_PATH 	= ./src/
SRC 		= $(addprefix $(SRC_PATH), $(FILES))
OBJ			= $(SRC:.c=.o)
FILES 		= main.c 					\
			  signal.c 					\
			  prompt.c 					\
			  env_into_list.c			\
			  parsing.c					\
			  parsing2.c				\
			  parsing3.c				\
			  parsing4.c				\
			  heredoc.c					\
			  quotes.c					\
			  quotes_list.c				\
			  reset_shell.c				\
			  dollar.c					\
			  cmd_list.c				\
			  utils.c					\
			  quit.c					\
			  free.c					\
			  free2.c					\
			  exec_cmd.c				\
			  path.c					\
			  pipe.c					\
			  builtins/cd_builtin.c		\
			  builtins/echo_builtin.c	\
			  builtins/env_builtin.c	\
			  builtins/pwd_builtin.c	\
			  builtins/exit_builtin.c	\
			  builtins/export_builtin.c	\
			  builtins/export_utils.c	\
			  builtins/unset_builtin.c	\

# =============================================================================

all :	$(NAME)

$(NAME) :	$(OBJ)
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
