/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_ants.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egottlie <egottlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 17:18:08 by ljonnel-          #+#    #+#             */
/*   Updated: 2019/09/21 16:29:40 by egottlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		check_line(char *s)
{
	while (*s)
	{
		if (*s > '9' || *s < '0')
			return (1);
		s++;
	}
	return (0);
}

void	ants_determination(t_data *data)
{
	char	*line;

	null_struct(data);
	if (get_next_line(data->fd, &line) == 0)
	{
		ft_putstr_fd("ERROR (empty_maps)\n", 2);
		free_data(data, 0);
		exit(-1);
	}
	data->ants = ft_atoi(line);
	if (data->ants <= 0 || check_line(line))
	{
		ft_putendl(line);
		free(line);
		ft_putstr_fd("ERROR (error_ants)\n", 2);
		free_data(data, 0);
		exit(-1);
	}
	ft_putendl(line);
	free(line);
	data->t = (t_new*)malloc(sizeof(t_new) * data->max_size);
}

int		binarysearch_str(char *a, t_new *t, int n)
{
	int low;
	int	high;
	int	middle;

	low = 0;
	high = n - 1;
	while (low <= high)
	{
		middle = (low + high) / 2;
		if (strcmp(a, t[middle].name) < 0)
			high = middle - 1;
		else if (strcmp(a, t[middle].name) > 0)
			low = middle + 1;
		else
			return (middle);
	}
	return (-1);
}

void	null_struct(t_data *data)
{
	data->max_size = 20;
	data->start = -2;
	data->end = -2;
	data->ants = 0;
	data->size = 0;
}
