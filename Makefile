# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/05 15:19:20 by trpham            #+#    #+#              #
#    Updated: 2025/03/06 16:18:03 by trpham           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc 
CFLAGS = -Wall -Wextra -Werror -g

SERVER_SRCS = server.c
CLIENT_SRCS = client.c
SERVER_OBJS = $(SERVER_SRCS:%.c=%.o)
CLIENT_OBJS = $(CLIENT_SRCS:%.c=%.o)

SERVER_NAME = server
CLIENT_NAME = client

LIBFT_DIR = ./libft
LIBFT_NAME = $(LIBFT_DIR)/libft.a
INCLUDES = -I$(LIBFT_DIR)

HEADERS = minitalk.h
	
all: $(SERVER_NAME) $(CLIENT_NAME)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ 

$(SERVER_NAME): $(SERVER_OBJS) $(LIBFT_NAME)
	$(CC) $(CFLAGS) $^ -o $@

$(CLIENT_NAME): $(CLIENT_OBJS) $(LIBFT_NAME)
	$(CC) $(CFLAGS) $^ -o $@

$(LIBFT_NAME):
	@make -C $(LIBFT_DIR)

clean:
	@make clean -C $(LIBFT_DIR)
	rm -f $(CLIENT_OBJS) $(SERVER_OBJS)

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	rm -f  $(CLIENT_NAME) $(SERVER_NAME)

re: fclean all

.PHONY: all clean fclean re
