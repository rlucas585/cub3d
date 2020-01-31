/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/15 15:08:58 by rlucas        #+#    #+#                 */
/*   Updated: 2020/01/31 21:02:03 by rlucas        ########   odam.nl         */
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

typedef struct		s_2i
{
	int				x;
	int				y;
}					t_2i;

typedef struct		s_2d
{
	double			x;
	double			y;
}					t_2d;

typedef struct		s_imginf
{
	int				bpp;
	int				size_line;
	int				endian;
}					t_imginf;

typedef struct		s_info
{
	char			**map;
	t_2i			res;
	char			*texs[5];
	int				floor;
	int				ceiling;
	int				spritenum;
	t_2d			pos;
	double			dir;
	int				*texstrs[5];
	void			*imgs[5];
	t_imginf		*texinf;
}					t_info;

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

typedef struct		s_cub
{
	t_display		xsrv;
	t_info			info;
	t_keys			key;
}					t_cub;

typedef struct		s_floor
{
	double			weight;
	t_2d			wall;
	t_2d			pos;
	t_2i			tx;
}					t_floor;

typedef struct		s_ray
{
	t_2d			plane;
	t_2d			beam;
	t_2i			map;
	double			camx;
	t_2d			delt;
	t_2i			step;
	t_2d			sidedist;
	int				side;
	double			pdist;
	int				hit;
	int				height;
	int				draw_start;
	int				draw_end;
	double			wallx;
	t_2i			tx;
	double			txstep;
	double			tex_pos;
}					t_ray;

typedef int			(*t_parsef)(char *line, t_info *info);

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

int					check_file(const char *str);
int					open_file(int argc, char **argv);

/*
** Color function, converts from 8-bit integers into a single 32-bit integer
** containing the information from three 8-bit integers. In color.c.
*/

int					rgb(int red, int green, int blue);

/*
** Error messaging, in errors.c.
*/

int					ft_error(int err, int linenum);

/*
** Check that the map is valid, both during creation and after completion.
** Located in validation.c.
*/

int					validate_map(char *line, size_t width);
void				validate_n_s_walls(t_info info);

/*
** Function to find and create the player on the map. In find_player.c.
*/

void				find_player(t_info *info);

/*
** Functions to read info from a line into relevant mapinfo, in get_info.c.
*/

int					get_resolution(char *line, t_info *info);
int					get_texture(char *line, t_info *info);
int					get_color(char *line, t_info *info);

/*
** Utility functions in utils.c.
*/

char				*make_row(char *line);
char				**row_ptrs(char *newrow, t_info info);
size_t				ft_arrlen(char **array);
int					numstrchr(char *str, int c);

/*
** Utility functions in utils2.c.
*/

void				count_sprites(t_info *info);
void				bump(double *x, double *y, char **map);

/*
** Troubleshooting functions that should be deleted, in utils.c.
*/

void				print_mapinfo(t_info info);
void				print_playerinfo(t_info info);
void				print_gameinfo(t_info info);

/*
** Functions to direct parsing of .cub file, in parse_cub.c.
*/

t_parsef			route_parsing(char c);
void				parse_map(int fd, char *line, int linenum, t_info *info);
int					parse_line(int fd, char *line, t_info *info, int linenum);
t_info				cub_parser(int fd);

/*
** Functions to delete malloced data when exiting the program. In exit.c.
*/

void				delete_map(char **map);
void				delete_tex(char *textures[5]);
void				delete_imgs(void *imgs[5]);
int					delete_info(int err, t_info info);
int					delete_all(int err, t_cub cub);

/*
** DDA function, in raycasting.c
*/

void				dda(t_info info, t_ray *ray);

/*
** Orchestrator of the raycasting algorithm, and functions to create images,
** in raycasting.c.
*/

void				img_put_pixel(t_display xsrv, int x, int y,
		unsigned int color);
void				create_image(t_cub *cub);
void				ray(t_cub *cub);

/*
** Casting functions to fill in an image.
*/

void				wallcast(t_cub *cub, t_ray *ray, int x);
void				floorcast_setup(t_info info, t_ray *ray, t_2d *wall_pos);
void				floorcast(t_cub *cub, t_ray *ray, int x);

/*
** Function to establish connection with Xserver, initialize a window and
** image. In connect.c.
*/

void				establish_connection(t_cub *cub);

/*
** Initialise textures, in textures.c.
*/

void				init_tex(t_cub *cub);

/*
** Small math functions, not super necessary.
*/

double				to_degrees(double radians);
double				to_radians(double degrees);

/*
** Movement functions, in actions1.c
*/

void				move(t_info *info, double dist, int dir);
void				move_left(t_cub *cub);
void				move_right(t_cub *cub);
void				move_forward(t_cub *cub);
void				move_back(t_cub *cub);

/*
** Movement functions, in actions2.c
*/

void				turn_left(t_cub *cub);
void				turn_right(t_cub *cub);
void				escape(t_cub *cub);
void				player_actions(t_cub *cub);

/*
** Hook functions, in hooks*.c.
*/

void				toggle(int key, t_cub *cub, int on_off);
int					keypress(int key, t_cub *cub);
int					keyrelease(int key, t_cub *cub);
int					crosspress(t_cub *cub);
int					loop_func(t_cub *cub);
void				init_keys(t_cub *cub);
void				init_hooks(t_cub *cub);

#endif
