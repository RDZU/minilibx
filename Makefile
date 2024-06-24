# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: razamora <razamora@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/24 19:39:28 by razamora          #+#    #+#              #
#    Updated: 2024/06/24 23:12:50 by razamora         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol
COMPILE = gcc
FLAGS = -Werror -Wextra -Wall
LINKS = -Lminilibx-linux -lmlx_Linux -lX11 -lXext

# MLX Functions

MLX_PATH = ./minilibx-linux/libmlx_Linux.a

# OBJECTS
SRCS = fractol.c math.c utils.c event.c draw.c
OBJECTS = $(SRCS:.c=.o)

all: $(MLX_PATH) $(NAME)

$(MLX_PATH):
	cd ./minilibx-linux && make 

$(NAME): $(OBJECTS)
	$(COMPILE) $(FLAGS) $(OBJECTS) $(LINKS) -o $(NAME)

%.o: %.c
	$(COMPILE) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJECTS) 

fclean: clean
	cd ./minilibx-linux && make clean && cd .. && $(RM) $(NAME)

re: fclean all

.PHONY: all