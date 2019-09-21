/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egottlie <egottlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 20:45:30 by ljonnel-          #+#    #+#             */
/*   Updated: 2019/09/21 16:28:33 by egottlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	draw_rect(SDL_Renderer *renderer, int x, int y)
{
	SDL_Rect	rect;

	rect.x = x - 25;
	rect.y = y - 25;
	rect.w = 50;
	rect.h = 50;
	SDL_SetRenderDrawColor(renderer, 80, 80, 80, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(renderer, &rect);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRect(renderer, &rect);
}

void	draw_5_lines_2(t_sdl *sdl, int *tmp, t_new *t1, t_new *t2)
{
	SDL_RenderDrawLine(sdl->ren, t2->coord[0] - 2 * tmp[0] + sdl->diff_x,
			t2->coord[1] - 2 * tmp[1] + sdl->diff_y, t1->coord[0] - 2 *
			tmp[0] + sdl->diff_x, t1->coord[1] - 2 * tmp[1] + sdl->diff_y);
	SDL_RenderDrawLine(sdl->ren, t2->coord[0] - tmp[0] + sdl->diff_x,
			t2->coord[1] - tmp[1] + sdl->diff_y, t1->coord[0] - tmp[0] +
			sdl->diff_x, t1->coord[1] - tmp[1] + sdl->diff_y);
	SDL_RenderDrawLine(sdl->ren, t2->coord[0] + sdl->diff_x,
			t2->coord[1] + sdl->diff_y, t1->coord[0] + sdl->diff_x,
			t1->coord[1] + sdl->diff_y);
	SDL_RenderDrawLine(sdl->ren, t2->coord[0] + tmp[0] + sdl->diff_x,
			t2->coord[1] + tmp[1] + sdl->diff_y, t1->coord[0] + tmp[0] +
			sdl->diff_x, t1->coord[1] + tmp[1] + sdl->diff_y);
	SDL_RenderDrawLine(sdl->ren, t2->coord[0] + 2 * tmp[0] + sdl->diff_x,
			t2->coord[1] + 2 * tmp[1] + sdl->diff_y,
			t1->coord[0] + 2 * tmp[0] + sdl->diff_x,
			t1->coord[1] + 2 * tmp[1] + sdl->diff_y);
}

void	draw_5_lines(t_sdl *sdl, t_new *t1, t_new *t2)
{
	int tmp[2];

	tmp[0] = 0;
	tmp[1] = 0;
	if (t2->coord[0] == t1->coord[0])
		tmp[0] = 1;
	else if (t2->coord[1] == t1->coord[1])
		tmp[1] = 1;
	else
	{
		if (abs(t2->coord[1] - t1->coord[1]) / abs(t2->coord[0] - t1->coord[0]))
			tmp[0] = 1;
		else
			tmp[1] = 1;
	}
	SDL_SetRenderDrawColor(sdl->ren, 255, 0, 255, SDL_ALPHA_OPAQUE);
	draw_5_lines_2(sdl, tmp, t1, t2);
}

void	ft_draw_start_end(t_data *data, t_sdl *sdl)
{
	char	*s;

	s = ft_lltoa(sdl->ants_start);
	ft_draw_text(sdl, data->t[data->start].coord[0] + 25 + sdl->diff_x,
			data->t[data->start].coord[1] + sdl->diff_y, s);
	free(s);
	s = ft_lltoa(sdl->ants_end);
	ft_draw_text(sdl, data->t[data->end].coord[0] + 25 + sdl->diff_x,
			data->t[data->end].coord[1] + sdl->diff_y, s);
	free(s);
}

void	draw_ants(t_sdl *sdl, t_data *data, t_ant *ants)
{
	int			tmp_x;
	int			tmp_y;
	SDL_Rect	rect;

	if (ants)
	{
		tmp_x = ants->curr_step * ((ants->after[0] - ants->before[0]) / 40);
		tmp_y = ants->curr_step * ((ants->after[1] - ants->before[1]) / 40);
		rect = ft_read_rect(ants->before[0] + tmp_x - 34 + sdl->diff_x,
							ants->before[1] + tmp_y - 34 + sdl->diff_y, 69, 69);
		SDL_RenderCopy(sdl->ren, sdl->tex_ant, NULL, &rect);
		ants->curr_step++;
	}
	ft_draw_start_end(data, sdl);
}
