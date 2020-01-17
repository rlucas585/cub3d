/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/15 15:08:58 by rlucas        #+#    #+#                 */
/*   Updated: 2020/01/17 18:08:57 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define VALID_MAP_CHARS "012NESW "

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
	int				dir;
}					t_player;

typedef struct		s_game
{
	t_map			map;
	t_player		player;
}					t_game;

typedef int		(*t_parsef)(char *line, t_map *mapinfo);

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
	INVALID_ARGUMENT = 22,
	BAD_FILETYPE = 79
}					t_errors;

/* Opening file functions, and checking argument errors. In open_file.c. */
int			check_file(const char *str);
int			open_file(int argc, char **argv);

/* Color function, converts from 8-bit integers into a single 32-bit integer
 * containing the information from three 8-bit integers. In color.c. */
int			rgb(int red, int green, int blue);

/* Error messaging, in errors.c. */
int			ft_error(int err, int linenum);

int			validate_map(char *line, size_t width);
void		validate_n_s_walls(t_map mapinfo);

/* Functions to read info from a line into relevant mapinfo, in get_info.c. */
int			get_resolution(char *line, t_map *mapinfo);
int			get_texture(char *line, t_map *mapinfo);
int			get_color(char *line, t_map *mapinfo);

/* Utility functions in utils.c */
char		*make_row(char *line);
char		**row_ptrs(char *newrow, char **oldarray);
size_t		ft_arrlen(char **array);

/* Functions to direct parsing of .cub file, in parse_cub.c. */
t_parsef	route_parsing(char c);
char		**parse_map(int fd, char *firstline, int linenum);
int			parse_line(int fd, char *line, t_map *mapinfo, int linenum);
t_map		cub_parser(int fd);

/* Troubleshooting functions that should be deleted, in utils.c. */
void		print_mapinfo(t_map mapinfo);
void		print_playerinfo(t_player player);
void		print_gameinfo(t_game game);

#endif
