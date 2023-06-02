#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/23 14:52:15 by mcutura           #+#    #+#              #
#    Updated: 2023/06/02 19:29:25 by mcutura          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME := pipex
#----- DIRECTORIES -----
SRCDIR := src
INCDIR := inc
LIBDIR := lib
#----- ----------- -----
FILES := $(addprefix $(SRCDIR)/, main.c pipex.c ft_getpaths.c ft_heredoc.c \
ft_validatecmd.c ft_parenting.c error_handling.c)
OBJS := $(FILES:%.c=%.o)
#----- ----------- -----
LIBFTPRINTF := $(LIBDIR)/libftprintf.a
HEADERS := $(addprefix $(INCDIR)/, pipex.h libft.h ft_printf.h get_next_line.h)
#----- ----------- -----
CFLAGS := -Wall -Wextra -Werror -I$(INCDIR)
DEBUGFLAGS := -ggdb3 -D DEBUG=1
LDFLAGS := -L$(LIBDIR)
LDLIBS := -lftprintf
#----- ----------- -----

all: $(NAME)

$(NAME): $(HEADERS) $(LIBFTPRINTF) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS) $(LDLIBS) 

bonus: $(NAME)

$(LIBFTPRINTF):
	$(MAKE) -C $(LIBDIR) all

$(HEADERS):
	ln $(LIBDIR)/libft/libft.h $(INCDIR)/libft.h
	ln $(LIBDIR)/get_next_line.h $(INCDIR)/get_next_line.h
	ln $(LIBDIR)/ft_printf.h $(INCDIR)/ft_printf.h

clean:
	$(RM) $(OBJS)
	$(RM) $(INCDIR)/libft.h
	$(RM) $(INCDIR)/ft_printf.h
	$(RM) $(INCDIR)/get_next_line.h
	$(MAKE) -C $(LIBDIR) clean

fclean:
	$(RM) $(OBJS)
	$(RM) $(NAME)
	$(RM) $(INCDIR)/libft.h
	$(RM) $(INCDIR)/ft_printf.h
	$(RM) $(INCDIR)/get_next_line.h
	$(MAKE) -C $(LIBDIR) fclean

re: fclean all

debug: $(HEADERS) $(LIBFTPRINTF) $(OBJS)
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS) $(LDLIBS)

.PHONY: all clean fclean re debug
