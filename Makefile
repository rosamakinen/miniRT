# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/05 13:30:50 by rmakinen          #+#    #+#              #
#    Updated: 2023/10/14 17:00:21 by rmakinen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT
SRC = main.c \
		handle_window.c \
		scene.c \
		vector_math.c \
		vector_math2.c \
		normals.c \
		light.c \
		shadows.c \
		parser/ft_atox.c \
		parser/ft_print_error.c \
		parser/get_ambient_light.c \
		parser/get_new_object.c \
		parser/get_camera.c \
		parser/get_light_source.c \
		parser/get_object_identifier.c \
		parser/parser_utils.c \
		parser/parser.c \
		ray_hit.c \
		colors.c \
		color_math.c \
		color_math2.c \
		object_colors.c \
		object_intersection.c \

OBJ = main.o \
		handle_window.o \
		scene.o \
		vector_math.o \
		vector_math2.o \
		normals.o \
		light.o \
		shadows.o \
		ft_atox.o \
		ft_print_error.o \
		get_camera.o \
		get_light_source.o \
		get_ambient_light.o \
		get_new_object.o \
		get_object_identifier.o \
		parser_utils.o \
		parser.o \
		ray_hit.o \
		colors.o \
		color_math.o \
		color_math2.o \
		object_colors.o \
		object_intersection.o \

FLAGS = -Wall -Wextra -Werror -g -fsanitize=address,undefined

all: $(NAME)

$(NAME): $(SRC)
	@cd libft && $(MAKE)
	@cc $(FLAGS) -c $(SRC)
	@cc $(FLAGS) $(OBJ) libft/libft.a -L /usr/local/include -lmlx -framework OpenGL -framework AppKit -o $(NAME)
	#@cc $(FLAGS) $(OBJ) libft/libft.a mlx/libmlx.a -framework OpenGL -framework AppKit -o $(NAME)

clean:
	@cd libft && make clean
	@rm -f $(OBJ)

fclean: clean
	@cd libft && make fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
