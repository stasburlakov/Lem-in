/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egottlie <egottlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 17:59:01 by ljonnel-          #+#    #+#             */
/*   Updated: 2019/09/21 16:30:49 by egottlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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
	data->fd = 0;
	ants_determination(data);
	line = rooms_determination(data, &line);
	sort_parse(data, &line);
	links_determintation(data, line, j);
	ft_viz(data);
	free_data(data, 1);
	return (0);
}
