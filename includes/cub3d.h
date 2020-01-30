/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/15 15:08:58 by rlucas        #+#    #+#                 */
/*   Updated: 2020/01/30 18:42:32 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define VALID_MAP_CHARS "012NESW "
# define FORWARDSPEED 0.3
# define BACKWARDSPEED 0.25
# define STRAFESPEED 0.2
# define TURNANGLE 5
# define TEXWIDTH 64
# define TEXHEIGHT 64

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

typedef struct		s_imginf
{
	int				bpp;
	int				size_line;
	int				endian;
}					t_imginf;

typedef struct		s_game
{
	t_map			map;
	t_player		player;
	char			*texstrs[5];
	void			*imgs[5];
	t_imginf		*texinf;
}					t_game;

typedef struct		s_display
{
	void			*dpy;
	void			*w;
	void			*img;
	t_imginf		*imginf;
	char			*imga;
}					t_display;

typedef struct		s_keys
{
	int				w;
	int				s;
	int				a;
	int				d;
	int				left;
	int				right;
}					t_keys;

typedef struct		s_all
{
	t_display		*xsrv;
	t_game			*info;
	t_keys			key;
}					t_all;

typedef struct		s_dda
{
	double			rayDirX;
	double			rayDirY;
	double			deltaDistX;
	double			deltaDistY;
	double			sideDistX;
	double			sideDistY;
	double			perpWallDist;
	int				mapX;
	int				mapY;
	int				stepX;
	int				stepY;
	int				hit;
	int				side;
}					t_dda;

typedef struct		s_raytex
{
	double			wallX;
	int				texX;
	int				texY;
	double			step;
	double			texPos;
}					t_raytex;

typedef struct		s_ray
{
	t_dda			dda;
	t_raytex		tx;
	double			planeX;
	double			planeY;
	double			cameraX;
	int				x;
	int				y;
	unsigned int	color;
	int				lineheight;
	int				drawStart;
	int				drawEnd;
}					t_ray;

typedef int			(*t_parsef)(char *line, t_map *mapinfo);
typedef void		(*t_act)(t_all *all);

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
	PURPLE = 13862555,
	CEILING = 2631720,
	FLOOR = 9601908
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
	NO_PLAYER = 13,
	MISSING_TEX = 14,
	INVALID_ARGUMENT = 22,
	BAD_FILETYPE = 79,
	CONNECTION_FAIL = 111
}					t_errors;

typedef enum		e_keydefs
{
	KEY_A = 0,
	KEY_S,
	KEY_D,
	KEY_W = 13,
	KEY_ESC = 53,
	KEY_LEFT = 123,
	KEY_RIGHT,
}					t_keydefs;

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
void		delete_imgs(void *imgs[5]);
int			delete_info(int err, t_map map);
int			delete_all(int err, t_all all);

/*
** DDA functions, in dda.c
*/

void		noray_dda(t_dda *dda, t_game info, int dir);
void		dda_setup(t_dda *dda, t_game info);
void		dda(t_dda *dda, t_game info);
void		dda_movement(t_dda *dda, t_game info, double dist);

/*
** Separate components of the raycasting algorithm, in ray_setup.c.
*/

void		init_plane(t_ray *ray, t_game info);
void		new_ray(t_ray *ray, t_game info);
void		image_setup(t_ray *ray, t_game info);
void		texture_setup(t_ray *ray, t_game info);

/*
** Orchestrator of the raycasting algorithm, and functions to create images,
** in raycasting.c.
*/

void		img_put_pixel(t_display xsrv, int x, int y, unsigned int color);
void		create_image(t_display xsrv, t_game info);
void		ray(t_game info, t_display xsrv); // Waaaay too long

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

void		move_left(t_all *all);
void		move_right(t_all *all);
void		move_forward(t_all *all);
void		move_back(t_all *all);
void		turn_left(t_all *all);
void		turn_right(t_all *all);
void		escape(t_all *all);

// Testing

int			keyrelease(int key, t_all *all);
void		player_actions(t_all *all);

/*
**
*/

#endif
