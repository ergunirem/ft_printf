/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/31 18:58:35 by icikrikc      #+#    #+#                 */
/*   Updated: 2020/12/31 20:59:34 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
print_argument: mallocs a char *to_print to save argument.
Set default values for alingment, width, and filler.
Then calls formatting functions to adjust char *to_print based on flags,precision,width.
Then, writes the the adjusted to_print version at the end of the function.
Finally, frees the char *to_print.
*/

int		print_argument(va_list args, t_data *data)
{
	int		arg_len;
	int		width;
	char	*to_print;
	char	alignment;
	char	filler;

	arg_len = 0;
	width = 0;
	alignment = 'R';
	filler = ' ';
	to_print = ft_strdup("");
	if (!to_print)
		return (-1); //then what in parse_format func?
	//what about '*' w/width and precision?
	to_print = handle_argument(args, data, to_print);
	to_print = adjust_precision(data, to_print);
	apply_flag(data, &width, &alignment, &filler);
	to_print = adjust_width(to_print, width, alignment, filler);
	//check if to_print is null and return -1?
	arg_len = ft_strlen(to_print);
	ft_putstr_fd(to_print, 1);
	free(to_print);
	return(arg_len);
}

/*
print_regular: iterates in format until if finds a %s by printing each char.
*/

int	print_regular(const char *format, int *i)
{
	int	counter;

	counter = 0;
	while(format[*i] && format[*i] != '%')
	{
		counter += write(1, &format[*i], 1); //more efficient way to print chunk of chars?
		(*i)++;
	}
	return (counter);
}
