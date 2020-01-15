/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rlucas <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 13:40:28 by rlucas        #+#    #+#                 */
/*   Updated: 2019/11/19 16:52:33 by rlucas        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <libft.h>

typedef struct		s_opts
{
	char			*flags;
	int				width;
	int				prcs;
	char			length;
	char			type;
}					t_opts;

char				*int_string(t_opts *options, va_list arg);
size_t				ignore_sign_len(const char *stringnum);
int					ft_chkchar_instr(char c, const char *s1);
char				*flagchk(const char *str);
int					widthchk(const char *str);
int					prcschk(const char *str);
char				lenchk(const char *str);
char				typechk(const char *str);
int					countargs(const char *str);
char				*make_string(t_opts *options, va_list arg);
void				printopts(t_opts *options);
t_opts				*parser(const char *str);
int					arglength(const char *str);
char				*pad_with_zeros(char *str, size_t init, int prcs);
char				*apply_precision(size_t prcs, char *string);
char				*apply_width(t_opts *options, char *str);
char				*left_align(int width, char *string);
char				*ft_itoa(int n);
char				*ft_ltoa(long n);
char				*ft_lltoa(long long n);
char				*ft_ulltoa(unsigned long long n);
char				*ft_ulltox(unsigned long long num, char c, int base);
unsigned long		upower(unsigned int number, int power);
char				*char_string(t_opts *options, va_list arg);
int					output(const char *str, va_list arg, int *printed);
char				*ptr_to_hex(t_opts *options, va_list arg);
int					ft_printf(char *str, ...);
void				ft_putnbr_fd_and_count(int n, int fd, int *printed);
char				*add_flag(char *flags);
t_opts				*arg_width_prcs(t_opts *options, va_list arg);
char				*type_c(t_opts *options, va_list arg);
char				*type_s(t_opts *options, va_list arg);
char				*type_u_o_x(t_opts *options, va_list arg);
int					crazy_strings(t_opts *options, va_list arg, \
					int *printed, int sum);
int					dist_to_char(const char *str, char c);
char				*onecharstring(char c);
char				*hashflags(t_opts *options, char *result);
char				*prepend(char *old, char *c);
char				*hex_processing(t_opts *options, char *result);
t_opts				*no_ast_parse(const char *str, t_opts *options, int prcs);
int					astcheck(const char *str);
t_opts				*asterisk_troubles(const char *str, t_opts *options);
t_opts				*neg_width(t_opts *options);
void				*free_and_null(void *ptr, void *ptr2);

#endif
