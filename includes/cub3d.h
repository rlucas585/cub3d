/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/14 15:43:26 by rlucas        #+#    #+#                 */
/*   Updated: 2020/02/14 15:43:31 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/15 15:08:58 by rlucas        #+#    #+#                 */
/*   Updated: 2020/02/14 15:37:36 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define VALID_MAP_CHARS "012NESW "
# define FORWARDSPEED 0.3
# define BACKWARDSPEED 0.25
# define STRAFESPEED 0.2
# define TURNANGLE 5

# include <stdlib.h>

typedef struct		s_rgb
{
	unsigned char	b;
	unsigned char	g;
	unsigned char	r;
	unsigned char	a;
}					t_rgb;

typedef union		u_color
{
	t_rgb			rgb;
	unsigned int	x;
}					t_color;

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

typedef	struct		s_wh
{
	int				width;
	int				height;
}					t_wh;

typedef struct		s_sprite
{
	t_2d			pos;
	int				type;
}					t_sprite;

typedef struct		s_sray
{
	int				*sprite_order;
	double			*sprite_dist;
	t_2d			spos;
	double			inv_det;
	t_2d			transform;
	int				sscreenx;
	t_wh			sprt;
	t_2i			draw_start;
	t_2i			draw_end;
	t_2i			tx;
	unsigned int	color;
}					t_sray;

typedef struct		s_imginf
{
	int				bpp;
	int				size_line;
	int				endian;
	t_2i			size;
}					t_imginf;

typedef struct		s_info
{
	char			**map;
	t_2i			res;
	char			*texs[7];
	t_2i			f_or_c;
	t_color			floor;
	t_color			ceiling;
	int				spritenum;
	t_2d			pos;
	double			dir;
	char			*texstrs[7];
	void			*imgs[7];
	t_sprite		*sprts;
	t_imginf		*texinf[7];
	double			*z_buffer;
}					t_info;

typedef struct		s_display
{
	void			*dpy;
	void			*w;
	void			*img;
	void			*img2;
	t_imginf		*imginf;
	char			*imga;
	char			*imga2;
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
	int				save;
	int				imgswap;
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
	SPRITE = 4,
	FLOOR = 5,
	CEILING = 6
}					t_textures;

typedef enum		e_errors
{
	ERROR = -1,
	BAD_FORMAT = 1,
	INVALID_FILE = 2,
	NOT_CONTAINED = 3,
	TOO_SHORT = 4,
	DUP_PLAYERS = 6,
	MORE_ARG = 7,
	NO_MAP = 8,
	MEM_FAIL = 12,
	NO_PLAYER = 13,
	MISSING_TEX = 14,
	MISSING_PARAM = 15,
	DUP_PARAM = 16,
	BMP_FAIL = 17,
	INVALID_ARGUMENT = 22,
	BIG_MAP = 23,
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
*******************************Opening File************************************
*/

/*
** Opening file functions, and checking argument errors. In open_file.c.
*/

int					check_file(const char *str);
int					open_file(int argc, char **argv, t_cub *cub);

/*
**********************Parse lines of .cub file and store info******************
*/

/*
** Functions to direct parsing of .cub file, in parse_cub.c.
*/

t_parsef			route_parsing(char c);
void				parse_map(int fd, char *line, int linenum, t_info *info);
int					parse_line(int fd, char *line, t_info *info, int linenum);
t_info				cub_parser(int fd);

/*
** Functions to read info from a line into relevant info structure, in
** get_info.c.
*/

int					get_resolution(char *line, t_info *info);
int					get_texture(char *line, t_info *info);
int					get_floor_ceiling(char *line, t_info *info);

/*
** More functions to read info from relevant .cub file, in get_info2.c.
*/

int					get_color(char *line, t_info *info);

/*
** Function to find and create the player on the map. In find_player.c.
*/

void				find_player(t_info *info);

/*
** Initialise textures, in textures.c.
*/

void				init_tex(t_cub *cub);

/*
**********************Error messaging and freeing memory***********************
*/

/*
** Error messaging, in errors.c.
*/

int					ft_error(int err, int linenum);

/*
** Functions to delete malloced data when exiting the program. In exit.c.
*/

void				delete_map(char **map);
void				delete_tex(char *textures[7]);
void				delete_imgs(t_cub cub, void *imgs[7]);
int					delete_info(int err, t_info info);
int					delete_all(int err, t_cub cub);

/*
*******************************Map validation**********************************
*/

/*
** Check that the map is valid, both during creation and after completion.
** Located in validation.c.
*/

int					only_chars_in_set(char *str, char *validchars);
int					validate_map1(char *line);
void				validate(t_info info);

/*
** Flood_fill algorithm function, found in flood_fill.c
*/

int					validate_map2(t_info info);

/*
***********************Raycasting and Drawing in image*************************
*/

/*
** Functions to draw with. In draw_images.c
*/

void				put_sprite_pixel(t_cub *cub, int y, int stripe,
		t_sray *sray);
void				img_put_pixel(t_cub cub, int x, int y, unsigned int color);

/*
** Orchestrator of the raycasting algorithm, and functions to create images,
** in raycasting.c.
*/

void				ray(t_cub *cub);

/*
** Casting functions to fill in an image. In cast.c.
*/

void				wallcast(t_cub *cub, t_ray *ray, int x);
void				floorcast_setup(t_info info, t_ray *ray, t_2d *wall_pos);
void				floorcast(t_cub *cub, t_ray *ray, int x);

/*
** Filling in textured ceiling and floor, used in floorcasting. Found in
** f_c_tex.c.
*/

unsigned int		init_tex_pos(t_floor *fc, t_cub *cub, int side);
void				tex_c_and_f(t_cub *cub, t_ray *ray, int x);
void				tex_c(t_cub *cub, t_ray *ray, int x);
void				tex_f(t_cub *cub, t_ray *ray, int x);
void				no_tex(t_cub *cub, t_ray *ray, int x);

/*
** Casting sprites, int sprite_cast.c
*/

void				draw_sprites(t_cub *cub, double *z_buffer, t_2d plane);

/*
**********************Connection to XServer functions**************************
*/

/*
** Function to establish connection with Xserver, initialize a window and
** image. In connect.c.
*/

void				establish_connection(t_cub *cub);

/*
**************************Program management***********************************
*/

/*
** Bitmap function, to save a bitmap of the initial image if the '--save'
** argument is supplied.
*/

void				save_init_img(t_cub cub);

/*
** Looping function of the program. In loop.c
*/

void				create_image(t_cub *cub);
int					loop_func(t_cub *cub);

/*
** Hook functions, in hooks1.c and hooks2.c.
*/

void				toggle(int key, t_cub *cub, int on_off);
int					keypress(int key, t_cub *cub);
int					keyrelease(int key, t_cub *cub);
int					crosspress(t_cub *cub);
void				init_keys(t_cub *cub);
void				init_hooks(t_cub *cub);

/*
**************************Player action functions******************************
*/

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
****************************Utility Functions**********************************
*/

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

void				int_swap(int *a, int *b);
void				double_swap(double *a, double *b);
void				init_sprites(t_info *info);
void				bump(double *x, double *y, char **map);

/*
** Utility functions in utils3.c.
*/

void				sortsprites(int number, int **order, double **dist);
int					close_file(int fd, int errno);
int					travel_to_char(char *line, char *stopatchars);
int					travel_through_char(char *line, char *movethroughchars);
void				free_exit(int fd, char *line, t_info *info, int linenum);

/*
** Small math functions, not super necessary, in math1.c.
*/

double				to_degrees(double radians);
double				to_radians(double degrees);

/*
*******************************************************************************
*/

#endif
