/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_links.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egottlie <egottlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 17:18:13 by ljonnel-          #+#    #+#             */
/*   Updated: 2019/09/21 16:30:33 by egottlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	links_determ2(t_data *data, char *buf, int j)
{
	int k;
	int i;

	k = j;
	buf[j] = 0;
	while (buf[j + 1] && buf[j + 1] != '\n')
		j++;
	buf[j + 1] = 0;
	i = binarysearch_str(buf, data->t, data->size);
	j = binarysearch_str(buf + k + 1, data->t, data->size);
	if (i == -1 || j == -1)
	{
		free(buf);
		ft_putstr_fd("ERROR (name_rooms)\n", 2);
		free_data(data, 1);
		exit(-1);
	}
	push(&data->t[i].list, j);
	push(&data->t[j].list, i);
}

void	exit_links(t_data *data, char *line)
{
	free(line);
	ft_putstr_fd("ERROR (error links)\n", 2);
	free_data(data, 1);
	exit(-1);
}

void	links_determintation(t_data *data, char *line, int j)
{
	if (line[0] == '#')
		(line[1] != '#') ? 0 : exit_links(data, line);
	else
	{
		j = ft_strclen(line, '-');
		if (line[j] == 0)
			exit_links(data, line);
		else
			links_determ2(data, line, j);
	}
	free(line);
	while (get_next_line(data->fd, &line) > 0)
	{
		if (line[0] == '#')
			(line[1] != '#') ? 0 : exit_links(data, line);
		else
		{
			j = ft_strclen(line, '-');
			if (line[j] == 0)
				return ;
			else
				links_determ2(data, line, j);
		}
		free(line);
	}
}

int		ft_strclen(const char *s, char c)
{
	int i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}
