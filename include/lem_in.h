/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egottlie <egottlie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 22:05:49 by ljonnel-          #+#    #+#             */
/*   Updated: 2019/09/21 16:28:18 by egottlie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "ft_printf.h"
# include "SDL.h"
# include "SDL_ttf.h"
# include "SDL_image.h"
# define Q_MAX 10000

typedef struct				s_ant
{
	int						before[2];
	int						after[2];
	int						ant;
	int						curr_step;
	struct s_ant			*next_ant;
}							t_ant;

typedef struct				s_sdl
{
	SDL_Texture				*background;
	SDL_Texture				*tex_ant;
	SDL_Window				*win;
	SDL_Renderer			*ren;
	TTF_Font				*font;
	int						diff_x;
	int						diff_y;
	int						delay;
	int						ants_start;
	int						ants_end;
	t_ant					*ants;
}							t_sdl;

typedef struct				s_queue
{
	int						q[60000];
	int						head;
	int						tail;
}							t_queue;

typedef struct				s_path_for_ant
{
	char					*name;
	int						path;
	struct s_path_for_ant	*next;
}							t_path_for_ant;

typedef struct				s_list_path
{
	int						number_node;
	struct s_list_path		*next;
}							t_list_path;

typedef struct				s_several_path
{
	int						count_str;
	int						count_route;
	int						route[1000][1000];
	int						options_paths[1000][1000];
	struct s_several_path	*next;
}							t_several_path;

typedef struct				s_list_link
{
	int						number;
	int						priority;
	int						path;
	int						possible_path;
	struct s_list_link		*next;
}							t_list_link;

typedef struct				s_new
{
	char					*name;
	int						color;
	int						flag;
	int						possible_path;
	int						paths[10000];
	int						size;
	int						len;
	int						size_list_step;
	int						coord[2];
	t_list_link				*list;
}							t_new;

typedef struct				s_data
{
	t_new					*t;
	int						fd;
	int						j;
	int						size;
	int						max_size;
	int						ants;
	t_list_path				*path;
	int						route[1000][1000];
	int						options_paths[1000][1000];
	t_path_for_ant			**path_ant;
	t_several_path			*few_route;
	t_several_path			*few_route_last;
	int						size_route;
	int						best_route;
	int						count_route;
	int						max_len;
	int						flag;
	int						the_shortest_path;
	int						**sort_array_path;
	int						**array_count_step;
	int						count_links_start;
	int						count_links_end;
	int						start;
	int						end;
}							t_data;

void						init_que(t_queue *queue);
int							moving_que(t_queue *que);
int							push_que(t_queue *que, int n);
int							isempty_que(t_queue *que);
int							pop_que(t_queue *que);
void						push(t_list_link **head, int data);

int							ft_display_ants_moved(t_data *data);
int							ft_display_output(t_data *data, int end);
int							ft_display_output2(int i, int ant, t_data *data,
		int path);
int							ft_path_for_ants(t_data *data);
int							ft_add_path_for_ant(t_data *data, int ant,
		int path);
void						ft_del_path_for_ant(t_data *data);

void						ft_check_paths_target(t_data *data);
void						ft_count_route(t_data *data);
int							ft_count_ants_in_path(int j, int count_step);
int							ft_options_route(t_data *data);
int							ft_search_route(t_data *data);

void						ft_free_path(t_data *data);

void						ft_copy_arr(t_data *data);
void						ft_few_route(t_data *data, int i);
void						ft_free_route(t_data *data);
void						ft_clear_possible_path(t_data *data);

int							ft_traverse(t_data *data);
int							ft_traverse_2(t_data *data, t_queue *queue,
		int number_room, t_list_link *tmp_link);
int							ft_check_all_path(t_data *data, int tmp_len);
int							ft_check_all_path_1(t_data *data,
		t_list_link *tmp_link, int len, t_list_path **path);
int							ft_check_all_path_2(t_data *data,
		t_list_path *path, t_list_path *tmp_path, int i);
void						ft_clear_path(t_data *data,
		t_list_path *path, t_list_path *tmp_path);

int							ft_check_route(int ants, int count_path,
		int sum_step);
void						ft_clear_color_and_len(t_data *data);
int							ft_choice_route(t_data *data);
void						ft_search_path(t_data *data);
void						ft_search_route_1(t_data *data);
int							ft_new_several_path(t_data *t);
int							ft_check_count_path(t_data *data, int path);

void						push(t_list_link **head, int data);
int							check_duplicate(t_new *t, int size);
void						sort_parse(t_data *data, char **line);
void						quick_sort(t_new *t, int n);
int							partition(t_new *t, int n);
void						ft_swap_strings(t_new *t, int i, int j);
int							binarysearch_str(char *a, t_new *t, int n);
int							rooms_determination2(t_data *data, char *buf);
char						*rooms_determination(t_data *data, char **line);
int							check_line_with_space(int i, t_data *data,
		char *s);
void						doubling_struct(t_new **t, int old_size);
int							ft_read_coord(int *coord, char *s);
int							ft_strclen(const char *s, char c);
void						free_data(t_data *data, int i);
void						links_determ2(t_data *data, char *buf, int j);
void						exit_links(t_data *data, char *line);
void						links_determintation(t_data *data,
		char *line, int j);
void						null_struct(t_data *data);
void						ants_determination(t_data *data);

void						ft_viz(t_data *data);
int							ft_search_ant2(t_ant *tmp, int number,
		int ant, t_data *data);
void						ft_serch_ant(int number, int ant,
		t_data *data, t_sdl *sdl);
void						ft_read_paths(char *buf, t_data *data,
		t_sdl *sdl);
void						ft_viz(t_data *data);
void						ft_init_sdl(t_sdl *sdl, int ants_start);
void						ft_free_lst_ant(t_ant **ants, int ant);
int							free_sdl(t_sdl *sdl);
int							draw_line_circles(t_sdl *sdl, t_data *data,
		t_ant **all);
t_ant						*ft_draw_all_ants(t_ant **ants, t_sdl *sdl,
		int i, t_data *data);
void						draw_texture(t_data *data, t_sdl *sdl);
void						ft_draw_text(t_sdl *sdl, int x, int y, char *s);
SDL_Rect					ft_read_rect(int x, int y, int w, int h);
void						draw_texture(t_data *data, t_sdl *sdl);
int							draw_line_circle(t_sdl *sdl, t_data *data,
		t_ant **all);
t_ant						*ft_draw_all_ants(t_ant **ants, t_sdl *sdl,
		int i, t_data *data);
SDL_Texture					*loadimage(char *string, SDL_Renderer *ren);
SDL_Rect					ft_read_rect(int x, int y, int w, int h);
int							ft_event(t_sdl *sdl, t_data *data);
int							ft_event_key(t_sdl *sdl, SDL_Event event);
int							ft_event_pausa(SDL_Event event);
void						draw_rect(SDL_Renderer *renderer, int x, int y);
void						draw_5_lines(t_sdl *sdl, t_new *t1, t_new *t2);
void						draw_5_lines_2(t_sdl *sdl, int *tmp, t_new *t1,
		t_new *t2);
void						ft_draw_start_end(t_data *data, t_sdl *sdl);
void						draw_ants(t_sdl *sdl, t_data *data, t_ant *ants);
void						ft_draw_end(t_sdl *sdl, t_data *data, int i);
void						ft_exit(t_data *data);
int							rooms_determination3(t_data	*data, char *line);
#endif
