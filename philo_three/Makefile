# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: geldiss <geldiss@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/28 20:17:27 by geldiss           #+#    #+#              #
#    Updated: 2021/04/11 14:31:13 by geldiss          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_three

FLAGS = -pthread -Wall -Wextra -Werror

O_DIR = obj

S_DIR = srcs

HEADER_DIR = ./

SRCS = main.c ft_atoi.c utils.c ft_life.c all_init.c

OBJ = $(addprefix $(O_DIR)/,$(SRCS:.c=.o))

$(O_DIR)/%.o: ./%.c
	@mkdir -p $(O_DIR)
	gcc $(FLAGS) -I $(HEADER_DIR) -o $@ -c $<

all: $(NAME)

$(NAME): $(OBJ)
	gcc $(FLAGS) -o $(NAME) $(OBJ) -I $(HEADER_DIR)

clean:
	@rm -rf $(O_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
