# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rlucas <marvin@codam.nl>                     +#+                      #
#                                                    +#+                       #
#    Created: 2020/01/10 18:37:39 by rlucas        #+#    #+#                  #
#    Updated: 2020/02/17 18:22:44 by rlucas        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

LIBFTDIR = libft/

MLXDIR = minilibx_mms_20191207_beta/

MLXLIB = libmlx.dylib

SRCDIR = src/

OBJDIR = obj/

NOBONUS = $(SRCDIR)loop.c \
		  $(SRCDIR)sprite_cast.c

BONUS = $(filter-out $(NOBONUS),$(SRCS)) \
		$(SRCDIR)threads_bonus.c \
		$(SRCDIR)loop_bonus.c \
		$(SRCDIR)sprite_threads_bonus.c \
		$(SRCDIR)sprite_cast_bonus.c

SRCS = $(SRCDIR)main.c \
	   $(SRCDIR)get_info.c \
	   $(SRCDIR)get_info2.c \
	   $(SRCDIR)utils.c \
	   $(SRCDIR)utils2.c \
	   $(SRCDIR)utils3.c \
	   $(SRCDIR)utils4.c \
	   $(SRCDIR)errors.c \
	   $(SRCDIR)open_file.c \
	   $(SRCDIR)parse_cub.c \
	   $(SRCDIR)validation.c \
	   $(SRCDIR)exit.c \
	   $(SRCDIR)raycasting.c \
	   $(SRCDIR)find_player.c \
	   $(SRCDIR)connect.c \
	   $(SRCDIR)actions1.c \
	   $(SRCDIR)actions2.c \
	   $(SRCDIR)cast.c \
	   $(SRCDIR)math1.c \
	   $(SRCDIR)draw_images.c \
	   $(SRCDIR)textures.c \
	   $(SRCDIR)hooks1.c \
	   $(SRCDIR)hooks2.c \
	   $(SRCDIR)loop.c \
	   $(SRCDIR)flood_fill.c \
	   $(SRCDIR)bmpsave.c \
	   $(SRCDIR)f_c_tex.c \
	   $(SRCDIR)sprite_setup.c \
	   $(SRCDIR)sprite_cast.c

ALLSRC = $(SRCS)$(BONUS)

ifdef WITH_BONUS
	OBJ = $(patsubst $(SRCDIR)%.c,$(OBJDIR)%.o,$(BONUS))
else
	OBJ = $(patsubst $(SRCDIR)%.c,$(OBJDIR)%.o,$(SRCS))
endif


INCLUDES = -Iincludes/ -I$(LIBFTDIR)includes/ -I$(MLXDIR)

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	@echo  "Compiling Program..."
	@gcc -O3 $(FLAGS) -o $(NAME) $(INCLUDES) \
		-lmlx -L$(LIBFTDIR) -lft $(OBJ)

bonus:
	$(MAKE) WITH_BONUS=1 all

$(MLXDIR)$(MLXLIB):
	@echo "Compiling libft.a..."
	@$(MAKE) -C $(LIBFTDIR)
	@echo "Compiling libmlx.dylib..."
	@$(MAKE) -C $(MLXDIR)
	@cp $(MLXDIR)libmlx.dylib .

$(OBJDIR)%.o: $(SRCDIR)%.c $(MLXDIR)$(MLXLIB)
	@echo "Compiling $@"
	@gcc -O3 -c $(FLAGS) $(INCLUDES) -o $@ $<

clean:
	@echo "Removing objects in all directories..."
	@$(MAKE) -C $(LIBFTDIR) clean
	@rm -f $(ALLOBJ)

fclean: clean
	@echo "Removing program and libraries in all directories..."
	@$(MAKE) -C $(LIBFTDIR) fclean
	@$(MAKE) -C $(MLXDIR) clean
	@rm -f libmlx.dylib
	@rm -f $(NAME)

re: fclean all


.PHONY: clean fclean all re bonus
