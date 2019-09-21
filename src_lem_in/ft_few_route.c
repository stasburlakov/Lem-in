/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_few_route.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egottlie <egottlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 14:07:53 by ljonnel-          #+#    #+#             */
/*   Updated: 2019/09/21 16:29:32 by egottlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void				ft_copy_arr(t_data *data)
{
	int				i;
	t_several_path	*tmp;
	int				j;

	i = -1;
	tmp = data->few_route;
	while (++i < data->best_route)
		tmp = tmp->next;
	data->count_route = tmp->count_route;
	i = 0;
	while (i < 1000)
	{
		j = 0;
		while (j < 1000)
		{
			data->route[i][j] = tmp->route[i][j];
			data->options_paths[i][j] = tmp->options_paths[i][j];
			j++;
		}
		i++;
	}
}

void				ft_few_route(t_data *data, int i)
{
	t_several_path	*tmp;
	int				min_number;

	data->best_route = 0;
	tmp = data->few_route;
	while (tmp)
	{
		if (tmp->count_route != 0)
		{
			min_number = tmp->count_str;
			break ;
		}
		tmp = tmp->next;
	}
	tmp = data->few_route;
	while (tmp != NULL)
	{
		if (min_number > tmp->count_str && tmp->count_route != 0)
		{
			min_number = tmp->count_str;
			data->best_route = i;
		}
		tmp = tmp->next;
		i++;
	}
}

void				ft_free_route(t_data *data)
{
	t_several_path	*tmp;

	tmp = data->few_route;
	while (tmp)
	{
		data->few_route = data->few_route->next;
		free(tmp);
		tmp = data->few_route;
	}
}

int					ft_count_ants_in_path(int j, int count_step)
{
	int				tmp;

	tmp = 0;
	while (j > count_step)
	{
		tmp++;
		count_step++;
	}
	return (tmp);
}

int					ft_check_count_path(t_data *data, int path)
{
	int				count;
	int				i;

	count = 1;
	i = 0;
	while (count <= path)
	{
		if (data->route[count][data->route[count][1] + 3] == 0)
			i++;
		else
			data->route[count][data->route[count][1] + 3] -= 1;
		count++;
	}
	return (path - i);
}
