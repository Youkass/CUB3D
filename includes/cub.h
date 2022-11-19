/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobougre <yobougre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 12:52:24 by yobougre          #+#    #+#             */
/*   Updated: 2021/10/19 15:08:54 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "struct.h"
# include "includes.h"

/* -------------------------------------------------------------------------- */
/*                 FILE = ./srcs/raycasting/player_casting.c                  */
/* -------------------------------------------------------------------------- */
int	compute_distance(t_vector2F a, t_vector2F b);
void	sort_by_distance(t_obj *player);
void	player_casting(void);

/* -------------------------------------------------------------------------- */
/*                  FILE = ./srcs/raycasting/name_casting.c                   */
/* -------------------------------------------------------------------------- */
void	name_casting(void);

/* -------------------------------------------------------------------------- */
/*                 FILE = ./srcs/raycasting/bullet_casting.c                  */
/* -------------------------------------------------------------------------- */
void	bullet_casting(void);

/* -------------------------------------------------------------------------- */
/*                   FILE = ./srcs/raycasting/raycasting.c                    */
/* -------------------------------------------------------------------------- */
void	init_ray(t_raycasting *r);
void	init_dda(t_raycasting *r);
void	dda(t_raycasting *r);
void	compute_drawing_data(t_raycasting *r);
void	draw_wall(t_raycasting *r);
void	*ray_draw(void *t);
void	draw_rays(void);

/* -------------------------------------------------------------------------- */
/*                    FILE = ./srcs/raycasting/check_box.c                    */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/*                FILE = ./srcs/raycasting/raycasting_utils.c                 */
/* -------------------------------------------------------------------------- */
int intersects(t_circle circle, t_rect rect);
void	ft_put_pixel(t_data *a, t_data *b, t_vector2D pos_a, t_vector2D pos_b);
void	ft_put_pixel_color(t_data *a, char color[4], int x, int y);

/* -------------------------------------------------------------------------- */
/*                  FILE = ./srcs/raycasting/spritecasting.c                  */
/* -------------------------------------------------------------------------- */
void	sprite_casting(void);

/* -------------------------------------------------------------------------- */
/*                           FILE = ./srcs/shoot.c                            */
/* -------------------------------------------------------------------------- */
t_vector2F	closest_point(t_vector2F a, t_vector2F b, t_vector2F c);
int	is_shoot_touch(t_vector2F a, t_vector2F b, t_circle c, t_vector2F *closest);
void	shoot_alone3F(void);
void	shoot(void);
int	nearest_wall3D(t_vector3F	*closest);
void	init_shot3F(t_vector3F start, t_vector3F end);

/* -------------------------------------------------------------------------- */
/*                            FILE = ./srcs/init.c                            */
/* -------------------------------------------------------------------------- */
void	init_weapons(void);

/* -------------------------------------------------------------------------- */
/*                     FILE = ./srcs/utils/singleton_2.c                      */
/* -------------------------------------------------------------------------- */
t_obj	*_player2();
t_spritecasting	*_pc();
t_menu	*_menu();
t_weapon	**_weapon(void);
t_team	**_team(void);
t_image	*_image();

/* -------------------------------------------------------------------------- */
/*                      FILE = ./srcs/utils/singleton.c                       */
/* -------------------------------------------------------------------------- */
t_data	*_img(void);
t_mlx	*_mlx(void);
t_media	*_media(void);
t_obj	*_player(void);
t_raycasting	**_ray(void);
t_var	*_var(void);
t_log	*_log(void);

/* -------------------------------------------------------------------------- */
/*                        FILE = ./srcs/utils/sound.c                         */
/* -------------------------------------------------------------------------- */
void	ft_add_sound(int index_1, int index_2, char *path);
void	ft_init_game_music(void);
void	ft_init_sound(void);
void	ft_init_media(void);
int	ft_check_game_music(void);
void	ft_init_ran(void);
void	ft_start_from_start(ma_sound *sound);
void	ft_play_end_sound(ma_sound *sound);
int	ft_play_end_round(void);
int	ft_play_end_game(void);
void	ft_check_end_songs(void);
int	ft_check_enemie_team(void);
int	ft_check_my_team(void);
void	ft_play_music(int index);
void	ft_play_shot_sound(t_obj player);
void	ft_play_own_shot(void);

/* -------------------------------------------------------------------------- */
/*                        FILE = ./srcs/utils/clock.c                         */
/* -------------------------------------------------------------------------- */
struct timeval	start_clock(void);
unsigned long	get_clock(struct timeval start);
unsigned long	get_time(unsigned long start);
unsigned long	get_time_server(unsigned long start, struct timeval clock);

/* -------------------------------------------------------------------------- */
/*                        FILE = ./srcs/utils/click.c                         */
/* -------------------------------------------------------------------------- */
void	click(void);
int	click_update(void);
int	click_delay(void);
void	replace_player(void);
void	restart_player(void);
int	is_neutral(void);

/* -------------------------------------------------------------------------- */
/*                      FILE = ./srcs/utils/key_hooks.c                       */
/* -------------------------------------------------------------------------- */
void	crouch(int	mode);
void	key_hook(void);
int	ft_game_hook(int keycode);
int	ft_up_head(void);
int	ft_down_head(void);
int	ft_jump(void);
int	ft_forward(void);
int	ft_is_wall(t_vector2D pos);
int	ft_back(void);
int	ft_right(void);
int	ft_strafe_left(void);
int	ft_strafe_right(void);
int	ft_left(void);
int	ft_escape(void);

/* -------------------------------------------------------------------------- */
/*                         FILE = ./srcs/utils/list.c                         */
/* -------------------------------------------------------------------------- */
t_list	*ft_lstnew(void *content);
int	ft_lstsize(t_list *lst);
void	ft_lstadd_front(t_list **alst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
void	ft_lst_dellast(t_list **lst);

/* -------------------------------------------------------------------------- */
/*                       FILE = ./srcs/utils/garbage.c                        */
/* -------------------------------------------------------------------------- */
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstclear_img(t_list **lst);
void	ft_lstclear_media(t_list **lst);
void	ft_lstadd_back(t_list **alst, t_list *new);
t_list	*_lst(void);
t_list	*_lstimg(void);
t_list	*_lstmedia(void);
t_list	*ft_new_node(void *content);
void	*ft_malloc(int size);
void	ft_black_hole(int exit_code);

/* -------------------------------------------------------------------------- */
/*                  FILE = ./srcs/utils/malloc_hooks_enum.c                   */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/*                      FILE = ./srcs/utils/collisions.c                      */
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
/*                            FILE = ./srcs/main.c                            */
/* -------------------------------------------------------------------------- */
void get_key(int keycode);
int ft_release(int keycode);
void generate_dsprite(void);
void generate_dsprite_red(void);
void ft_init_player_pos(void);
void walk_clock(void);
void death_clock(void);
void reload_clock(void);
void ft_init_player2(void);
void ft_print_tab(char **s);
int ft_hook(int keycode);
int ft_mouse_hook(int keycode);
int ft_loop_hook(void);
int ft_mouse_release(int keycode);
int ft_expose(void *data);
int ft_rotate(double rot_speed);
int mouse_rotate(void);
int ft_game(void);
void init_key(void);
void init_var(void);
void init_data_shot(t_obj *player);
void init_image(void);
int main(int argc, char **argv);

/* -------------------------------------------------------------------------- */
/*                   FILE = ./srcs/network_client/client.c                    */
/* -------------------------------------------------------------------------- */
char	*ft_get_ip_input(void);
int	ft_init_client(void);
void	ft_copy_data_before_pong(t_obj *player);
void	print_data_recv(t_obj	*player);
void	restart_round(void);
void	render_kill_log();
void	get_data(int i, t_send_server_game serv);
void	ft_pong_client(void);

/* -------------------------------------------------------------------------- */
/*                FILE = ./srcs/network_client/network_utils.c                */
/* -------------------------------------------------------------------------- */
int	end_of_line(char *s);
char	*ft_get_host_ip(void);
t_obj	ft_get_data(t_obj *player);

/* -------------------------------------------------------------------------- */
/*                      FILE = ./srcs/menu/recv_utils.c                       */
/* -------------------------------------------------------------------------- */
int	ft_recv_players(t_send_server *o_player, int size);
int	ft_recv_one(int socket, t_send_client *player, int size);

/* -------------------------------------------------------------------------- */
/*                      FILE = ./srcs/menu/menu_lobby.c                       */
/* -------------------------------------------------------------------------- */
void	get_pseudos(void);
void	menu_pong(void);

/* -------------------------------------------------------------------------- */
/*                        FILE = ./srcs/menu/dragbar.c                        */
/* -------------------------------------------------------------------------- */
void	s_bar_drag(void);
void	m_bar_drag(void);
void	drag_bar(void);

/* -------------------------------------------------------------------------- */
/*                        FILE = ./srcs/menu/render.c                         */
/* -------------------------------------------------------------------------- */
void	draw_bg(char color[4]);
int	perc(int a, int b);
void	menu_start(void);
void	menu_player(void);
void	draw_lobby(void);
void	draw_leaderboard(void);
void	update_key(void);
void	draw_pseudo_box(char	*pseudo, int i, int team);
void	draw_pseudo_box_leader(char	*pseudo, int id, int i, int team);
int	get_ratio(int kills, int deaths);
void	sort_team(void);
void	menu_lobby(void);
void	menu_leaderboard(void);
void	menu_pseudo(void);
void	menu_ip(void);
void	menu_option(void);

/* -------------------------------------------------------------------------- */
/*                         FILE = ./srcs/menu/loop.c                          */
/* -------------------------------------------------------------------------- */
void	check_button_state(void);
void	check_button_state_pl(void);
void	check_action_state_bar(int i);
void	check_action_state_options(int i);
void	check_button_state_options(void);
void	planet_clock(void);
int	menu_loop(void);
int	menu_hook(int keycode);
int	menu_hook_pseudo(int keycode);
int	menu_hook_ip(int keycode);

/* -------------------------------------------------------------------------- */
/*                       FILE = ./srcs/menu/generate.c                        */
/* -------------------------------------------------------------------------- */
t_data	generate_image(char *path);
t_vector2D	*_butp(void);
t_vector2D	*_butpl(void);
void	gen_serv_but(void);
void	generate_button_state(void);
void	gen_alpha(void);
void    gen_menu_images(void);

/* -------------------------------------------------------------------------- */
/*                         FILE = ./srcs/menu/intro.c                         */
/* -------------------------------------------------------------------------- */
void	ft_open_intro_sprites(void);
void	ft_intro_sprite_to_image(int i1, int i2, t_vector2D v1, t_vector2D v2);
t_vector2D	ft_draw_youri(void);
t_vector2D	ft_draw_darian(void);
void	ft_end_intro(t_vector2D *double_pos);
void	ft_intro(void);

/* -------------------------------------------------------------------------- */
/*                      FILE = ./srcs/menu/mouse_hook.c                       */
/* -------------------------------------------------------------------------- */
void	check_button_state_mouse(int kc);
void	check_button_state_mouse_pl(int kc);
void	check_button_state_mouse_options(int kc);
int	menu_mouse_hook(int keycode);

/* -------------------------------------------------------------------------- */
/*                         FILE = ./srcs/menu/utils.c                         */
/* -------------------------------------------------------------------------- */
void	restart_button(void);
int	ft_hitbox(t_vector2D hitbox[4], t_vector2D pos);
void	draw_pixel(t_data *big, t_data lil, t_vector2D it, t_vector2D rel_pos);
void	draw_pixel_create(t_data *big, t_data lil, t_vector2D it, t_vector2D rel_pos);
t_data	ft_put_image_to_image_scale(t_data big, t_data lil, t_vector2D p, t_vector2F scale);
t_data	ft_put_image_to_image(t_data big, t_data lil, t_vector2D pos);
t_data	ft_put_image_to_image_create(t_data big, t_data lil, t_vector2D pos);
t_data	ft_put_sprite_to_images_scale(t_data big, t_data lil, t_vector2D pos, t_vector2D sp_pos, t_vector2D size, t_vector2D scale);
t_data	ft_put_sprite_to_images(t_data big, t_data lil, t_vector2D pos, t_vector2D sp_pos, t_vector2D size);
void	draw_pixel_color(t_data *big, t_vector2D rel_pos, char pix[4]);
void	draw_vertical_line(t_data *img, t_vector2D pos, int h);
void	draw_bar_fill(void);

/* -------------------------------------------------------------------------- */
/*                   FILE = ./srcs/network/server_thread.c                    */
/* -------------------------------------------------------------------------- */
void	ft_exit(int signal);
int	ft_init_client_thread(t_server_data *data);
int	ft_connect_clients(t_server_data *data);
int	ft_recv_first_data(t_client_thread *client);
int	ft_is_get(t_client_thread *client);
int ft_is_send(t_client_thread *client);
int	check_only(int nb, int r, int type);
int	round_play(int round, t_send_server_game *data, t_client_thread *client, int is_finished);
int	round_end(t_send_server_game *data, t_client_thread *client);
int	round_end_wait(t_send_server_game *data, t_client_thread *client);
int	round_wait_start(t_send_server_game *data, t_client_thread *client);
int	round_start(int *round, t_send_server_game *data, t_client_thread *client);
void	round_leaderboard(t_send_server_game *data, t_client_thread *client);
int	ft_send_all_data(t_client_thread *client);
int	send_nb_players(t_client_thread *client);
void	check_team(t_client_thread *c);
void	init_team_server(t_client_thread *c);
void	get_team_id(t_client_thread	*c);
void	*client_routine(void *client_t);

/* -------------------------------------------------------------------------- */
/*                       FILE = ./srcs/network/lobby.c                        */
/* -------------------------------------------------------------------------- */
int	ft_recv_first_data_lobby(t_client_thread *client, int nb);
int	ft_send_all_data_lobby(t_client_thread *client, int nb);
int	ft_player_team(t_client_thread *client, int id);
int	ft_update(t_client_thread *client);
int	wait_lobby(t_client_thread *client);

/* -------------------------------------------------------------------------- */
/*                       FILE = ./srcs/network/server.c                       */
/* -------------------------------------------------------------------------- */
t_server_data	*_server(void);
void	restart_state(t_client_thread	*c);
int	ft_init_server(t_server_data *data);
void	ft_exit(int signal);
int main(int ac, char **av);

/* -------------------------------------------------------------------------- */
/*                            FILE = ./srcs/team.c                            */
/* -------------------------------------------------------------------------- */
void	init_player_team();
int	get_id_by_pseudo(char *pseudo);
void	init_teams(void);

/* -------------------------------------------------------------------------- */
/*                      FILE = ./srcs/mlx_utils/render.c                      */
/* -------------------------------------------------------------------------- */
void	render_health(t_vector2D	a);

/* -------------------------------------------------------------------------- */
/*                    FILE = ./srcs/mlx_utils/mlx_utils.c                     */
/* -------------------------------------------------------------------------- */
void	ft_init_mlx();
void	ft_init_img();
void	ft_pixel_put(float x, float y, int color);
void	ft_reload_frame();
void	ft_fps(void);
void	draw_sky(void);
void	*ft_draw_void(void *r);
void	draw_void_thread(void);
void	check_death(void);
void	update_bullets(void);
void	recompute_array_shot(int index);
void	update_bullets3F(void);
void	hud(void);
void	set_spectate(void);
void	draw_death(void);
int	ft_loop(void);

/* -------------------------------------------------------------------------- */
/*                      FILE = ./srcs/parsing/parsing.c                       */
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
/*                         FILE = ./srcs/math/math.c                          */
/* -------------------------------------------------------------------------- */
float	mag(t_vector2F v);
t_vector2F	norm(t_vector2F v);
float	max_f(float a, float b);
float	min_f(float a, float b);
float	min(int a, int b);
int	normalise_between(t_vector2D r, t_vector2D t, int nb);
float	normalise_between2F(t_vector2F r, t_vector2F t, int nb);
int mod(int a, int b);
float	rad_to_deg(float rad);
float	deg_to_rad(float deg);

/* -------------------------------------------------------------------------- */
/*                   FILE = ./srcs/math/vector/operator2D.c                   */
/* -------------------------------------------------------------------------- */
t_vector2D div_2D(t_vector2D a, t_vector2D b);
t_vector2D mult_2D(t_vector2D a, t_vector2D b);

/* -------------------------------------------------------------------------- */
/*                   FILE = ./srcs/math/vector/operator2F.c                   */
/* -------------------------------------------------------------------------- */
t_vector2F div_2F(t_vector2F a, t_vector2F b);
t_vector2F mult_2F(t_vector2F a, t_vector2F b);
float	fdot(t_vector2F a, t_vector2F b);
t_vector2F	sub_2f(t_vector2F a, t_vector2F b);
t_vector2F	add_2f(t_vector2F a, t_vector2F b);
t_vector3F	add_3f(t_vector3F a, t_vector3F b);

/* -------------------------------------------------------------------------- */
/*                     FILE = ./srcs/math/vector/tools.c                      */
/* -------------------------------------------------------------------------- */
t_vector2F	dist_2f(t_vector2F a, t_vector2F b);
t_vector3F	dist_3f(t_vector3F a, t_vector3F b);
t_vector2F	velocity_ms(t_vector2F dist, float time_ms);
t_vector3F	velocity_ms3F(t_vector3F dist, float time_ms);
float	get_time_velo3F(float dist, float time_ms_per_unit);
t_vector2F	velocity_get_point(t_vector2F start, t_vector2F velo, int time_ms);
t_vector3F	velocity_get_point3F(t_vector3F start, t_vector3F velo, int time_ms);
float	one_dist2F(t_vector2F a, t_vector2F b);
float	one_dist3F(t_vector3F a, t_vector3F b);

/* -------------------------------------------------------------------------- */
/*                       FILE = ./srcs/new_raycaster.c                        */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/*                          FILE = ./srcs/ft_itoa.c                           */
/* -------------------------------------------------------------------------- */
int	size_nb(int nb);
char	*ft_itoa(int n);

/* -------------------------------------------------------------------------- */
/*                          FILE = ./srcs/kill_log.c                          */
/* -------------------------------------------------------------------------- */
t_elem	*new_log(int id1, int id2);
void	print_log(t_list	*li);

/* -------------------------------------------------------------------------- */
/*                      FILE = ./srcs/drawing/draw_map.c                      */
/* -------------------------------------------------------------------------- */
void	ft_find_wall_scale(void);
void	ft_give_id(void);
t_obj	*ft_copy_map_line(char *line, int index);
int	ft_malloc_map(void);
void	ft_draw_wall(t_obj wall, t_vector2D pos);
void	ft_draw_floor(t_obj wall);
void DrawCircle(int xp, int yp, float radius, int color);
void	draw_player_map(void);
void	ft_draw_map(void);

/* -------------------------------------------------------------------------- */
/*                     FILE = ./srcs/drawing/draw_text.c                      */
/* -------------------------------------------------------------------------- */
int	is_allow_alpha(char c);
char	char_up(char c);
void	draw_text(char *text, t_vector2D pos, char color[4]);
t_data	ft_draw_char(t_data big, t_data lil, t_vector2D pos, char color[4]);
t_data	ft_draw_char_scale(t_data big, t_data lil, t_vector2D p, t_vector2D scale, char color[4]);
void	draw_text_scale(char *text, t_vector2D pos, t_vector2D scale, char color[4]);
t_data	create_text_img(char *text, char color[4]);
void	draw_rectange(t_vector2D a, t_vector2D size, char color[4]);

/* -------------------------------------------------------------------------- */
/*                    FILE = ./srcs/drawing/draw_player.c                     */
/* -------------------------------------------------------------------------- */
void plot_line (t_vector2D a, t_vector2D b, int color);
t_vector2D	ft_first_vector(void);
t_vector2D	ft_scnd_vector(void);
int	ft_return_xp(t_obj *player, t_obj *my_player);
int	ft_return_yp(t_obj *player, t_obj *my_player);
float	ft_return_radius(t_obj *player);
int	ft_return_xp_2(void);
int	ft_return_yp_2(void);
float	ft_return_radius_2(void);

/* -------------------------------------------------------------------------- */
/*                         FILE = ./srcs/dyn_array.c                          */
/* -------------------------------------------------------------------------- */
void	init_array(t_array *a, int size);
int	kill_push(int	value);
int	arr_push(t_array *a, int	value);
void	arr_pop(t_array *a, int	id);
void	arr_destroy(t_array *a);
void	arr_fill(t_array *a, int value);
void	print_arr(t_array *a);
int	ft_in_array(t_array *a, int value);
t_vector2F	get_90_angle(int	dir);

/* -------------------------------------------------------------------------- */
/*                           FILE = ./srcs/tools.c                            */
/* -------------------------------------------------------------------------- */
t_vector2D	pos(int x, int y);
t_vector2F	posf(float x, float y);
t_vector3F	pos3f(float x, float y, float z);


#endif
