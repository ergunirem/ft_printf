/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_flags.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/31 18:41:17 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/01/06 21:08:12 by icikrikc      ########   odam.nl         */
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
** Else, saves the following width number. If none,
** it saves 0 as the width.
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
** Else, saves the following precision number.
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
** get_wildcard_arg: This is actually called from print_arguments
** because it calls va_arg to save the arguments given with * flag.
** If there's * in width/precision, it modifies the data accordingly.
*/

void	get_wildcard_arg(t_data *data, va_list args)
{
	int precision;

	if (!data->width || !data->precision)
		return ;
	if (*(data->width) == '*')
	{
		free(data->width);
		data->width = ft_itoa(va_arg(args, int));
	}
	if (*(data->precision) == '*')
	{
		precision = va_arg(args, int);
		free(data->precision);
		if (precision >= 0)
			data->precision = ft_itoa(precision);
		else
			data->precision = ft_strdup("");
	}
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
