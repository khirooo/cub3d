# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/03 13:59:31 by kfergani          #+#    #+#              #
#    Updated: 2022/11/22 13:55:41 by kfergani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= cub3d

SOURCES 	= $(shell find ./src -name "*.c") $(shell find ./get_next_line -name "*.c")
HEADERS		= ./includes

LIBFT		= ./libft/libft.a
MLX			= ./MLX42/libmlx42.a

OBJECTS 	= $(patsubst %.c, %.o, $(SOURCES))

CC			= 	gcc
CFLAGS 		= -lglfw 
MLXFLAGS	= /Users/kfergani/.brew/opt/glfw/lib/

all: $(NAME)

%.o: %.c
	@$(CC) -I $(HEADERS) -c $< -o $@

$(NAME): $(OBJECTS) $(LIBFT) $(MLX)
	@$(CC) $(CFLAGS) $(LIBFT) $(MLX) -I $(HEADERS) $(OBJECTS) -o $(NAME) -L $(MLXFLAGS)
	@echo "Compiled !"

$(LIBFT): 
	@make -C ./libft
	@cp  $(LIBFT) .

$(MLX): 
	@make -C ./MLX42
	@cp  $(MLX) .

clean:
	@make fclean -C ./libft
	@make clean -C ./MLX42
	-@rm $(OBJECTS)
	@echo "Everything is Cleaned !"

fclean: clean
	-@rm $(NAME)
	-@rm ./libft.a
	@make fclean -C ./MLX42

git:
	@git add .
	-@git commit -m "Update!"
	@git push
	@echo "Commited!"

re: clean all

.PHONY: re fclean clean all
