/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_viz.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egottlie <egottlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 14:18:52 by ljonnel-          #+#    #+#             */
/*   Updated: 2019/09/21 16:30:45 by egottlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			ft_search_ant2(t_ant *tmp, int number, int ant, t_data *data)
{
	if (tmp->ant == ant)
	{
		tmp->curr_step = 0;
		tmp->before[0] = tmp->after[0];
		tmp->before[1] = tmp->after[1];
		tmp->after[0] = data->t[number].coord[0];
		tmp->after[1] = data->t[number].coord[1];
		return (0);
	}
	else
	{
		tmp->next_ant = (t_ant*)malloc(sizeof(t_ant));
		tmp->next_ant->curr_step = 0;
		tmp->next_ant->ant = ant;
		tmp->next_ant->next_ant = NULL;
		tmp->next_ant->after[0] = data->t[number].coord[0];
		tmp->next_ant->after[1] = data->t[number].coord[1];
		tmp->next_ant->before[0] = data->t[data->start].coord[0];
		tmp->next_ant->before[1] = data->t[data->start].coord[1];
		return (-1);
	}
}

void		ft_serch_ant(int number, int ant, t_data *data, t_sdl *sdl)
{
	t_ant *tmp;

	tmp = sdl->ants;
	while (tmp->next_ant)
	{
		if (tmp->ant == ant)
		{
			tmp->curr_step = 0;
			tmp->before[0] = tmp->after[0];
			tmp->before[1] = tmp->after[1];
			tmp->after[0] = data->t[number].coord[0];
			tmp->after[1] = data->t[number].coord[1];
			return ;
		}
		tmp = tmp->next_ant;
	}
	sdl->ants_start += ft_search_ant2(tmp, number, ant, data);
}

void		ft_read_paths(char *buf, t_data *data, t_sdl *sdl)
{
	int		j;
	char	check;
	int		ant;
	int		i;

	ant = 0;
	i = 0;
	while (buf[i])
	{
		if (buf[i] == 'L')
			ant = ft_atoi(buf + i + 1);
		if (buf[i] == '-')
		{
			j = i;
			while (buf[j] != ' ' && buf[j] && buf[j] != '\n')
				j++;
			check = buf[j];
			buf[j] = 0;
			ft_serch_ant(binarysearch_str(buf + i + 1, data->t, data->size),
					ant, data, sdl);
			buf[j] = check;
		}
		i++;
	}
}

void		ft_draw_end(t_sdl *sdl, t_data *data, int i)
{
	SDL_SetRenderDrawColor(sdl->ren, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(sdl->ren);
	draw_texture(data, sdl);
	ft_draw_start_end(data, sdl);
	SDL_RenderPresent(sdl->ren);
	(i) ? SDL_Delay(1500) : 0;
	free_sdl(sdl);
}

void		ft_viz(t_data *data)
{
	t_sdl	sdl;
	char	*line;
	int		i;

	ft_init_sdl(&sdl, data->ants);
	while (get_next_line(data->fd, &line) > 0)
	{
		if (line[0] != 'L')
			free(line);
		else
		{
			ft_read_paths(line, data, &sdl);
			if ((i = draw_line_circle(&sdl, data, &(sdl.ants->next_ant))) <= 0)
			{
				ft_draw_end(&sdl, data, 0);
				free(line);
				return ;
			}
			free(line);
		}
	}
	ft_draw_end(&sdl, data, 1);
}
