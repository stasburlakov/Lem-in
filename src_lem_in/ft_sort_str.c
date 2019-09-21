/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egottlie <egottlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 17:18:38 by ljonnel-          #+#    #+#             */
/*   Updated: 2019/09/21 16:29:56 by egottlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		check_duplicate(t_new *t, int size)
{
	while (--size > 0)
		if (!ft_strcmp(t[size].name, t[size - 1].name))
			return (1);
	return (0);
}

void	sort_parse(t_data *data, char **line)
{
	char	*tmp_start;
	char	*tmp_end;

	if (data->start < 0 || data->end < 0 || data->start == data->end)
	{
		free_data(data, 1);
		ft_putendl(*line);
		free(*line);
		ft_putstr_fd("ERROR (invalid start or and)\n", 2);
		exit(-1);
	}
	tmp_start = data->t[data->start].name;
	tmp_end = data->t[data->end].name;
	quick_sort(data->t, data->size);
	if (check_duplicate(data->t, data->size) > 0)
	{
		ft_putstr_fd("ERROR (duplicate_rooms)\n", 2);
		free_data(data, 1);
		exit(-1);
	}
	data->start = binarysearch_str(tmp_start, data->t, data->size);
	data->end = binarysearch_str(tmp_end, data->t, data->size);
}

void	quick_sort(t_new *t, int n)
{
	int	index_pivot;

	index_pivot = partition(t, n);
	if (index_pivot > 0)
		quick_sort(t, index_pivot);
	if (index_pivot + 1 < n)
		quick_sort(t + index_pivot + 1, n - (index_pivot + 1));
}

int		partition(t_new *t, int n)
{
	char	*pivot;
	int		i;
	int		j;

	if (n <= 1)
		return (0);
	pivot = t[n - 1].name;
	i = 0;
	j = n - 2;
	while (i <= j)
	{
		while (ft_strcmp(t[i].name, pivot) < 0)
			i++;
		while (j >= 0 && ft_strcmp(t[j].name, pivot) >= 0)
			j--;
		if (i < j)
			ft_swap_strings(t, i++, j--);
	}
	if (i != n - 1)
		ft_swap_strings(t, i, n - 1);
	return (i);
}

void	ft_swap_strings(t_new *t, int i, int j)
{
	char	*tmp;
	int		tmp_x;
	int		tmp_y;

	tmp = t[i].name;
	tmp_x = t[i].coord[0];
	tmp_y = t[i].coord[1];
	t[i].coord[0] = t[j].coord[0];
	t[i].coord[1] = t[j].coord[1];
	t[j].coord[0] = tmp_x;
	t[j].coord[1] = tmp_y;
	t[i].name = t[j].name;
	t[j].name = tmp;
}
