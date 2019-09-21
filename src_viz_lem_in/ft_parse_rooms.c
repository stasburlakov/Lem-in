/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_rooms.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egottlie <egottlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 17:18:22 by ljonnel-          #+#    #+#             */
/*   Updated: 2019/09/21 16:30:37 by egottlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		rooms_determination2(t_data *data, char *line)
{
	int j;

	if (line[0] == 'L')
	{
		free(line);
		ft_putstr_fd("ERROR (there is a 'L')\n", 2);
		free_data(data, 1);
		exit(-1);
	}
	else
	{
		j = check_line_with_space(data->size, data, line);
		if (j == -2)
		{
			free_data(data, 1);
			free(line);
			ft_putstr("ERROR (error coord_or_links)\n");
			exit(-1);
		}
		else if (j == -1)
			return (-1);
		data->size++;
	}
	return (0);
}

char	*rooms_determination(t_data *data, char **line)
{
	while (get_next_line(data->fd, line) > 0)
	{
		if ((*line)[0] == '#')
		{
			if ((!ft_strncmp((*line), "##start", ft_strlen((*line)))))
				data->start = -1;
			if ((!ft_strncmp((*line), "##end", ft_strlen((*line)))))
				data->end = -1;
			free(*line);
		}
		else if (rooms_determination2(data, (*line)) == -1)
			return ((*line));
	}
	ft_putstr_fd("ERROR (error_maps)\n", 2);
	free_data(data, 1);
	exit(-1);
}

int		check_line_with_space(int i, t_data *data, char *s)
{
	int	j;

	if (i >= data->max_size)
	{
		doubling_struct(&data->t, data->max_size);
		data->max_size += data->max_size;
	}
	if ((j = ft_read_coord(data->t[i].coord, s)) < 0)
		return (j);
	s[j] = 0;
	data->t[i].name = s;
	data->t[i].len = -1;
	data->t[i].size = 0;
	if (data->start == -1)
		data->start = i;
	if (data->end == -1)
		data->end = i;
	return (j);
}

void	doubling_struct(t_new **t, int old_size)
{
	t_new	*new_t;
	int		i;

	i = -1;
	new_t = (t_new*)malloc(sizeof(*new_t) * 2 * old_size);
	while (++i < old_size)
	{
		new_t[i].name = (*t)[i].name;
		new_t[i].list = NULL;
		new_t[i].coord[0] = (*t)[i].coord[0];
		new_t[i].coord[1] = (*t)[i].coord[1];
	}
	free(*t);
	*t = new_t;
}

int		ft_read_coord(int *coord, char *s)
{
	int j;
	int i;

	i = ft_strclen(s, '\n');
	if (ft_memchr(s, '-', i))
		return (-1);
	j = 2;
	coord[0] = 0;
	coord[1] = 0;
	while (--j >= 0)
	{
		i--;
		while (s[i] <= '9' && s[i] >= '0')
			i--;
		if (s[i] != ' ')
			return (-2);
		else
			coord[j] = ft_atoi(s + i);
	}
	return (i);
}
