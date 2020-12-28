/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/14 18:38:43 by ergunirem     #+#    #+#                 */
/*   Updated: 2020/12/25 19:23:26 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// #include "./libft/libft.h"
#include "ft_printf.h"
#include <stdio.h>

// int	handle_character(va_list args, t_data *data)
// {
// 	char	to_print;
// 	int		count;

// 	count = 0;
// 	to_print = va_arg(args, int);
// 	count += write(1, &to_print, 1);
// 	return (count);
// }

// int	handle_string(va_list args)
// {
// 	// char	*to_print;
// 	int		len;

// 	// to_print = va_arg(args, char *);
// 	len = ft_strlen(va_arg(args, char *));
// 	write(1, va_arg(args, char *), len);
// 	return (len);
// }

// int	handle_conversion(char specifier, t_data *data, va_list args)
// {
// 	int		count;

// 	count = 0;
// 	if (specifier == 'c')
// 		count += handle_character(args, data);
// 	else if (specifier == 's')
// 		count += handle_string(args);
// 	// else if (specifier == 'p')
// 	// 	format_len += handle_pointer(args, specifier);
// 	// else if (specifier == 'd' || specifier == 'i')
// 	// 	format_len += handle_integer(args, specifier);
// 	// else if (specifier == 'u')
// 	// 	format_len += handle_decimal_int(args, specifier, format_len);
// 	// else if (specifier == 'x')
// 	// 	format_len += handle_hex_int_lower(args, specifier, format_len);
// 	// else if (specifier == 'X')
// 	// 	format_len += handle_hex_int_upper(args, specifier, format_len);
// 	// else if (specifier == '%')
// 	// 	format_len += write(1, '%', 1);
// 	return (count);
// }

int	parse_format(const char *format)
{
	int	format_len;
	int	i; //should this be a pointer so that we can still keep track of where index is after functions have been called
	t_data *data;

	format_len = 0;
	i = 0;
	while (format[i] != '\0')
	{
		printf("AMCIK");
		if (format[i] != '%' && format[i])
		{
			// format_len += write(1, "a", 1); //another function to parse regular input?
			printf("AMCIK");
		}
		else if (format[i] == '%')
		{
			write(1, "inside\n", 7);
			data = create_t_data(format_len);
			// printf("type: %d\n", data->counter);
			if (!data)
				return (-1);
			//check if there are further symbols (cspdiouxXfyb%#-+ .*0123456789hLljz)?
			if (!ft_strchr("cspdiouxXfyb%#-+ .*0123456789hLljz", format[i + 1])) //another function is valid_type_flag etc.
				break ;
			while (ft_strchr("cspdiouxXfyb%#-+ .*0123456789hLljz", format[i + 1]))
			{
				i =  i + 1; //for traversing over %'s index
				// if there are no other specifier other than conversion
				if (ft_strchr("cspdiuxX%", format[i]))
				{
					// format_len += handle_conversion(format[i], data, args);
					data->type = format[i];
					printf("type: %c ", data->type);
					free_t_data(data);
					i++;
					break ; //?we are done with the specifier. this argument is over, move on to the next by breaking from the loop
				}
				// else
				// 	parse_flags(format, data, &i);
			}
			//print this particular arg with t_data info? + free data?
			printf("ONE ARG DONE!\n");

		}
		i++; //? now this is a pointer!
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
	//** t_data	*list;
	int		format_len;

	format_len = 0;
	//input validation (other things to consider?)
	if (format == NULL)
		return (0);

	//WHERE MAGIC HAPPENS
	// ** list = parse_format(format);
	// if (!list)
	// 	return (-1);

	//handle variadic-macro initilisation & print everything
	va_start(args, format);
	//** format_len = print_list(list, format);
	format_len += parse_format(format);
	//the very end (add free's if there are any)
	va_end(args);
	//free the whole list
	return(format_len);
}

