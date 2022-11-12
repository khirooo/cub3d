# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/08 17:37:19 by kfergani          #+#    #+#              #
#    Updated: 2022/11/04 16:00:11 by kfergani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	libft.a
CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror

SRCS			=	ft_atoi.c ft_calloc.c ft_isalpha.c ft_isdigit.c ft_itoa.c ft_memcmp.c ft_memmove.c \
					ft_putchar_fd.c ft_putnbr_fd.c ft_split.c ft_strdup.c ft_strjoin.c ft_strlcpy.c ft_strmapi.c \
					ft_strnstr.c ft_strtrim.c ft_tolower.c ft_bzero.c ft_isalnum.c ft_isascii.c ft_isprint.c \
					ft_memchr.c ft_memcpy.c ft_memset.c ft_putendl_fd.c ft_putstr_fd.c ft_strchr.c ft_striteri.c \
					ft_strlcat.c ft_strlen.c ft_strncmp.c ft_strrchr.c ft_substr.c ft_toupper.c ft_strcmp.c 
BONUS			=	ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c \
					ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c \
					ft_lstnew.c ft_lstsize.c

OBJS			= $(SRCS:.c=.o)
BONUS_OBJS		= $(BONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)

bonus:	$(OBJS) $(BONUS_OBJS)
	@ar rcs $(NAME) $(OBJS) $(BONUS_OBJS)

clean:
	rm -rf $(OBJS) $(BONUS_OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

$(OBJS): %.o:%.c
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(BONUS_OBJS): %.o:%.c
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) -c $< -o $@

.PHONY: bonus all clean fclean re
