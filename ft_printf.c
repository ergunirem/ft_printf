/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ergunirem <ergunirem@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/14 18:38:43 by ergunirem     #+#    #+#                 */
/*   Updated: 2020/12/16 22:33:55 by ergunirem     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdio.h>

int	ft_printf(const char *format, ...)
{
	// int		pf_char_count;
	va_list	args;

	va_start(args, format);
	printf("%d\n",va_arg(args, int));
	printf("%s\n", va_arg(args, char *));
	va_end(args);
	// return(pf_char_count);
	return (1);
}

int main(void)
{
	ft_printf("xyz", 3, "irem");
	return (0);
}
