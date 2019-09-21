/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egottlie <egottlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 20:48:01 by ljonnel-          #+#    #+#             */
/*   Updated: 2019/09/21 16:30:16 by egottlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_ant	*ft_draw_all_ants(t_ant **ants, t_sdl *sdl, int i, t_data *data)
{
	t_ant	*tmp;

	tmp = (*ants);
	while (*ants)
	{
		if (!ft_event(sdl, data))
		{
			data->j = -1;
			return (0);
		}
		draw_ants(sdl, data, *ants);
		if (i == 41 && (*ants)->after[0] == data->t[data->end].coord[0]
			&& (*ants)->after[1] == data->t[data->end].coord[1])
		{
			ft_free_lst_ant(&tmp, (*ants)->ant);
			(*ants) = tmp;
			sdl->ants_end++;
		}
		else
			*ants = (*ants)->next_ant;
	}
	*ants = tmp;
	return (tmp);
}

int		draw_line_circle(t_sdl *sdl, t_data *data, t_ant **all)
{
	int		i;
	t_ant	*ants;
	t_ant	*tmp;

	i = 0;
	ants = *all;
	while (i++ < 41)
	{
		data->j = 0;
		SDL_SetRenderDrawColor(sdl->ren, 255, 255, 255, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(sdl->ren);
		draw_texture(data, sdl);
		if ((tmp = ft_draw_all_ants(&ants, sdl, i, data)) == NULL)
		{
			if (data->j)
				return (-1);
		}
		(*all) = tmp;
		SDL_RenderPresent(sdl->ren);
		SDL_Delay(sdl->delay);
	}
	return (1);
}

void	draw_texture(t_data *data, t_sdl *sdl)
{
	int			i;
	t_list_link *tmp;
	SDL_Rect	rect;

	rect = ft_read_rect(0, 0, 1500, 1200);
	SDL_RenderCopy(sdl->ren, sdl->background, NULL, &rect);
	i = data->size;
	while (--i > 0)
	{
		tmp = data->t[i].list;
		while (tmp)
		{
			draw_5_lines(sdl, &data->t[i], &data->t[tmp->number]);
			tmp = tmp->next;
		}
	}
	i = data->size;
	while (--i >= 0)
		draw_rect(sdl->ren, data->t[i].coord[0] + sdl->diff_x,
				data->t[i].coord[1] + sdl->diff_y);
}

void	ft_draw_text(t_sdl *sdl, int x, int y, char *s)
{
	SDL_Texture	*tex;
	SDL_Surface	*sur;
	SDL_Rect	rect;
	SDL_Color	white;

	TTF_SizeText(sdl->font, s, &rect.w, &rect.h);
	white.r = 255;
	white.b = 255;
	white.g = 255;
	white.a = 255;
	rect.x = x;
	rect.y = y;
	sur = TTF_RenderText_Blended(sdl->font, s, white);
	tex = SDL_CreateTextureFromSurface(sdl->ren, sur);
	SDL_RenderCopy(sdl->ren, tex, NULL, &rect);
	SDL_FreeSurface(sur);
	SDL_DestroyTexture(tex);
}
