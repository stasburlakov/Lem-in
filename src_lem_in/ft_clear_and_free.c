/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear_and_free.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egottlie <egottlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 14:42:44 by ljonnel-          #+#    #+#             */
/*   Updated: 2019/09/21 16:29:19 by egottlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_clear_color_and_len(t_data *data)
{
	int				i;

	i = 0;
	while (i <= data->size)
	{
		data->t[i].color = 0;
		data->t[i].len = 0;
		i++;
	}
}

void	ft_clear_possible_path(t_data *data)
{
	int				i;

	i = 0;
	while (i < data->size)
	{
		data->t[i].possible_path = 0;
		i++;
	}
}

void	ft_clear_path(t_data *data, t_list_path *path,
		t_list_path *tmp_path)
{
	path = tmp_path;
	while (path)
	{
		data->t[path->number_node].possible_path = 1;
		path = path->next;
	}
}

void	ft_free_path(t_data *data)
{
	t_list_path		*path;

	while (data->path != NULL)
	{
		path = data->path->next;
		free(data->path);
		data->path = path;
	}
}

void	ft_del_path_for_ant(t_data *data)
{
	t_path_for_ant	*tmp;
	int				ant;

	ant = 1;
	if (data && data->path_ant != NULL)
	{
		while (data->ants >= ant)
		{
			tmp = data->path_ant[ant];
			while (tmp != NULL)
			{
				data->path_ant[ant] = data->path_ant[ant]->next;
				free(tmp);
				tmp = data->path_ant[ant];
			}
			ant++;
		}
		free(data->path_ant);
	}
}
