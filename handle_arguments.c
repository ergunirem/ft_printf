/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_arguments.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/31 18:49:33 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/01/04 21:58:23 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** handle_argument: based on the type conversion, it calls the appropriate handle function
*/

char	*handle_argument(va_list args, t_data *data, char *to_print)
{
	char *tmp;

	if (data->type == 'c')
		tmp = handle_char(va_arg(args, int));
	if (data->type == 's')
		tmp = handle_string(va_arg(args, char *));
	if (data->type == 'p')
		tmp = handle_pointer(va_arg(args, void *));
	if (data->type == '%')
		tmp = ft_strdup("%");
	if (data->type == 'd' || data->type == 'i')
		tmp = handle_decimal(va_arg(args, int));
	if (data->type == 'u')
		tmp = handle_unsigned(va_arg(args, unsigned int));
	if (data->type == 'x' || data->type == 'X')
		tmp = handle_hexa(va_arg(args, unsigned int), data->type);//why  unsingedint?
	free(to_print);
	return (tmp);
}

/*
** adjust_int_precision: specific adaptation of adjust_print for integers.
** If precision is smaller than argument len, it does not change anything.
** Else if precision is bigger than len, it pads the remaining spaces with '0'.
** Also handles exception case: precision is 0 and argument is 0 returns empty string.
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
		if (precision == 0 & to_print[0] == '0') //(difference with hexa&p??
			return(ft_strdup(""));
		return (ft_strdup(to_print));
	}
	sign = ft_substr(to_print, 0 , is_negative);
	pad = (char *)ft_calloc(precision + is_negative - len + 1, sizeof(char));
	pad = ft_memset(pad, '0', precision + is_negative - len);
	padded_str = ft_strjoin(pad, to_print + is_negative);
	tmp = ft_strjoin(sign, padded_str);
	free(pad);
	free(sign);
	free(padded_str);
	return (tmp);
}

/*
** adjust_precision: ?
*/

char	*adjust_precision(t_data *data, char *to_print)
{
	char	*tmp;
	int		precision;
	int		len;

	if (!to_print || !data->precision || *(data->precision) == '\0')
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
	if (data->type == 'd' || data->type == 'i' || data->type == 'u' || data->type == 'x' || data->type == 'X')
		tmp = adjust_int_precision(to_print, precision, len);
	free(to_print);
	return (tmp);
}

/*
apply_flag: based on the saved flags, it changes the alignment from right to left,
changes filler from ' ' to '0', transforms width from char * to int.
*/

void	apply_flag(t_data *data, int *width, char *alignment, char *filler)
{
	if (!data->flag)
		return ;
	*width = (int)ft_atoi(data->width);
	if (ft_strchr(data->flag, '-') || *(width) < 0)
		*alignment = 'L';
	if (*alignment == 'R' && ft_strchr(data->flag, '0') > 0 && !((data->type == 'd' || data->type == 'i' || data->type == 'u' || data->type == 'x' || data->type == 'X') && ft_strlen(data->precision) > 0))
		*filler = '0';
	if (*(width) < 0)
		*(width) *= -1;
}

/*
** adjust_width: based on width, aligment and filler, it determines whether the argument should
** be padded with '0' or ' ' if width is bigger than argument length. Also, whether it should be left
** aligned or not. It also handles negative integers.
*/

char	*adjust_width(char *to_print, int width, char alignment, char filler)
{
	char	*tmp;
	char	*pad;
	char	*padded_str;
	char	*sign;
	int		is_negative;
	//if width == 0 ?
	is_negative = 0;
	if (to_print[0] == '-')
		is_negative = 1;
	if (width > (int)ft_strlen(to_print))
	{
		sign = ft_substr(to_print, 0 , is_negative); //might be different if you add #?
		pad = (char *)ft_calloc(width - ft_strlen(to_print) + 1, sizeof(char));
		pad = ft_memset(pad, filler, width  - ft_strlen(to_print)); //another func?
		if (alignment == 'L')
			tmp = ft_strjoin(to_print, pad); //3
		if (alignment == 'R' && filler != '0')
			tmp = ft_strjoin(pad, to_print);
		if (alignment == 'R' && filler == '0') // && data->type > integers! & negative numbers?
		{
			padded_str = ft_strjoin(pad, to_print + is_negative);
			tmp = ft_strjoin(sign, padded_str);
			free(padded_str);
		}
		free(sign);
		free(pad);
		free(to_print);
		return (tmp);
	}
	else
		return (to_print);
}

void get_wildcard_arg(t_data *data, va_list args)
{
	long long int precision;

	if (!data->width || !data->precision)
		return ;
	if (*(data->width) == '*')
	{
		free(data->width);
		data->width = ft_itoa(va_arg(args, int));
	}
	if (*(data->precision) == '*')
	{
		precision = (long long int)va_arg(args, int);
		free(data->precision);
		if (precision >= 0)
			data->precision = ft_itoa(precision);
		else
			data->precision = ft_strdup("");
	}
}

