# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/13 17:07:03 by kmacquet          #+#    #+#              #
#    Updated: 2021/06/17 14:04:25 by kmacquet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCS = main.c action.c init.c utils.c
OBJS = $(SRCS:.c=.o)
RM = rm -rf

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lpthread -o $(NAME)

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re