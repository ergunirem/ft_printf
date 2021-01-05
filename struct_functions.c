/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   struct_functions.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/03 10:31:04 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/01/04 22:04:30 by icikrikc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
