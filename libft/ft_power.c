/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_power.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/17 11:25:03 by rlucas        #+#    #+#                 */
/*   Updated: 2020/01/17 11:26:31 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* Originally created for miniprintf project, Very basic and has undefined
 * behaviour for negative powers - which could be amended */

long		ft_power(long n, int pow)
{
	if (pow == 0)
		return (1);
	if (pow == 1)
		return (n);
	return (n * ft_power(n, pow - 1));
}
