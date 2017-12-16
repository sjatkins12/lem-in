# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: satkins <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/07/25 14:05:53 by satkins           #+#    #+#              #
#    Updated: 2017/11/30 12:58:59 by satkins          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

LIBFT = libft/ft_atoi.c \
		  libft/ft_bzero.c \
		  libft/ft_isalnum.c \
		  libft/ft_isalpha.c \
		  libft/ft_isascii.c \
		  libft/ft_isdigit.c \
		  libft/ft_isprint.c \
		  libft/ft_memccpy.c \
		  libft/ft_memchr.c \
		  libft/ft_memcmp.c \
		  libft/ft_memcpy.c \
		  libft/ft_memmove.c \
		  libft/ft_memset.c \
		  libft/ft_strcat.c \
		  libft/ft_strchr.c \
		  libft/ft_strcmp.c \
		  libft/ft_strcpy.c \
		  libft/ft_strdup.c \
		  libft/ft_strlcat.c \
		  libft/ft_strlen.c \
		  libft/ft_strncat.c \
		  libft/ft_strncmp.c \
		  libft/ft_strncpy.c \
		  libft/ft_strnstr.c \
		  libft/ft_strrchr.c \
		  libft/ft_strstr.c \
		  libft/ft_tolower.c \
		  libft/ft_toupper.c \
		  libft/ft_memalloc.c \
		  libft/ft_memdel.c \
		  libft/ft_strnew.c \
		  libft/ft_strdel.c \
		  libft/ft_strclr.c \
		  libft/ft_striter.c \
		  libft/ft_striteri.c \
		  libft/ft_strmap.c \
		  libft/ft_strmapi.c \
		  libft/ft_strequ.c \
		  libft/ft_strnequ.c \
		  libft/ft_strsub.c \
		  libft/ft_strjoin.c \
		  libft/ft_strtrim.c \
		  libft/ft_strsplit.c \
		  libft/ft_itoa.c \
		  libft/ft_putchar.c \
		  libft/ft_putstr.c \
		  libft/ft_putendl.c \
		  libft/ft_putnbr.c \
		  libft/ft_putchar_fd.c \
		  libft/ft_putstr_fd.c \
		  libft/ft_putendl_fd.c \
		  libft/ft_putnbr_fd.c  \
		  libft/ft_strnjoin.c \
		  libft/get_next_line.c \
		  libft/ft_putnstr.c \
		  libft/ft_handle_error.c \
		  libft/ft_toupper_str.c \
		  libft/ft_ullitoa_base.c \
		  libft/ft_lstnew.c \
		  libft/ft_lstadd.c \
		  libft/is_numstr.c

PRINTF = libft/printf/ft_printf.c \
		 libft/printf/argument_handlers.c \
		 libft/printf/printer.c \
		 libft/printf/num_format.c \
		 libft/printf/hex_print.c \
		 libft/printf/int_printer.c \
		 libft/printf/uint_printer.c \
		 libft/printf/oct_printer.c \
		 libft/printf/ptr_printer.c \
		 libft/printf/wstr_print.c \
		 libft/printf/wchar_print.c \
		 libft/printf/char_print.c

LEM_IN = src/rooms.c \
		 src/ants.c \
		 src/lem_in.c
		 
SRCS = $(LIBFT) $(PRINTF)

EXE = exe

MAIN = main_tests.c

LIBNAME = libftprintf.a

HEADER = includes

CC = gcc

FLAGS = -Wall -Wextra -Werror

CFLAGS = -Wall -Wextra -Werror -c

TARG = $(SRCS:.c=.o) $(LEM_IN:.c=.o)

LIBTARG = $(SRCS:.c=.o)


all: $(NAME)

$(NAME): $(LIBFT)
	@$(CC) $(CFLAGS) -I$(HEADER) $^ && mv *.o libft/
	@$(CC) $(CFLAGS) -I$(HEADER) $(PRINTF) && mv *.o 'libft/printf/'
	@ar rc $(LIBNAME) $(LIBTARG)
	@$(CC) $(CFLAGS) -I$(HEADER) $(LEM_IN) && mv *.o src/
	@$(CC) $(FLAGS) -I$(HEADER) -o $(NAME) $(LEM_IN) $(LIBNAME)

clean:
	@/bin/rm -f $(TARG)

fclean: clean
	@/bin/rm -f $(NAME) $(LIBNAME)

re: fclean all