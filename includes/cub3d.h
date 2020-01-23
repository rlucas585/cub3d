/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/15 15:08:58 by rlucas        #+#    #+#                 */
/*   Updated: 2020/01/23 12:05:49 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define VALID_MAP_CHARS "012NESW "

# include <stdlib.h>

typedef struct		s_map
{
	char			**coords;
	int				res[2];
	char			*textures[5];
	int				floorcolor;
	int				ceilingcolor;
}					t_map;

typedef struct		s_player
{
	double			location[2];
	double			dir;
}					t_player;

typedef struct		s_game
{
	t_map			map;
	t_player		player;
}					t_game;

typedef struct		s_imginf
{
	int				bpp;
	int				size_line;
	int				endian;
}					t_imginf;

typedef struct		s_display
{
	void			*dpy;
	void			*w;
	void			*img;
	t_imginf		*imginf;
	char			*imga;
}					t_display;

typedef struct		s_all
{
	t_display		*xsrv;
	t_game			*info;
}					t_all;

typedef int			(*t_parsef)(char *line, t_map *mapinfo);
typedef void		(*t_act)(t_game *info, t_display *xsrv);

typedef enum		e_coords
{
	Y = 0,
	X
}					t_coords;

typedef enum		e_textures
{
	NORTH = 0,
	EAST = 1,
	SOUTH = 2,
	WEST = 3,
	SPRITE = 4
}					t_textures;

typedef enum		e_colors
{
	RED = 16468276,
	GREEN = 12106534,
	BLUE = 8627608,
	PURPLE = 13862555
}					t_colors;

typedef enum		e_errors
{
	ERROR = -1,
	BAD_FORMAT = 1,
	INVALID_FILE = 2,
	N_S_WALL_ERROR = 3,
	TOO_SHORT = 4,
	TOO_THIN = 5,
	DUP_PLAYERS = 6,
	MORE_ARG = 7,
	MEM_FAIL = 12,
	INVALID_ARGUMENT = 22,
	BAD_FILETYPE = 79,
	CONNECTION_FAIL = 111
}					t_errors;

typedef enum		e_keys
{
	KEY_A = 0,
	KEY_S,
	KEY_D,
	KEY_W = 13,
	KEY_ESC = 53,
	KEY_LEFT = 123,
	KEY_RIGHT,
}					t_keys;

/*
** Opening file functions, and checking argument errors. In open_file.c.
*/

int			check_file(const char *str);
int			open_file(int argc, char **argv);

/*
** Color function, converts from 8-bit integers into a single 32-bit integer
** containing the information from three 8-bit integers. In color.c.
*/

int			rgb(int red, int green, int blue);

/*
** Error messaging, in errors.c.
*/

int			ft_error(int err, int linenum);

/*
** Check that the map is valid, both during creation and after completion.
** Located in validation.c.
*/

int			validate_map(char *line, size_t width);
void		validate_n_s_walls(t_map mapinfo);

/*
** Function to find and create the player on the map. In find_player.c.
*/

t_player	find_player(t_game game);

/* 
** Functions to read info from a line into relevant mapinfo, in get_info.c.
*/

int			get_resolution(char *line, t_map *mapinfo);
int			get_texture(char *line, t_map *mapinfo);
int			get_color(char *line, t_map *mapinfo);

/*
** Utility functions in utils.c
*/

char		*make_row(char *line);
char		**row_ptrs(char *newrow, t_map map);
size_t		ft_arrlen(char **array);

/*
** Troubleshooting functions that should be deleted, in utils.c.
*/

void		print_mapinfo(t_map mapinfo);
void		print_playerinfo(t_player player);
void		print_gameinfo(t_game game);

/*
** Functions to direct parsing of .cub file, in parse_cub.c.
*/

t_parsef	route_parsing(char c);
void		parse_map(int fd, char *line, int linenum, t_map *map);
int			parse_line(int fd, char *line, t_map *mapinfo, int linenum);
t_map		cub_parser(int fd);

/*
** Functions to delete malloced data when exiting the program. In exit.c.
*/

void		delete_map(char **map);
void		delete_tex(char *textures[5]);
int			delete_info(int err, t_map map);

/*
** Raycasting algorithm and writing, in raycasting.c
*/

void		ray(t_game info, t_display xsrv); // Waaaay too long
void		verLine(int x, int start, int end, int color, t_display xsrv, t_game info);
void		img_put_pixel(t_display xsrv, int x, int y, unsigned int color);
void		create_image(t_display xsrv, t_game info);

/*
** Function to establish connection with Xserver, initialize a window and
** image. In connect.c.
*/

t_display	establish_connection(t_game info);

/*
** Small math functions, not super necessary.
*/

double		to_degrees(double radians);
double		to_radians(double degrees);

/*
** Movement functions, in actions1.c
*/

void		move_left(t_game *info, t_display *xsrv);
void		move_right(t_game *info, t_display *xsrv);
void		move_forward(t_game *info, t_display *xsrv);
void		move_back(t_game *info, t_display *xsrv);
void		turn_left(t_game *info, t_display *xsrv);
void		turn_right(t_game *info, t_display *xsrv);
void		escape(t_game *info, t_display *xsrv);

/*
**
*/

#endif
