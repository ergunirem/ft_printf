# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft/libft.h"

char RED[] = "\033[1;31m";
char GREEN[] = "\033[0;32m";
char PURPLE[] = "\033[0;35m";
char YELLOW[] = "\033[0;33m";
char BLUE[] = "\033[0;36m";
char RESET[]= "\033[0m";

typedef	struct			s_data
{
	// int					index;
	// int					index_arg;
	char				type;
	char				*flag;
	char				*width;
	char				*precision;
	int					length;
}						t_data;

t_data	*create_t_data(void)
{
	t_data *data;

	data = (t_data*)malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->type = 0;
	data->flag = 0;
	data->width = 0;
	data->precision = 0;
	data->length = 0;
	return (data);
}

void	free_t_data(t_data *ptr_data)
{
	// if (!ptr_data || !*ptr_data)
	// 	return (NULL);
		free(ptr_data->flag);
		free(ptr_data->width);
		free(ptr_data->precision);
		free(ptr_data);
}

char	*get_flag(const char *format, int *i)
{
	int	start;

	start = *i;
	while (format[*i] == '0' || format[*i] == '-')
		(*i)++;
	return (ft_substr(format, start, *i - start));
}

char	*get_width(const char *format, int *i)
{
	int	start;

	start = *i;
	if (format[*i] == '*')
	{
		(*i)++;
		return(ft_strdup("*"));
	}
	while (format[*i] >= '0' && format[*i] <= '9' )
		(*i)++;
	if (*i > start)
		return (ft_substr(format, start, *i - start)); //not sure?
	return (ft_strdup("0"));
}

char	*get_precision(const char *format, int *i)
{
	int	start;

	if (format[*i] != '.')
		return(ft_strdup(""));
	(*i)++;
	start = *i;
	if (format[*i] == '*')
	{
		(*i)++;
		return(ft_strdup("*"));
	}
	while (format[*i] >= '0' && format[*i] <= '9' )
		(*i)++;
	if (*i > start)
		return (ft_substr(format, start, *i - start)); //not sure?
	return (ft_strdup("0"));
}

int	parse_flags(const char *format, t_data *data, int *i)
{
	//follow the format specifier prototype order while you are calling functions!
	//%[flags][width][.precision][length]specifier
	data->flag = get_flag(format, i);
	data->width = get_width(format, i);
	data->precision = get_precision(format, i);
	// data->length = get_length(); // >>> BONUS?
	if (!data->flag || !data->width || !data->precision)
		return (-1);//?
	return (1);
}

void get_argument(const char *format, int *i, t_data *data)
{
	//not sure about where i is pointing at!
	*i = *i + 1;
	while (ft_strchr("cspdiouxXfyb%#-+ .*0123456789hLljz", format[*i]))
	{
		// if there are no other specifier other than conversion + this leaves width etc as null!
		if (ft_strchr("cspdiuxX%", format[*i]))
		{
			// format_len += handle_conversion(format[i], data, args);
			data->type = format[*i];
			(*i)++;
			break; //?we are done with the specifier. this argument is over, move on to the next by breaking from the loop
		}
		else
			parse_flags(format, data, i);
	}
	// printf("%s  >> type: %s%c ", BLUE, RESET, data->type);
	// printf("%sflag: %s%s ", PURPLE, RESET, data->flag);
	// printf("%swidth: %s%s ", GREEN, RESET, data->width);
	// printf("%sprecision: %s%s ", YELLOW, RESET, data->precision);
}

int	print_regular(const char *format, int *i)
{
	int	counter;

//malloc a char *str to save argument then format based on specifiers + write the the last version at the end of the function.
	counter = 0;
	while(format[*i] && format[*i] != '%')
	{
		counter += write(1, &format[*i], 1);
		(*i)++;
	}
	return (counter);
}

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

	to_print = ft_itoa(nbr);
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
	//if precision is smaller than dont touch to_print & 0 exception
	if (len - is_negative >= precision)
	{	//exception: precision = 0 and to_print = 0;
		if (precision == 0 & to_print[0] == '0') //(difference with hexa&p??
			return(ft_strdup(""));
		return (ft_strdup(to_print));
	}
	//othewise pad with 0's
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

char	*adjust_precision(t_data *data, char *to_print)
{
	char	*tmp;
	int		precision;
	int		len;

	if (!to_print || !data->precision)
		return (to_print);
	precision = ft_atoi(data->precision);
	len = ft_strlen(to_print);
	if (data->type == 's' && precision < len)
		tmp = ft_substr(to_print, 0, precision);
	if (data->type == 'p')
		return (to_print);
	if (data->type == 'c')
		return (to_print);
	if (data->type == 'd' || data->type == 'i' || data->type == 'u' || data->type == 'x' || data->type == 'X')
		tmp = adjust_int_precision(to_print, precision, len);
	free(to_print);
	return (tmp);
}

void	apply_flag(t_data *data, int *width, char *alignment, char *filler)
{
	*width = (int)ft_atoi(data->width);
	if (ft_strchr(data->flag, '-') || *width < 0)
		*alignment = 'L';
	if (*alignment == 'R' && ft_strchr(data->flag, '0') > 0 && !((data->type == 'd' || data->type == 'i' || data->type == 'u' || data->type == 'x' || data->type == 'X') && ft_strlen(data->precision) > 0))
		*filler = '0';
}

char	*adjust_width(char *to_print, int width, char alignment, char filler)
{
	char	*tmp;
	char	*pad;

	if (width > (int)ft_strlen(to_print))
	{
		pad = (char *)ft_calloc(width - ft_strlen(to_print) + 1, sizeof(char));
		pad = ft_memset(pad, filler, width  - ft_strlen(to_print)); //another func?
		if (alignment == 'L')
			tmp = ft_strjoin(to_print, pad); //3
		// if (alignment == 'R' && target == '0') // && data->type > integers!
		// {
		// 	s_fill = ft_strjoin(pad, to_print + check_sign); //1
		// 	tmp = ft_strjoin(s_sign, s_fill); //2
		// }
		if (alignment == 'R' && filler != '0') //what happens when check_sign = 0;
			tmp = ft_strjoin(pad, to_print); //1
		free(pad);
		free(to_print);
		return (tmp);
	}
	else
		return (to_print);
}

int		print_argument(va_list args, t_data *data)
{
	int		arg_len;
	int		width;
	char	*to_print;
	char	alignment;
	char	filler;

	arg_len = 0;
	//default values > will be adjusted based on flags,precision,width
	width = 0;
	alignment = 'R';
	filler = ' ';
	to_print = ft_strdup("");
	if (!to_print)
		return (-1); //then what in parse_format func?
	//what about '*' w/width and precision?
	to_print = handle_argument(args, data, to_print);
	to_print = adjust_precision(data, to_print);
	apply_flag(data, &width, &alignment, &filler);
	to_print = adjust_width(to_print, width, alignment, filler);
	//check if to_print is null and return -1?
	arg_len = ft_strlen(to_print);
	ft_putstr_fd(to_print, 1);
	free(to_print); // where to free?
	return(arg_len);
}

int	parse_format(const char *format, va_list args)
{
	int	format_len;
	t_data *data;
	int	 i;

	i = 0;

	format_len = 0;
	while (format[i] != '\0')
	{
		if (format[i] != '%' && format[i])
			format_len += print_regular(format, &i);
		else if (format[i])
		{
			data = create_t_data();
			if (!data)
				return (-1);
			//check if there are further symbols (cspdiouxXfyb%#-+ .*0123456789hLljz)?
			if (!ft_strchr("cspdiouxXfyb%#-+ .*0123456789hLljz", format[i + 1])) //another function is valid_type_flag etc.
				break ; // which loop does this break from? is it okay? or return (-1)?
			get_argument(format, &i, data);
			format_len += print_argument(args, data);
			// printf("%s !arg!%s\n", RED, RESET);
			free_t_data(data);
		}
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

	if (format == NULL)
		return (0);
	//WHERE MAGIC HAPPENS
	//handle variadic-macro initilisation & print everything
	va_start(args, format);
	format_len = 0;
	format_len += parse_format(format, args);
	//the very end (add free's if there are any)
	va_end(args);
	return(format_len);
}

int main(void)
{
	int	ptr;
	unsigned char c = 0x7f;

	ptr = 8;

	//my func
	printf("\n%s--ft func--%s\n\n", RED, RESET);
	ft_printf("\nreturn value = %d", ft_printf("Regular argument\n\n%c \n%.4s \n%p \n%.8d \n|%-9.06u| \n%.0d \n%X", 'X', "mahmut", &ptr, -1223, 999, 0, c));
	ft_printf("\n");

	// ft_printf("%.6u", 999);

	//lib func
	printf("\n%s--library func--%s\n\n", RED, RESET);
	printf(  "\nreturn value = %d\n", printf("Regular argument\n\n%-c \n%.4s \n%p \n%.8d \n|%9.06u| \n%.0d \n%X", 'X', "mahmut", &ptr, -1223, 999, 0, c));
	return (0);
}

// int main(void)
// {
// 	int				di = 28;
// 	printf("\n%s/////////////////////////////////////////////////////////////////////////////////////////////////////%s\n\n", YELLOW, RESET);
// 	printf("%sHandling precision%s (controls the max number of characters to print)\n", PURPLE, RESET);
// 	printf("%sA dot (.) followed by a number > %%.5d or %%.02d\n\n%s", GREEN, RESET);

// 	printf(" (%d)\n", printf("(0) P. 0: |%.0i|", 0));
// 	ft_printf(" (%d)\n", ft_printf("(0) P. 0: |%.0i|", 0));
// 	printf(" (%d)\n", printf("(0) P. 1: |%.1i|", 0));
// 	ft_printf(" (%d)\n", ft_printf("(0) P. 1: |%.1i|", 0));
// 	printf(" (%d)\n", printf("(0) P. 2: |%.2i|", 0));
// 	ft_printf(" (%d)\n", ft_printf("(0) P. 2: |%.2i|", 0));
// 	printf(" (%d)\n", printf("P. 0: |%.0i|", di));
// 	ft_printf(" (%d)\n", ft_printf("P. 0: |%.0i|", di));
// 	printf(" (%d)\n", printf("P. 1: |%.1i|", di));
// 	ft_printf(" (%d)\n", ft_printf("P. 1: |%.1i|", di));
// 	printf(" (%d)\n", printf("P. 2: |%.2i|", di));
// 	ft_printf(" (%d)\n", ft_printf("P. 2: |%.2i|", di));
// 	printf(" (%d)\n", printf("P. 3: |%.3i|", di));
// 	ft_printf(" (%d)\n", ft_printf("P. 3: |%.3i|", di));
// 	printf(" (%d)\n", printf("P. 4: |%.4i|", di));
// 	ft_printf(" (%d)\n", ft_printf("P. 4: |%.4i|", di));
// 	printf(" (%d)\n", printf("P. 5: |%.5i|", di));
// 	ft_printf(" (%d)\n", ft_printf("P. 5: |%.5i|", di));
// 	printf(" (%d)\n", printf("P. 10: |%.10i|", di));
// 	ft_printf(" (%d)\n", ft_printf("P. 10: |%.10i|", di));
// 	printf(" (%d)\n", printf("P. 15: |%.15i|", di));
// 	ft_printf(" (%d)\n", ft_printf("P. 15: |%.15i|", di));
// 	printf(" (%d)\n", printf("P. 42: |%.42i|", di));
// 	ft_printf(" (%d)\n", ft_printf("P. 42: |%.42i|", di));

// 	printf("\n");
// 	printf(" (%d)\n", printf("(0) P .00: |%.00i|", 0));
// 	ft_printf(" (%d)\n", ft_printf("(0) P .00: |%.00i|", 0));
// 	printf(" (%d)\n", printf("(0) P .01: |%.01i|", 0));
// 	ft_printf(" (%d)\n", ft_printf("(0) P .01: |%.01i|", 0));
// 	printf(" (%d)\n", printf("P .00: |%.00i|", di));
// 	ft_printf(" (%d)\n", ft_printf("P .00: |%.00i|", di));
// 	printf(" (%d)\n", printf("P .01: |%.01i|", di));
// 	ft_printf(" (%d)\n", ft_printf("P .01: |%.01i|", di));
// 	printf(" (%d)\n", printf("P .02: |%.02i|", di));
// 	ft_printf(" (%d)\n", ft_printf("P .02: |%.02i|", di));
// 	printf(" (%d)\n", printf("P .03: |%.03i|", di));
// 	ft_printf(" (%d)\n", ft_printf("P .03: |%.03i|", di));
// 	printf(" (%d)\n", printf("P .04: |%.04i|", di));
// 	ft_printf(" (%d)\n", ft_printf("P .04: |%.04i|", di));
// 	printf(" (%d)\n", printf("P .05: |%.05i|", di));
// 	ft_printf(" (%d)\n", ft_printf("P .05: |%.05i|", di));
// 	printf(" (%d)\n", printf("P .010: |%.010i|", di));
// 	ft_printf(" (%d)\n", ft_printf("P .010: |%.010i|", di));
// 	printf(" (%d)\n", printf("P .015: |%.015i|", di));
// 	ft_printf(" (%d)\n", ft_printf("P .015: |%.015i|", di));
// 	printf(" (%d)\n", printf("P .042: |%.042i|", di));
// 	ft_printf(" (%d)\n", ft_printf("P .042: |%.042i|", di));

// 	printf(" (%d)\n", printf("P .007: |%.007i|", di));
// 	ft_printf(" (%d)\n", ft_printf("P .007: |%.007i|", di));
// 	printf(" (%d)\n", printf("P .000000000007: |%.000000000007i|", di));
// 	ft_printf(" (%d)\n", ft_printf("P .000000000007: |%.000000000007i|", di));




// 	return (0);
// }
