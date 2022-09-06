# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oabushar <oabushar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/15 15:42:26 by oabushar          #+#    #+#              #
#    Updated: 2022/09/04 03:31:07 by oabushar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = philo.c

OBJS = $(SRCS:.c=.o)

NAME	= philo

CFLAGS	= -Wall -Werror -Wextra -g

$(NAME)	:
		gcc $(CFLAGS) -pthread -o $(NAME) $(SRCS) 

all	: $(NAME)

clean :
		rm -f $(OBJS)

fclean : clean
		rm -f $(NAME)

re : fclean all