# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rlucas <marvin@codam.nl>                     +#+                      #
#                                                    +#+                       #
#    Created: 2020/01/10 18:37:39 by rlucas        #+#    #+#                  #
#    Updated: 2020/02/24 11:01:21 by rlucas        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

LIBFTDIR = libft/

SHELL := /bin/bash		# Allows bash syntax

MLXDIR = minilibx_mms_20191207_beta/

MLXLIB = libmlx.dylib

SRCDIR = src/

OBJDIR = obj/

MLX_C_DIR = minilibx/

NOBONUS = $(SRCDIR)loop.c \
		  $(SRCDIR)sprite_cast.c

BONUS = $(SRCDIR)thread_ray_bonus.c \
		$(SRCDIR)loop_bonus.c \
		$(SRCDIR)sprite_threads_bonus.c \
		$(SRCDIR)sprite_threads_2_bonus.c \
		$(SRCDIR)sprite_cast_bonus.c \

BONUS_AND_SRC = $(filter-out $(NOBONUS),$(SRCS)) \
				$(SRCDIR)thread_ray_bonus.c \
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

ALLSRC = $(NOBONUS) $(BONUS_AND_SRC)

ALLOBJ = $(patsubst $(SRCDIR)%.c,$(OBJDIR)%.o,$(ALLSRC))

WITH_BONUS = 0

NO_SWIFT = 0

ifeq ($(WITH_BONUS), 1)
	OBJ = $(patsubst $(SRCDIR)%.c,$(OBJDIR)%.o,$(BONUS_AND_SRC))
else
	OBJ = $(patsubst $(SRCDIR)%.c,$(OBJDIR)%.o,$(SRCS))
endif


ifeq ($(NO_SWIFT), 1)
	INCLUDES = -Iincludes/ -I$(LIBFTDIR)includes/ -I$(MLX_C_DIR)
	DEFINES += -D LINUX=1
else
	INCLUDES = -Iincludes/ -I$(LIBFTDIR)includes/ -I$(MLXDIR)
endif

FLAGS = -Wall -Wextra -Werror -g -O3

all: bonus_convert $(NAME)

$(NAME): $(OBJ)
	@echo  "Compiling Program..."
	@gcc $(FLAGS) $(OBJ) -o $(NAME) $(DEFINES) $(INCLUDES) \
		-L$(MLXDIR) -lmlx -L$(LIBFTDIR) -lft

bonus_convert:
	@if [[ "$(WITH_BONUS)" == 1 ]]; then\
		rm -f $(patsubst $(SRCDIR)%.c,$(OBJDIR)%.o,$(NOBONUS)); \
		fi
	@if [[ "$(WITH_BONUS)" == 0 ]]; then\
		rm -f $(patsubst $(SRCDIR)%.c,$(OBJDIR)%.o,$(BONUS)); \
		fi

bonus:
	@$(MAKE) WITH_BONUS=1 all

noswift:
	@$(MAKE) WITH_BONUS=1 NO_SWIFT=1 noswift2

noswift2: bonus_convert $(OBJ)
	@echo "Compiling Program with C MiniLibX..."
	@gcc $(FLAGS) -o $(NAME) $(OBJ) $(DEFINES) $(INCLUDES) \
		-L$(MLX_C_DIR) -lmlx_x86_64 -L$(LIBFTDIR) -lft -lm -pthread -lX11 \
		-lz -lXext

make_libraries:
ifeq ($(NO_SWIFT),0)
	@echo "Compiling libft.a..."
	@$(MAKE) -C $(LIBFTDIR)
	@echo "Compiling libmlx.dylib..."
	@$(MAKE) -C $(MLXDIR)
	@cp $(MLXDIR)libmlx.dylib .
else
	@echo "Compiling libft.a..."
	@$(MAKE) -C $(LIBFTDIR)
	@echo "Compiling libmlx.a"
	@$(MAKE) -C $(MLX_C_DIR)
endif

$(OBJDIR)%.o: $(SRCDIR)%.c make_libraries
	@echo "Compiling $@"
	@gcc -c $(FLAGS) -o $@ $<  $(INCLUDES) $(DEFINES)

clean:
	@echo "Removing objects in all directories..."
	@$(MAKE) -C $(LIBFTDIR) clean
	@rm -f $(ALLOBJ)

fclean: clean
	@echo "Removing program and libraries in all directories..."
	@$(MAKE) -C $(LIBFTDIR) fclean
	@$(MAKE) -C $(MLXDIR) clean
	@$(MAKE) -C $(MLX_C_DIR) clean
	@rm -f libmlx.dylib
	@rm -f $(NAME)

re: fclean all


.PHONY: clean fclean all re bonus bonus_convert make_libraries
