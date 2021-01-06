/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   struct_functions.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: icikrikc <icikrikc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/03 10:31:04 by icikrikc      #+#    #+#                 */
/*   Updated: 2021/01/06 16:02:26 by icikrikc      ########   odam.nl         */
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

void	free_t_data(t_data *data)
{
	if (!data)
		return ;
	free(data->flag);
	free(data->width);
	free(data->precision);
	free(data);
}
