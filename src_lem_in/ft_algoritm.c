/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_algoritm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egottlie <egottlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 14:00:44 by ljonnel-          #+#    #+#             */
/*   Updated: 2019/09/21 16:28:24 by egottlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				ft_traverse(t_data *data)
{
	t_queue		queue;
	int			number_room;
	t_list_link	*tmp_link;

	data->t[data->start].len = 0;
	init_que(&queue);
	data->max_len = 0;
	push_que(&queue, data->start);
	while (!isempty_que(&queue))
	{
		number_room = pop_que(&queue);
		tmp_link = data->t[number_room].list;
		data->t[number_room].color = 1;
		ft_traverse_2(data, &queue, number_room, tmp_link);
	}
	return (1);
}

int				ft_traverse_2(t_data *data, t_queue *queue, int number_room,
				t_list_link *tmp_link)
{
	while (tmp_link)
	{
		if (number_room != data->end && number_room != data->start &&
			data->t[number_room].size_list_step == 1)
		{
			if (data->t[number_room].possible_path != -1)
				data->t[number_room].possible_path = -1;
		}
		else if (data->t[tmp_link->number].color == 0 &&
			data->t[tmp_link->number].possible_path != -1 &&
			data->t[number_room].possible_path != -1)
		{
			data->t[tmp_link->number].color = 1;
			data->t[tmp_link->number].len = data->t[number_room].len + 1;
			if (tmp_link->number != data->end)
				push_que(queue, tmp_link->number);
			if (data->max_len < data->t[tmp_link->number].len)
				data->max_len = data->t[tmp_link->number].len;
		}
		tmp_link = tmp_link->next;
	}
	return (1);
}

int				ft_check_all_path_2(t_data *data, t_list_path *path,
				t_list_path *tmp_path, int i)
{
	if (path->number_node == data->start && tmp_path->number_node == data->end
		&& data->flag)
	{
		path = tmp_path;
		data->count_route++;
		data->few_route_last->route[data->count_route][1] = i - 1;
		i += 1;
		while (i > 1)
		{
			data->few_route_last->route[data->count_route][i] =
			path->number_node;
			path = path->next;
			i--;
		}
		data->few_route_last->route[data->count_route][0] = ft_check_route(
		data->ants, 1, data->few_route_last->route[data->count_route][1]);
		data->path = tmp_path;
		ft_free_path(data);
		return (1);
	}
	else if (data->flag == 1)
		ft_clear_path(data, path, tmp_path);
	return (-1);
}

int				ft_check_all_path_1(t_data *data, t_list_link *tmp_link,
				int len, t_list_path **path)
{
	int			i;

	i = 1;
	while (tmp_link)
	{
		if (data->t[tmp_link->number].len == len &&
			data->t[tmp_link->number].list->possible_path != -1 &&
			data->t[tmp_link->number].possible_path != -1)
		{
			i++;
			if ((tmp_link->number != data->start &&
				tmp_link->number != data->end) || i == 2)
				data->t[tmp_link->number].possible_path = -1;
			if (!((*path)->next = (t_list_path *)malloc(sizeof(t_list_path))))
				return (-1);
			(*path) = (*path)->next;
			(*path)->next = NULL;
			(*path)->number_node = tmp_link->number;
			len--;
			tmp_link = data->t[(*path)->number_node].list;
		}
		else
			tmp_link = tmp_link->next;
	}
	return (i);
}

int				ft_check_all_path(t_data *data, int tmp_len)
{
	int			len;
	int			i;
	t_list_path	*path;
	t_list_path	*tmp_path;
	t_list_link	*tmp_link;

	tmp_link = data->t[data->end].list;
	len = tmp_len;
	if (tmp_len > data->max_len)
		return (10);
	if (!(path = (t_list_path *)malloc(sizeof(t_list_path))))
		return (-1);
	path->number_node = data->end;
	path->next = NULL;
	tmp_path = path;
	i = ft_check_all_path_1(data, tmp_link, len, &path);
	data->flag = i > 1 ? 1 : 0;
	if (i == -1 || (ft_check_all_path_2(data, path, tmp_path, i) == 1))
		return (-1);
	data->path = tmp_path;
	ft_free_path(data);
	return (ft_check_all_path(data, tmp_len + 1));
}
