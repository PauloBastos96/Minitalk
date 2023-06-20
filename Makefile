# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/05 12:49:38 by paulorod          #+#    #+#              #
#    Updated: 2023/06/20 12:57:21 by paulorod         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minitalk
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = client.c \
	server.c
BINS = client server
BINS_BONUS = client_bonus server_bonus
LIBFT_PATH = ./Libft
LIBFT = $(LIBFT_PATH)/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(BINS)
bonus: $(LIBFT) $(BINS_BONUS)
$(BINS): %: %.c
	$(CC) $(CFLAGS) -o $@ $< $(LIBFT)
$(BINS_BONUS): %: %.c
	$(CC) $(CFLAGS) -o $@ $< $(LIBFT)
$(LIBFT):
	make -C $(LIBFT_PATH) all
clean:
	make -C $(LIBFT_PATH) clean
fclean: clean
	rm -f $(BINS)
	rm -f $(BINS_BONUS)
	make -C $(LIBFT_PATH) fclean
re: fclean all
