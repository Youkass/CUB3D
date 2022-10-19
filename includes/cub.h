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
/*                   FILE = srcs/raycasting/spritecasting.c                   */
/* -------------------------------------------------------------------------- */
void	sprite_casting(void);

/* -------------------------------------------------------------------------- */
/*                     FILE = srcs/raycasting/check_box.c                     */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/*                    FILE = srcs/raycasting/raycasting.c                     */
/* -------------------------------------------------------------------------- */
void	init_ray(t_raycasting *r);
void	init_dda(t_raycasting *r);
void	dda(t_raycasting *r);
void	compute_drawing_data(t_raycasting *r);
void	draw_wall(t_raycasting *r);
void	*ray_draw(void *t);
void	draw_rays(void);

/* -------------------------------------------------------------------------- */
/*                 FILE = srcs/raycasting/raycasting_utils.c                  */
/* -------------------------------------------------------------------------- */
int intersects(t_circle circle, t_rect rect);
void	ft_put_pixel(t_data *a, t_data *b, t_vector2D pos_a, t_vector2D pos_b);
void	ft_put_pixel_color(t_data *a, char color[4], int x, int y);

/* -------------------------------------------------------------------------- */
/*                  FILE = srcs/raycasting/player_casting.c                   */
/* -------------------------------------------------------------------------- */
int	compute_distance(t_vector2F a, t_vector2F b);
void	sort_by_distance(void);
void	player_casting(void);

/* -------------------------------------------------------------------------- */
/*                       FILE = srcs/drawing/draw_map.c                       */
/* -------------------------------------------------------------------------- */
void	ft_find_wall_scale(void);
void	ft_give_id(void);
t_obj	*ft_copy_map_line(char *line, int index);
int	ft_malloc_map(void);
void	ft_draw_wall(t_obj wall, t_vector2D pos);
void	ft_draw_floor(t_obj wall);
void DrawCircle(int xp, int yp, float radius, int color);
void	ft_draw_map(void);

/* -------------------------------------------------------------------------- */
/*                     FILE = srcs/drawing/draw_player.c                      */
/* -------------------------------------------------------------------------- */
void plot_line (t_vector2D a, t_vector2D b, int color);
t_vector2D	ft_first_vector(void);
t_vector2D	ft_scnd_vector(void);
int	ft_return_xp(void);
int	ft_return_yp(void);
float	ft_return_radius(void);
int	ft_return_xp_2(void);
int	ft_return_yp_2(void);
float	ft_return_radius_2(void);

/* -------------------------------------------------------------------------- */
/*                    FILE = srcs/network/server_thread.c                     */
/* -------------------------------------------------------------------------- */
int	ft_init_client_thread(t_server_data *data);
int	ft_connect_clients(t_server_data *data);
int	ft_recv_first_data(t_client_thread *client);
int	ft_is_get(t_client_thread *client);
int	is_shoot_touch(t_vector2F a, t_vector2F b, t_vector2F c, float r);
void	shoot(t_client_thread *client);
void	routine_before_send(t_client_thread *client);
void	ft_send_all_data(t_client_thread *client);
void	*client_routine(void *client_t);

/* -------------------------------------------------------------------------- */
/*                        FILE = srcs/network/server.c                        */
/* -------------------------------------------------------------------------- */
t_server_data	*_server(void);
int	ft_init_server(t_server_data *data);
int main(int ac, char **av);

/* -------------------------------------------------------------------------- */
/*                          FILE = srcs/utils/math.c                          */
/* -------------------------------------------------------------------------- */
float	mag(t_vector2F v);
t_vector2F	norm(t_vector2F v);
float	max_f(float a, float b);
float	min_f(float a, float b);
float	min(int a, int b);
int	normalise_between(t_vector2D r, t_vector2D t, int nb);
int mod(int a, int b);
float	rad_to_deg(float rad);

/* -------------------------------------------------------------------------- */
/*                         FILE = srcs/utils/clock.c                          */
/* -------------------------------------------------------------------------- */
struct timeval	start_clock();
unsigned long	get_clock(struct timeval start);

/* -------------------------------------------------------------------------- */
/*                       FILE = srcs/utils/collisions.c                       */
/* -------------------------------------------------------------------------- */
void	*detect_neighbors(void);
int	is_neighbor(t_vector2D pos);
t_vector2F	init_potential_dist(int up);
t_nb	*_nb(void);
void	*compute_nb(int i);
int	check_neighbor(int up);
int	circle_circle_col(t_obj *pl);
int	circle_collide(void);

/* -------------------------------------------------------------------------- */
/*                      FILE = srcs/utils/singleton_2.c                       */
/* -------------------------------------------------------------------------- */
t_obj	*_player2();
t_spritecasting	*_pc();

/* -------------------------------------------------------------------------- */
/*                       FILE = srcs/utils/singleton.c                        */
/* -------------------------------------------------------------------------- */
t_data	*_img(void);
t_mlx	*_mlx(void);
t_obj	*_player(void);
t_obj	**__player(void);
t_raycasting	**_ray(void);
t_var	*_var(void);

/* -------------------------------------------------------------------------- */
/*                       FILE = srcs/utils/key_hooks.c                        */
/* -------------------------------------------------------------------------- */
void	key_hook(void);
int	ft_game_hook(int keycode);
int	ft_up_head(void);
int	ft_down_head(void);
int	ft_jump(void);
int	ft_forward(void);
int	ft_is_wall(t_vector2D pos);
int	ft_back(void);
int	ft_right(void);
int	ft_left(void);
int	ft_escape(void);

/* -------------------------------------------------------------------------- */
/*                   FILE = srcs/utils/malloc_hooks_enum.c                    */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/*                    FILE = srcs/network_client/client.c                     */
/* -------------------------------------------------------------------------- */
char	*ft_get_ip_input(void);
int	ft_init_client(void);
void	ft_pong_client();

/* -------------------------------------------------------------------------- */
/*                 FILE = srcs/network_client/network_utils.c                 */
/* -------------------------------------------------------------------------- */
int	end_of_line(char *s);
char	*ft_get_host_ip(void);
int	ft_network_type(char *argv);
t_obj	ft_get_data(t_obj *player);

/* -------------------------------------------------------------------------- */
/*                             FILE = srcs/main.c                             */
/* -------------------------------------------------------------------------- */
void	get_key(int keycode);
int	ft_release(int keycode);
void	generate_dsprite(void);
void	ft_init_player_pos(void);
void	walk_clock(void);
void	death_clock(t_obj *pl);
void	ft_init_player2(void);
void	ft_print_tab(char **s);
int	ft_hook(int keycode);
int	ft_mouse_hook(int keycode);
int	ft_loop_hook(void);
int	ft_mouse_release(int keycode);
int	ft_game(void);
void	init_key(void);
int main(int argc, char **argv);

/* -------------------------------------------------------------------------- */
/*                            FILE = srcs/shoot.c                             */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/*                        FILE = srcs/menu/generate.c                         */
/* -------------------------------------------------------------------------- */
t_data	generate_image(char *path);
t_vector2D	*_butp(void);
void	generate_button_state(void);
void    gen_menu_images(void);

/* -------------------------------------------------------------------------- */
/*                          FILE = srcs/menu/loop.c                           */
/* -------------------------------------------------------------------------- */
void	check_button_state(void);
void	check_action_state_bar(int i);
void	check_action_state_options(int i);
void	check_button_state_options(void);
void	planet_clock(void);
int	menu_loop(void);
int	menu_hook(int keycode);

/* -------------------------------------------------------------------------- */
/*                         FILE = srcs/menu/render.c                          */
/* -------------------------------------------------------------------------- */
void	draw_bg(void);
int	perc(int a, int b);
void	menu_start(void);
void	menu_option(void);

/* -------------------------------------------------------------------------- */
/*                       FILE = srcs/menu/mouse_hook.c                        */
/* -------------------------------------------------------------------------- */
void	check_button_state_mouse(int kc);
void	check_button_state_mouse_options(int kc);
int	menu_mouse_hook(int keycode);

/* -------------------------------------------------------------------------- */
/*                          FILE = srcs/menu/utils.c                          */
/* -------------------------------------------------------------------------- */
void	restart_button(void);
int	ft_hitbox(t_vector2D hitbox[4], t_vector2D pos);
void	draw_pixel(t_data *big, t_data lil, t_vector2D it, t_vector2D rel_pos);
t_data	ft_put_image_to_image(t_data big, t_data lil, t_vector2D pos);
t_data	ft_put_sprite_to_image(t_data big, t_data lil, t_vector2D pos, t_vector2D sp_pos, t_vector2D size);
void	draw_pixel_color(t_data *big, t_vector2D rel_pos, char pix[4]);
void	draw_vertical_line(t_data *img, t_vector2D pos, int h);
void	draw_bar_fill(void);

/* -------------------------------------------------------------------------- */
/*                         FILE = srcs/menu/dragbar.c                         */
/* -------------------------------------------------------------------------- */
void	s_bar_drag(void);
void	m_bar_drag(void);
void	drag_bar(void);

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

/* -------------------------------------------------------------------------- */
/*                     FILE = srcs/mlx_utils/mlx_utils.c                      */
/* -------------------------------------------------------------------------- */
void	ft_init_mlx();
void	ft_init_img();
void	ft_pixel_put(float x, float y, int color);
void	ft_reload_frame();
void	ft_fps(void);
void	*ft_draw_void(void *r);
void	draw_void_thread();
int	ft_loop();


#endif
