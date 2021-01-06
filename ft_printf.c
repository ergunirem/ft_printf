/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/03 10:28:28 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/01/06 20:35:30 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** get_argument_info: after '%' character, it checks valid argument/flag types,
** if it is just type conversion it immediately saves the type in t_data.
** Else, it first calls parse_flag to save flag information in t_data.
** Then, it saves the type conversion after parsing the flags.
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
		else if (ft_strchr("-.*0123456789", format[*i]))
			parse_flags(format, data, i);
	}
}

/*
** parse_format: itirates in format, and creates an instance of t_data.
** It calls different print funcs if it's an argument or regular character.
** If there is an argument calls info function to save format specifiers
** in this t_data. Finally, it returns -1 if there has been an error.
** Then, it frees the t_data.
*/

int		parse_format(const char *format, va_list args)
{
	t_data	*data;
	int		format_len;
	int		i;

	i = 0;
	format_len = 0;
	while (format[i] != '\0')
	{
		data = create_t_data();
		if (!data)
			return (-1);
		if (format[i] != '%' && format[i])
			format_len += print_plain_character(format, &i, data);
		else if (format[i])
		{
			if (!ft_strchr("cspdiuxX%-.*0123456789", format[i + 1]))
				return (-1);
			get_argument_info(format, &i, data);
			format_len += print_argument(args, data);
		}
		if (data->error == 1)
			return (-1);
		free_t_data(data);
	}
	return (format_len);
}

/*
** ft_printf: starter function of the project.
** So, every other function is initially called from here.
** (The diagram of function calls can be found at diagram.jpg)
** Return value is the count of printed characters when
** the function is successful and -1 when the function fails.
*/

int		ft_printf(const char *format, ...)
{
	va_list	args;
	int		format_len;

	if (format == NULL)
		return (0);
	va_start(args, format);
	format_len = parse_format(format, args);
	if (format_len == -1)
		return (-1);
	va_end(args);
	return (format_len);
}
