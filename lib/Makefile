# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/05 17:16:43 by mcutura           #+#    #+#              #
#    Updated: 2023/05/18 13:54:34 by mcutura          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := libftprintf.a
LIBFT := libft/libft.a
FILES := ft_printf.c ft_printf_utils.c ft_printf_converters.c \
		ft_printf_converters_hex.c ft_printf_handle_flags.c
OBJS := $(FILES:%.c=%.o)
HEADERS := ft_printf.h libft/libft.h
CFLAGS := -Wall -Wextra -Werror
ARFLAGS := rcs

$(NAME): $(LIBFT) $(OBJS) $(HEADERS)
	cp -a $(LIBFT) $(NAME)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)

$(LIBFT):
	cp libft/libft.h libft.h
	$(MAKE) -C libft all

all: $(NAME)

bonus: $(NAME)

clean:
	$(RM) $(OBJS)
	$(MAKE) -C libft clean

fclean:
	$(RM) $(OBJS)
	$(RM) $(NAME)
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all bonus clean fclean re
