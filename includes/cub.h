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
/*                 FILE = srcs/raycasting/raycasting_utils.c                  */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/*                     FILE = srcs/drawing/draw_player.c                      */
/* -------------------------------------------------------------------------- */
void	ft_draw_player(void);

/* -------------------------------------------------------------------------- */
/*                       FILE = srcs/utils/singleton.c                        */
/* -------------------------------------------------------------------------- */
t_data	*_img(void);
t_mlx	*_mlx(void);
t_player	*_player(void);
t_var	*_var(void);

/* -------------------------------------------------------------------------- */
/*                       FILE = srcs/utils/key_hooks.c                        */
/* -------------------------------------------------------------------------- */
int	ft_game_hook(int keycode);
int	ft_forward(void);
int	ft_back(void);
int	ft_left(void);
int	ft_right(void);
int	ft_escape(void);

/* -------------------------------------------------------------------------- */
/*                   FILE = srcs/utils/malloc_hooks_enum.c                    */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/*                             FILE = srcs/main.c                             */
/* -------------------------------------------------------------------------- */
void	ft_init_player_pos(void);
int	ft_hook(int keycode);
int	ft_mouse_hook(int keycode);
int	ft_loop_hook(void);
int	ft_game(void);
int main(int argc, char **argv);

/* -------------------------------------------------------------------------- */
/*                        FILE = srcs/menu/generate.c                         */
/* -------------------------------------------------------------------------- */
t_data	generate_image(char *path);
void	generate_button_state(void);
void    gen_menu_images(void);

/* -------------------------------------------------------------------------- */
/*                          FILE = srcs/menu/loop.c                           */
/* -------------------------------------------------------------------------- */
int	ft_hitbox(t_vector2D hitbox[4], t_vector2D pos);
t_data	ft_put_image_to_image(t_data big, t_data lil, t_vector2D pos);
void	menu_option(void);
void	check_button_state(void);
void	check_button_state_options(void);
void	menu_start(void);
int	menu_loop(void);
int	menu_hook(int keycode);
void	check_button_state_mouse(int keycode);
void	check_button_state_mouse_options(int keycode);
int	menu_mouse_hook(int keycode);

/* -------------------------------------------------------------------------- */
/*                       FILE = srcs/parsing/parsing.c                        */
/* -------------------------------------------------------------------------- */
size_t	ft_strlen(const char *s);
void	*free_tab(char **tab, int k);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);

/* -------------------------------------------------------------------------- */
/*                     FILE = srcs/mlx_utils/mlx_utils.c                      */
/* -------------------------------------------------------------------------- */
void	ft_init_mlx();
void	ft_init_img();
void	ft_pixel_put(float x, float y, int color);
void	ft_reload_frame();
int	ft_loop();


#endif
