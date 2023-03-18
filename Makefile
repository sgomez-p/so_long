# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sgomez-p <sgomez-p@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/23 10:55:41 by sgomez-p          #+#    #+#              #
#    Updated: 2023/03/18 13:43:11 by sgomez-p         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME		=	so_long
CC			=	gcc
SRCS		=	so_long.c parse_map.c print.c moves.c end_game.c errors.c

LIBFT		=	libft/libft.a
CFLAGS		=	-Wall -Wextra -Werror
MLXFLAGS	=	-L ./mlx/ -lmlx -framework OpenGL -framework AppKit -lz
RM			=	rm -f
OBJS		=	$(SRCS:%.c=%.o)

ifeq ($(shell uname), Linux)
MLXFLAGS	=	-L ./mlx_linux/ -lmlx -Ilmlx -lXext -lX11 -lbsd
endif


all:		$(NAME)

$(NAME):	$(OBJS)
			@make -C libft >/dev/null 2>&1
			@make clean -C libft >/dev/null 2>&1
			@$(CC) $(SRCS) $(LIBFT) $(MLXFLAGS) $(CFLAGS) -o $(NAME) >/dev/null 2>&1

%o:			%.c
			@$(CC) $(CFLAGS) -Imlx -c $< -o $@ >/dev/null 2>&1

clean:
			@$(RM) $(OBJS) >/dev/null 2>&1

fclean:		clean
			@$(RM) $(NAME) >/dev/null 2>&1
			@$(RM) *.out >/dev/null 2>&1
			@make fclean -C libft/ >/dev/null 2>&1

re:			fclean all

git: fclean
			@echo "\t${BIPurple}>>Push To Git<<${NoColor}"
			@git add . ;
			@read -p "Name the commit: " commit ;\
			git commit -m "$$commit" ;\
			git push;

.PHONY:		all clean fclean re
