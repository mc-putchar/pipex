#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/23 14:52:15 by mcutura           #+#    #+#              #
#    Updated: 2023/05/27 00:13:37 by mcutura          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME := pipex
#----- DIRECTORIES -----
SRCDIR := srcs
#OBJDIR := obj
#BINDIR := bin
INCDIR := includes
LIBDIR := lib
#----- ----------- -----
FILES := $(addprefix $(SRCDIR)/, pipex.c ft_getpaths.c)
OBJS := $(FILES:%.c=%.o)
#----- ----------- -----
LIBFTPRINTF := $(LIBDIR)/libftprintf.a
HEADERS := $(addprefix $(INCDIR)/, pipex.h libft.h ft_printf.h)
#----- ----------- -----
CFLAGS := -Wall -Wextra -Werror -I$(INCDIR)
DEBUGFLAGS := -ggdb3 -D DEBUG=1
LDFLAGS := -L$(LIBDIR)
LDLIBS := -lftprintf
#----- ----------- -----

all: $(NAME)

$(NAME): $(HEADERS) $(LIBFTPRINTF) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS) $(LDLIBS) 

$(LIBFTPRINTF):
	$(MAKE) -C $(LIBDIR) all

$(HEADERS):
	cp $(LIBDIR)/ft_printf.h $(INCDIR)/ft_printf.h
	cp $(LIBDIR)/libft/libft.h $(INCDIR)/libft.h

clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(LIBDIR) clean

fclean:
	$(RM) $(OBJS)
	$(RM) $(NAME)
	$(MAKE) -C $(LIBDIR) fclean

re: fclean all

debug: $(HEADERS) $(LIBFTPRINTF) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS) $(LDLIBS) \
	$(DEBUGFLAGS)

.PHONY: all clean fclean re debug
