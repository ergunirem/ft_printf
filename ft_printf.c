/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ergunirem <ergunirem@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/14 18:38:43 by ergunirem     #+#    #+#                 */
/*   Updated: 2020/12/18 12:51:57 by ergunirem     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include "./libft/libft.h"

/*
** things to parse:

	parse flag

	get width

	parse specifier
*/

///i += write(1, " ", 1); > write returns number of written characters?
//two option for format_len > send format_len as argument and format_len = handle_conversion(args, format_len)

int	handle_character(va_list args)
{
	char	to_print;
	int		count;

	count = 0;
	to_print = va_arg(args, int);
	count += write(1, &to_print, 1);
	return (count);
}

int	handle_string(va_list args)
{
	// char	*to_print;
	int		len;

	// to_print = va_arg(args, char *);
	len = ft_strlen(va_arg(args, char *));
	write(1, va_arg(args, char *), len);
	return (len);
}

int	handle_conversion(va_list args, char specifier)
{
	int		count;

	count = 0;
	if (specifier == 'c')
		count += handle_character(args);
	else if (specifier == 's')
		count += handle_string(args);
	// else if (specifier == 'p')
	// 	format_len += handle_pointer(args, specifier);
	// else if (specifier == 'd' || specifier == 'i')
	// 	format_len += handle_integer(args, specifier);
	// else if (specifier == 'u')
	// 	format_len += handle_decimal_int(args, specifier, format_len);
	// else if (specifier == 'x')
	// 	format_len += handle_hex_int_lower(args, specifier, format_len);
	// else if (specifier == 'X')
	// 	format_len += handle_hex_int_upper(args, specifier, format_len);
	// else if (specifier == '%')
	// 	format_len += write(1, '%', 1);
	return (count);
}

int	parse_format(const char *format, va_list args)
{
	int	format_len;
	int	i;

	format_len = 0;
	i = 0;
	while (format[i] != '\0')
	{
		if (format[i] != '%' && format[i])
			format_len += write(1, &format[i], 1);
		else if (format[i] == '%')
		{
			//check if there are further symbols (cspdiouxXfyb%#-+ .*0123456789hLljz)?
			if (!ft_strchr("cspdiouxXfyb%#-+ .*0123456789hLljz", format[i + 1]))
				break ;
			while (ft_strchr("cspdiouxXfyb%#-+ .*0123456789hLljz", format[i + 1]))
			{
				i =  i + 1; //for traversing over %'s index
				// if there are no other specifier other than conversion
				if (ft_strchr("cspdiuxX%", format[i]))
				{
					format_len += handle_conversion(args, format[i]);
				}
				// else
				// {

				// }
			}
		}
		i++;
	}
	return (format_len);
}

/*
** ft_printf: starter function of the project. So, every other function is initially called from here.
** Then, it returns the count of printed characters when the function is successful and -1 when the function fails.
*/

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		format_len;

	//input validation (other things to consider?)
	if (format == NULL)
		return (0);
	//handle variadic-macro initilisation
	va_start(args, format);


	//WHERE MAGIC HAPPENS
	format_len = parse_format(format, args);


	//the very end (add free's if there are any)
	va_end(args);
	return(format_len);
}

int main(void)
{
	int	return_val;
	return_val = ft_printf("what will happen %c and %s", 'X', "mahmut");
	ft_printf("\n");
	printf("ft_return_val: %d\n", return_val);
	return_val = printf("what will happen %c and %s", 'X', "mahmut");
	printf("\n");
	printf("li_return_val: %d\n", return_val);
	return (0);
}
