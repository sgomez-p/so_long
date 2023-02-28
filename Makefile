# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sgomez-p <sgomez-p@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/23 10:55:41 by sgomez-p          #+#    #+#              #
#    Updated: 2023/02/24 12:50:44 by sgomez-p         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long.out

SRC = $(MAIN_SRC) $(SRC_ERR) $(SRC_GNL) $(SRC_MAP) $(SRC_GAME)

MAIN_SRC = parse_map.c so_long.c

LIBFT_A = libft.a
LIBF_DIR = libft/
LIBFT  = $(addprefix $(LIBF_DIR), $(LIBFT_A))

GNL = get_next_line.c get_next_line_utils.c
SRC_GNL = $(addprefix gnl/, $(GNL))

MAP = 
SRC_MAP = $(addprefix map/, $(MAP))

GAME =	
SRC_GAME = $(addprefix game/, $(GAME))

OBJ = *.o

FLAGS = -lmlx -lXext -lX11 -Wall -Wextra -Werror
INCLUDE =  -framework OpenGL -framework AppKit

NONE='\033[0m'
GREEN='\033[32m'
YELLOW='\033[33m'
GRAY='\033[2;37m'
CURSIVE='\033[3m'

all: $(NAME)

$(NAME): $(OBJ)
	@echo $(CURSIVE)$(GRAY) "     - Making libft..." $(NONE)
	@make -C $(LIBF_DIR)
	@echo $(CURSIVE)$(GRAY) "     - Compiling $(NAME)..." $(NONE)
	@gcc $(FLAGS) $(OBJ) $(LIBFT) $(INCLUDE) -o $(NAME)
	@echo $(GREEN)"- Compiled -"$(NONE)

$(OBJ): $(SRC)
	@echo $(CURSIVE)$(GRAY) "     - Making object files..." $(NONE)
	@gcc $(FALGS) -c $(SRC)

exe: re
	@make -C ./ clean
	@echo $(YELLOW)"     - Executing $(NAME)... \n"$(NONE)
	@./$(NAME) $(m)
	@echo $(YELLOW)"\n     - Done -"$(NONE)

play: all
	@echo $(YELLOW)"     - Playing all maps... \n"$(NONE)
	@make -C ./ clean
	@./$(NAME) map_files/map_0.ber

norm:
	@echo $(GRAY) ""
	@norminette $(SRC) *.h */*.h
	@echo $(NONE) ""

libftnorm:
	@echo $(GRAY) ""
	@make -C $(LIBF_DIR) norm HEADER_DIRECTORY=.
	@echo $(NONE) ""

clean:
	@echo $(CURSIVE)$(GRAY) "     - Removing object files..." $(NONE)
	@rm -rf $(OBJ)
	@make -C $(LIBF_DIR) clean

fclean: clean
	@echo $(CURSIVE)$(GRAY) "     - Removing $(NAME)..." $(NONE)
	@rm -rf $(NAME)
	@make -C $(LIBF_DIR) fclean

re: fclean all
