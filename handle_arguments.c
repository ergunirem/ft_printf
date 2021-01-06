/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_arguments.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/31 18:49:33 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/01/06 21:53:28 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** handle_argument: based on the type conversion,
** it calls the appropriate handle function
*/

char	*handle_argument(va_list args, t_data *data, char *to_print)
{
	char *tmp;

	if (!to_print)
		return (NULL);
	if (data->type == 'c')
		tmp = handle_char(va_arg(args, int));
	else if (data->type == 's')
		tmp = handle_string(va_arg(args, char *));
	else if (data->type == 'p')
		tmp = handle_pointer(va_arg(args, void *));
	else if (data->type == '%')
		tmp = ft_strdup("%");
	else if (data->type == 'd' || data->type == 'i')
		tmp = handle_decimal(va_arg(args, int));
	else if (data->type == 'u')
		tmp = handle_unsigned(va_arg(args, unsigned int));
	else if (data->type == 'x' || data->type == 'X')
		tmp = handle_hexa(va_arg(args, unsigned int), data->type);
	else
		return (NULL);
	free(to_print);
	return (tmp);
}

/*
** adjust_int_precision: specific adaptation of adjust_precision for integers.
** If precision is smaller than argument len, it does not change anything.
** Else if precision is bigger than len, it pads the remaining spaces with '0'.
** Also handles exception case: precision 0 and argument 0 returns empty string.
*/

char	*adjust_int_precision(char *to_print, int precision, int len)
{
	char	*tmp;
	char	*sign;
	char	*pad;
	char	*padded_str;
	int		is_negative;

	is_negative = 0;
	if (to_print[0] == '-')
		is_negative = 1;
	if (len - is_negative >= precision)
	{
		if (precision == 0 & to_print[0] == '0')
			return (ft_strdup(""));
		return (ft_strdup(to_print));
	}
	sign = ft_substr(to_print, 0, is_negative);
	pad = (char *)ft_calloc(precision + is_negative - len + 1, sizeof(char));
	pad = ft_memset(pad, '0', precision + is_negative - len);
	padded_str = ft_strjoin_free(pad, to_print + is_negative, 1);
	tmp = ft_strjoin_free(sign, padded_str, 3);
	return (tmp);
}

/*
** adjust_precision: based on valid type specifier, it pads argument with '0'
** if there is enough space when precision minus string length.
** Else, it does not touch anything.
*/

char	*adjust_precision(t_data *data, char *to_print)
{
	char	*tmp;
	int		precision;
	int		len;

	if (!to_print)
		return (NULL);
	if (!data->precision || *(data->precision) == '\0')
		return (to_print);
	precision = ft_atoi(data->precision);
	len = ft_strlen(to_print);
	if (data->type == 's' && precision < len)
		tmp = ft_substr(to_print, 0, precision);
	if (data->type == 's' && precision >= len)
		return (to_print);
	if (data->type == 'p')
		return (to_print);
	if (data->type == 'c')
		return (to_print);
	if (ft_strchr("diuxX", data->type))
		tmp = adjust_int_precision(to_print, precision, len);
	free(to_print);
	return (tmp);
}

/*
** apply_flag: based on the saved flags, it changes the alignment from right
** to left, changes filler from ' ' to '0', transforms width from char * to int.
** It also turns negative width to positive after alignment value is changed.
*/

void	apply_flag(t_data *data, int *width, char *alignment, char *filler)
{
	if (!data->flag)
		return ;
	*width = (int)ft_atoi(data->width);
	if (ft_strchr(data->flag, '-') || *(width) < 0)
		*alignment = 'L';
	if (*alignment == 'R' && ft_strchr(data->flag, '0') > 0 &&
		!(ft_strchr("diuxX", data->type) && ft_strlen(data->precision) > 0))
		*filler = '0';
	if (*(width) < 0)
		*(width) *= -1;
}

/*
** adjust_width: based on width, aligment and filler, it determines whether
** the argument should be padded with '0' or ' ' if width is bigger than
** argument length. Also, whether it should be left aligned or not.
** It also handles negative integers.
*/

char	*adjust_width(char *to_print, int width, char alignment, char filler)
{
	char	*pad;
	char	*padded_str;
	int		is_negative;

	if (!to_print)
		return (NULL);
	is_negative = 0;
	if (to_print[0] == '-')
		is_negative = 1;
	if (width <= (int)ft_strlen(to_print))
		return (to_print);
	pad = (char *)ft_calloc(width - ft_strlen(to_print) + 1, sizeof(char));
	pad = ft_memset(pad, filler, width - ft_strlen(to_print));
	if (alignment == 'L')
		to_print = ft_strjoin_free(to_print, pad, 3);
	if (alignment == 'R' && filler != '0')
		to_print = ft_strjoin_free(pad, to_print, 3);
	if (alignment == 'R' && filler == '0')
	{
		padded_str = ft_strjoin_free(pad, to_print + is_negative, 1);
		pad = ft_substr(to_print, 0, is_negative);
		free(to_print);
		to_print = ft_strjoin_free(pad, padded_str, 3);
	}
	return (to_print);
}
