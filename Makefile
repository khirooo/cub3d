# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nkolle <nkolle@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/03 13:59:31 by kfergani          #+#    #+#              #
#    Updated: 2022/12/05 16:46:50 by nkolle           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= cub3D

SRCDIR		= src/

GNLDIR		= get_next_line/

GNLFILES	= get_next_line.c get_next_line_utils.c

SRCFILES	= draw.c free.c main.c mlx.c move.c music.c parse_map.c raycast.c \
			utils.c utils2.c set.c mouse_rotate.c

SOURCES 	= $(addprefix $(SRCDIR), $(SRCFILES))
SOURCES		+= $(addprefix $(GNLDIR), $(GNLFILES))

HEADERS		= ./includes

LIBFT		= ./libft/libft.a
MLX			= ./MLX42/libmlx42.a

OBJECTS 	= $(patsubst %.c, %.o, $(SOURCES))

CC			= 	gcc
CFLAGS 		= -Wall -Wextra -Werror -lglfw 
MLXFLAGS	= /Users/$(USER)/.brew/opt/glfw/lib/

all: $(NAME)

%.o: %.c
	@$(CC) -Wall -Wextra -Werror -I $(HEADERS) -c $< -o $@

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
