# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rlucas <marvin@codam.nl>                     +#+                      #
#                                                    +#+                       #
#    Created: 2019/10/28 15:06:46 by rlucas        #+#    #+#                  #
#    Updated: 2020/01/15 12:49:04 by rlucas        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

PRINTFDIR = ft_printf/

GNLDIR = get_next_line/

SRCS = ft_isalpha.c ft_memset.c ft_bzero.c \
	   ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c \
	   ft_memcmp.c ft_strlen.c ft_strlcpy.c ft_strlcat.c \
	   ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strncmp.c \
	   ft_atoi.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
	   ft_isprint.c ft_toupper.c ft_tolower.c ft_calloc.c \
	   ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c \
	   ft_split.c ft_itoa.c ft_strmapi.c ft_putchar_fd.c \
	   ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	   ft_strclen.c \
	   ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
	   ft_lstlast_bonus.c ft_lstadd_back_bonus.c \
	   ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c \
	   ft_lstmap_bonus.c \
	   $(PRINTFDIR)ft_printf.c \
	   $(PRINTFDIR)ft_ltoa.c \
	   $(PRINTFDIR)ft_ptrtohex.c \
	   $(PRINTFDIR)make_string.c \
	   $(PRINTFDIR)parsing.c \
	   $(PRINTFDIR)utils1.c \
	   $(PRINTFDIR)utils2.c \
	   $(PRINTFDIR)processing.c \
	   $(PRINTFDIR)int_strings.c \
	   $(PRINTFDIR)char_strings.c \
	   $(PRINTFDIR)output.c \
	   $(PRINTFDIR)lltoa.c \
	   $(PRINTFDIR)ulltoa.c \
	   $(PRINTFDIR)ulltox.c \
	   $(PRINTFDIR)crazy_strings.c \
	   $(PRINTFDIR)hexprocessing.c \
	   $(PRINTFDIR)processing2.c \
	   $(PRINTFDIR)ft_putnbr_fd_and_count.c \
	   $(GNLDIR)get_next_line.c

OBJ = $(notdir $(SRCS:.c=.o))

INCLUDES= -Iincludes/

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Compiling libft.a..."
	@ar -rc $(NAME) $(OBJ)

$(OBJ):
	@echo "Compiling objects..."
	@gcc -c $(FLAGS) $(INCLUDES) $(SRCS)

clean:
	@echo "Removing objects..."
	@rm -f $(OBJ)

fclean: clean
	@echo "Removing libft.a..."
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
