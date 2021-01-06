/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_types_int.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/04 21:23:50 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/01/06 21:58:43 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
	if (!to_print)
		return (NULL);
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
