# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/03 13:59:31 by kfergani          #+#    #+#              #
#    Updated: 2022/11/16 14:32:58 by kfergani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= cub3d

SOURCES 	= $(shell find ./src -name "*.c") $(shell find ./get_next_line -name "*.c")
HEADERS		= ./includes

LIBFT		= ./libft/libft.a
MLX			= ./mlx/libmlx.a

OBJECTS 	= $(patsubst %.c, %.o, $(SOURCES))

CC			= 	gcc
CFLAGS 		= 
MLXFLAGS	= -Lmlx -lmlx -framework OpenGL -framework AppKit -lz

all: $(NAME)

%.o: %.c
	@$(CC) -I $(HEADERS) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJECTS) $(LIBFT) $(MLX)
	@$(CC) $(CFLAGS) $(LIBFT) $(MLXFLAGS) -I $(HEADERS) $(OBJECTS) -o $(NAME)
	@echo "Compiled !"

$(LIBFT): 
	@make -C ./libft
	@cp  $(LIBFT) .

$(MLX): 
	@make -C ./mlx
	@cp  $(MLX) .

clean:
	@make fclean -C ./libft
	@make clean -C ./mlx
	-@rm $(OBJECTS)
	@echo "Everything is Cleaned !"

fclean: clean
	-@rm $(NAME)
	-@rm ./libft.a
	@rm ./libmlx.a

git:
	@git add .
	-@git commit -m "Update!"
	@git push
	@echo "Commited!"

re: clean all

.PHONY: re fclean clean all
