# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/05 13:30:50 by rmakinen          #+#    #+#              #
#    Updated: 2023/09/13 12:37:00 by rmakinen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT
SRC = main.c \
		handle_window.c \
		sphere.c \
		scene.c \
		camera.c \
		parser/ft_atox.c \
		parser/ft_print_error.c \
		parser/get_ambient_light.c \
		parser/get_new_object.c \
		parser/get_object_identifier.c \
		parser/parser_utils.c \
		parser/parser.c \

OBJ = main.o \
		handle_window.o \
		sphere.o \
		scene.o \
		camera.o \
		ft_atox.o \
		ft_print_error.o \
		get_ambient_light.o \
		get_new_object.o \
		get_object_identifier.o \
		parser_utils.o \
		parser.o \

FLAGS = #-Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(SRC)
	@cd libft && $(MAKE)
	@cc $(FLAGS) -c $(SRC)
	@cc $(FLAGS) $(OBJ) libft/libft.a -L /usr/local/include -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean:
	@cd libft && make clean
	@rm -f $(OBJ)

fclean: clean
	@cd libft && make fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
