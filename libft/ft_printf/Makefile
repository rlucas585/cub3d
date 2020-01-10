# **************************************************************************** #
                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rlucas <marvin@codam.nl>                     +#+                      #
#                                                    +#+                       #
#    Created: 2019/11/04 13:23:58 by rlucas        #+#    #+#                  #
#    Updated: 2019/12/01 10:29:17 by rlucas        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

LIBDIR = libft/

SRC = ft_ltoa.c \
	  ft_ptrtohex.c \
	  make_string.c \
	  parsing.c \
	  utils1.c \
	  utils2.c \
	  processing.c \
	  int_strings.c \
	  char_strings.c \
	  ft_printf.c \
	  output.c \
	  lltoa.c \
	  ulltoa.c \
	  ulltox.c \
	  crazy_strings.c \
	  hexprocessing.c \
	  processing2.c \
	  ft_putnbr_fd_and_count.c

LIBSRCS =	$(LIBDIR)ft_bzero.c \
			$(LIBDIR)ft_calloc.c \
			$(LIBDIR)ft_memset.c \
			$(LIBDIR)ft_itoa.c \
			$(LIBDIR)ft_strlcpy.c \
			$(LIBDIR)ft_strlen.c \
			$(LIBDIR)ft_strnstr.c \
			$(LIBDIR)ft_isalpha.c \
			$(LIBDIR)ft_putchar_fd.c \
			$(LIBDIR)ft_putstr_fd.c \
			$(LIBDIR)ft_strdup.c \
			$(LIBDIR)ft_strlcat.c \
			$(LIBDIR)ft_atoi.c

OBJ = $(SRC:.c=.o)

LIBOBJ = $(LIBSRCS:.c=.o)

INCLUDES = -I includes/

FLAGS = -Wall -Wextra -Werror

all: $(OBJ)

$(NAME): $(OBJ)
	@echo "Compiling libft.a ..."
	@make -C $(LIBDIR)
	@echo "Compiling libftprintf.a ..."
	@ar -rc $(NAME) $(OBJ) $(LIBOBJ)

$(OBJ): $(SRC)
	@echo "Compiling objects from new source files"
	@$(CC) -c $(FLAGS) $(SRC) $(INCLUDES)

clean:
	@echo "Removing objects"
	@make -C $(LIBDIR) clean
	@rm -f $(OBJ) $(OLDOBJ)

fclean: clean
	@echo "Removing library"
	@make -C $(LIBDIR) fclean
	@rm -f $(NAME)

re: fclean all
