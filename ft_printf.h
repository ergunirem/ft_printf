/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/03 10:29:21 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/01/04 20:31:57 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft/libft.h"

typedef	struct			s_data
{
	char				type;
	char				*flag;
	char				*width;
	char				*precision;
	int					error;
}						t_data;

t_data	*create_t_data(void);
void	free_t_data(t_data *ptr_data);
void	parse_flags(const char *format, t_data *data, int *i);
char	*get_precision(const char *format, int *i);
char	*get_width(const char *format, int *i);
char	*get_flag(const char *format, int *i);
void get_argument_info(const char *format, int *i, t_data *data);
int	print_regular(const char *format, int *i);
char	*handle_argument(va_list args, t_data *data, char *to_print);
char	*handle_hexa(unsigned int nbr, char c);
char	*handle_unsigned(unsigned int nbr);
char	*handle_decimal(int nbr);
char	*handle_pointer(void *pointer);
char	*handle_string(char *str);
char	*handle_char(char c);
char	*adjust_int_precision(char *to_print, int precision, int len);
char	*adjust_precision(t_data *data, char *to_print);
void	apply_flag(t_data *data, int *width, char *alignment, char *filler);
char	*adjust_width(char *to_print, int width, char alignment, char filler);
void get_wildcard_arg(t_data *data, va_list args);
int		print_argument(va_list args, t_data *data);
int print_nullchar(char *to_print, int width, char alignment);
int	parse_format(const char *format, va_list args, t_data *data);
int	ft_printf(const char *format, ...);
#endif
