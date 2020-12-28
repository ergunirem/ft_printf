/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   struct_functions.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/24 21:37:38 by ergunirem     #+#    #+#                 */
/*   Updated: 2020/12/25 15:47:37 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
