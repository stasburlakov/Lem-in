/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egottlie <egottlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 17:59:01 by ljonnel-          #+#    #+#             */
/*   Updated: 2019/09/21 16:30:02 by egottlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		rooms_determination3(t_data *data, char *line)
{
	int	j;

	j = check_line_with_space(data->size, data, line);
	if (j == -2)
	{
		free_data(data, 1);
		ft_putendl(line);
		free(line);
		ft_putstr_fd("ERROR (error coord_or_links)\n", 2);
		exit(-1);
	}
	else if (j == -1)
		return (-1);
	data->size++;
	ft_putstr(line);
	write(1, " ", 1);
	ft_putendl(line + j + 1);
	return (0);
}

void	ft_exit(t_data *data)
{
	ft_free_route(data);
	ft_free_path(data);
	ft_del_path_for_ant(data);
	free_data(data, 1);
	ft_putstr_fd("ERROR (no_path)\n", 2);
	exit(0);
}

void	push(t_list_link **head, int data)
{
	t_list_link *tmp;

	if (head && (tmp = (t_list_link*)malloc(sizeof(*tmp))) != NULL)
	{
		tmp->number = data;
		tmp->next = *head;
		*head = tmp;
	}
}

void	free_data(t_data *data, int i)
{
	int			len;
	t_list_link	*tmp;
	t_list_link	*head;

	len = data->size;
	while (--len >= 0)
	{
		head = data->t[len].list;
		while (head != NULL)
		{
			tmp = head;
			head = head->next;
			free(tmp);
		}
		free(data->t[len].name);
	}
	if (i)
		free(data->t);
	free(data);
}

int		main(void)
{
	t_data	*data;
	char	*line;
	int		j;

	j = 0;
	data = (t_data*)malloc(sizeof(t_data));
	data->path_ant = NULL;
	data->path = NULL;
	data->count_route = 0;
	data->fd = 0;
	ants_determination(data);
	line = rooms_determination(data, &line);
	sort_parse(data, &line);
	links_determintation(data, line, j);
	ft_clear_color_and_len(data);
	ft_traverse(data);
	if (data->t[data->end].len == 0)
		ft_exit(data);
	ft_search_route(data);
	ft_choice_route(data);
	free_data(data, 1);
	return (0);
}
