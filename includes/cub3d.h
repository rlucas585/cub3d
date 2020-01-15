/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/15 15:08:58 by rlucas        #+#    #+#                 */
/*   Updated: 2020/01/15 18:36:27 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

typedef struct		s_map
{
	int				*x;
	int				*y;
	int				res[2];
	char			*textures[5];
	int				floorcolor;
	int				ceilingcolor;
}					t_map;

typedef enum		e_errors
{
	INVALID_FILE = 2,
	INVALID_ARGUMENT = 22,
	BAD_FILETYPE = 79
}					t_errors;

typedef enum		e_myerrors
{
	INVALID_INPUT = 1
}					t_myerrors;

#endif
