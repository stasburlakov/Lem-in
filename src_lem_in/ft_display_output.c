/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_output.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egottlie <egottlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 14:01:54 by ljonnel-          #+#    #+#             */
/*   Updated: 2019/09/21 16:29:27 by egottlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft__display_ants_moved_2(t_data *data)
{
	int				end;
	int				path;

	end = 0;
	path = data->count_route;
	while (1)
	{
		if (end >= data->ants)
		{
			ft_display_output(data, data->ants);
			break ;
		}
		path = ft_check_count_path(data, path);
		end += path;
		ft_display_output(data, end);
	}
}

int		ft_display_ants_moved(t_data *data)
{
	t_path_for_ant	**tmp;

	ft_putchar('\n');
	if (ft_path_for_ants(data) == -1)
	{
		ft_del_path_for_ant(data);
		return (-1);
	}
	tmp = data->path_ant;
	ft__display_ants_moved_2(data);
	while (ft_display_output(data, data->ants) > 0)
		;
	data->path_ant = tmp;
	return (1);
}

int		ft_display_output2(int i, int ant, t_data *data, int path)
{
	t_path_for_ant	*tmp;

	tmp = data->path_ant[ant];
	if (data->path_ant[ant] && data->path_ant[ant]->path == path)
	{
		if (data->flag == 0)
			ft_printf("L%d-%s", ant, data->path_ant[ant]->name);
		else
			ft_printf(" L%d-%s", ant, data->path_ant[ant]->name);
		data->path_ant[ant] = data->path_ant[ant]->next;
		free(tmp);
		i++;
		data->flag++;
	}
	return (i);
}

int		ft_display_output(t_data *data, int end)
{
	int				path;
	int				ant;
	int				i;

	path = 1;
	i = 0;
	data->flag = 0;
	while (path <= data->count_route)
	{
		ant = 1;
		while (ant <= end)
		{
			i = ft_display_output2(i, ant, data, path);
			ant++;
		}
		path++;
	}
	(i != 0) ? ft_printf("\n") : 0;
	return (i);
}

int		ft_add_path_for_ant(t_data *data, int ant, int path)
{
	t_path_for_ant	*tmp;
	int				i;

	i = 3;
	if (!(tmp = (t_path_for_ant *)malloc(sizeof(t_path_for_ant))))
		return (-1);
	tmp->name = data->t[data->route[path][i]].name;
	tmp->path = path;
	tmp->next = NULL;
	data->path_ant[ant] = tmp;
	while (data->route[path][1] > ++i - 3)
	{
		if (!(tmp->next = (t_path_for_ant *)malloc(sizeof(t_path_for_ant))))
			return (-1);
		tmp = tmp->next;
		tmp->name = data->t[data->route[path][i]].name;
		tmp->path = path;
		tmp->next = NULL;
	}
	return (1);
}
