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
	char				type;
	char				*flag;
	char				*width;
	char				*precision;
	int					error;
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
	data->error = 0;
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

void get_argument_info(const char *format, int *i, t_data *data)
{
	//not sure about where i is pointing at!
	*i = *i + 1;
	while (ft_strchr("cspdiuxX%-.*0123456789", format[*i]))
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

int print_nullchar(char *to_print, int width, char alignment)
{
	int tmp_width;

	tmp_width = width;
	free(to_print);
	if (alignment == 'L')
	{
		ft_putchar_fd(0, 1);
		while (width - 1 > 0)
		{
			ft_putchar_fd(' ', 1);
			width--;
		}
	}
	if (alignment == 'R')
	{
		while (width - 1 > 0)
		{
			ft_putchar_fd(' ', 1);
			width--;
		}
		ft_putchar_fd(0, 1);
	}
	if (tmp_width == 0)
		return (1);
	return (tmp_width);
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
	get_wildcard_arg(data, args);
	to_print = handle_argument(args, data, to_print);
	to_print = adjust_precision(data, to_print);
	apply_flag(data, &width, &alignment, &filler);
	if (data->type == 'c' && *to_print == '\0')
		return (print_nullchar(to_print, width, alignment));
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
			if (!ft_strchr("cspdiuxX%-.*0123456789", format[i + 1])) //another function is valid_type_flag etc.
				break ; // which loop does this break from? is it okay? or return (-1)?
			get_argument_info(format, &i, data);
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
	int	di;
	// unsigned char c = 0x7f;

	di = 28;
	//WILDCARD

	// printf(" (%d)\n", printf("Handling wildcards"));
	// ft_printf(" (%d)\n", ft_printf("Handling wildcards"));

	// printf(" (%d)\n", printf("Mfw *1: |%*i|", 1, di));
	// ft_printf(" (%d)\n", ft_printf("Mfw *1: |%*i|", 1, di));
	// printf(" (%d)\n", printf("Mfw *5: |%*i|", 5, di));
	// ft_printf(" (%d)\n", ft_printf("Mfw *5: |%*i|", 5, di));
	// printf(" (%d)\n", printf("Mfw *5: |%*i|",5, di));
	// ft_printf(" (%d)\n", ft_printf("Mfw *5: |%*i|", 5, di));
	// printf(" (%d)\n", printf("Mfw *5: |%*i|",        5, di));
	// ft_printf(" (%d)\n", ft_printf("Mfw *5: |%*i|",        5, di));
	// printf(" (%d)\n", printf("Mfw *10: |%*i|", 10, di));
	// ft_printf(" (%d)\n", ft_printf("Mfw *10: |%*i|", 10, di));
	// printf(" (%d)\n", printf("Mfw *i: |%*i|", di, di));
	// ft_printf(" (%d)\n", ft_printf("Mfw *i: |%*i|", di, di));
	// printf(" (%d)\n", printf("Mfw **5: |%*.*i|", 5, 6, di));
	// ft_printf(" (%d)\n", ft_printf("Mfw **5: |%*.*i|", 5, 6, di));
	// printf("\n");

	//negative *
	// ft_printf("|%*i|\n", -5, di); //DONE
	// printf(" (%d)\n", printf("|%c|", 0));
	// ft_printf(" (%d)\n",ft_printf("|%c|", 0));
	//printf(" (%d)\n", printf("|%5c|", -0));
	//ft_printf(" (%d)\n",ft_printf("|%5c|", -0));
	printf(" (%d)\n", printf("|%5c|", 0));
	ft_printf(" (%d)\n",ft_printf("|%5c|", 0));


	// STRINGS
	// printf("%.7s\n", "hello");
	// ft_printf("%.7s\n", "hello");
	// printf(" (%d)\n", printf("%.09s", NULL));
	// ft_printf(" (%d)\n", ft_printf("%.09s", NULL));
	// printf(" (%d)\n", printf("%.00s", ""));
	// ft_printf(" (%d)\n", ft_printf("%.00s", ""));
	// printf(" (%d)\n", printf("%.01s", ""));
	// ft_printf(" (%d)\n", ft_printf("%.01s", ""));
	// printf(" (%d)\n", printf("%.03s", ""));
	// ft_printf(" (%d)\n", ft_printf("%.03s", ""));
	// printf(" (%d)\n", printf("%1.s", ""));
	// ft_printf(" (%d)\n", ft_printf("%1.s", ""));
	// printf(" (%d)\n", printf("%9.s", ""));
	// ft_printf(" (%d)\n", ft_printf("%9.s", ""));
	// printf(" (%d)\n", printf("%.*s", -1, (char *)0));
	// ft_printf(" (%d)\n", ft_printf("%.*s", -1, (char *)0));
	// printf(" (%d)\n", printf("%.*s", -3, (char *)0));
	// ft_printf(" (%d)\n", ft_printf("%.*s", -3, (char *)0));


	//NEGATIVE *PRECISION
	// printf(" (%d)\n", printf("%*s", -3, "hello"));
	// ft_printf(" (%d)\n", ft_printf("%*s", -3, "hello"));
	// printf(" (%d)\n", printf("%.*s", -3, "hello"));
	// ft_printf(" (%d)\n", ft_printf("%.*s", -3, "hello"));
	// printf(" (%d)\n", printf("%*i", -4, 94827));
	// ft_printf(" (%d)\n", ft_printf("%*i", -4, 94827));
	// printf(" (%d)\n", printf("%*i", -14, 94827));
	// ft_printf(" (%d)\n", ft_printf("%*i", -14, 94827));

	//CHARS
	// printf("%c", 0);
	// ft_printf(" (%d)\n", ft_printf("%c", '\0'));
	// printf(" (%d)\n", printf("%5c", '\0'));
	// ft_printf(" (%d)\n", ft_printf("%5c", '\0'));
	// printf(" (%d)\n", printf("%-5c", '\0'));
	// ft_printf(" (%d)\n", ft_printf("%-5c", '\0'));


	// printf(" (%d)\n", printf("%% *.5i 42 == |% *.5i|", 4, 42));
	// ft_printf(" (%d)\n", ft_printf("%% *.5i 42 == |% *.5i|", 4, 42));

	//my func
	// printf("\n%s--ft func--%s\n\n", RED, RESET);
	// ft_printf("\nreturn value = %d", ft_printf("Regular argument\n\n%c \n%.4s \n%p \n%*.8d \n|%-9.06u| \n%.0d \n%X", 'X', "mahmut", &di, 10, -1223, 999, 0, c));
	// ft_printf("\n");

	//lib func
	// printf("\n%s--library func--%s\n\n", RED, RESET);
	// printf(  "\nreturn value = %d\n", printf("Regular argument\n\n%-c \n%.4s \n%p \n%.8d \n|%-9.06u| \n%.0d \n%X", 'X', "mahmut", &ptr, -1223, 999, 0, c));
	return (0);
}

// int main(void)
// {
// 	int				ndi;
// 	ndi = -28;

// 	int broken;
// 	int	bonus;

// 	char			c = 'F';
// 	char			*s = "my string example";
// 	int				di = 28;
// 	int				*p = &di;
// 	unsigned int	u = 42;
// 	unsigned int	xcap = 185334478;
// 	unsigned int	x = 185334478;

// 	broken = 0;
// 	bonus = 0;

// 	printf("%sBEGINNING OF COMPARISON TESTS\n\n\n%s", RED, RESET);
// 	printf("%sBLUE IS LIBRARY PRINTF TESTS\n%s", BLUE, RESET);
// 	ft_printf("%sGREEN IS MY FT_PRINTF TESTS\n\n%s", GREEN, RESET);

// 	printf("%s --- Basics --- \n\n%s", RED, RESET);
// 	printf(" (%d)\n", printf("%s|Regular input without arguments|%s", BLUE, RESET));
// 	ft_printf(" (%d)\n\n", ft_printf("%s|Regular input without arguments|%s", GREEN, RESET));

// 	printf(" (%d)\n", printf("%sa single character: |%c|%s", BLUE, c, RESET));
// 	ft_printf(" (%d)\n\n", ft_printf("%sa single character: |%c|%s", GREEN, c, RESET));

// 	printf(" (%d)\n", printf("%sa string: |%s|%s", BLUE, s, RESET));
// 	ft_printf(" (%d)\n\n", ft_printf("%sa string: |%s|%s", GREEN, s, RESET));

// 	printf(" (%d)\n", printf("%sa decimal: |%d|%s", BLUE, di, RESET));
// 	ft_printf(" (%d)\n\n", ft_printf("%sa decimal: |%d|%s", GREEN, di, RESET));

// 	printf(" (%d)\n", printf("%san integer: |%i|%s", BLUE, di, RESET));
// 	ft_printf(" (%d)\n\n", ft_printf("%san integer: |%i|%s", GREEN, di, RESET));

// 	printf(" (%d)\n", printf("%sa zero integer: |%i|%s", BLUE, 0, RESET));
// 	ft_printf(" (%d)\n\n", ft_printf("%sa zero integer: |%i|%s", GREEN, 0, RESET));

// 	printf(" (%d)\n", printf("%sa pointer: |%p|%s", BLUE, &di, RESET));
// 	ft_printf(" (%d)\n\n", ft_printf("%sa pointer: |%p|%s", GREEN, &di, RESET));

// 	printf(" (%d)\n", printf("%san unsignted int |%u|%s", BLUE, u, RESET));
// 	ft_printf(" (%d)\n\n", ft_printf("%san unsignted int |%u|%s", GREEN, u, RESET));

// 	printf(" (%d)\n", printf("%sA HEXADECIMAL |%X|%s", BLUE, xcap, RESET));
// 	ft_printf(" (%d)\n\n", ft_printf("%sA HEXADECIMAL |%X|%s", GREEN, xcap, RESET));

// 	printf(" (%d)\n", printf("%sa hexadecimal |%x|%s", BLUE, x, RESET));
// 	ft_printf(" (%d)\n\n", ft_printf("%sa hexadecimal |%x|%s", GREEN, x, RESET));

// 	printf(" (%d)\n", printf("%sAll types at once: |%c %s %p %d %i %u %x %X|%s", BLUE, c, s, p, di, di, u, x, x, RESET));
// 	ft_printf(" (%d)\n\n", ft_printf("%sAll types at once: |%c %s %p %d %i %u %x %X|%s", GREEN, c, s, p, di, di, u, x, x, RESET));

// 	// %% //
// 	printf(" (%d)\n", printf("%s%% x 2 > double percentage sign: |%%|%s", BLUE, RESET));
// 	ft_printf(" (%d)\n\n", ft_printf("%s%% x 2 > double percentage sign: |%%|%s", GREEN, RESET));

// 	printf(" (%d)\n", printf("%s|%s|%s", BLUE, "a percentage sign % in a string?", RESET));
// 	ft_printf(" (%d)\n\n", ft_printf("%s|%s|%s", GREEN, "a percentage sign % in a string?", RESET));

// 	printf(" (%d)\n", printf("Type conversion specifiers inside string: %s|%s|%s", BLUE, "%c, %s, %p, %d, %i, %u, %x, %X, %%", RESET));
// 	ft_printf(" (%d)\n\n", ft_printf("Type conversion specifiers inside string: %s|%s|%s", GREEN, "%c, %s, %p, %d, %i, %u, %x, %X, %%", RESET));

// 	printf("\n%s/////////////////////////////////////////////////////////////////////////////////////////////////////%s\n\n", YELLOW, RESET);

// 	// MIN - MAX
// 	printf("%sMIN & MAX values%s\n\n", RED, RESET);

// 	printf(" (%d)\n", printf("%sChar: |%c|%s", BLUE, '%', RESET));
// 	ft_printf(" (%d)\n\n", ft_printf("%sChar: |%c|%s", GREEN, '%', RESET));

// 	printf(" (%d)\n", printf("%sMAX Decimal: |%d|%s", BLUE, 2147483647, RESET));
// 	ft_printf(" (%d)\n\n", ft_printf("%sMAX Decimal: |%d|%s", GREEN, 2147483647, RESET));

// 	printf(" (%d)\n", printf("%sMIN Decimal: |%d|%s", BLUE, ((int)(-2147483648)), RESET));
// 	ft_printf(" (%d)\n\n", ft_printf("%sMIN Decimal: |%d|%s", GREEN, ((int)(-2147483648)), RESET));

// 	printf(" (%d)\n", printf("%sMAX Integer: |%i|%s", BLUE, 2147483647, RESET));
// 	ft_printf(" (%d)\n\n", ft_printf("%sMAX Integer: |%i|%s", GREEN, 2147483647, RESET));

// 	printf(" (%d)\n", printf("%sMIN Integer: |%i|%s", BLUE, ((int)(-2147483648)), RESET));
// 	ft_printf(" (%d)\n\n", ft_printf("%sMIN Integer: |%i|%s", GREEN, ((int)(-2147483648)), RESET));

// 	printf(" (%d)\n", printf("%sMAX Unsignted int |%u|%s", BLUE, (unsigned int)4294967295, RESET));
// 	ft_printf(" (%d)\n\n", ft_printf("%sMAX Unsignted int |%u|%s", GREEN, (unsigned int)4294967295, RESET));

// 	printf(" (%d)\n", printf("%sMAX INT AS HEXADECIMAL |%X|%s", BLUE, 2147483647, RESET));
// 	ft_printf(" (%d)\n\n", ft_printf("%sMAX INT AS HEXADECIMAL |%X|%s", GREEN, 2147483647, RESET));

// 	printf(" (%d)\n", printf("%sMAX HEXADECIMAL |%X|%s", BLUE, ((unsigned int)(4294967295)), RESET));
// 	ft_printf(" (%d)\n\n", ft_printf("%sMAX HEXADECIMAL |%X|%s", GREEN, ((unsigned int)(4294967295)), RESET));

// 	printf(" (%d)\n", printf("%sHEXadecimal with negative number |%X|%s", BLUE, -42, RESET));
// 	ft_printf(" (%d)\n\n", ft_printf("%sHEXadecimal with negative number |%X|%s", GREEN, -42, RESET));

// 	printf(" (%d)\n", printf("%sHexadecimal with negative number |%x|%s", BLUE, -42, RESET));
// 	ft_printf(" (%d)\n\n", ft_printf("%sHexadecimal with negative number |%x|%s", GREEN, -42, RESET));

// 	printf(" (%d)\n", printf("%sMAX int as hex |%x|%s", BLUE, 2147483647, RESET));
// 	ft_printf(" (%d)\n\n", ft_printf("%sMAX int as hex |%x|%s", GREEN, 2147483647, RESET));

// 	printf(" (%d)\n", printf("%sMAX hex |%x|%s", BLUE, ((unsigned int)(4294967295)), RESET));
// 	ft_printf(" (%d)\n\n", ft_printf("%sMAX hex |%x|%s", GREEN, ((unsigned int)(4294967295)), RESET));

// 	// MIN - 1 & MAX + 1 values
// 	printf("%sMIN - 1 & MAX + 1 values%s\n\n", RED, RESET);

// 	printf(" (%d)\n", printf("%sChar: |%c|%s", BLUE, ('%' + 1), RESET));
// 	ft_printf(" (%d)\n\n", ft_printf("%sChar: |%c|%s", GREEN, ('%' + 1), RESET));

// 	printf(" (%d)\n", printf("%sMAX Decimal: |%d|%s", BLUE, (2147483647 + 1), RESET));
// 	ft_printf(" (%d)\n\n", ft_printf("%sMAX Decimal: |%d|%s", GREEN, (2147483647 + 1), RESET));

// 	printf(" (%d)\n", printf("%sMIN Decimal: |%d|%s", BLUE, (((int)(-2147483648))- 1), RESET));
// 	ft_printf(" (%d)\n\n", ft_printf("%sMIN Decimal: |%d|%s", GREEN, (((int)(-2147483648))- 1), RESET));

// 	printf(" (%d)\n", printf("%sMAX Integer: |%i|%s", BLUE, (2147483647 + 1), RESET));
// 	ft_printf(" (%d)\n\n", ft_printf("%sMAX Integer: |%i|%s", GREEN, (2147483647 + 1), RESET));

// 	printf(" (%d)\n", printf("%sMIN Integer: |%i|%s", BLUE, (((int)(-2147483648))- 1), RESET));
// 	ft_printf(" (%d)\n\n", ft_printf("%sMIN Integer: |%i|%s", GREEN, (((int)(-2147483648))- 1), RESET));

// 	//why are the results 0 for hex + 1's?
// 	printf(" (%d)\n", printf("%sMAX HEX |%X|%s", BLUE, (((unsigned int)(4294967295)) + 1), RESET));
// 	ft_printf(" (%d)\n\n", ft_printf("%sMAX HEX |%X|%s", GREEN, (((unsigned int)(4294967295)) + 1), RESET));

// 	printf(" (%d)\n", printf("%sMAX hex |%x|%s", BLUE, (((unsigned int)(4294967295)) + 1), RESET));
// 	ft_printf(" (%d)\n\n", ft_printf("%sMAX hex |%x|%s", GREEN, (((unsigned int)(4294967295)) + 1), RESET));

// 	// width with integer
// 	printf("\n%s/////////////////////////////////////////////////////////////////////////////////////////////////////%s\n\n", YELLOW, RESET);
// 	printf("%sMINIMUM FIELD WIDTH %s (controls the min number of characters to print)\n", RED, RESET);
// 	printf("%s%%5d or %%23d = A number follows flags or percentage sign\n\n%s", PURPLE, RESET);


// 	printf(" (%d)\n", printf("%s(0) Mfw 0: |%0i|%s", BLUE, 0, RESET));
// 	ft_printf(" (%d)\n", ft_printf("%s(0) Mfw 0: |%0i|%s", GREEN, 0, RESET));
// 	printf(" (%d)\n", printf("%s(0) Mfw 1: |%1i|%s", BLUE, 0, RESET));
// 	ft_printf(" (%d)\n", ft_printf("%s(0) Mfw 1: |%1i|%s", GREEN, 0, RESET));
// 	printf(" (%d)\n", printf("Mfw 0: |%0i|", ndi));
// 	ft_printf(" (%d)\n", ft_printf("Mfw 0: |%0i|", ndi));
// 	printf(" (%d)\n", printf("Mfw 1: |%1i|", ndi));
// 	ft_printf(" (%d)\n", ft_printf("Mfw 1: |%1i|", ndi));
// 	printf(" (%d)\n", printf("Mfw 2: |%2i|", ndi));
// 	ft_printf(" (%d)\n", ft_printf("Mfw 2: |%2i|", ndi));
// 	printf(" (%d)\n", printf("Mfw 3: |%3i|", ndi));
// 	ft_printf(" (%d)\n", ft_printf("Mfw 3: |%3i|", ndi));
// 	printf(" (%d)\n", printf("Mfw 4: |%4i|", ndi));
// 	ft_printf(" (%d)\n", ft_printf("Mfw 4: |%4i|", ndi));
// 	printf(" (%d)\n", printf("Mfw 5: |%5i|", ndi));
// 	ft_printf(" (%d)\n", ft_printf("Mfw 5: |%5i|", ndi));
// 	printf(" (%d)\n", printf("Mfw 10: |%10i|", ndi));
// 	ft_printf(" (%d)\n", ft_printf("Mfw 10: |%10i|", ndi));
// 	printf(" (%d)\n", printf("Mfw 35: |%35i|", ndi));
// 	ft_printf(" (%d)\n", ft_printf("Mfw 35: |%35i|", ndi));

// 	// precision
// 	printf("\n%s/////////////////////////////////////////////////////////////////////////////////////////////////////%s\n\n", YELLOW, RESET);
// 	printf("%sPRECISION%s (controls the max number of characters to print)\n", RED, RESET);
// 	printf("%s%%.5d or %%.02d = A dot (.) followed by a number\n\n%s", GREEN, RESET);

// 	printf(" (%d)\n", printf("(0) P. 0: |%.0i|", 0));
// 	ft_printf(" (%d)\n", ft_printf("(0) P. 0: |%.0i|", 0));
// 	printf(" (%d)\n", printf("(0) P. 1: |%.1i|", 0));
// 	ft_printf(" (%d)\n", ft_printf("(0) P. 1: |%.1i|", 0));
// 	printf(" (%d)\n", printf("(0) P. 2: |%.2i|", 0));
// 	ft_printf(" (%d)\n", ft_printf("(0) P. 2: |%.2i|", 0));
// 	printf(" (%d)\n", printf("P. 0: |%.0i|", ndi));
// 	ft_printf(" (%d)\n", ft_printf("P. 0: |%.0i|", ndi));
// 	printf(" (%d)\n", printf("P. 1: |%.1i|", ndi));
// 	ft_printf(" (%d)\n", ft_printf("P. 1: |%.1i|", ndi));
// 	printf(" (%d)\n", printf("P. 2: |%.2i|", ndi));
// 	ft_printf(" (%d)\n", ft_printf("P. 2: |%.2i|", ndi));
// 	printf(" (%d)\n", printf("P. 3: |%.3i|", ndi));
// 	ft_printf(" (%d)\n", ft_printf("P. 3: |%.3i|", ndi));
// 	printf(" (%d)\n", printf("P. 4: |%.4i|", ndi));
// 	ft_printf(" (%d)\n", ft_printf("P. 4: |%.4i|", ndi));
// 	printf(" (%d)\n", printf("P. 5: |%.5i|", ndi));
// 	ft_printf(" (%d)\n", ft_printf("P. 5: |%.5i|", ndi));
// 	printf(" (%d)\n", printf("P. 10: |%.10i|", ndi));
// 	ft_printf(" (%d)\n", ft_printf("P. 10: |%.10i|", ndi));
// 	printf(" (%d)\n", printf("P. 15: |%.15i|", ndi));
// 	ft_printf(" (%d)\n", ft_printf("P. 15: |%.15i|", ndi));
// 	printf(" (%d)\n", printf("P. 42: |%.42i|", ndi));
// 	ft_printf(" (%d)\n", ft_printf("P. 42: |%.42i|", ndi));

// 	printf("\n");
// 	printf(" (%d)\n", printf("(0) P .00: |%.00i|", 0));
// 	ft_printf(" (%d)\n", ft_printf("(0) P .00: |%.00i|", 0));
// 	printf(" (%d)\n", printf("(0) P .01: |%.01i|", 0));
// 	ft_printf(" (%d)\n", ft_printf("(0) P .01: |%.01i|", 0));
// 	printf(" (%d)\n", printf("P .00: |%.00i|", ndi));
// 	ft_printf(" (%d)\n", ft_printf("P .00: |%.00i|", ndi));
// 	printf(" (%d)\n", printf("P .01: |%.01i|", ndi));
// 	ft_printf(" (%d)\n", ft_printf("P .01: |%.01i|", ndi));
// 	printf(" (%d)\n", printf("P .02: |%.02i|", ndi));
// 	ft_printf(" (%d)\n", ft_printf("P .02: |%.02i|", ndi));
// 	printf(" (%d)\n", printf("P .03: |%.03i|", ndi));
// 	ft_printf(" (%d)\n", ft_printf("P .03: |%.03i|", ndi));
// 	printf(" (%d)\n", printf("P .04: |%.04i|", ndi));
// 	ft_printf(" (%d)\n", ft_printf("P .04: |%.04i|", ndi));
// 	printf(" (%d)\n", printf("P .05: |%.05i|", ndi));
// 	ft_printf(" (%d)\n", ft_printf("P .05: |%.05i|", ndi));
// 	printf(" (%d)\n", printf("P .010: |%.010i|", ndi));
// 	ft_printf(" (%d)\n", ft_printf("P .010: |%.010i|", ndi));
// 	printf(" (%d)\n", printf("P .015: |%.015i|", ndi));
// 	ft_printf(" (%d)\n", ft_printf("P .015: |%.015i|", ndi));
// 	printf(" (%d)\n", printf("P .042: |%.042i|", ndi));
// 	ft_printf(" (%d)\n", ft_printf("P .042: |%.042i|", ndi));

// 	printf(" (%d)\n", printf("P .007: |%.007i|", ndi));
// 	ft_printf(" (%d)\n", ft_printf("P .007: |%.007i|", ndi));
// 	printf(" (%d)\n", printf("P .000000000007: |%.000000000007i|", ndi));
// 	ft_printf(" (%d)\n", ft_printf("P .000000000007: |%.000000000007i|", ndi));

// 	printf("\n%s/////////////////////////////////////////////////////////////////////////////////////////////////////%s\n\n", YELLOW, RESET);
// 	printf("%sPRECISION & MINIMUM FIELD WIDTH%s\n", RED, RESET);
// 	printf("%s%%10.5d or %%3.2d = Numbers followwed by a dot (.) followed by a number\n\n%s", GREEN, RESET);

// 	printf(" (%d)\n", printf("(0) 0.0: |%0.0i|", 0));
// 	ft_printf(" (%d)\n", ft_printf("(0) 0.0: |%0.0i|", 0));
// 	printf(" (%d)\n", printf("(0) 1.0: |%1.0i|", 0));
// 	ft_printf(" (%d)\n", ft_printf("(0) 1.0: |%1.0i|", 0));
// 	printf(" (%d)\n", printf("(10) 1.0: |%1.0i|", 10));
// 	ft_printf(" (%d)\n", ft_printf("(10) 1.0: |%1.0i|", 10));
// 	printf(" (%d)\n", printf("(0) 0.1: |%0.1i|", 0));
// 	ft_printf(" (%d)\n", ft_printf("(0) 0.1: |%0.1i|", 0));
// 	printf(" (%d)\n", printf("(0) 1.1: |%1.1i|", 0));
// 	ft_printf(" (%d)\n", ft_printf("(0) 1.1: |%1.1i|", 0));
// 	printf(" (%d)\n", printf("0.0: |%0.0i|", ndi));
// 	ft_printf(" (%d)\n", ft_printf("0.0: |%0.0i|", ndi));
// 	printf(" (%d)\n", printf("1.1: |%1.1i|", ndi));
// 	ft_printf(" (%d)\n", ft_printf("1.1: |%1.1i|", ndi));
// 	printf(" (%d)\n", printf("2.2: |%2.2i|", ndi));
// 	ft_printf(" (%d)\n", ft_printf("2.2: |%2.2i|", ndi));
// 	printf(" (%d)\n", printf("3.2: |%3.2i|", ndi));
// 	ft_printf(" (%d)\n", ft_printf("3.2: |%3.2i|", ndi));
// 	printf(" (%d)\n", printf("2.3: |%2.3i|", ndi));
// 	ft_printf(" (%d)\n", ft_printf("2.3: |%2.3i|", ndi));
// 	printf(" (%d)\n", printf("8.4: |%8.4i|", ndi));
// 	ft_printf(" (%d)\n", ft_printf("8.4: |%8.4i|", ndi));
// 	printf(" (%d)\n", printf("4.8: |%4.8i|", ndi));
// 	ft_printf(" (%d)\n", ft_printf("4.8: |%4.8i|", ndi));
// 	printf(" (%d)\n", printf("8.8: |%8.8i|", ndi));
// 	ft_printf(" (%d)\n", ft_printf("8.8: |%8.8i|", ndi));
// 	printf(" (%d)\n", printf("8.2: |%8.2i|", ndi));
// 	ft_printf(" (%d)\n", ft_printf("8.2: |%8.2i|", ndi));
// 	printf(" (%d)\n", printf("2.8: |%2.8i|", ndi));
// 	ft_printf(" (%d)\n", ft_printf("2.8: |%2.8i|", ndi));
// 	printf(" (%d)\n", printf("8.1: |%8.1i|", ndi));
// 	ft_printf(" (%d)\n", ft_printf("8.1: |%8.1i|", ndi));
// 	printf(" (%d)\n", printf("1.8: |%1.8i|", ndi));
// 	ft_printf(" (%d)\n", ft_printf("1.8: |%1.8i|", ndi));

// 	printf("\n%s/////////////////////////////////////////////////////////////////////////////////////////////////////%s\n\n", YELLOW, RESET);
// 	printf("%s(0) flag & & MFW & PRECISION %s\n", RED, RESET);
// 	printf("0 > Left-pads the number with zeroes (0) instead of spaces when padding is specified\n");
// 	printf("%s%%010.5d or %%03.2d = 0 followed by numbers & a dot+a number\n\n%s", GREEN, RESET);

// 	printf(" (%d)\n", printf("(0) 00.0: |%00.0i|", 0));
// 	ft_printf(" (%d)\n", ft_printf("(0) 00.0: |%00.0i|", 0));
// 	printf(" (%d)\n", printf("(0) 01.0: |%01.0i|", 0));
// 	ft_printf(" (%d)\n", ft_printf("(0) 01.0: |%01.0i|", 0));
// 	printf(" (%d)\n", printf("(0) 00.1: |%00.1i|", 0));
// 	ft_printf(" (%d)\n", ft_printf("(0) 00.1: |%00.1i|", 0));
// 	printf(" (%d)\n", printf("01.1: |%01.1i|", ndi));
// 	ft_printf(" (%d)\n", ft_printf("01.1: |%01.1i|", ndi));
// 	printf(" (%d)\n", printf("02.2: |%02.2i|", ndi));
// 	ft_printf(" (%d)\n", ft_printf("02.2: |%02.2i|", ndi));
// 	printf(" (%d)\n", printf("03.2: |%03.2i|", ndi));
// 	ft_printf(" (%d)\n", ft_printf("03.2: |%03.2i|", ndi));
// 	printf(" (%d)\n", printf("02.3: |%02.3i|", ndi));
// 	ft_printf(" (%d)\n", ft_printf("02.3: |%02.3i|", ndi));
// 	printf(" (%d)\n", printf("08.4: |%08.4i|", ndi));
// 	ft_printf(" (%d)\n", ft_printf("08.4: |%08.4i|", ndi));
// 	printf(" (%d)\n", printf("04.8: |%04.8i|", ndi));
// 	ft_printf(" (%d)\n", ft_printf("04.8: |%04.8i|", ndi));
// 	printf(" (%d)\n", printf("08.8: |%08.8i|", ndi));
// 	ft_printf(" (%d)\n", ft_printf("08.8: |%08.8i|", ndi));
// 	printf(" (%d)\n", printf("08.2: |%08.2i|", ndi));
// 	ft_printf(" (%d)\n", ft_printf("08.2: |%08.2i|", ndi));
// 	printf(" (%d)\n", printf("02.8: |%02.8i|", ndi));
// 	ft_printf(" (%d)\n", ft_printf("02.8: |%02.8i|", ndi));
// 	printf(" (%d)\n", printf("08.1: |%08.1i|", ndi));
// 	ft_printf(" (%d)\n", ft_printf("08.1: |%08.1i|", ndi));
// 	printf(" (%d)\n", printf("01.8: |%01.8i|", ndi));
// 	ft_printf(" (%d)\n", ft_printf("01.8: |%01.8i|", ndi));


// 	printf("\n%s/////////////////////////////////////////////////////////////////////////////////////////////////////%s\n\n", YELLOW, RESET);
// 	printf("%sMFW & (0) flag%s\n", RED, RESET);
// 	printf("0 > Left-pads the number with zeroes (0) instead of spaces when padding is specified\n");
// 	printf("%s%%010d or %%03d=0 followed by numbers\n\n%s", GREEN, RESET);

// 	printf(" (%d)\n", printf("(0) 0: |%0i|", 0));
// 	ft_printf(" (%d)\n", ft_printf("(0) 0: |%0i|", 0));
// 	printf(" (%d)\n", printf("(0) 00: |%00i|", 0));
// 	ft_printf(" (%d)\n", ft_printf("(0) 00: |%00i|", 0));
// 	printf(" (%d)\n", printf("(0) 01: |%01i|", 0));
// 	ft_printf(" (%d)\n", ft_printf("(0) 01: |%01i|", 0));
// 	printf(" (%d)\n", printf("(0) 02: |%02i|", 0));
// 	ft_printf(" (%d)\n", ft_printf("(0) 02: |%02i|", 0));
// 	printf(" (%d)\n", printf("0: |%0i|", ndi));
// 	ft_printf(" (%d)\n", ft_printf("0: |%0i|", ndi));
// 	printf(" (%d)\n", printf("00: |%00i|", ndi));
// 	ft_printf(" (%d)\n", ft_printf("00: |%00i|", ndi));
// 	printf(" (%d)\n", printf("01: |%01i|", ndi));
// 	ft_printf(" (%d)\n", ft_printf("01: |%01i|", ndi));
// 	printf(" (%d)\n", printf("02: |%02i|", ndi));
// 	ft_printf(" (%d)\n", ft_printf("02: |%02i|", ndi));
// 	printf(" (%d)\n", printf("03: |%03i|", ndi));
// 	ft_printf(" (%d)\n", ft_printf("03: |%03i|", ndi));
// 	printf(" (%d)\n", printf("08: |%08i|", ndi));
// 	ft_printf(" (%d)\n", ft_printf("08: |%08i|", ndi));
// 	printf(" (%d)\n", printf("000000000008: |%000000000008i|", ndi));
// 	ft_printf(" (%d)\n", ft_printf("000000000008: |%000000000008i|", ndi));
// 	printf(" (%d)\n", printf("010: |%010i|", ndi));
// 	ft_printf(" (%d)\n", ft_printf("010: |%010i|", ndi));
// 	printf(" (%d)\n", printf("0000000000010: |%0000000000010i|", ndi));
// 	ft_printf(" (%d)\n", ft_printf("0000000000010: |%0000000000010i|", ndi));

// 	printf("\n%s/////////////////////////////////////////////////////////////////////////////////////////////////////%s\n\n", YELLOW, RESET);
// 	printf("%s(-) flag & MFW\n%s", RED, RESET);
// 	printf("- > Left-justify within the given field width; Right justification is the default\n");
// 	printf("%s%%-10d or %%-3d = (-) followed by numbers\n\n%s", GREEN, RESET);

// 	// not compiling! " " (%d)\n", printf("(0) Mfw -0: |%-0%si|",0));
// 	// ft_printf(" (%d)\n", ft_printf("(0) Mfw -0: |%-0i|", 0));
// 	printf(" (%d)\n", printf("(0) Mfw -1: |%-1i|", 0));
// 	ft_printf(" (%d)\n", ft_printf("(0) Mfw -1: |%-1i|", 0));
// 	printf(" (%d)\n", printf("(0) Mfw -2: |%-2i|", 0));
// 	ft_printf(" (%d)\n", ft_printf("(0) Mfw -2: |%-2i|", 0));

// 	// not compiling! " (%d)\n", printf("Mfw -0: |%-0i|", di));
// 	// ft_printf(" (%d)\n", ft_printf("Mfw -0: |%-0i|", di));
// 	printf(" (%d)\n", printf("Mfw -1: |%-1i|", di));
// 	ft_printf(" (%d)\n", ft_printf("Mfw -1: |%-1i|", di));
// 	printf(" (%d)\n", printf("Mfw -2: |%-2i|", di));
// 	ft_printf(" (%d)\n", ft_printf("Mfw -2: |%-2i|", di));
// 	printf(" (%d)\n", printf("Mfw -3: |%-3i|", di));
// 	ft_printf(" (%d)\n", ft_printf("Mfw -3: |%-3i|", di));
// 	printf(" (%d)\n", printf("Mfw -4: |%-4i|", di));
// 	ft_printf(" (%d)\n", ft_printf("Mfw -4: |%-4i|", di));
// 	printf(" (%d)\n", printf("Mfw -5: |%-5i|", di));
// 	ft_printf(" (%d)\n", ft_printf("Mfw -5: |%-5i|", di));
// 	printf(" (%d)\n", printf("Mfw -10: |%-10i|", di));
// 	ft_printf(" (%d)\n", ft_printf("Mfw -10: |%-10i|", di));
// 	printf(" (%d)\n", printf("Mfw --10: |%--10i|", di));
// 	ft_printf(" (%d)\n", ft_printf("Mfw --10: |%--10i|", di));
// 	printf(" (%d)\n", printf("Mfw ---10: |%---10i|", di));
// 	ft_printf(" (%d)\n", ft_printf("Mfw ---10: |%---10i|", di));
// 	printf(" (%d)\n", printf("Mfw -15: |%-15i|", di));
// 	ft_printf(" (%d)\n", ft_printf("Mfw -15: |%-15i|", di));
// 	printf(" (%d)\n", printf("Mfw -42: |%-42i|", di));
// 	ft_printf(" (%d)\n", ft_printf("Mfw -42: |%-42i|", di));

// 	printf("\n%s/////////////////////////////////////////////////////////////////////////////////////////////////////%s\n\n", YELLOW, RESET);
// 	printf("%s(-) flag & MFW & PRECISION%s\n\n", RED, RESET);

// 	//ppprintf(" (%d)\n", printf("(0) -0.0: |%-0.0i|", 0));
// 	// ft_ppprintf(" (%d)\n", ft_printf("(0) -0.0: |%-0.0i|", 0));
// 	///pppprintf(" (%d)\n", printf("(0) -0.1: |%-0.1i|", 0));
// 	// ft_ppprintf(" (%d)\n", ft_printf("(0) -0.1: |%-0.1i|", 0));
// 	printf(" (%d)\n", printf("(0) -1.0: |%-1.0i|", 0));
// 	ft_printf(" (%d)\n", ft_printf("(0) -1.0: |%-1.0i|", 0));
// 	printf(" (%d)\n", printf("(0) -1.1: |%-1.1i|", 0));
// 	ft_printf(" (%d)\n", ft_printf("(0) -1.1: |%-1.1i|", 0));
// 	////ppprintf(" (%d)\n", printf("(0) -0.2: |%-0.2i|", 0));
// 	// ft_ppprintf(" (%d)\n", ft_printf("(0) -0.2: |%-0.2i|", 0));
// 	printf(" (%d)\n", printf("(0) -2.0: |%-2.0i|", 0));
// 	ft_printf(" (%d)\n", ft_printf("(0) -2.0: |%-2.0i|", 0));
// 	printf(" (%d)\n", printf("(0) -2.2: |%-2.2i|", 0));
// 	ft_printf(" (%d)\n", ft_printf("(0) -2.2: |%-2.2i|", 0));


// 	//ppprintf(" (%d)\n", printf("-0.0: |%-0.0i|", 5));
// 	// ft_ppprintf(" (%d)\n", ft_printf("-0.0: |%-0.0i|", 5));
// 	///pprintf(" (%d)\n", printf("-0.1: |%-0.1i|", 5));
// 	// ft_ppprintf(" (%d)\n", ft_printf("-0.1: |%-0.1i|", 5));
// 	printf(" (%d)\n", printf("-1.0: |%-1.0i|", 5));
// 	ft_printf(" (%d)\n", ft_printf("-1.0: |%-1.0i|", 5));
// 	printf(" (%d)\n", printf("-1.1: |%-1.1i|", 5));
// 	ft_printf(" (%d)\n", ft_printf("-1.1: |%-1.1i|", 5));
// 	printf(" (%d)\n", printf("-2.0: |%-2.0i|", 5));
// 	ft_printf(" (%d)\n", ft_printf("-2.0: |%-2.0i|", 5));
// 	printf(" (%d)\n", printf("-2.2: |%-2.2i|", 5));
// 	ft_printf(" (%d)\n", ft_printf("-2.2: |%-2.2i|", 5));


// 	printf(" (%d)\n", printf("-1.1: |%-1.1i|", di));
// 	ft_printf(" (%d)\n", ft_printf("-1.1: |%-1.1i|", di));
// 	printf(" (%d)\n", printf("-2.2: |%-2.2i|", di));
// 	ft_printf(" (%d)\n", ft_printf("-2.2: |%-2.2i|", di));
// 	printf(" (%d)\n", printf("-3.2: |%-3.2i|", di));
// 	ft_printf(" (%d)\n", ft_printf("-3.2: |%-3.2i|", di));
// 	printf(" (%d)\n", printf("-2.3: |%-2.3i|", di));
// 	ft_printf(" (%d)\n", ft_printf("-2.3: |%-2.3i|", di));
// 	printf(" (%d)\n", printf("-8.4: |%-8.4i|", di));
// 	ft_printf(" (%d)\n", ft_printf("-8.4: |%-8.4i|", di));
// 	printf(" (%d)\n", printf("-4.8: |%-4.8i|", di));
// 	ft_printf(" (%d)\n", ft_printf("-4.8: |%-4.8i|", di));
// 	printf(" (%d)\n", printf("-8.8: |%-8.8i|", di));
// 	ft_printf(" (%d)\n", ft_printf("-8.8: |%-8.8i|", di));
// 	printf(" (%d)\n", printf("-8.2: |%-8.2i|", di));
// 	ft_printf(" (%d)\n", ft_printf("-8.2: |%-8.2i|", di));
// 	printf(" (%d)\n", printf("-2.8: |%-2.8i|", di));
// 	ft_printf(" (%d)\n", ft_printf("-2.8: |%-2.8i|", di));
// 	printf(" (%d)\n", printf("-8.1: |%-8.1i|", di));
// 	ft_printf(" (%d)\n", ft_printf("-8.1: |%-8.1i|", di));
// 	printf(" (%d)\n", printf("-1.8: |%-1.8i|", di));
// 	ft_printf(" (%d)\n", ft_printf("-1.8: |%-1.8i|", di));

// 	printf("\n------------------------------------------------------------------------------------------------\n\n");

// 	printf(" (%d)\n", printf("Negative ints are a pain:"));
// 	ft_printf(" (%d)\n", ft_printf("Negative ints are a pain:"));
// 	printf("\n");

// 	int negative_int = -1994;

// 	// printf(" (%d)\n", printf("Sometimes it struggles with negative ints: -08.7i |%-08.7i|", negative_int));
// 	// ft_printf(" (%d)\n", ft_printf("Sometimes it struggles with negative ints: -08.7i |%-08.7i|", negative_int));
// 	// printf(" (%i)\n", printf("Sometimes it struggles with negative ints: -08.10i |%-08.10i|", negative_int));
// 	// ft_printf(" (%i)\n", ft_printf("Sometimes it struggles with negative ints: -08.10i |%-08.10i|", negative_int));
// 	// printf("\n");

// 	printf(" (%d)\n", printf("Sometimes it struggles with negative ints: -8.7i |%-8.7i|", negative_int));
// 	ft_printf(" (%d)\n", ft_printf("Sometimes it struggles with negative ints: -8.7i |%-8.7i|", negative_int));
// 	printf(" (%i)\n", printf("Sometimes it struggles with negative ints: -8.10i |%-8.10i|", negative_int));
// 	ft_printf(" (%i)\n", ft_printf("Sometimes it struggles with negative ints: -8.10i |%-8.10i|", negative_int));
// 	printf("\n");

// 	printf(" (%d)\n", printf("Sometimes it struggles with negative ints: 8.7i |%8.7i|", negative_int));
// 	ft_printf(" (%d)\n", ft_printf("Sometimes it struggles with negative ints: 8.7i |%8.7i|", negative_int));
// 	printf(" (%i)\n", printf("Sometimes it struggles with negative ints: 8.10i |%8.10i|", negative_int));
// 	ft_printf(" (%i)\n", ft_printf("Sometimes it struggles with negative ints: 8.10i |%8.10i|", negative_int));
// 	printf("\n");

// 	printf(" (%d)\n", printf("Sometimes it struggles with negative ints: 08i |%08i|", negative_int));
// 	ft_printf(" (%d)\n", ft_printf("Sometimes it struggles with negative ints: 08i |%08i|", negative_int));
// 	printf("\n");

// 	printf(" (%d)\n", printf("Sometimes it struggles with negative ints: 8i |%8i|", negative_int));
// 	ft_printf(" (%d)\n", ft_printf("Sometimes it struggles with negative ints: 8i |%8i|", negative_int));
// 	printf("\n");

// 	printf(" (%d)\n", printf("Sometimes it struggles with negative ints: 8.5i |%8.5i|", negative_int));
// 	ft_printf(" (%d)\n", ft_printf("Sometimes it struggles with negative ints: 8.5i |%8.5i|", negative_int));
// 	printf("\n");

// 	printf(" (%d)\n", printf("Sometimes it struggles with negative ints: -8i |%-8i|", negative_int));
// 	ft_printf(" (%d)\n", ft_printf("Sometimes it struggles with negative ints: -8i |%-8i|", negative_int));
// 	printf("\n");

// 	printf(" (%d)\n", printf("Sometimes it struggles with negative ints: -8.5i |%-8.5i|", negative_int));
// 	ft_printf(" (%d)\n", ft_printf("Sometimes it struggles with negative ints: -8.5i |%-8.5i|", negative_int));
// 	printf("\n");

// 	negative_int = -2147483648;

// 	// printf(" (%d)\n", printf("Sometimes it struggles with negative ints: -08.7i |%-08.7i|", negative_int));
// 	// ft_printf(" (%d)\n", ft_printf("Sometimes it struggles with negative ints: -08.7i |%-08.7i|", negative_int));
// 	// printf(" (%i)\n", printf("Sometimes it struggles with negative ints: -08.10i |%-08.10i|", negative_int));
// 	// ft_printf(" (%i)\n", ft_printf("Sometimes it struggles with negative ints: -08.10i |%-08.10i|", negative_int));
// 	// printf("\n");

// 	printf(" (%d)\n", printf("Sometimes it struggles with negative ints: -8.7i |%-8.7i|", negative_int));
// 	ft_printf(" (%d)\n", ft_printf("Sometimes it struggles with negative ints: -8.7i |%-8.7i|", negative_int));
// 	printf(" (%i)\n", printf("Sometimes it struggles with negative ints: -8.10i |%-8.10i|", negative_int));
// 	ft_printf(" (%i)\n", ft_printf("Sometimes it struggles with negative ints: -8.10i |%-8.10i|", negative_int));
// 	printf("\n");

// 	printf(" (%d)\n", printf("Sometimes it struggles with negative ints: 8.7i |%8.7i|", negative_int));
// 	ft_printf(" (%d)\n", ft_printf("Sometimes it struggles with negative ints: 8.7i |%8.7i|", negative_int));
// 	printf(" (%i)\n", printf("Sometimes it struggles with negative ints: 8.10i |%8.10i|", negative_int));
// 	ft_printf(" (%i)\n", ft_printf("Sometimes it struggles with negative ints: 8.10i |%8.10i|", negative_int));
// 	printf("\n");

// 	printf(" (%d)\n", printf("Sometimes it struggles with negative ints: 08i |%08i|", negative_int));
// 	ft_printf(" (%d)\n", ft_printf("Sometimes it struggles with negative ints: 08i |%08i|", negative_int));
// 	printf("\n");

// 	printf(" (%d)\n", printf("Sometimes it struggles with negative ints: 8i |%8i|", negative_int));
// 	ft_printf(" (%d)\n", ft_printf("Sometimes it struggles with negative ints: 8i |%8i|", negative_int));
// 	printf("\n");

// 	printf(" (%d)\n", printf("Sometimes it struggles with negative ints: 8.5i |%8.5i|", negative_int));
// 	ft_printf(" (%d)\n", ft_printf("Sometimes it struggles with negative ints: 8.5i |%8.5i|", negative_int));
// 	printf("\n");

// 	printf(" (%d)\n", printf("Sometimes it struggles with negative ints: -8i |%-8i|", negative_int));
// 	ft_printf(" (%d)\n", ft_printf("Sometimes it struggles with negative ints: -8i |%-8i|", negative_int));
// 	printf("\n");

// 	printf(" (%d)\n", printf("Sometimes it struggles with negative ints: -8.5i |%-8.5i|", negative_int));
// 	ft_printf(" (%d)\n", ft_printf("Sometimes it struggles with negative ints: -8.5i |%-8.5i|", negative_int));
// 	printf("\n");


// 	printf("\n------------------------------------------------------------------------------------------------\n\n");

// 	printf(" (%d)\n", printf("Some edge cases I thought of whilst writing:"));
// 	ft_printf(" (%d)\n", ft_printf("Some edge cases I thought of whilst writing:"));
// 	printf("\n");

// 	printf(" (%d)\n", printf("8.: |%8.i|", 0));
// 	ft_printf(" (%d)\n", ft_printf("8.: |%8.i|", 0));
// 	printf(" (%d)\n", printf("8.: |%8.i|", 42));
// 	ft_printf(" (%d)\n", ft_printf("8.: |%8.i|", 42));
// 	printf(" (%d)\n", printf("8.: |%8.s|", "test"));
// 	ft_printf(" (%d)\n", ft_printf("8.: |%8.s|", "test"));
// 	// printf(" (%d)\n", printf("08.*(-4): |%08.*i|", -4, 42));
// 	// ft_printf(" (%d)\n", ft_printf("08.*(-4): |%08.*i|", -4, 42));
// 	// printf(" (%d)\n", printf("(string) 8.*(-5): |%8.*s|", -5, "test"));
// 	// ft_printf(" (%d)\n", ft_printf("(string) 8.*(-5): |%8.*s|", -5, "test"));

// 	return (0);
// }



// int		main(void)
// {
// 	char	val = 'a';
// 	val = '%';
// 	// val = 'c';
// 	// val = '$';
//     val = (char)-42;

// 	int broken = 0;
// 	int	bonus = 0;

// 	printf(" (%d)\n", printf("Handling minimum field width"));
// 	ft_printf(" (%d)\n", ft_printf("Handling minimum field width"));

// 	printf(" (%d)\n", printf("(0) Mfw 0: |%0c|", 0));
// 	ft_printf(" (%d)\n", ft_printf("(0) Mfw 0: |%0c|", 0));
// 	printf(" (%d)\n", printf("(0) Mfw 1: |%1c|", 0));
// 	ft_printf(" (%d)\n", ft_printf("(0) Mfw 1: |%1c|", 0));
// 	printf(" (%d)\n", printf("Mfw 0: |%0c|", val));
// 	ft_printf(" (%d)\n", ft_printf("Mfw 0: |%0c|", val));
// 	printf(" (%d)\n", printf("Mfw 1: |%1c|", val));
// 	ft_printf(" (%d)\n", ft_printf("Mfw 1: |%1c|", val));
// 	printf(" (%d)\n", printf("Mfw 2: |%2c|", val));
// 	ft_printf(" (%d)\n", ft_printf("Mfw 2: |%2c|", val));
// 	printf(" (%d)\n", printf("Mfw 3: |%3c|", val));
// 	ft_printf(" (%d)\n", ft_printf("Mfw 3: |%3c|", val));
// 	printf(" (%d)\n", printf("Mfw 4: |%4c|", val));
// 	ft_printf(" (%d)\n", ft_printf("Mfw 4: |%4c|", val));
// 	printf(" (%d)\n", printf("Mfw 5: |%5c|", val));
// 	ft_printf(" (%d)\n", ft_printf("Mfw 5: |%5c|", val));
// 	printf(" (%d)\n", printf("Mfw 10: |%10c|", val));
// 	ft_printf(" (%d)\n", ft_printf("Mfw 10: |%10c|", val));
// 	printf(" (%d)\n", printf("Mfw 15: |%15c|", val));
// 	ft_printf(" (%d)\n", ft_printf("Mfw 15: |%15c|", val));
// 	printf(" (%d)\n", printf("Mfw 42: |%42c|", val));
// 	ft_printf(" (%d)\n", ft_printf("Mfw 42: |%42c|", val));

// 	printf("\n------------------------------------------------------------------------------------------------\n\n");

// 	printf(" (%d)\n", printf("Handling precision"));
// 	ft_printf(" (%d)\n", ft_printf("Handling precision"));

// 	// printf(" (%d)\n", printf("(0) Precis. 0: |%.0c|", 0));
// 	// ft_printf(" (%d)\n", ft_printf("(0) Precis. 0: |%.0c|", 0));
// 	// printf(" (%d)\n", printf("(0) Precis. 1: |%.1c|", 0));
// 	// ft_printf(" (%d)\n", ft_printf("(0) Precis. 1: |%.1c|", 0));
// 	// printf(" (%d)\n", printf("(0) Precis. 2: |%.2c|", 0));
// 	// ft_printf(" (%d)\n", ft_printf("(0) Precis. 2: |%.2c|", 0));
// 	// printf(" (%d)\n", printf("Precis. 0: |%.0c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("Precis. 0: |%.0c|", val));
// 	// printf(" (%d)\n", printf("Precis. 1: |%.1c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("Precis. 1: |%.1c|", val));
// 	// printf(" (%d)\n", printf("Precis. 2: |%.2c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("Precis. 2: |%.2c|", val));
// 	// printf(" (%d)\n", printf("Precis. 3: |%.3c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("Precis. 3: |%.3c|", val));
// 	// printf(" (%d)\n", printf("Precis. 4: |%.4c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("Precis. 4: |%.4c|", val));
// 	// printf(" (%d)\n", printf("Precis. 5: |%.5c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("Precis. 5: |%.5c|", val));
// 	// printf(" (%d)\n", printf("Precis. 10: |%.10c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("Precis. 10: |%.10c|", val));
// 	// printf(" (%d)\n", printf("Precis. 15: |%.15c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("Precis. 15: |%.15c|", val));
// 	// printf(" (%d)\n", printf("Precis. 42: |%.42c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("Precis. 42: |%.42c|", val));

// 	// printf(" (%d)\n", printf("(0) P .00: |%.00c|", 0));
// 	// ft_printf(" (%d)\n", ft_printf("(0) P .00: |%.00c|", 0));
// 	// printf(" (%d)\n", printf("(0) P .01: |%.01c|", 0));
// 	// ft_printf(" (%d)\n", ft_printf("(0) P .01: |%.01c|", 0));
// 	// printf(" (%d)\n", printf("P .00: |%.00c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("P .00: |%.00c|", val));
// 	// printf(" (%d)\n", printf("P .01: |%.01c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("P .01: |%.01c|", val));
// 	// printf(" (%d)\n", printf("P .02: |%.02c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("P .02: |%.02c|", val));
// 	// printf(" (%d)\n", printf("P .03: |%.03c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("P .03: |%.03c|", val));
// 	// printf(" (%d)\n", printf("P .04: |%.04c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("P .04: |%.04c|", val));
// 	// printf(" (%d)\n", printf("P .05: |%.05c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("P .05: |%.05c|", val));
// 	// printf(" (%d)\n", printf("P .010: |%.010c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("P .010: |%.010c|", val));
// 	// printf(" (%d)\n", printf("P .015: |%.015c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("P .015: |%.015c|", val));
// 	// printf(" (%d)\n", printf("P .042: |%.042c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("P .042: |%.042c|", val));

// 	// printf(" (%d)\n", printf("P .007: |%.007c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("P .007: |%.007c|", val));
// 	// printf(" (%d)\n", printf("P .000000000007: |%.000000000007c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("P .000000000007: |%.000000000007c|", val));


// 	// printf("\n------------------------------------------------------------------------------------------------\n\n");

// 	// printf(" (%d)\n", printf("Handling precision & minimum field width"));
// 	// ft_printf(" (%d)\n", ft_printf("Handling precision & minimum field width"));

// 	// printf(" (%d)\n", printf("(0) 0.0: |%0.0c|", 0));
// 	// ft_printf(" (%d)\n", ft_printf("(0) 0.0: |%0.0c|", 0));
// 	// printf(" (%d)\n", printf("(0) 1.0: |%1.0c|", 0));
// 	// ft_printf(" (%d)\n", ft_printf("(0) 1.0: |%1.0c|", 0));
// 	// printf(" (%d)\n", printf("(10) 1.0: |%1.0c|", 10));
// 	// ft_printf(" (%d)\n", ft_printf("(10) 1.0: |%1.0c|", 10));
// 	// printf(" (%d)\n", printf("(0) 0.1: |%0.1c|", 0));
// 	// ft_printf(" (%d)\n", ft_printf("(0) 0.1: |%0.1c|", 0));
// 	// printf(" (%d)\n", printf("(0) 1.1: |%1.1c|", 0));
// 	// ft_printf(" (%d)\n", ft_printf("(0) 1.1: |%1.1c|", 0));
// 	// printf(" (%d)\n", printf("0.0: |%0.0c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("0.0: |%0.0c|", val));
// 	// printf(" (%d)\n", printf("1.1: |%1.1c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("1.1: |%1.1c|", val));
// 	// printf(" (%d)\n", printf("2.2: |%2.2c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("2.2: |%2.2c|", val));
// 	// printf(" (%d)\n", printf("3.2: |%3.2c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("3.2: |%3.2c|", val));
// 	// printf(" (%d)\n", printf("2.3: |%2.3c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("2.3: |%2.3c|", val));
// 	// printf(" (%d)\n", printf("8.4: |%8.4c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("8.4: |%8.4c|", val));
// 	// printf(" (%d)\n", printf("4.8: |%4.8c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("4.8: |%4.8c|", val));
// 	// printf(" (%d)\n", printf("8.8: |%8.8c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("8.8: |%8.8c|", val));
// 	// printf(" (%d)\n", printf("8.2: |%8.2c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("8.2: |%8.2c|", val));
// 	// printf(" (%d)\n", printf("2.8: |%2.8c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("2.8: |%2.8c|", val));
// 	// printf(" (%d)\n", printf("8.1: |%8.1c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("8.1: |%8.1c|", val));
// 	// printf(" (%d)\n", printf("1.8: |%1.8c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("1.8: |%1.8c|", val));

// 	// printf("\n------------------------------------------------------------------------------------------------\n\n");

// 	// printf(" (%d)\n", printf("Handling precision & minimum field width & 0-flag"));
// 	// ft_printf(" (%d)\n", ft_printf("Handling precision & minimum field width & 0-flag"));

// 	// printf(" (%d)\n", printf("(0) 00.0: |%00.0c|", 0));
// 	// ft_printf(" (%d)\n", ft_printf("(0) 00.0: |%00.0c|", 0));
// 	// printf(" (%d)\n", printf("(0) 01.0: |%01.0c|", 0));
// 	// ft_printf(" (%d)\n", ft_printf("(0) 01.0: |%01.0c|", 0));
// 	// printf(" (%d)\n", printf("(0) 00.1: |%00.1c|", 0));
// 	// ft_printf(" (%d)\n", ft_printf("(0) 00.1: |%00.1c|", 0));
// 	// printf(" (%d)\n", printf("01.1: |%01.1c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("01.1: |%01.1c|", val));
// 	// printf(" (%d)\n", printf("02.2: |%02.2c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("02.2: |%02.2c|", val));
// 	// printf(" (%d)\n", printf("03.2: |%03.2c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("03.2: |%03.2c|", val));
// 	// printf(" (%d)\n", printf("02.3: |%02.3c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("02.3: |%02.3c|", val));
// 	// printf(" (%d)\n", printf("08.4: |%08.4c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("08.4: |%08.4c|", val));
// 	// printf(" (%d)\n", printf("04.8: |%04.8c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("04.8: |%04.8c|", val));
// 	// printf(" (%d)\n", printf("08.8: |%08.8c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("08.8: |%08.8c|", val));
// 	// printf(" (%d)\n", printf("08.2: |%08.2c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("08.2: |%08.2c|", val));
// 	// printf(" (%d)\n", printf("02.8: |%02.8c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("02.8: |%02.8c|", val));
// 	// printf(" (%d)\n", printf("08.1: |%08.1c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("08.1: |%08.1c|", val));
// 	// printf(" (%d)\n", printf("01.8: |%01.8c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("01.8: |%01.8c|", val));

// 	printf("\n------------------------------------------------------------------------------------------------\n\n");

// 	printf(" (%d)\n", printf("Handling minimum field width & 0-flag"));
// 	ft_printf(" (%d)\n", ft_printf("Handling minimum field width & 0-flag"));

// 	printf(" (%d)\n", printf("(0) 0: |%0c|", 0));
// 	ft_printf(" (%d)\n", ft_printf("(0) 0: |%0c|", 0));
// 	printf(" (%d)\n", printf("(0) 00: |%00c|", 0));
// 	ft_printf(" (%d)\n", ft_printf("(0) 00: |%00c|", 0));
// 	printf(" (%d)\n", printf("(0) 01: |%01c|", 0));
// 	ft_printf(" (%d)\n", ft_printf("(0) 01: |%01c|", 0));
// 	printf(" (%d)\n", printf("(0) 02: |%02c|", 0));
// 	ft_printf(" (%d)\n", ft_printf("(0) 02: |%02c|", 0));
// 	printf(" (%d)\n", printf("0: |%0c|", val));
// 	ft_printf(" (%d)\n", ft_printf("0: |%0c|", val));
// 	printf(" (%d)\n", printf("00: |%00c|", val));
// 	ft_printf(" (%d)\n", ft_printf("00: |%00c|", val));
// 	printf(" (%d)\n", printf("01: |%01c|", val));
// 	ft_printf(" (%d)\n", ft_printf("01: |%01c|", val));
// 	printf(" (%d)\n", printf("02: |%02c|", val));
// 	ft_printf(" (%d)\n", ft_printf("02: |%02c|", val));
// 	printf(" (%d)\n", printf("03: |%03c|", val));
// 	ft_printf(" (%d)\n", ft_printf("03: |%03c|", val));
// 	printf(" (%d)\n", printf("08: |%08c|", val));
// 	ft_printf(" (%d)\n", ft_printf("08: |%08c|", val));
// 	printf(" (%d)\n", printf("000000000008: |%000000000008c|", val));
// 	ft_printf(" (%d)\n", ft_printf("000000000008: |%000000000008c|", val));
// 	printf(" (%d)\n", printf("010: |%010c|", val));
// 	ft_printf(" (%d)\n", ft_printf("010: |%010c|", val));
// 	printf(" (%d)\n", printf("0000000000010: |%0000000000010c|", val));
// 	ft_printf(" (%d)\n", ft_printf("0000000000010: |%0000000000010c|", val));

// 	printf("\n------------------------------------------------------------------------------------------------\n\n");

// 	printf(" (%d)\n", printf("Handling minimum field width & 0-flag & '-' flag"));
// 	ft_printf(" (%d)\n", ft_printf("Handling minimum field width & 0-flag & '-' flag"));

// 	printf(" (%d)\n", printf("(0) -0: |%-0c|", 0));
// 	ft_printf(" (%d)\n", ft_printf("(0) -0: |%-0c|", 0));
// 	printf(" (%d)\n", printf("(0) -00: |%-00c|", 0));
// 	ft_printf(" (%d)\n", ft_printf("(0) -00: |%-00c|", 0));
// 	printf(" (%d)\n", printf("(0) -01: |%-01c|", 0));
// 	ft_printf(" (%d)\n", ft_printf("(0) -01: |%-01c|", 0));
// 	printf(" (%d)\n", printf("(0) -02: |%-02c|", 0));
// 	ft_printf(" (%d)\n", ft_printf("(0) -02: |%-02c|", 0));

// 	printf(" (%d)\n", printf("-0: |%-0c|", val));
// 	ft_printf(" (%d)\n", ft_printf("-0: |%-0c|", val));
// 	printf(" (%d)\n", printf("-00: |%-00c|", val));
// 	ft_printf(" (%d)\n", ft_printf("-00: |%-00c|", val));
// 	printf(" (%d)\n", printf("-01: |%-01c|", val));
// 	ft_printf(" (%d)\n", ft_printf("-01: |%-01c|", val));
// 	printf(" (%d)\n", printf("-02: |%-02c|", val));
// 	ft_printf(" (%d)\n", ft_printf("-02: |%-02c|", val));
// 	printf(" (%d)\n", printf("-03: |%-03c|", val));
// 	ft_printf(" (%d)\n", ft_printf("-03: |%-03c|", val));
// 	printf(" (%d)\n", printf("-08: |%-08c|", val));
// 	ft_printf(" (%d)\n", ft_printf("-08: |%-08c|", val));
// 	printf(" (%d)\n", printf("0-8: |%0-8c|", val));
// 	ft_printf(" (%d)\n", ft_printf("0-8: |%0-8c|", val));
// 	printf(" (%d)\n", printf("-000000000008: |%-000000000008c|", val));
// 	ft_printf(" (%d)\n", ft_printf("-000000000008: |%-000000000008c|", val));
// 	printf(" (%d)\n", printf("-010: |%-010c|", val));
// 	ft_printf(" (%d)\n", ft_printf("-010: |%-010c|", val));
// 	printf(" (%d)\n", printf("-0000000000010: |%-0000000000010c|", val));
// 	ft_printf(" (%d)\n", ft_printf("-0000000000010: |%-0000000000010c|", val));


// 	printf("\n------------------------------------------------------------------------------------------------\n\n");

// 	printf(" (%d)\n", printf("Handling minimum field width & left justification"));
// 	ft_printf(" (%d)\n", ft_printf("Handling minimum field width & left justification"));

// 	printf(" (%d)\n", printf("(0) Mfw -0: |%-0c|", 0));
// 	ft_printf(" (%d)\n", ft_printf("(0) Mfw -0: |%-0c|", 0));
// 	printf(" (%d)\n", printf("(0) Mfw -1: |%-1c|", 0));
// 	ft_printf(" (%d)\n", ft_printf("(0) Mfw -1: |%-1c|", 0));
// 	printf(" (%d)\n", printf("(0) Mfw -2: |%-2c|", 0));
// 	ft_printf(" (%d)\n", ft_printf("(0) Mfw -2: |%-2c|", 0));

// 	printf(" (%d)\n", printf("Mfw -0: |%-0c|", val));
// 	ft_printf(" (%d)\n", ft_printf("Mfw -0: |%-0c|", val));
// 	printf(" (%d)\n", printf("Mfw -1: |%-1c|", val));
// 	ft_printf(" (%d)\n", ft_printf("Mfw -1: |%-1c|", val));
// 	printf(" (%d)\n", printf("Mfw -2: |%-2c|", val));
// 	ft_printf(" (%d)\n", ft_printf("Mfw -2: |%-2c|", val));
// 	printf(" (%d)\n", printf("Mfw -3: |%-3c|", val));
// 	ft_printf(" (%d)\n", ft_printf("Mfw -3: |%-3c|", val));
// 	printf(" (%d)\n", printf("Mfw -4: |%-4c|", val));
// 	ft_printf(" (%d)\n", ft_printf("Mfw -4: |%-4c|", val));
// 	printf(" (%d)\n", printf("Mfw -5: |%-5c|", val));
// 	ft_printf(" (%d)\n", ft_printf("Mfw -5: |%-5c|", val));
// 	printf(" (%d)\n", printf("Mfw -10: |%-10c|", val));
// 	ft_printf(" (%d)\n", ft_printf("Mfw -10: |%-10c|", val));
// 	printf(" (%d)\n", printf("Mfw --10: |%--10c|", val));
// 	ft_printf(" (%d)\n", ft_printf("Mfw --10: |%--10c|", val));
// 	printf(" (%d)\n", printf("Mfw ---10: |%---10c|", val));
// 	ft_printf(" (%d)\n", ft_printf("Mfw ---10: |%---10c|", val));
// 	printf(" (%d)\n", printf("Mfw -15: |%-15c|", val));
// 	ft_printf(" (%d)\n", ft_printf("Mfw -15: |%-15c|", val));
// 	printf(" (%d)\n", printf("Mfw -42: |%-42c|", val));
// 	ft_printf(" (%d)\n", ft_printf("Mfw -42: |%-42c|", val));

// 	printf("\n------------------------------------------------------------------------------------------------\n\n");

// 	printf(" (%d)\n", printf("Handling precision & minimum field width & left justification"));
// 	ft_printf(" (%d)\n", ft_printf("Handling precision & minimum field width & left justification"));

// 	// printf(" (%d)\n", printf("(0) -0.0: |%-0.0c|", 0));
// 	// ft_printf(" (%d)\n", ft_printf("(0) -0.0: |%-0.0c|", 0));
// 	// printf(" (%d)\n", printf("(0) -0.1: |%-0.1c|", 0));
// 	// ft_printf(" (%d)\n", ft_printf("(0) -0.1: |%-0.1c|", 0));
// 	// printf(" (%d)\n", printf("(0) -1.0: |%-1.0c|", 0));
// 	// ft_printf(" (%d)\n", ft_printf("(0) -1.0: |%-1.0c|", 0));
// 	// printf(" (%d)\n", printf("(0) -1.1: |%-1.1c|", 0));
// 	// ft_printf(" (%d)\n", ft_printf("(0) -1.1: |%-1.1c|", 0));
// 	// printf(" (%d)\n", printf("(0) -0.2: |%-0.2c|", 0));
// 	// ft_printf(" (%d)\n", ft_printf("(0) -0.2: |%-0.2c|", 0));
// 	// printf(" (%d)\n", printf("(0) -2.0: |%-2.0c|", 0));
// 	// ft_printf(" (%d)\n", ft_printf("(0) -2.0: |%-2.0c|", 0));
// 	// printf(" (%d)\n", printf("(0) -2.2: |%-2.2c|", 0));
// 	// ft_printf(" (%d)\n", ft_printf("(0) -2.2: |%-2.2c|", 0));


// 	// printf(" (%d)\n", printf("-0.0: |%-0.0c|", 5));
// 	// ft_printf(" (%d)\n", ft_printf("-0.0: |%-0.0c|", 5));
// 	// printf(" (%d)\n", printf("-0.1: |%-0.1c|", 5));
// 	// ft_printf(" (%d)\n", ft_printf("-0.1: |%-0.1c|", 5));
// 	// printf(" (%d)\n", printf("-1.0: |%-1.0c|", 5));
// 	// ft_printf(" (%d)\n", ft_printf("-1.0: |%-1.0c|", 5));
// 	// printf(" (%d)\n", printf("-1.1: |%-1.1c|", 5));
// 	// ft_printf(" (%d)\n", ft_printf("-1.1: |%-1.1c|", 5));
// 	// printf(" (%d)\n", printf("-0.2: |%-0.2c|", 5));
// 	// ft_printf(" (%d)\n", ft_printf("-0.2: |%-0.2c|", 5));
// 	// printf(" (%d)\n", printf("-2.0: |%-2.0c|", 5));
// 	// ft_printf(" (%d)\n", ft_printf("-2.0: |%-2.0c|", 5));
// 	// printf(" (%d)\n", printf("-2.2: |%-2.2c|", 5));
// 	// ft_printf(" (%d)\n", ft_printf("-2.2: |%-2.2c|", 5));


// 	// printf(" (%d)\n", printf("-1.1: |%-1.1c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("-1.1: |%-1.1c|", val));
// 	// printf(" (%d)\n", printf("-2.2: |%-2.2c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("-2.2: |%-2.2c|", val));
// 	// printf(" (%d)\n", printf("-3.2: |%-3.2c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("-3.2: |%-3.2c|", val));
// 	// printf(" (%d)\n", printf("-2.3: |%-2.3c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("-2.3: |%-2.3c|", val));
// 	// printf(" (%d)\n", printf("-8.4: |%-8.4c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("-8.4: |%-8.4c|", val));
// 	// printf(" (%d)\n", printf("-4.8: |%-4.8c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("-4.8: |%-4.8c|", val));
// 	// printf(" (%d)\n", printf("-8.8: |%-8.8c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("-8.8: |%-8.8c|", val));
// 	// printf(" (%d)\n", printf("-8.2: |%-8.2c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("-8.2: |%-8.2c|", val));
// 	// printf(" (%d)\n", printf("-2.8: |%-2.8c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("-2.8: |%-2.8c|", val));
// 	// printf(" (%d)\n", printf("-8.1: |%-8.1c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("-8.1: |%-8.1c|", val));
// 	// printf(" (%d)\n", printf("-1.8: |%-1.8c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("-1.8: |%-1.8c|", val));

// 	printf("\n------------------------------------------------------------------------------------------------\n\n");

// 	printf(" (%d)\n", printf("Handling wildcards"));
// 	ft_printf(" (%d)\n", ft_printf("Handling wildcards"));

// 	// printf(" (%d)\n", printf("Mfw *1: |%*c|", 1, val));
// 	// ft_printf(" (%d)\n", ft_printf("Mfw *1: |%*c|", 1, val));
// 	// printf(" (%d)\n", printf("Mfw *5: |%*c|", 5, val));
// 	// ft_printf(" (%d)\n", ft_printf("Mfw *5: |%*c|", 5, val));
// 	// printf(" (%d)\n", printf("Mfw *5: |%*c|",5, val));
// 	// ft_printf(" (%d)\n", ft_printf("Mfw *5: |%*c|", 5, val));
// 	// printf(" (%d)\n", printf("Mfw *5: |%*c|",        5, val));
// 	// ft_printf(" (%d)\n", ft_printf("Mfw *5: |%*c|",        5, val));
// 	// printf(" (%d)\n", printf("Mfw *10: |%*c|", 10, val));
// 	// ft_printf(" (%d)\n", ft_printf("Mfw *10: |%*c|", 10, val));
// 	// // printf(" (%d)\n", printf("Mfw *i: |%*c|", val, val));
// 	// // ft_printf(" (%d)\n", ft_printf("Mfw *i: |%*c|", val, val));
// 	// printf(" (%d)\n", printf("Mfw **5: |%*.*c|", 5, 6, val));
// 	// ft_printf(" (%d)\n", ft_printf("Mfw **5: |%*.*c|", 5, 6, val));
// 	// printf("\n");

// 	// printf(" (%d)\n", printf("Precis. .*1: |%.*c|", 1, val));
// 	// ft_printf(" (%d)\n", ft_printf("Precis. .*1: |%.*c|", 1, val));
// 	// printf(" (%d)\n", printf("Precis. .*5: |%.*c|", 5, val));
// 	// ft_printf(" (%d)\n", ft_printf("Precis. .*5: |%.*c|", 5, val));
// 	// printf(" (%d)\n", printf("Precis. .*5: |%.*c|",5, val));
// 	// ft_printf(" (%d)\n", ft_printf("Precis. .*5: |%.*c|",5, val));
// 	// printf(" (%d)\n", printf("Precis. .*5: |%.*c|",      5, val));
// 	// ft_printf(" (%d)\n", ft_printf("Precis. .*5: |%.*c|",      5, val));
// 	// printf(" (%d)\n", printf("Precis. .*10: |%.*c|", 10, val));
// 	// ft_printf(" (%d)\n", ft_printf("Precis. .*10: |%.*c|", 10, val));
// 	// // printf(" (%d)\n", printf("Precis. .*i: |%.*c|", val, val));
// 	// // ft_printf(" (%d)\n", ft_printf("Precis. .*i: |%.*c|", val, val));
// 	// printf("\n");

// 	// printf(" (%d)\n", printf("P .*0: |%.*c|", 0, val));
// 	// ft_printf(" (%d)\n", ft_printf("P .*0: |%.*c|", 0, val));
// 	// printf(" (%d)\n", printf("P .*01: |%.*c|", 01, val));
// 	// ft_printf(" (%d)\n", ft_printf("P .*01: |%.*c|", 01, val));
// 	// printf(" (%d)\n", printf("P .*05: |%.*c|", 05, val));
// 	// ft_printf(" (%d)\n", ft_printf("P .*05: |%.*c|", 05, val));
// 	// printf(" (%d)\n", printf("P .*010: |%.*c|", 010, val));
// 	// ft_printf(" (%d)\n", ft_printf("P .*010: |%.*c|", 010, val));
// 	// printf(" (%d)\n", printf("P .*000000000007: |%.*c|", 000000000007, val));
// 	// ft_printf(" (%d)\n", ft_printf("P .*000000000007: |%.*c|", 000000000007, val));
// 	// printf("\n");

// 	// printf(" (%d)\n", printf("*8.4: |%*.4c|", 8, val));
// 	// ft_printf(" (%d)\n", ft_printf("*8.4: |%*.4c|", 8, val));
// 	// printf(" (%d)\n", printf("*4.8: |%*.8c|", 4, val));
// 	// ft_printf(" (%d)\n", ft_printf("*4.8: |%*.8c|", 4, val));
// 	// printf(" (%d)\n", printf("*8.8: |%*.8c|", 8, val));
// 	// ft_printf(" (%d)\n", ft_printf("*8.8: |%*.8c|", 8, val));
// 	// printf("\n");

// 	// printf(" (%d)\n", printf("8.*4: |%8.*c|", 4, val));
// 	// ft_printf(" (%d)\n", ft_printf("8.*4: |%8.*c|", 4, val));
// 	// printf(" (%d)\n", printf("4.*8: |%4.*c|", 8, val));
// 	// ft_printf(" (%d)\n", ft_printf("4.*8: |%4.*c|", 8, val));
// 	// printf(" (%d)\n", printf("8.*8: |%8.*c|", 8, val));
// 	// ft_printf(" (%d)\n", ft_printf("8.*8: |%8.*c|", 8, val));
// 	// printf("\n");

// 	// printf(" (%d)\n", printf("*8.*4: |%*.*c|", 8, 4, val));
// 	// ft_printf(" (%d)\n", ft_printf("*8.*4: |%*.*c|", 8, 4, val));
// 	// printf(" (%d)\n", printf("*4.*8: |%*.*c|", 4, 8, val));
// 	// ft_printf(" (%d)\n", ft_printf("*4.*8: |%*.*c|", 4, 8, val));
// 	// printf(" (%d)\n", printf("*8.*8: |%*.*c|", 8, 8, val));
// 	// ft_printf(" (%d)\n", ft_printf("*8.*8: |%*.*c|", 8, 8, val));
// 	// printf("\n");

// 	// printf("WEIRD OCTAL SHIT:\n");
// 	// printf(" (%d)\n", printf("*010.*4: |%*.*c|", 010, 4, val));
// 	// ft_printf(" (%d)\n", ft_printf("*010.*4: |%*.*c|", 010, 4, val));
// 	// printf(" (%d)\n", printf(" *07.*4: |%*.*c|", 07, 4, val));
// 	// ft_printf(" (%d)\n", ft_printf(" *07.*4: |%*.*c|", 07, 4, val));
// 	// printf(" (%d)\n", printf("*4.*010: |%*.*c|", 4, 010, val));
// 	// ft_printf(" (%d)\n", ft_printf("*4.*010: |%*.*c|", 4, 010, val));
// 	// printf("WEIRD HEXADECIMAL SHIT:\n");
// 	// printf(" (%d)\n", printf("*0x10.*4: |%*.*c|", 0x10, 4, val));
// 	// ft_printf(" (%d)\n", ft_printf("*0x10.*4: |%*.*c|", 0x10, 4, val));
// 	// printf(" (%d)\n", printf(" *0x7.*4: |%*.*c|", 0x7, 4, val));
// 	// ft_printf(" (%d)\n", ft_printf(" *0x7.*4: |%*.*c|", 0x7, 4, val));
// 	// printf(" (%d)\n", printf("*4.*0x10: |%*.*c|", 4, 0x10, val));
// 	// ft_printf(" (%d)\n", ft_printf("*4.*0x10: |%*.*c|", 4, 0x10, val));
// 	// printf("\n");



// 	//int octal;

// 	// octal = 010;
// 	// octal--;

// 	// printf("octal: %i\n", octal);

// 	// //this will print 7.

// 	// int octal_atoi;

// 	// octal_atoi = atoi("010");
// 	// octal_atoi--;

// 	// printf("octal: %i\n", octal_atoi);

// 	// //this will print 9.

// 	// int hexadec;

// 	// hexadec = 0x10;
// 	// hexadec--;

// 	// printf("hexadec: %i\n", hexadec);

// 	// //this will print 15.

// 	// int hexadec_atoi;

// 	// hexadec_atoi = atoi("0x10");
// 	// hexadec_atoi--;

// 	// printf("hexadec: %i\n", hexadec_atoi);

// 	// //this will print -1.

// 	// printf(" (%d)\n", printf("*8: |%*c|", 8, val));
// 	// ft_printf(" (%d)\n", ft_printf("*8: |%*c|", 8, val));
// 	// printf(" (%d)\n", printf("0*8: |%0*c|", 8, val));
// 	// ft_printf(" (%d)\n", ft_printf("0*8: |%0*c|", 8, val));
// 	// printf(" (%d)\n", printf("00*8: |%00*c|", 8, val));
// 	// ft_printf(" (%d)\n", ft_printf("00*8: |%00*c|", 8, val));
// 	// printf(" (%d)\n", printf("00000000000000000*8: |%00000000000000000*c|", 8, val));
// 	// ft_printf(" (%d)\n", ft_printf("00000000000000000*8: |%00000000000000000*c|", 8, val));
// 	// printf("\n");


// 	// printf(" (%d)\n", printf("-*0: |%-*c|", 0, val));
// 	// ft_printf(" (%d)\n", ft_printf("-*0: |%-*c|", 0, val));
// 	// printf(" (%d)\n", printf("-0*0: |%-0*c|", 0, val));
// 	// ft_printf(" (%d)\n", ft_printf("-0*0: |%-0*c|", 0, val));
// 	// printf(" (%d)\n", printf("-0*3: |%-0*c|", 3, val));
// 	// ft_printf(" (%d)\n", ft_printf("-0*3: |%-0*c|", 3, val));
// 	// printf(" (%d)\n", printf("*(-03): |%*c|", -03, val));
// 	// ft_printf(" (%d)\n", ft_printf("*(-03): |%*c|", -03, val));
// 	// printf(" (%d)\n", printf("*(-5): |%*c|", -5, val));
// 	// ft_printf(" (%d)\n", ft_printf("*(-5): |%*c|", -5, val));
// 	// printf(" (%d)\n", printf("*(5): |%*c|", 5, val));
// 	// ft_printf(" (%d)\n", ft_printf("*(5): |%*c|", 5, val));
// 	// printf(" (%d)\n", printf("-*(5): |%-*c|", 5, val));
// 	// ft_printf(" (%d)\n", ft_printf("-*(5): |%-*c|", 5, val));
// 	// printf(" (%d)\n", printf("-8.4: |%-8.4c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("-8.4: |%-8.4c|", val));
// 	// printf(" (%d)\n", printf("-*(8).4: |%-*.4c|", 8, val));
// 	// ft_printf(" (%d)\n", ft_printf("-*(8).4: |%-*.4c|", 8, val));
// 	// printf(" (%d)\n", printf("*(-8).4: |%*.4c|", -8, val));
// 	// ft_printf(" (%d)\n", ft_printf("*(-8).4: |%*.4c|", -8, val));
// 	// printf(" (%d)\n", printf("*(int)(-8.4): |%*c|", ((int)(-8.4)), val));
// 	// ft_printf(" (%d)\n", ft_printf("*(int)(-8.4): |%*c|", ((int)(-8.4)), val));
// 	// printf(" (%d)\n", printf("-8.*(4): |%-8.*c|", 4, val));
// 	// ft_printf(" (%d)\n", ft_printf("-8.*(4): |%-8.*c|", 4, val));
// 	// printf(" (%d)\n", printf("-8.*(-4): |%-8.*c|", -4, val));
// 	// ft_printf(" (%d)\n", ft_printf("-8.*(-4): |%-8.*c|", -4, val));
// 	// printf(" (%d)\n", printf("-8.*(0): |%-8.*c|", 0, val));
// 	// ft_printf(" (%d)\n", ft_printf("-8.*(0): |%-8.*c|", 0, val));
// 	// printf(" (%d)\n", printf("-8.*(1): |%-8.*c|", 1, val));
// 	// ft_printf(" (%d)\n", ft_printf("-8.*(1): |%-8.*c|", 1, val));
// 	// printf(" (%d)\n", printf("-*(0).4: |%-*.4c|", 0, val));
// 	// ft_printf(" (%d)\n", ft_printf("-*(0).4: |%-*.4c|", 0, val));
// 	// printf(" (%d)\n", printf("*(0).4: |%*.4c|", 0, val));
// 	// ft_printf(" (%d)\n", ft_printf("*(0).4: |%*.4c|", 0, val));


// 	printf("\n------------------------------------------------------------------------------------------------\n\n");

// 	printf(" (%d)\n", printf("Handling wildcards with 0 as input"));
// 	ft_printf(" (%d)\n", ft_printf("Handling wildcards with 0 as input"));
// 	printf("\n");

// 	// printf(" (%d)\n", printf("Mfw *1: |%*c|", 1, 0));
// 	// ft_printf(" (%d)\n", ft_printf("Mfw *1: |%*c|", 1, 0));
// 	// printf(" (%d)\n", printf("Mfw *5: |%*c|", 5, 0));
// 	// ft_printf(" (%d)\n", ft_printf("Mfw *5: |%*c|", 5, 0));
// 	// printf(" (%d)\n", printf("Mfw *5: |%*c|",5, 0));
// 	// ft_printf(" (%d)\n", ft_printf("Mfw *5: |%*c|", 5, 0));
// 	// printf(" (%d)\n", printf("Mfw *5: |%*c|",        5, 0));
// 	// ft_printf(" (%d)\n", ft_printf("Mfw *5: |%*c|",        5, 0));
// 	// printf(" (%d)\n", printf("Mfw *10: |%*c|", 10, 0));
// 	// ft_printf(" (%d)\n", ft_printf("Mfw *10: |%*c|", 10, 0));
// 	// printf(" (%d)\n", printf("Mfw *i: |%*c|", 0, 0));
// 	// ft_printf(" (%d)\n", ft_printf("Mfw *i: |%*c|", 0, 0));
// 	// printf("\n");

// 	// printf(" (%d)\n", printf("Precis. .*1: |%.*c|", 1, 0));
// 	// ft_printf(" (%d)\n", ft_printf("Precis. .*1: |%.*c|", 1, 0));
// 	// printf(" (%d)\n", printf("Precis. .*5: |%.*c|", 5, 0));
// 	// ft_printf(" (%d)\n", ft_printf("Precis. .*5: |%.*c|", 5, 0));
// 	// printf(" (%d)\n", printf("Precis. .*5: |%.*c|",5, 0));
// 	// ft_printf(" (%d)\n", ft_printf("Precis. .*5: |%.*c|",5, 0));
// 	// printf(" (%d)\n", printf("Precis. .*5: |%.*c|",      5, 0));
// 	// ft_printf(" (%d)\n", ft_printf("Precis. .*5: |%.*c|",      5, 0));
// 	// printf(" (%d)\n", printf("Precis. .*10: |%.*c|", 10, 0));
// 	// ft_printf(" (%d)\n", ft_printf("Precis. .*10: |%.*c|", 10, 0));
// 	// printf(" (%d)\n", printf("Precis. .*i: |%.*c|", 0, 0));
// 	// ft_printf(" (%d)\n", ft_printf("Precis. .*i: |%.*c|", 0, 0));
// 	// printf("\n");

// 	// printf(" (%d)\n", printf("P .*0: |%.*c|", 0, 0));
// 	// ft_printf(" (%d)\n", ft_printf("P .*0: |%.*c|", 0, 0));
// 	// printf(" (%d)\n", printf("P .*01: |%.*c|", 01, 0));
// 	// ft_printf(" (%d)\n", ft_printf("P .*01: |%.*c|", 01, 0));
// 	// printf(" (%d)\n", printf("P .*05: |%.*c|", 05, 0));
// 	// ft_printf(" (%d)\n", ft_printf("P .*05: |%.*c|", 05, 0));
// 	// printf(" (%d)\n", printf("P .*010: |%.*c|", 010, 0));
// 	// ft_printf(" (%d)\n", ft_printf("P .*010: |%.*c|", 010, 0));
// 	// printf(" (%d)\n", printf("P .*000000000007: |%.*c|", 000000000007, 0));
// 	// ft_printf(" (%d)\n", ft_printf("P .*000000000007: |%.*c|", 000000000007, 0));
// 	// printf("\n");

// 	// printf(" (%d)\n", printf("*8.4: |%*.4c|", 8, 0));
// 	// ft_printf(" (%d)\n", ft_printf("*8.4: |%*.4c|", 8, 0));
// 	// printf(" (%d)\n", printf("*4.8: |%*.8c|", 4, 0));
// 	// ft_printf(" (%d)\n", ft_printf("*4.8: |%*.8c|", 4, 0));
// 	// printf(" (%d)\n", printf("*8.8: |%*.8c|", 8, 0));
// 	// ft_printf(" (%d)\n", ft_printf("*8.8: |%*.8c|", 8, 0));
// 	// printf("\n");

// 	// printf(" (%d)\n", printf("8.*4: |%8.*c|", 4, 0));
// 	// ft_printf(" (%d)\n", ft_printf("8.*4: |%8.*c|", 4, 0));
// 	// printf(" (%d)\n", printf("4.*8: |%4.*c|", 8, 0));
// 	// ft_printf(" (%d)\n", ft_printf("4.*8: |%4.*c|", 8, 0));
// 	// printf(" (%d)\n", printf("8.*8: |%8.*c|", 8, 0));
// 	// ft_printf(" (%d)\n", ft_printf("8.*8: |%8.*c|", 8, 0));
// 	// printf("\n");

// 	// printf(" (%d)\n", printf("*8.*4: |%*.*c|", 8, 4, 0));
// 	// ft_printf(" (%d)\n", ft_printf("*8.*4: |%*.*c|", 8, 4, 0));
// 	// printf(" (%d)\n", printf("*4.*8: |%*.*c|", 4, 8, 0));
// 	// ft_printf(" (%d)\n", ft_printf("*4.*8: |%*.*c|", 4, 8, 0));
// 	// printf(" (%d)\n", printf("*8.*8: |%*.*c|", 8, 8, 0));
// 	// ft_printf(" (%d)\n", ft_printf("*8.*8: |%*.*c|", 8, 8, 0));
// 	// printf("\n");

// 	// printf("WEIRD OCTAL SHIT:\n");
// 	// printf(" (%d)\n", printf("*010.*4: |%*.*c|", 010, 4, 0));
// 	// ft_printf(" (%d)\n", ft_printf("*010.*4: |%*.*c|", 010, 4, 0));
// 	// printf(" (%d)\n", printf(" *07.*4: |%*.*c|", 07, 4, 0));
// 	// ft_printf(" (%d)\n", ft_printf(" *07.*4: |%*.*c|", 07, 4, 0));
// 	// printf(" (%d)\n", printf("*4.*010: |%*.*c|", 4, 010, 0));
// 	// ft_printf(" (%d)\n", ft_printf("*4.*010: |%*.*c|", 4, 010, 0));
// 	// printf("WEIRD HEXADECIMAL SHIT:\n");
// 	// printf(" (%d)\n", printf("*0x10.*4: |%*.*c|", 0x10, 4, 0));
// 	// ft_printf(" (%d)\n", ft_printf("*0x10.*4: |%*.*c|", 0x10, 4, 0));
// 	// printf(" (%d)\n", printf(" *0x7.*4: |%*.*c|", 0x7, 4, 0));
// 	// ft_printf(" (%d)\n", ft_printf(" *0x7.*4: |%*.*c|", 0x7, 4, 0));
// 	// printf(" (%d)\n", printf("*4.*0x10: |%*.*c|", 4, 0x10, 0));
// 	// ft_printf(" (%d)\n", ft_printf("*4.*0x10: |%*.*c|", 4, 0x10, 0));
// 	// printf("\n");



// 	//int octal;

// 	// octal = 010;
// 	// octal--;

// 	// printf("octal: %i\n", octal);

// 	// //this will print 7.

// 	// int octal_atoi;

// 	// octal_atoi = atoi("010");
// 	// octal_atoi--;

// 	// printf("octal: %i\n", octal_atoi);

// 	// //this will print 9.

// 	// int hexadec;

// 	// hexadec = 0x10;
// 	// hexadec--;

// 	// printf("hexadec: %i\n", hexadec);

// 	// //this will print 15.

// 	// int hexadec_atoi;

// 	// hexadec_atoi = atoi("0x10");
// 	// hexadec_atoi--;

// 	// printf("hexadec: %i\n", hexadec_atoi);

// 	// //this will print -1.

// 	// printf(" (%d)\n", printf("*8: |%*c|", 8, 0));
// 	// ft_printf(" (%d)\n", ft_printf("*8: |%*c|", 8, 0));
// 	// printf(" (%d)\n", printf("0*8: |%0*c|", 8, 0));
// 	// ft_printf(" (%d)\n", ft_printf("0*8: |%0*c|", 8, 0));
// 	// printf(" (%d)\n", printf("00*8: |%00*c|", 8, 0));
// 	// ft_printf(" (%d)\n", ft_printf("00*8: |%00*c|", 8, 0));
// 	// printf(" (%d)\n", printf("00000000000000000*8: |%00000000000000000*c|", 8, 0));
// 	// ft_printf(" (%d)\n", ft_printf("00000000000000000*8: |%00000000000000000*c|", 8, 0));
// 	// printf("\n");


// 	// printf(" (%d)\n", printf("-*0: |%-*c|", 0, 0));
// 	// ft_printf(" (%d)\n", ft_printf("-*0: |%-*c|", 0, 0));
// 	// printf(" (%d)\n", printf("-0*0: |%-0*c|", 0, 0));
// 	// ft_printf(" (%d)\n", ft_printf("-0*0: |%-0*c|", 0, 0));
// 	// printf(" (%d)\n", printf("-0*3: |%-0*c|", 3, 0));
// 	// ft_printf(" (%d)\n", ft_printf("-0*3: |%-0*c|", 3, 0));
// 	// printf(" (%d)\n", printf("*(-03): |%*c|", -03, 0));
// 	// ft_printf(" (%d)\n", ft_printf("*(-03): |%*c|", -03, 0));
// 	// printf(" (%d)\n", printf("*(-5): |%*c|", -5, 0));
// 	// ft_printf(" (%d)\n", ft_printf("*(-5): |%*c|", -5, 0));
// 	// printf(" (%d)\n", printf("*(5): |%*c|", 5, 0));
// 	// ft_printf(" (%d)\n", ft_printf("*(5): |%*c|", 5, 0));
// 	// printf(" (%d)\n", printf("-*(5): |%-*c|", 5, 0));
// 	// ft_printf(" (%d)\n", ft_printf("-*(5): |%-*c|", 5, 0));
// 	// printf(" (%d)\n", printf("-8.4: |%-8.4c|", 0));
// 	// ft_printf(" (%d)\n", ft_printf("-8.4: |%-8.4c|", 0));
// 	// printf(" (%d)\n", printf("-*(8).4: |%-*.4c|", 8, 0));
// 	// ft_printf(" (%d)\n", ft_printf("-*(8).4: |%-*.4c|", 8, 0));
// 	// printf(" (%d)\n", printf("*(-8).4: |%*.4c|", -8, 0));
// 	// ft_printf(" (%d)\n", ft_printf("*(-8).4: |%*.4c|", -8, 0));
// 	// printf(" (%d)\n", printf("*(int)(-8.4): |%*c|", ((int)(-8.4)), 0));
// 	// ft_printf(" (%d)\n", ft_printf("*(int)(-8.4): |%*c|", ((int)(-8.4)), 0));
// 	// printf(" (%d)\n", printf("-8.*(4): |%-8.*c|", 4, 0));
// 	// ft_printf(" (%d)\n", ft_printf("-8.*(4): |%-8.*c|", 4, 0));
// 	// printf(" (%d)\n", printf("-8.*(-4): |%-8.*c|", -4, 0));
// 	// ft_printf(" (%d)\n", ft_printf("-8.*(-4): |%-8.*c|", -4, 0));
// 	// printf(" (%d)\n", printf("-8.*(0): |%-8.*c|", 0, 0));
// 	// ft_printf(" (%d)\n", ft_printf("-8.*(0): |%-8.*c|", 0, 0));
// 	// printf(" (%d)\n", printf("-8.*(1): |%-8.*c|", 1, 0));
// 	// ft_printf(" (%d)\n", ft_printf("-8.*(1): |%-8.*c|", 1, 0));
// 	// printf(" (%d)\n", printf("-*(0).4: |%-*.4c|", 0, 0));
// 	// ft_printf(" (%d)\n", ft_printf("-*(0).4: |%-*.4c|", 0, 0));
// 	// printf(" (%d)\n", printf("*(0).4: |%*.4c|", 0, 0));
// 	// ft_printf(" (%d)\n", ft_printf("*(0).4: |%*.4c|", 0, 0));


// 	printf("\n------------------------------------------------------------------------------------------------\n\n");



// 	printf(" (%d)\n", printf("Negative ints are a pain:"));
// 	ft_printf(" (%d)\n", ft_printf("Negative ints are a pain:"));
// 	printf("\n");


// 	// printf(" (%d)\n", printf("Sometimes it struggles with negative ints: -08.7i |%-08.7c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("Sometimes it struggles with negative ints: -08.7i |%-08.7c|", val));
// 	// printf(" (%i)\n", printf("Sometimes it struggles with negative ints: -08.10i |%-08.10c|", val));
// 	// ft_printf(" (%i)\n", ft_printf("Sometimes it struggles with negative ints: -08.10i |%-08.10c|", val));
// 	// printf("\n");

// 	// printf(" (%d)\n", printf("Sometimes it struggles with negative ints: -8.7i |%-8.7c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("Sometimes it struggles with negative ints: -8.7i |%-8.7c|", val));
// 	// printf(" (%i)\n", printf("Sometimes it struggles with negative ints: -8.10i |%-8.10c|", val));
// 	// ft_printf(" (%i)\n", ft_printf("Sometimes it struggles with negative ints: -8.10i |%-8.10c|", val));
// 	// printf("\n");

// 	// printf(" (%d)\n", printf("Sometimes it struggles with negative ints: 8.7i |%8.7c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("Sometimes it struggles with negative ints: 8.7i |%8.7c|", val));
// 	// printf(" (%i)\n", printf("Sometimes it struggles with negative ints: 8.10i |%8.10c|", val));
// 	// ft_printf(" (%i)\n", ft_printf("Sometimes it struggles with negative ints: 8.10i |%8.10c|", val));
// 	// printf("\n");

// 	// printf(" (%d)\n", printf("Sometimes it struggles with negative ints: 08i |%08c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("Sometimes it struggles with negative ints: 08i |%08c|", val));
// 	// printf("\n");

// 	// printf(" (%d)\n", printf("Sometimes it struggles with negative ints: 8i |%8c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("Sometimes it struggles with negative ints: 8i |%8c|", val));
// 	// printf("\n");

// 	// printf(" (%d)\n", printf("Sometimes it struggles with negative ints: 8.5i |%8.5c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("Sometimes it struggles with negative ints: 8.5i |%8.5c|", val));
// 	// printf("\n");

// 	// printf(" (%d)\n", printf("Sometimes it struggles with negative ints: -8i |%-8c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("Sometimes it struggles with negative ints: -8i |%-8c|", val));
// 	// printf("\n");

// 	// printf(" (%d)\n", printf("Sometimes it struggles with negative ints: -8.5i |%-8.5c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("Sometimes it struggles with negative ints: -8.5i |%-8.5c|", val));
// 	// printf("\n");


// 	// printf(" (%d)\n", printf("Sometimes it struggles with negative ints: -08.7i |%-08.7c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("Sometimes it struggles with negative ints: -08.7i |%-08.7c|", val));
// 	// printf(" (%i)\n", printf("Sometimes it struggles with negative ints: -08.10i |%-08.10c|", val));
// 	// ft_printf(" (%i)\n", ft_printf("Sometimes it struggles with negative ints: -08.10i |%-08.10c|", val));
// 	// printf("\n");

// 	// printf(" (%d)\n", printf("Sometimes it struggles with negative ints: -8.7i |%-8.7c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("Sometimes it struggles with negative ints: -8.7i |%-8.7c|", val));
// 	// printf(" (%i)\n", printf("Sometimes it struggles with negative ints: -8.10i |%-8.10c|", val));
// 	// ft_printf(" (%i)\n", ft_printf("Sometimes it struggles with negative ints: -8.10i |%-8.10c|", val));
// 	// printf("\n");

// 	// printf(" (%d)\n", printf("Sometimes it struggles with negative ints: 8.7i |%8.7c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("Sometimes it struggles with negative ints: 8.7i |%8.7c|", val));
// 	// printf(" (%i)\n", printf("Sometimes it struggles with negative ints: 8.10i |%8.10c|", val));
// 	// ft_printf(" (%i)\n", ft_printf("Sometimes it struggles with negative ints: 8.10i |%8.10c|", val));
// 	// printf("\n");

// 	// printf(" (%d)\n", printf("Sometimes it struggles with negative ints: 08i |%08c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("Sometimes it struggles with negative ints: 08i |%08c|", val));
// 	// printf("\n");

// 	// printf(" (%d)\n", printf("Sometimes it struggles with negative ints: 8i |%8c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("Sometimes it struggles with negative ints: 8i |%8c|", val));
// 	// printf("\n");

// 	// printf(" (%d)\n", printf("Sometimes it struggles with negative ints: 8.5i |%8.5c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("Sometimes it struggles with negative ints: 8.5i |%8.5c|", val));
// 	// printf("\n");

// 	// printf(" (%d)\n", printf("Sometimes it struggles with negative ints: -8i |%-8c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("Sometimes it struggles with negative ints: -8i |%-8c|", val));
// 	// printf("\n");

// 	// printf(" (%d)\n", printf("Sometimes it struggles with negative ints: -8.5i |%-8.5c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("Sometimes it struggles with negative ints: -8.5i |%-8.5c|", val));
// 	// printf("\n");


// 	// printf("\n------------------------------------------------------------------------------------------------\n\n");

// 	// // printf(" (%d)\n", printf("Some edge cases I thought of whilst writing:"));
// 	// // ft_printf(" (%d)\n", ft_printf("Some edge cases I thought of whilst writing:"));
// 	// // printf("\n");

// 	// // printf(" (%d)\n", printf("8.: |%8.c|", 0));
// 	// // ft_printf(" (%d)\n", ft_printf("8.: |%8.c|", 0));
// 	// // printf(" (%d)\n", printf("8.: |%8.c|", 42));
// 	// // ft_printf(" (%d)\n", ft_printf("8.: |%8.c|", 42));
// 	// // printf(" (%d)\n", printf("08.*(-4): |%08.*c|", -4, 42));
// 	// // ft_printf(" (%d)\n", ft_printf("08.*(-4): |%08.*c|", -4, 42));
// 	// // printf("\n");

// 	// printf("\n------------------------------------------------------------------------------------------------\n\n");

// 	// printf(" (%d)\n", printf("I LIKE BIG DIGITS AND I CANNOT LIE"));
// 	// ft_printf(" (%d)\n", ft_printf("I LIKE BIG DIGITS AND I CANNOT LIE"));
// 	// printf("\n");


// 	// printf(" (%d)\n", printf("Sometimes it be like that: -018.17i |%-018.17c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("Sometimes it be like that: -018.17i |%-018.17c|", val));
// 	// printf(" (%i)\n", printf("Sometimes it be like that: -018.20i |%-018.20c|", val));
// 	// ft_printf(" (%i)\n", ft_printf("Sometimes it be like that: -018.20i |%-018.20c|", val));
// 	// printf("\n");

// 	// printf(" (%d)\n", printf("Sometimes it be like that: -18.17i |%-18.17c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("Sometimes it be like that: -18.17i |%-18.17c|", val));
// 	// printf(" (%i)\n", printf("Sometimes it be like that: -18.20i |%-18.20c|", val));
// 	// ft_printf(" (%i)\n", ft_printf("Sometimes it be like that: -18.20i |%-18.20c|", val));
// 	// printf("\n");

// 	// printf(" (%d)\n", printf("Sometimes it be like that: 18.17i |%18.17c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("Sometimes it be like that: 18.17i |%18.17c|", val));
// 	// printf(" (%i)\n", printf("Sometimes it be like that: 18.20i |%18.20c|", val));
// 	// ft_printf(" (%i)\n", ft_printf("Sometimes it be like that: 18.20i |%18.20c|", val));
// 	// printf("\n");

// 	// printf(" (%d)\n", printf("Sometimes it be like that: 018i |%018c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("Sometimes it be like that: 018i |%018c|", val));
// 	// printf("\n");

// 	// printf(" (%d)\n", printf("Sometimes it be like that: 18i |%18c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("Sometimes it be like that: 18i |%18c|", val));
// 	// printf("\n");

// 	// printf(" (%d)\n", printf("Sometimes it be like that: 18.15i |%18.15c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("Sometimes it be like that: 18.15i |%18.15c|", val));
// 	// printf("\n");

// 	// printf(" (%d)\n", printf("Sometimes it be like that: -18i |%-18c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("Sometimes it be like that: -18i |%-18c|", val));
// 	// printf("\n");

// 	// printf(" (%d)\n", printf("Sometimes it be like that: -18.15i |%-18.15c|", val));
// 	// ft_printf(" (%d)\n", ft_printf("Sometimes it be like that: -18.15i |%-18.15c|", val));
// 	// printf("\n");


// 	return (0);
// }
