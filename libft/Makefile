# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rlucas <marvin@codam.nl>                     +#+                      #
#                                                    +#+                       #
#    Created: 2019/10/28 15:06:46 by rlucas        #+#    #+#                  #
#    Updated: 2019/12/01 11:43:18 by rlucas        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_isalpha.c ft_memset.c ft_bzero.c \
	   ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c \
	   ft_memcmp.c ft_strlen.c ft_strlcpy.c ft_strlcat.c \
	   ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strncmp.c \
	   ft_atoi.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
	   ft_isprint.c ft_toupper.c ft_tolower.c ft_calloc.c \
	   ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c \
	   ft_split.c ft_itoa.c ft_strmapi.c ft_putchar_fd.c \
	   ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	   ft_strclen.c # all following files were added after libft completion 
	   

BSRC = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
	   ft_lstlast_bonus.c ft_lstadd_back_bonus.c \
	   ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c \
	   ft_lstmap_bonus.c

OBJ = $(SRCS:.c=.o)

BOBJ = $(BSRC:.c=.o)

PRINTFDIR = ft_printf/

PRINTFOBJ = $(PRINTFDIR)ft_printf.o \
			$(PRINTFDIR)ft_ltoa.o \
			$(PRINTFDIR)ft_ptrtohex.o \
			$(PRINTFDIR)make_string.o \
			$(PRINTFDIR)parsing.o \
			$(PRINTFDIR)utils1.o \
			$(PRINTFDIR)utils2.o \
			$(PRINTFDIR)processing.o \
			$(PRINTFDIR)int_strings.o \
			$(PRINTFDIR)char_strings.o \
			$(PRINTFDIR)output.o \
			$(PRINTFDIR)lltoa.o \
			$(PRINTFDIR)ulltoa.o \
			$(PRINTFDIR)ulltox.o \
			$(PRINTFDIR)crazy_strings.o \
			$(PRINTFDIR)hexprocessing.o \
			$(PRINTFDIR)processing2.o \
			$(PRINTFDIR)ft_putnbr_fd_and_count.o

GNLDIR = get_next_line/

GNLSRC = $(GNLDIR)get_next_line.c

GNLOBJ = get_next_line.o

ifdef WITH_BONUS
	OBJ_FILES = $(OBJ) $(BOBJ) $(PRINTFOBJ) $(GNLOBJ)
	SRC_FILES = $(SRCS) $(BSRC) $(GNLSRC)
else
	OBJ_FILES = $(OBJ)
	SRC_FILES = $(SRCS)
endif

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ_FILES)
	ar -rc $(NAME) $(OBJ_FILES)

$(OBJ_FILES):
	gcc -c $(FLAGS) -I. $(SRC_FILES)

printf:
	@$(MAKE) -C $(PRINTFDIR)

bonus: printf
	@$(MAKE) WITH_BONUS=1 all

clean:
	rm -f $(OBJ) $(BOBJ) $(GNLOBJ)

fclean: clean
	@$(MAKE) -C $(PRINTFDIR) clean
	rm -f $(NAME)

re: fclean all

.PHONY = all clean fclean re bonus
