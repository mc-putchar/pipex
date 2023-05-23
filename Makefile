# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/23 14:52:15 by mcutura           #+#    #+#              #
#    Updated: 2023/05/23 14:56:31 by mcutura          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := pipex
FILES := pipex.c
OBJS := $(FILES:%.c=%.o)
HEADERS := pipex.h
CFLAGS := -Wall -Wextra -Werror

$(NAME): $(OBJS) $(HEADERS)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean:
	$(RM) $(OBJS)
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
