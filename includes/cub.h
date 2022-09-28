/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 12:52:24 by yobougre          #+#    #+#             */
/*   Updated: 2022/09/28 10:58:43 by denissereno      ###   ########.fr       */
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
/*                       FILE = srcs/utils/singleton.c                        */
/* -------------------------------------------------------------------------- */
t_data		*_img(void);
t_mlx		*_mlx(void);
t_enum_key	*_enum_key(void);
t_var		*_var(void);
t_player	*_player(void);

/* -------------------------------------------------------------------------- */
/*                       FILE = srcs/utils/key_hooks.c                        */
/* -------------------------------------------------------------------------- */
int	ft_hook(int keycode, t_mlx *mlx);
int	ft_forward(void);
int	ft_back(void);
int	ft_left(void);
int	ft_right(void);
int	ft_escape(void);

/* -------------------------------------------------------------------------- */
/*                   FILE = srcs/utils/malloc_hooks_enum.c                    */
/* -------------------------------------------------------------------------- */
int	ft_malloc_enum_key();
void	ft_init_enum_key(void);

/* -------------------------------------------------------------------------- */
/*                             FILE = srcs/main.c                             */
/* -------------------------------------------------------------------------- */
void	ft_init_player_pos(void);
int main(int argc, char **argv);

/* -------------------------------------------------------------------------- */
/*                     FILE = srcs/mlx_utils/mlx_utils.c                      */
/* -------------------------------------------------------------------------- */
void	ft_init_mlx();
void	ft_init_img();
void	ft_pixel_put(float x, float y, int color);
void	ft_reload_frame();
int	ft_loop();

/* -------------------------------------------------------------------------- */
/*                       FILE = srcs/parsing/parsing.c                        */
/* -------------------------------------------------------------------------- */
size_t	ft_strlen(const char *s);
void	*free_tab(char **tab, int k);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*read_file(int fd);
t_vector2D  get_pos(char **map, char c);
int	is_char_in_range(t_vector2D pos, char **map);
int	is_player(char c);
int check_map(char **map);
int	get_longest_line(char **map);
char	*copy_line_and_add(char *str, int size);
char	**resize_map(char **map);
int main(int argc, char **argv);
void    gen_menu_images(void);
t_data	generate_image(char *path);

/* -------------------------------------------------------------------------- */
/*                     FILE = srcs/drawing/draw_player.c                      */
/* -------------------------------------------------------------------------- */
void	ft_draw_player(void);


#endif
