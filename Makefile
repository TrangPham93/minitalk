# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: trpham <trpham@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/05 15:19:20 by trpham            #+#    #+#              #
#    Updated: 2025/10/26 18:47:18 by trpham           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc 
CFLAGS = -Wall -Wextra -Werror -g

SERVER_SRCS = server.c utils.c
CLIENT_SRCS = client.c utils.c
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
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ 

$(SERVER_NAME): $(SERVER_OBJS) $(LIBFT_NAME)
	@$(CC) $(CFLAGS) $^ -o $@
	@echo "Compiled server"

$(CLIENT_NAME): $(CLIENT_OBJS) $(LIBFT_NAME)
	@$(CC) $(CFLAGS) $^ -o $@
	@echo "Compiled client"

$(LIBFT_NAME):
	@make -C $(LIBFT_DIR)

clean:
	@make clean -C $(LIBFT_DIR)
	@rm -f $(CLIENT_OBJS) $(SERVER_OBJS)
	@echo "Clean objs"

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@rm -f  $(CLIENT_NAME) $(SERVER_NAME)
	@echo "Clean all"

re: fclean all

.PHONY: all clean fclean re
