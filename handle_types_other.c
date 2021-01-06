/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_types_other.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/31 18:45:27 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/01/06 21:57:39 by icikrikc      ########   odam.nl         */
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
	if (!str)
		return (NULL);
	to_print = ft_strjoin("0x", str);
	free(str);
	return (to_print);
}
