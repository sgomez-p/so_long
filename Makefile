# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sgomez-p <sgomez-p@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/23 10:55:41 by sgomez-p          #+#    #+#              #
#    Updated: 2023/03/06 13:23:41 by sgomez-p         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME		= so_long
SRCS		= so_long.c \
			  parse_map.c \
			  libft/get_next_line.c \
			  libft/get_next_line_utils.c

OBJS		= ${SRCS:.c=.o}

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror -I./libft -I./gnl -I/usr/local/include -g

LDFLAGS		= -L./minilibx -lmlx -lm -lX11 -lXext
RM			= rm -f

LIBFT_DIR	= ./libft

LIBFT		= libft.a

LIBFT_LIB	= $(addprefix $(LIBFT_DIR)/, $(LIBFT))


all: $(NAME)

$(NAME):	$(OBJS) $(LIBFT_LIB)
			$(CC) $(CFLAGS) $(LDFLAGS) -L$(LIBFT_DIR) -lft -o $(NAME) $(OBJS)

$(LIBFT_LIB):
			$(MAKE) -C $(LIBFT_DIR)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)
			$(RM) *.out
			$(MAKE) fclean -C $(LIBFT_DIR)

re:			fclean all

git:
			@git add .
			@git commit -m "$m"
			@git push
			@echo "Commit sent to github"
# To call: make git m="my commit"

.PHONY:		all clean fclean re git



# # MAC
# NAME		= so_long
# SRCS		= main.c \
# 			  so_long.c \
# 			  parse_map.c \
# 			  gnl/get_next_line.c \
# 			  gnl/get_next_line_utils.c

# OBJS		= ${SRCS:.c=.o}

# CC			= gcc
# CFLAGS		= -Wall -Wextra -Werror -I./libft -I./gnl -I/usr/local/include -g
# LDFLAGS		= -L/usr/local/lib -lmlx -framework OpenGL -framework AppKit
# RM			= rm -f

# LIBFT_DIR	= ./libft
# LIBFT		= libft.a
# LIBFT_LIB	= $(addprefix $(LIBFT_DIR)/, $(LIBFT))

# all:		$(NAME)

# $(NAME):	$(OBJS)
# 			$(MAKE) -C $(LIBFT_DIR)
# 			$(CC) $(CFLAGS) $(LDFLAGS) -L$(LIBFT_DIR) -lft -o $(NAME) $(OBJS)

# git: fclean
# 	@echo "\t${BIPurple}>>Push To Git<<${NoColor}"
# 	@git remote -v | cut -d " " -f 1 | uniq
# 	@git add . ;
# 	@read -p "Name the commit: " commit ;\
# 	git commit -m "$$commit" ;\
# 	read -p "Check the files..." -t 20;
# 	@git push ;
# clean:
# 			$(MAKE) clean -C $(LIBFT_DIR)
# 			$(RM) $(OBJS)

# fclean:		clean
# 			$(MAKE) fclean -C $(LIBFT_DIR)
# 			$(RM) $(NAME)

# re:			fclean all

# .PHONY:		all clean fclean re