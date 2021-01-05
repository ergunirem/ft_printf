/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_flags.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/31 18:41:17 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/01/04 22:02:57 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** get_flags:  Saves the mandatory section's flags in t_data..
*/

char	*get_flag(const char *format, int *i)
{
	int	start;

	start = *i;
	while (format[*i] == '0' || format[*i] == '-')
		(*i)++;
	return (ft_substr(format, start, *i - start));
}

/*
** get_width: Checks for '*' wildcard exception.
** Then, saves the following width number.
*/

char	*get_width(const char *format, int *i)
{
	int	start;

	start = *i;
	if (format[*i] == '*')
	{
		(*i)++;
		return (ft_strdup("*"));
	}
	while (format[*i] >= '0' && format[*i] <= '9')
		(*i)++;
	if (*i > start)
		return (ft_substr(format, start, *i - start));
	return (ft_strdup("0"));
}

/*
** get_precision: checks if it starts with '.' for precision validation.
** Checks for '*' wildcard exception.
** Then, saves the following precision number.
*/

char	*get_precision(const char *format, int *i)
{
	int	start;

	if (format[*i] != '.')
		return (ft_strdup(""));
	(*i)++;
	start = *i;
	if (format[*i] == '*')
	{
		(*i)++;
		return (ft_strdup("*"));
	}
	while (format[*i] >= '0' && format[*i] <= '9')
		(*i)++;
	if (*i > start)
		return (ft_substr(format, start, *i - start));
	return (ft_strdup("0"));
}

/*
** parse_flags: follows the format specifier prototype order
** while calling get functions. > %[flags][width][.precision][length]specifier
*/

void	parse_flags(const char *format, t_data *data, int *i)
{
	data->flag = get_flag(format, i);
	data->width = get_width(format, i);
	data->precision = get_precision(format, i);
	if (!data->flag || !data->width || !data->precision)
	{
		data->error = 1;
		return ;
	}
}
