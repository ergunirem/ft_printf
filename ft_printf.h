/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/18 18:42:07 by ergunirem     #+#    #+#                 */
/*   Updated: 2020/12/25 15:50:02 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#ifndef FTPRINTF_H
# define FTPRINTF_H
# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft/libft.h"

// typedef struct		s_data
// {
// 	// int				index;
// 	int				counter;
// 	// char			buffer;
// 	int				type;
// 	int				flag;
// 	int				width;
// 	int				precision;
// 	// struct s_data	*next;
// }					t_data;

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

int	ft_printf(const char *format, ...);
int	parse_format(const char *format);

//struct functions
t_data	*create_t_data(int format_len);
void	free_t_data(t_data *ptr_data);

#endif
