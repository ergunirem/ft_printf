/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_types.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/31 18:45:27 by icikrikc      #+#    #+#                 */
/*   Updated: 2020/12/31 18:49:05 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*handle_char(char c)
{
	char *to_print;

	if (c == 0)
		return (ft_strdup(""));
	to_print = (char *)malloc(2 * sizeof(char));
	if (!to_print)
		return (NULL);
	to_print[0] = c;
	to_print[1] = '\0';
	return (to_print);
}

char	*handle_string(char *str)
{
	char *to_print;

	if (!str)
		to_print = ft_strdup("(null)");
	else
		to_print = ft_strdup(str);
	return (to_print);
}

char	*handle_pointer(void *pointer)
{
	char *to_print;
	char *str;

	str = ft_xtoa((unsigned long long int)pointer);
	to_print = ft_strjoin("0x", str);
	free(str);
	return (to_print);
}

char	*handle_decimal(int nbr)
{
	char *to_print;

	to_print = ft_itoa(nbr);
	return (to_print);
}

char	*handle_unsigned(unsigned int nbr)
{
	char *to_print;

	to_print = ft_uitoa(nbr);
	return (to_print);
}

char	*handle_hexa(unsigned int nbr, char c)
{
	char	*to_print;
	int		i;

	to_print = ft_xtoa(nbr);
	if (c == 'X')
	{
		i = 0;
		while (to_print[i])
		{
			to_print[i] = ft_toupper(to_print[i]);
			i++;
		}
	}
	return (to_print);
}
