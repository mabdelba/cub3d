# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mabdelba <mabdelba@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/25 18:34:18 by mabdelba          #+#    #+#              #
#    Updated: 2023/01/12 01:46:58 by mabdelba         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c get_next_line.c get_next_line_utils.c parsing.c parsing_utils.c \
		check_map.c convert_color.c
		

OBJ = $(SRC:.c=.o)

NAME = cub3D

CFLAGS = -Wall -Wextra -Werror
CC = gcc

LIBFT = libft/libft.a

all : $(LIBFT) $(NAME)


%.o: %.c cub.h libft/libft.h
	$(CC) $(CFLAGS) -Imlx -c $< -o $@
	
$(NAME) : $(OBJ)
	$(CC) $(OBJ) -lmlx -framework OpenGL -framework AppKit -o $(NAME) $(LIBFT)

$(LIBFT):
	make -C libft

clean :
	rm -f $(OBJ) 
	make clean -C libft

fclean : clean
	rm -f $(NAME) 
	make fclean -C libft

re : fclean all 
