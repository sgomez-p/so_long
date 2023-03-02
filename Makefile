# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sgomez-p <sgomez-p@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/23 10:55:41 by sgomez-p          #+#    #+#              #
#    Updated: 2023/03/02 13:04:30 by sgomez-p         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# NAME		= so_long
# SRCS		= main.c \
# 			  so_long.c \
# 			  parse_map.c \
# 			  gnl/get_next_line.c \
# 			  gnl/get_next_line_utils.c

# OBJS		= ${SRCS:.c=.o}

# CC			= gcc
# # Linux
# CFLAGS		= -Wall -Wextra -Werror -I./libft -I./gnl -I./minilibx -g
#
# RM			= rm -f

# LIBFT_DIR	= ./libft
# LIBFT		= libft.a
# LIBFT_LIB	= $(addprefix $(LIBFT_DIR)/, $(LIBFT))

# MLX_DIR		= ./minilibx
# MLX			= libmlx.a
# MLX_LIB		= $(addprefix $(MLX_DIR)/, $(MLX))

# all:		$(NAME)

# $(NAME):	$(OBJS)
# 			$(MAKE) -C $(LIBFT_DIR)
# 			$(MAKE) -C $(MLX_DIR)
# # Linux
# #			$(CC) $(CFLAGS) -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lX11 -lXext -lm -o $(NAME) $(OBJS)
# 
# git: fclean
# 	@echo "\t${BIPurple}>>Push To Git<<${NoColor}"
# 	@git add * ;
# 	@read -p "Name the commit: " commit ;\
# 	git commit -m "$$commit" ;\
# 	git push;

# clean:
# 			$(MAKE) clean -C $(LIBFT_DIR)
# 			$(MAKE) clean -C $(MLX_DIR)
# 			$(RM) $(OBJS)

# fclean:		clean
# 			$(MAKE) fclean -C $(LIBFT_DIR)
# 			$(RM) $(NAME)

# re:			fclean all

# .PHONY:		all clean fclean re

# MAC
NAME		= so_long
SRCS		= main.c \
			  so_long.c \
			  parse_map.c \
			  gnl/get_next_line.c \
			  gnl/get_next_line_utils.c

OBJS		= ${SRCS:.c=.o}

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -I./libft -I./gnl -I/usr/local/include -g
LDFLAGS		= -L/usr/local/lib -lmlx -framework OpenGL -framework AppKit
RM			= rm -f

LIBFT_DIR	= ./libft
LIBFT		= libft.a
LIBFT_LIB	= $(addprefix $(LIBFT_DIR)/, $(LIBFT))

all:		$(NAME)

$(NAME):	$(OBJS)
			$(MAKE) -C $(LIBFT_DIR)
			$(CC) $(CFLAGS) $(LDFLAGS) -L$(LIBFT_DIR) -lft -o $(NAME) $(OBJS)

git: fclean
	@echo "\t${BIPurple}>>Push To Git<<${NoColor}"
	@git remote -v | cut -d " " -f 1 | uniq
	@git add . ;
	@read -p "Name the commit: " commit ;\
	git commit -m "$$commit" ;\
	read -p "Check the files..." -t 20;
	@git push ;
clean:
			$(MAKE) clean -C $(LIBFT_DIR)
			$(RM) $(OBJS)

fclean:		clean
			$(MAKE) fclean -C $(LIBFT_DIR)
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re