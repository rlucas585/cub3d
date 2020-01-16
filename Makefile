# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rlucas <marvin@codam.nl>                     +#+                      #
#                                                    +#+                       #
#    Created: 2020/01/10 18:37:39 by rlucas        #+#    #+#                  #
#    Updated: 2020/01/16 17:48:41 by rlucas        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

LIBFTDIR = libft/

MLXDIR = minilibx_mms_20191207_beta/

SRCS = main2.c color.c get_info.c

OBJ = $(SRCS:.c=.o)

INCLUDES = -Iincludes/ -I$(LIBFTDIR)includes/ -I$(MLXDIR)

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	@echo  "Compiling Program..."
	@gcc $(FLAGS) -o $(NAME) $(INCLUDES) \
		-Wl,-rpath,$(MLXDIR) -lmlx -L$(LIBFTDIR) -lft $(OBJ)

makelibraries:
	@echo "Compiling libft.a..."
	@$(MAKE) -C $(LIBFTDIR)
	@echo "Compiling libmlx.dylib..."
	@$(MAKE) -C $(MLXDIR)
	@cp $(MLXDIR)libmlx.dylib .

$(OBJ): makelibraries
	@echo "Compiling object files..."
	@echo "${CFLAGS}"
	@gcc -c $(FLAGS) $(INCLUDES) $(SRCS)

clean:
	@echo "Removing objects in all directories..."
	@$(MAKE) -C $(LIBFTDIR) clean
	@rm -f $(OBJ)

fclean: clean
	@echo "Removing program and libraries in all directories..."
	@$(MAKE) -C $(LIBFTDIR) fclean
	@$(MAKE) -C $(MLXDIR) clean
	@rm -f libmlx.dylib
	@rm -f $(NAME)

re: fclean all


.PHONY: clean fclean all re
