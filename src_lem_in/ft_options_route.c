/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_options_route.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egottlie <egottlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 14:07:03 by ljonnel-          #+#    #+#             */
/*   Updated: 2019/09/21 16:29:36 by egottlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			ft_check_paths_target(t_data *data)
{
	int			i;
	int			t;
	int			count_step;
	int			count;

	i = 1;
	count = 1;
	if (count <= data->count_route)
	{
		while (count <= data->count_route)
		{
			t = 0;
			count_step = 0;
			while (count >= ++t)
				count_step += data->few_route_last->route[t][1];
			data->few_route_last->options_paths[i][0] =
			ft_check_route(data->ants, count, count_step);
			t -= 1;
			data->few_route_last->options_paths[i][1] = t;
			i++;
			count++;
		}
		i--;
	}
	data->count_route = i;
}

int				ft_check_route(int ants, int count_path, int sum_step)
{
	int			res_iter;

	res_iter = (sum_step + (ants - count_path)) / count_path;
	if ((sum_step + (ants - count_path)) % count_path != 0)
		res_iter++;
	return (res_iter);
}

int				ft_options_route(t_data *data)
{
	int			min_path;
	int			i;

	i = 1;
	min_path = data->few_route_last->options_paths[i][0];
	while (i <= data->count_route)
	{
		if (min_path > data->few_route_last->options_paths[i][0])
			min_path = data->few_route_last->options_paths[i][0];
		i++;
	}
	i = 1;
	while (i <= data->count_route)
	{
		if (min_path == data->few_route_last->options_paths[i][0])
			return (i);
		i++;
	}
	return (i);
}

void			ft_count_route(t_data *data)
{
	int			j;
	int			tmp;
	int			count;
	int			ants;

	count = 1;
	ants = 1;
	j = data->route[data->count_route][1];
	data->route[data->count_route][j + 3] = 1;
	while (data->count_route > count && data->ants > ants)
	{
		tmp = ft_count_ants_in_path(j, data->route[count][1]);
		data->route[count][data->route[count][1] + 3] = tmp + 1;
		count++;
		ants += tmp + 1;
	}
	while (data->ants > ants)
	{
		count = 0;
		while (data->ants > ants && ++count <= data->count_route)
		{
			data->route[count][data->route[count][1] + 3] += 1;
			ants++;
		}
	}
}

int				ft_path_for_ants(t_data *data)
{
	int	path;
	int	j;
	int	ant;

	j = 0;
	if (!(data->path_ant = (t_path_for_ant **)malloc(sizeof(t_path_for_ant *) *
			(data->ants + 1))))
		return (-1);
	ant = 1;
	while (ant <= data->ants)
	{
		path = 1;
		while (path <= data->count_route)
		{
			if (data->route[path][data->route[path][1] + 3] > j)
			{
				if (ft_add_path_for_ant(data, ant, path) == -1)
					return (-1);
				ant++;
			}
			path++;
		}
		j++;
	}
	return (1);
}
