/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmechety <rmechety@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 12:52:24 by rmechety          #+#    #+#             */
/*   Updated: 2021/10/19 15:08:54 by rmechety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "struct.h"
# include "includes.h"

/* -------------------------------------------------------------------------- */
/*                        FILE = srcs/parsing/split.c                         */
/* -------------------------------------------------------------------------- */
void	*free_tab(char **tab, int k);
char	**ft_split(char const *s, char c);

/* -------------------------------------------------------------------------- */
/*                      FILE = srcs/parsing/parsing_2.c                       */
/* -------------------------------------------------------------------------- */
t_vector2F	set_position(char c);
void	body_map(t_vector2D *pt, t_vector2D *it, char **map, int *longest);
int	check_map(char **map, int start);
void	error_dir(char *new, int index, int *nb, char *str);

/* -------------------------------------------------------------------------- */
/*                         FILE = srcs/parsing/args.c                         */
/* -------------------------------------------------------------------------- */
void	parse_dir(char *str, int index, int *nb);
void	jump_spaces(int *i, char *str, int k);
void	is_error(int tmp, int k, int j);
void	body_color(t_vector3D *it, char *str, int index);
void	parse_color(char *str, int index, int *nb);

/* -------------------------------------------------------------------------- */
/*                       FILE = srcs/parsing/parsing.c                        */
/* -------------------------------------------------------------------------- */
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*read_file(int fd);
int	is_char_in_range(t_vector2D pos, char **map);
int	is_player(char c);

/* -------------------------------------------------------------------------- */
/*                        FILE = srcs/parsing/args_2.c                        */
/* -------------------------------------------------------------------------- */
int	is_nb_args(int	*tab);
int	is_empty(char *str);
int	is_map(char *str);
void	arg_check(char *str, int nb_types[6], int *index, int i);
void	parse_args(char **map);

/* -------------------------------------------------------------------------- */
/*                    FILE = srcs/raycasting/raycasting.c                     */
/* -------------------------------------------------------------------------- */
void	init_ray(void);
void	init_dda(void);
void	dda(void);

/* -------------------------------------------------------------------------- */
/*                 FILE = srcs/raycasting/raycasting_utils.c                  */
/* -------------------------------------------------------------------------- */
int	intersects(t_circle circle, t_rect rect);
void	get_directional_texture(void);
void	compute_drawing_data(void);
void	draw_wall(void);
void	draw_rays(void);

/* -------------------------------------------------------------------------- */
/*                     FILE = srcs/mlx_utils/mlx_utils.c                      */
/* -------------------------------------------------------------------------- */
void	ft_init_mlx(void);
void	ft_init_img(void);
void	ft_reload_frame(void);
void	ft_fps(void);
int	ft_loop(void);

/* -------------------------------------------------------------------------- */
/*                             FILE = srcs/main.c                             */
/* -------------------------------------------------------------------------- */
int	ft_mouse_release(int keycode);
int	ft_game(void);
void	init_key(void);
t_data	generate_image(char *path);
int	main(int argc, char **argv);

/* -------------------------------------------------------------------------- */
/*                          FILE = srcs/utils/math.c                          */
/* -------------------------------------------------------------------------- */
float	mag(t_vector2F v);
t_vector2F	norm(t_vector2F v);
float	rad_to_deg(float rad);
float	deg_to_rad(float deg);

/* -------------------------------------------------------------------------- */
/*                         FILE = srcs/utils/utils.c                          */
/* -------------------------------------------------------------------------- */
void	ft_pixel_put(float x, float y, int color);
void	ft_put_pixel(t_data *a, t_data *b, t_vector2D pos_a, t_vector2D pos_b);
void	get_key(int keycode);
int	ft_release(int keycode);
void	ft_put_pixel_color(t_data *a, unsigned char color[4], int x, int y);

/* -------------------------------------------------------------------------- */
/*                       FILE = srcs/utils/movements.c                        */
/* -------------------------------------------------------------------------- */
int	ft_forward(void);
int	ft_back(void);
int	ft_strafe_left(void);
int	ft_strafe_right(void);
t_vector2F	get_90_angle(int dir);

/* -------------------------------------------------------------------------- */
/*                         FILE = srcs/utils/clock.c                          */
/* -------------------------------------------------------------------------- */
struct timeval	start_clock(void);
unsigned long	get_clock(struct timeval start);
void	ft_black_hole(int exit_code);
int	ft_strcmp(char *s1, char *s2);
int	ft_check_map_name(char *name);

/* -------------------------------------------------------------------------- */
/*                       FILE = srcs/utils/key_hooks.c                        */
/* -------------------------------------------------------------------------- */
void	key_hook(void);
int	ft_game_hook(int keycode);
int	ft_right(void);
int	ft_left(void);
int	ft_escape(void);

/* -------------------------------------------------------------------------- */
/*                       FILE = srcs/utils/singleton.c                        */
/* -------------------------------------------------------------------------- */
t_data	*_img(void);
t_mlx	*_mlx(void);
t_obj	*_player(void);
t_raycasting	*_ray(void);
t_var	*_var(void);

/* -------------------------------------------------------------------------- */
/*                        FILE = srcs/utils/garbage.c                         */
/* -------------------------------------------------------------------------- */
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstadd_back(t_list **alst, t_list *new);
t_list	*_lst(void);
t_list	*ft_new_node(void *content);
void	*ft_malloc(int size);

/* -------------------------------------------------------------------------- */
/*                        FILE = srcs/utils/utils_2.c                         */
/* -------------------------------------------------------------------------- */
void	draw_void(void);
void	ft_init_player_pos(void);
void	ft_print_tab(char **s);
int	ft_hook(int keycode);
int	ft_loop_hook(void);


#endif
