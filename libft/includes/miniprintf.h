/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   miniprintf.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/17 11:20:53 by rlucas        #+#    #+#                 */
/*   Updated: 2020/01/31 21:05:16 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIPRINTF_H
# define MINIPRINTF_H

typedef struct		s_miniprint
{
	int				width;
	int				prec;
}					t_miniprint;

char				*num_processing(t_miniprint opts, char *pre, int sign);
char				*str_processing(t_miniprint opts, char *pre);
int					get_width(const char *str);
int					get_prec(const char *str);
int					get_type(const char *str);
char				*ft_charset(int n, int c);
char				*ft_combine(char *s1, char *s2);
char				*ft_cutstr(char *str, int n);
char				*ft_abs_base_itoa(long n, int base);

#endif
