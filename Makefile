# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/30 20:09:24 by rpehkone          #+#    #+#              #
#    Updated: 2020/03/12 20:08:42 by rpehkone         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Wolf3D
LIB = libft/libft.a
HEADERS = minilibx libft mlx_io src
MAIN_FILES = main.c handle_hook.c input_state.c input_state_wrappers.c  main_loop.c image.c
FILES = Wolf3D.c line.c
.PHONY: clean fclean re all

all: $(NAME)

$(NAME):
	@make re -C libft
	@make clean -C libft
	gcc -Wall -Wextra -Werror -O3 $(addprefix mlx_io/, $(MAIN_FILES)) $(addprefix src/, $(FILES)) $(LIB) $(addprefix -I , $(HEADERS)) -L minilibx -lmlx -framework OpenGL -framework Appkit -o $(NAME)

clean:
	@make clean -C libft

fclean: clean
	@make fclean -C libft
	rm -f $(NAME)

re: fclean
	make all
