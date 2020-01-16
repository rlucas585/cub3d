/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/15 15:08:58 by rlucas        #+#    #+#                 */
/*   Updated: 2020/01/16 17:47:45 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

typedef struct		s_map
{
	char			**coords;
	int				res[2];
	char			*textures[5];
	int				floorcolor;
	int				ceilingcolor;
}					t_map;

typedef int		(*t_parsef)(char *line, t_map *mapinfo);

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
	MORE_ARG = 7,
	MEM_FAIL = 12,
	INVALID_ARGUMENT = 22,
	BAD_FILETYPE = 79
}					t_errors;

int		rgb(int red, int green, int blue);
int		get_resolution(char *line, t_map *mapinfo);
int		textures(int c);
int		get_texture(char *line, t_map *mapinfo);
int		get_color(char *line, t_map *mapinfo);

#endif
