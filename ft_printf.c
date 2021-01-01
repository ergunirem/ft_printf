/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/14 18:38:43 by ergunirem     #+#    #+#                 */
/*   Updated: 2021/01/01 13:37:18 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
get_argument_info: after '%' character, it checks valid argument/flag types,
if it is type conversion it saves the type in t_data, else calls parse_flag func to
save flag information in t_data.
*/

void get_argument_info(const char *format, int *i, t_data *data)
{
	*i = *i + 1;
	while (ft_strchr("cspdiouxXfyb%#-+ .*0123456789hLljz", format[*i]))
	{
		// if there are no other specifier other than conversion + this leaves width etc as null!
		if (ft_strchr("cspdiuxX%", format[*i]))
		{
			// format_len += handle_conversion(format[i], data, args);
			data->type = format[*i];
			(*i)++;
			break; //?we are done with the specifier. this argument is over, move on to the next by breaking from the loop
		}
		else
			parse_flags(format, data, i);
	}
	// printf("%s  >> type: %s%c ", BLUE, RESET, data->type);
	// printf("%sflag: %s%s ", PURPLE, RESET, data->flag);
	// printf("%swidth: %s%s ", GREEN, RESET, data->width);
	// printf("%sprecision: %s%s ", YELLOW, RESET, data->precision);
}

/*
parse_format: itirates in format, first prints everything except %arguments.
Else, it creates an instance of t_data, checks for '%' and calls info function to
save argument informations in this t_data, prints this saved info and frees t_data.
*/

int	parse_format(const char *format, va_list args)
{
	int		format_len;
	int		i;
	t_data	*data;

	i = 0;
	format_len = 0;
	while (format[i] != '\0')
	{
		if (format[i] != '%' && format[i])
			format_len += print_regular(format, &i);
		else if (format[i])
		{
			data = create_t_data();
			if (!data)
				return (-1);
			if (!ft_strchr("cspdiouxXfyb%#-+ .*0123456789hLljz", format[i + 1])) //another function is valid_type_flag etc.
				break ; // which loop does this break from? is it okay? or return (-1)?
			get_argument_info(format, &i, data);
			format_len += print_argument(args, data);
			// printf("%s !arg!%s\n", RED, RESET);
			free_t_data(data);
		}
	}
	return (format_len);
}

/*
ft_printf: starter function of the project.
So, every other function is initially called from here.
(The diagram of function calls can be found at diagram.jpg)
Finally, it returns the count of printed characters when the function is successful
and -1 when the function fails.
*/

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		format_len;

	if (format == NULL)
		return (0);
	va_start(args, format);
	format_len = 0;
	format_len += parse_format(format, args);
	va_end(args);
	return (format_len);
}
