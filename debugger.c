# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft/libft.h"

typedef	struct			s_data
{
	// int					index;
	// int					index_arg;
	char				type;
	char				*flag;
	char				*width;
	char				*precision;
	int					length;
	// char				*content;
	int					counter;
	// double				n_double;
	// struct s_data		*next;
}						t_data;

t_data	*create_t_data(int format_len)
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
	data->counter = format_len;
	// data->next = NULL;
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

//pdf says minimum field? difference with max?
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

	start = *i;
	if (format[*i] != '.')
		return(ft_strdup(""));
	(*i)++;
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
	printf("type: %c ", data->type);
	printf("flag: %s ", data->flag);
	printf("width: %s ", data->width);
	printf("precision: %s ", data->precision);
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

// char *handle_pointer(void *pointer)
// {
// 	char *to_print;
// 	char *str;

// 	str = ft_xtoa(); // you need to write it downnnn!
// 	to_print = ft_strjoin("0x", str);
// 	free(str);
// 	return (to_print);
// }

char	*handle_argument(va_list args, t_data *data, char *to_print)
{
	char *tmp;

	if (data->type == 'c')
		tmp = handle_char(va_arg(args, int));
	if (data->type == 's')
		tmp = handle_string(va_arg(args, char *));
	// if (data->type == 'p')
	// 	tmp = handle_pointer(va_arg(args, void *));
	if (data->type == '%')
		tmp = ft_strdup("%");
	if (data->type == 'd' || data->type == 'i' ||data->type == 'u' ||
	data->type == 'x' || data->type == 'X')
		tmp = handle_integer(args);
	free(to_print);
	to_print = tmp;
	return (to_print); //should I return to_print or does it authomatically change outside of this function?
}

int	print_argument(va_list args, t_data *data)
{
	int		arg_len;
	char	*to_print;

	arg_len = 0;
	to_print = ft_strdup("");
	if (!to_print)
		return (-1); //then what in parse_format func?
	//what about * w/width and precision?
	to_print = handle_argument(args, data, to_print);


	//check if to_print is null and return -1?
	arg_len = ft_strlen(to_print);
	free(to_print);
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
			format_len += print_regular(format, &i); //another function to parse regular input?
		else if (format[i])
		{
			data = create_t_data(format_len);
			if (!data)
				return (-1);
			//check if there are further symbols (cspdiouxXfyb%#-+ .*0123456789hLljz)?
			if (!ft_strchr("cspdiouxXfyb%#-+ .*0123456789hLljz", format[i + 1])) //another function is valid_type_flag etc.
				break ; // which loop does this break from? is it okay? or return (-1)?
			get_argument(format, &i, data);
			//print this particular arg with t_data info? + free data?
			format_len += print_argument(args, data);
			printf("ONE ARG DONE!\n");
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
	int	return_val;
	// return_val = ft_printf("This is regular input. These are argument inputs:\nchar:%# c AND\nstring:%s", 'X', "mahmut");
	return_val = ft_printf("This\n%-0c &\n%s &\n%3.5d &\n%-4d", 'X', "mahmut", 1234, 3456);
	// return_val = ft_printf("This is regular input.");
	ft_printf("\n");
	printf("ft_return_val: %d\n", return_val);
	// return_val = printf("what will happen %c and %s", 'X', "mahmut");
	// printf("\n");
	// printf("li_return_val: %d\n", return_val);
	return (0);
}
