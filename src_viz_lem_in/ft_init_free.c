/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egottlie <egottlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 20:48:13 by ljonnel-          #+#    #+#             */
/*   Updated: 2019/09/21 16:30:25 by egottlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			free_sdl(t_sdl *sdl)
{
	SDL_DestroyTexture(sdl->background);
	SDL_DestroyTexture(sdl->tex_ant);
	SDL_DestroyRenderer(sdl->ren);
	SDL_DestroyWindow(sdl->win);
	TTF_FontDescent(sdl->font);
	free(sdl->ants);
	SDL_Quit();
	TTF_Quit();
	return (0);
}

void		ft_free_lst_ant(t_ant **ants, int ant)
{
	t_ant	*tmp;
	t_ant	*i;

	tmp = *ants;
	if (tmp->ant == ant)
	{
		(*ants) = (*ants)->next_ant;
		free(tmp);
	}
	else
	{
		while (tmp->next_ant->ant != ant)
			tmp = tmp->next_ant;
		i = tmp->next_ant;
		tmp->next_ant = tmp->next_ant->next_ant;
		free(i);
	}
}

void		ft_init_sdl(t_sdl *sdl, int ants_start)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	sdl->win = SDL_CreateWindow("Lem_in", 0, 0, 1500, 1200, SDL_WINDOW_SHOWN);
	sdl->ren = SDL_CreateRenderer(sdl->win, -1, SDL_RENDERER_ACCELERATED);
	sdl->background = loadimage("image/zemlya.bmp", sdl->ren);
	sdl->tex_ant = loadimage("image/ant.bmp", sdl->ren);
	sdl->diff_x = 0;
	sdl->diff_y = 0;
	sdl->delay = 100;
	sdl->font = TTF_OpenFont("image/Roboto-Italic.ttf", 24);
	sdl->ants = (t_ant*)malloc(sizeof(t_ant));
	sdl->ants->ant = -1;
	sdl->ants->next_ant = NULL;
	sdl->ants_start = ants_start;
	sdl->ants_end = 0;
	SDL_RenderClear(sdl->ren);
}

SDL_Texture	*loadimage(char *string, SDL_Renderer *ren)
{
	SDL_Surface	*loadedimage;
	SDL_Texture	*tex;

	tex = NULL;
	loadedimage = SDL_LoadBMP(string);
	if (loadedimage)
	{
		tex = SDL_CreateTextureFromSurface(ren, loadedimage);
		SDL_FreeSurface(loadedimage);
	}
	else
		ft_putstr(SDL_GetError());
	return (tex);
}
