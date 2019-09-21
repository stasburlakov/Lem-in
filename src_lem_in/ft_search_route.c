/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_route.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egottlie <egottlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 14:00:33 by ljonnel-          #+#    #+#             */
/*   Updated: 2019/09/21 16:29:51 by egottlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void				ft_search_path(t_data *data)
{
	ft_clear_color_and_len(data);
	ft_traverse(data);
	if (ft_check_all_path(data, 0) != 10)
		ft_search_path(data);
}

void				ft_search_route_1(t_data *data)
{
	int				t;
	int				count_step;
	int				len;

	data->count_route = 0;
	t = 1;
	count_step = 0;
	ft_search_path(data);
	if (data->count_route != 0)
	{
		ft_check_paths_target(data);
		data->few_route_last->count_route = ft_options_route(data);
		len = data->few_route_last->count_route;
		while (len >= t)
		{
			count_step += data->few_route_last->route[t][1];
			t++;
		}
		data->few_route_last->count_str = ft_check_route(data->ants,
		data->few_route_last->count_route, count_step);
	}
	ft_clear_possible_path(data);
}

int					ft_new_several_path(t_data *data)
{
	if (!(data->few_route_last->next =
	(t_several_path *)malloc(sizeof(t_several_path))))
		return (-1);
	data->few_route_last = data->few_route_last->next;
	data->few_route_last->count_route = 0;
	data->few_route_last->next = NULL;
	return (1);
}

int					ft_search_route(t_data *data)
{
	int				i;
	int				tr;

	tr = 1;
	if (!(data->few_route_last =
	(t_several_path *)malloc(sizeof(t_several_path))))
		return (-1);
	data->few_route_last->count_route = 0;
	data->few_route_last->next = NULL;
	data->few_route = data->few_route_last;
	while (1)
	{
		ft_search_route_1(data);
		if (tr == 1)
			i = data->few_route->route[1][1];
		tr++;
		if (--i <= 0)
			break ;
		else
			data->t[data->few_route->route[1][tr]].possible_path = -1;
		if (data->count_route != 0)
			ft_new_several_path(data);
	}
	return (1);
}

int					ft_choice_route(t_data *data)
{
	int i;

	i = 0;
	ft_few_route(data, i);
	ft_copy_arr(data);
	ft_count_route(data);
	ft_display_ants_moved(data);
	ft_del_path_for_ant(data);
	ft_free_route(data);
	return (1);
}
