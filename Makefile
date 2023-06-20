# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/05 12:49:38 by paulorod          #+#    #+#              #
#    Updated: 2023/06/05 13:25:39 by paulorod         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minitalk
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = client.c \
	server.c
BINS = client server
LIBFT_PATH = ./Libft
LIBFT = $(LIBFT_PATH)/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(BINS)
$(BINS): %: %.c
	$(CC) $(CFLAGS) -o $@ $< $(LIBFT)
$(LIBFT):
	make -C $(LIBFT_PATH) all
clean:
	make -C $(LIBFT_PATH) clean
fclean: clean
	rm -f $(BINS)
	make -C $(LIBFT_PATH) fclean
re: fclean all
