/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_funcs.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/31 18:58:35 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/01/06 21:44:25 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	check_return_val(t_data *data, int width, char *to_print)
{
	free(to_print);
	if (data->error)
		return (-1);
	else if (width == 0)
		return (1);
	else
		return (width);
}

/*
** print_nullchar: this is an exception function for null character.
** To mimic printf's behaviour, it prints null char based on alignment.
** If there is no width, it returns 1 which represents one character printed.
** Else, it calls check_return_val which returns width
** while printing one char plus spaces.
*/

int	print_nullchar(char *to_print, int width, char alignment, t_data *data)
{
	int i;

	i = 0;
	if (alignment == 'L')
	{
		if ((ft_putchar_fd_protected(0, 1)) == -1)
			data->error = 1;
		while (width - 1 > i)
		{
			if ((ft_putchar_fd_protected(' ', 1)) == -1)
				data->error = 1;
			i++;
		}
		return (check_return_val(data, width, to_print));
	}
	while (width - 1 > i)
	{
		if ((ft_putchar_fd_protected(' ', 1)) == -1)
			data->error = 1;
		i++;
	}
	if ((ft_putchar_fd_protected(0, 1)) == -1)
		data->error = 1;
	return (check_return_val(data, width, to_print));
}

/*
** print_argument: mallocs a char *to_print to save formatted argument.
** Sets default values for alingment, width, and filler.
** Then calls formatting functions to adjust to_print based on
** flags,precision,width. Then, writes the adjusted to_print.
** Finally, checks for errors and frees the char *to_print.
*/

int	print_argument(va_list args, t_data *data)
{
	char	*to_print;
	char	alignment;
	char	filler;
	int		width;
	int		arg_len;

	width = 0;
	alignment = 'R';
	filler = ' ';
	to_print = ft_strdup("");
	get_wildcard_arg(data, args);
	to_print = handle_argument(args, data, to_print);
	to_print = adjust_precision(data, to_print);
	apply_flag(data, &width, &alignment, &filler);
	if (data->type == 'c' && *to_print == '\0')
		return (print_nullchar(to_print, width, alignment, data));
	to_print = adjust_width(to_print, width, alignment, filler);
	if (!to_print)
		data->error = 1;
	arg_len = ft_strlen(to_print);
	if (ft_putstr_fd_protected(to_print, 1) == -1)
		data->error = 1;
	free(to_print);
	return (arg_len);
}

/*
** print_plain_characters: iterates in format
** by printing each char until if finds a %.
*/

int	print_plain_character(const char *format, int *i, t_data *data)
{
	int counter;
	int ret;

	counter = 0;
	while (format[*i] && format[*i] != '%')
	{
		ret = write(1, &format[*i], 1);
		if (ret == -1)
		{
			data->error = 1;
			return (-1);
		}
		counter += ret;
		(*i)++;
	}
	return (counter);
}
