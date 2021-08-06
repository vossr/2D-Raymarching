# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/30 20:09:24 by rpehkone          #+#    #+#              #
#    Updated: 2021/08/05 19:31:23 by rpehkone         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d
LIB = libft/libft.a
FOLDERS = libft mlx_io src minilibx
IO_FILES = init_window.c handle_hook.c input_state.c input_state_wrappers.c image.c
FILES = main.c read_map.c wolf.c render.c raycast.c
#FLAGS = -Wall -Wextra -Werror -O3
FLAGS = -fsanitize=address -Wall -Wextra -Werror -O3 -g
.PHONY: clean fclean re all

all: $(NAME)

$(NAME):
	@make re -C libft
	gcc $(FLAGS) $(addprefix mlx_io/, $(IO_FILES)) $(addprefix src/, $(FILES)) $(LIB) $(addprefix -I , $(FOLDERS)) -L minilibx -lmlx -framework OpenGL -framework Appkit -o $(NAME)

clean:
	@make clean -C libft

fclean: clean
	@make fclean -C libft
	rm -f $(NAME)

re: fclean
	make all
