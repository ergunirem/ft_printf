/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/31 18:58:35 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/01/04 21:57:15 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_nullchar(char *to_print, int width, char alignment)
{
	int tmp_width;

	tmp_width = width;
	free(to_print);
	if (alignment == 'L')
	{
		ft_putchar_fd(0, 1);
		while (width - 1 > 0)
		{
			ft_putchar_fd(' ', 1);
			width--;
		}
	}
	if (alignment == 'R')
	{
		while (width - 1 > 0)
		{
			ft_putchar_fd(' ', 1);
			width--;
		}
		ft_putchar_fd(0, 1);
	}
	if (tmp_width == 0)
		return (1);
	return (tmp_width);
}

/*
** print_argument: mallocs a char *to_print to save argument.
** Set default values for alingment, width, and filler.
** Then calls formatting functions to adjust char *to_print
** based on flags,precision,width.
** Then, writes the the adjusted to_print version at the end of the function.
** Finally, frees the char *to_print.
*/

int	print_argument(va_list args, t_data *data)
{
	int		arg_len;
	int		width;
	char	*to_print;
	char	alignment;
	char	filler;

	width = 0;
	alignment = 'R';
	filler = ' ';
	to_print = ft_strdup("");
	if (!to_print)
		data->error = 1;
	get_wildcard_arg(data, args);
	to_print = handle_argument(args, data, to_print);
	to_print = adjust_precision(data, to_print);
	apply_flag(data, &width, &alignment, &filler);
	if (data->type == 'c' && *to_print == '\0')
		return (print_nullchar(to_print, width, alignment));
	to_print = adjust_width(to_print, width, alignment, filler);
	if (!to_print)
		data->error = 1;
	arg_len = ft_strlen(to_print);
	ft_putstr_fd(to_print, 1);
	free(to_print);
	return (arg_len);
}

/*
** print_regular: iterates in format by printing each char until if finds a %.
*/

int	print_regular(const char *format, int *i)
{
	int counter;

	counter = 0;
	while (format[*i] && format[*i] != '%')
	{
		counter += write(1, &format[*i], 1);
		(*i)++;
	}
	return (counter);
}
