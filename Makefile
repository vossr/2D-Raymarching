# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/30 20:09:24 by rpehkone          #+#    #+#              #
#    Updated: 2020/08/15 14:02:17 by rpehkone         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d
LIB = libft/libft.a
FOLDERS = libft mlx_io src
IO_FILES = init_window.c handle_hook.c input_state.c input_state_wrappers.c image.c
FILES = main.c wolf.c render.c
FLAGS = -Wall -Wextra -Werror -O3
.PHONY: clean fclean re all

all: $(NAME)

$(NAME):
	@make re -C libft
	gcc $(FLAGS) $(addprefix mlx_io/, $(IO_FILES)) $(addprefix src/, $(FILES)) $(LIB) $(addprefix -I , $(FOLDERS)) -lmlx -framework OpenGL -framework Appkit -o $(NAME)

clean:
	@make clean -C libft

fclean: clean
	@make fclean -C libft
	rm -f $(NAME)

re: fclean
	make all
