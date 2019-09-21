/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_event.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egottlie <egottlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 20:47:07 by ljonnel-          #+#    #+#             */
/*   Updated: 2019/09/21 16:30:20 by egottlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			ft_event_pausa(SDL_Event event)
{
	event.key.keysym.scancode = 1;
	while (1)
	{
		SDL_Delay(50);
		SDL_PollEvent(&event);
		if (event.type == SDL_KEYUP)
		{
			if (event.key.keysym.scancode == SDL_SCANCODE_SPACE)
				break ;
			else if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				return (0);
		}
		else if (event.type == SDL_QUIT)
			return (0);
	}
	return (1);
}

int			ft_event_key(t_sdl *sdl, SDL_Event event)
{
	if (event.key.keysym.scancode == SDL_SCANCODE_UP)
		sdl->diff_y += 100;
	else if (event.key.keysym.scancode == SDL_SCANCODE_DOWN)
		sdl->diff_y -= 100;
	else if (event.key.keysym.scancode == SDL_SCANCODE_LEFT)
		sdl->diff_x += 100;
	else if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT)
		sdl->diff_x -= 100;
	else if (event.key.keysym.scancode == 86 && sdl->delay < 400)
		sdl->delay = sdl->delay * 5 / 4;
	else if (event.key.keysym.scancode == 87 && sdl->delay > 5)
		sdl->delay = sdl->delay * 4 / 5;
	else if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
		return (0);
	else if (event.key.keysym.scancode == SDL_SCANCODE_SPACE)
		return (ft_event_pausa(event));
	return (1);
}

int			ft_event(t_sdl *sdl, t_data *data)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			return (0);
		else if (event.type == SDL_KEYUP)
		{
			if (!ft_event_key(sdl, event))
				return (0);
			SDL_SetRenderDrawColor(sdl->ren, 255, 255, 255, SDL_ALPHA_OPAQUE);
			SDL_RenderClear(sdl->ren);
			draw_texture(data, sdl);
		}
	}
	return (1);
}

SDL_Rect	ft_read_rect(int x, int y, int w, int h)
{
	SDL_Rect	pos;

	pos.x = x;
	pos.y = y;
	pos.h = h;
	pos.w = w;
	return (pos);
}
