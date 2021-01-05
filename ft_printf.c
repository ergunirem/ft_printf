/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/03 10:28:28 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/01/04 22:00:27 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** get_argument_info: after '%' character, it checks valid argument/flag types,
** if it is type conversion it saves the type in t_data, else calls parse_flag
** func to save flag information in t_data.
*/

void	get_argument_info(const char *format, int *i, t_data *data)
{
	*i = *i + 1;
	while (ft_strchr("cspdiuxX%-.*0123456789", format[*i]))
	{
		if (ft_strchr("cspdiuxX%", format[*i]))
		{
			data->type = format[*i];
			(*i)++;
			break ;
		}
		else
			parse_flags(format, data, i);
	}
}

/*
** parse_format: itirates in format, first prints everything except %arguments.
** Else, it creates an instance of t_data, checks for '%' and
** calls info function to save argument informations in this t_data,
** prints this saved info and frees t_data.
*/

int		parse_format(const char *format, va_list args, t_data *data)
{
	int		format_len;
	int		i;

	i = 0;
	format_len = 0;
	while (format[i] != '\0')
	{
		if (format[i] != '%' && format[i])
			format_len += print_regular(format, &i);
		else if (format[i])
		{
			if (!ft_strchr("cspdiuxX%-.*0123456789", format[i + 1]))
			{
				data->error = 1;
				return (-1);
			}
			get_argument_info(format, &i, data);
			format_len += print_argument(args, data);
			free_t_data(data);
		}
	}
	return (format_len);
}

/*
** ft_printf: starter function of the project.
**So, every other function is initially called from here.
** (The diagram of function calls can be found at diagram.jpg)
** Finally, it returns the count of printed characters
** when the function is successful
** and -1 when the function fails.
*/

int		ft_printf(const char *format, ...)
{
	va_list	args;
	t_data	*data;
	int		format_len;

	if (format == NULL)
		return (0);
	va_start(args, format);
	data = create_t_data();
	if (!data)
		return (-1);
	format_len = 0;
	format_len += parse_format(format, args, data);
	if (data->error == 1)
		return (-1);
	va_end(args);
	return (format_len);
}
