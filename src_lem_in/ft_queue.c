/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queue.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egottlie <egottlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 14:00:38 by ljonnel-          #+#    #+#             */
/*   Updated: 2019/09/21 16:29:46 by egottlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	init_que(t_queue *queue)
{
	queue->head = 1;
	queue->tail = 0;
}

int		moving_que(t_queue *que)
{
	int head;
	int i;

	i = 0;
	head = que->head;
	while (head < Q_MAX)
		que->q[i++] = que->q[head++];
	que->tail -= que->head;
	que->head = 0;
	return (que->tail);
}

int		push_que(t_queue *que, int n)
{
	if (que->tail < Q_MAX - 1)
		que->q[++que->tail] = n;
	else
		return (-1);
	return (0);
}

int		isempty_que(t_queue *que)
{
	if (que->tail < que->head)
		return (1);
	else
		return (0);
}

int		pop_que(t_queue *que)
{
	int	n;

	n = -1;
	if (!isempty_que(que))
	{
		n = que->q[que->head];
		que->q[que->head++] = 0;
	}
	return (n);
}
