# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rlucas <marvin@codam.nl>                     +#+                      #
#                                                    +#+                       #
#    Created: 2020/01/10 18:37:39 by rlucas        #+#    #+#                  #
#    Updated: 2020/01/22 16:56:12 by rlucas        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

LIBFTDIR = libft/

MLXDIR = minilibx_mms_20191207_beta/

SRCS = main2.c \
	   color.c \
	   get_info.c \
	   utils.c \
	   errors.c \
	   open_file.c \
	   parse_cub.c \
	   validation.c \
	   exit.c \
	   raycasting.c \
	   find_player.c \
	   connect.c \
	   actions1.c

OBJ = $(SRCS:.c=.o)

INCLUDES = -Iincludes/ -I$(LIBFTDIR)includes/ -I$(MLXDIR)

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): makeobjects
	@echo  "Compiling Program..."
	@gcc $(FLAGS) -o $(NAME) $(INCLUDES) \
		-Wl,-rpath,$(MLXDIR) -lmlx -L$(LIBFTDIR) -lft $(OBJ)

makelibraries:
	@echo "Compiling libft.a..."
	@$(MAKE) -C $(LIBFTDIR)
	@echo "Compiling libmlx.dylib..."
	@$(MAKE) -C $(MLXDIR)
	@cp $(MLXDIR)libmlx.dylib .

makeobjects: makelibraries
	@echo "Compiling object files..."
	@gcc -c $(FLAGS) $(INCLUDES) $(SRCS)

clean:
	@echo "Removing objects in all directories..."
	@$(MAKE) -C $(LIBFTDIR) clean
	@rm -f $(OBJ)

test: makeobjects
	@echo "Compiling test program"
	@gcc $(FLAGS) -g -o $(NAME) $(INCLUDES) \
		-Wl,-rpath,$(MLXDIR) -lmlx -L$(LIBFTDIR) -lft main3.c

fclean: clean
	@echo "Removing program and libraries in all directories..."
	@$(MAKE) -C $(LIBFTDIR) fclean
	@$(MAKE) -C $(MLXDIR) clean
	@rm -f libmlx.dylib
	@rm -f $(NAME)

re: fclean all


.PHONY: clean fclean all re makelibraries makeobjects
