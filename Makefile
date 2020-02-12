# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rlucas <marvin@codam.nl>                     +#+                      #
#                                                    +#+                       #
#    Created: 2020/01/10 18:37:39 by rlucas        #+#    #+#                  #
#    Updated: 2020/02/12 14:53:49 by rlucas        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

LIBFTDIR = libft/

MLXDIR = minilibx_mms_20191207_beta/

SRCS = main.c \
	   get_info.c \
	   get_info2.c \
	   utils.c \
	   utils2.c \
	   utils3.c \
	   errors.c \
	   open_file.c \
	   parse_cub.c \
	   validation.c \
	   exit.c \
	   raycasting.c \
	   find_player.c \
	   connect.c \
	   actions1.c \
	   actions2.c \
	   cast.c \
	   math1.c \
	   draw_images.c \
	   textures.c \
	   hooks1.c \
	   hooks2.c \
	   loop.c \
	   sprite_cast.c \
	   flood_fill.c \
	   bmpsave.c \
	   f_c_tex.c

OBJ = $(SRCS:.c=.o)

INCLUDES = -Iincludes/ -I$(LIBFTDIR)includes/ -I$(MLXDIR)

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): makelibraries
	@echo  "Compiling Program..."
	@gcc -g $(FLAGS) -o $(NAME) $(INCLUDES) \
		-Wl,-rpath,$(MLXDIR) -lmlx -L$(LIBFTDIR) -lft $(SRCS)

bonus: all

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

fclean: clean
	@echo "Removing program and libraries in all directories..."
	@$(MAKE) -C $(LIBFTDIR) fclean
	@$(MAKE) -C $(MLXDIR) clean
	@rm -f libmlx.dylib
	@rm -f $(NAME)

re: fclean all


.PHONY: clean fclean all re makelibraries makeobjects bonus
