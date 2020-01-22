/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/16 17:48:05 by rlucas        #+#    #+#                 */
/*   Updated: 2020/01/22 14:21:05 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int		rgb(int red, int green, int blue)
{
	int		result;

	result = 0;
	if (red > 255 || red < 0 || green > 255 || green < 0 || blue > 255 ||
			blue < 0)
		return (-1);
	red = red << 16;
	green = green << 8;
	result = red | green | blue;
	return (result);
}
