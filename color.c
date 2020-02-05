/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/16 17:48:05 by rlucas        #+#    #+#                 */
/*   Updated: 2020/02/05 13:17:15 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int		rgb(int red, int green, int blue)
{
	int		result;

	result = 0;
	red = red << 16;
	green = green << 8;
	result = red | green | blue;
	return (result);
}
