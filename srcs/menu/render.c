/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 13:05:50 by denissereno       #+#    #+#             */
/*   Updated: 2022/11/17 22:25:43 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	draw_bg(char color[4])
{

	t_int		var;

	var.i = 0;
	while (var.i < WIN_W)
	{
		var.j = 0;
		while (var.j < WIN_H)
		{
			ft_put_pixel_color(_img(), color, (int)var.i, (int)var.j);
			var.j++;
		}
		var.i++;
	}
}

/*
-Compute the percentage of b in a. 30% {b} of 100 {b} = 30 {result};
*/
int	perc(int a, int b)
{
	return ((a / 100) * b);
}

/*
-Display starting menu
*/
void	menu_start(void)
{
	static t_vector2D	double_pos[2];
	static int 			start = 0;

	if (!start)
	{
		double_pos[1].x = 430;
		double_pos[1].y = 50;
		double_pos[0].x = 722;
		double_pos[0].y = 50;
		++start;
	}
	ft_play_music(MENU_MUSIC);
	draw_bg((char [4]){0, 0, 0, 0});
	ft_put_image_to_image(*_img(), _menu()->bg,
		(t_vector2D){0, 0});
	ft_put_image_to_image(*_img(), _menu()->buttons
	[_menu()->s_state[0].state][PLAY], _butp()[0]);
	ft_put_image_to_image(*_img(), _menu()->buttons
	[_menu()->s_state[1].state][OPTIONS], _butp()[1]);
	ft_put_image_to_image(*_img(), _menu()->buttons
	[_menu()->s_state[2].state][CREDITS], _butp()[2]);
	ft_put_image_to_image(*_img(), _menu()->buttons
	[_menu()->s_state[3].state][EXIT], _butp()[3]);
	ft_end_intro(double_pos);
}

void	menu_player(void)
{
	draw_bg((char [4]){0, 0, 0, 0});
	ft_put_image_to_image(*_img(), _menu()->bg,
		(t_vector2D){0, 0});
	ft_put_image_to_image(*_img(), _menu()->logo,
		(t_vector2D){WIN_W / 2 - (_menu()->logo.w / 2), perc(WIN_H, 20) - (_menu()->logo.h / 2)});

	ft_put_image_to_image(*_img(), _menu()->nb_p[0][_menu()->p_state[0].state], _butpl()[0]);
	ft_put_image_to_image(*_img(), _menu()->nb_p[1][_menu()->p_state[1].state],  _butpl()[1]);
	ft_put_image_to_image(*_img(), _menu()->nb_p[2][_menu()->p_state[2].state],  _butpl()[2]);
	ft_put_image_to_image(*_img(), _menu()->nb_p[3][_menu()->p_state[3].state],  _butpl()[3]);
}

void	draw_lobby(void)
{
	int	i;
	int	size_box;

	i = 0;
	size_box = _menu()->wait.w / _var()->nb_player;
	// Couleur rouge blanc et bleu
	draw_rectange(pos(0, 0), pos(WIN_W / 3, WIN_H), RED);
	draw_rectange(pos(WIN_W / 3, 0), pos(WIN_W / 3, WIN_H), LIGTH_GREY);
	draw_rectange(pos((WIN_W / 3) * 2, 0), pos(WIN_W / 3, WIN_H), BLUE);
	//bandeau gris en haut
	draw_rectange(pos(0, 0), pos(WIN_W, WIN_H / 3), LIGTH_GREY);
	// bande grise
	draw_rectange(pos(0, WIN_H / 3 - 8), pos(WIN_W, 16), DARK_GREY);
	draw_rectange(pos(WIN_W / 3 - 8, WIN_H / 3), pos(16, WIN_H), DARK_GREY);
	draw_rectange(pos((WIN_W / 3) * 2 - 8, WIN_H / 3), pos(16, WIN_H), DARK_GREY);
	draw_rectange(pos(0, WIN_H / 3), pos(16, (WIN_H / 3) * 2), DARK_GREY);
	draw_rectange(pos(WIN_W - 16, WIN_H / 3), pos(16, (WIN_H / 3) * 2), DARK_GREY);
	while (i < _var()->linked_players)
	{
		if (_var()->o_player[i].team == TEAM_VOID)
		{
			draw_rectange(
			pos(WIN_W / 4 - (_menu()->wait.w / 2) + i * size_box, (WIN_H / 3) / 2 + 16),
			pos(size_box - 16, 16), colo(0, 0, 0));
		}
		else if (_var()->o_player[i].team == TEAM_RED)
		{
			draw_rectange(
			pos(WIN_W / 4 - (_menu()->wait.w / 2) + i * size_box, (WIN_H / 3) / 2 + 16),
			pos(size_box - 16, 16), RED);
		}
		else
		{
			draw_rectange(
			pos(WIN_W / 4 - (_menu()->wait.w / 2) + i * size_box, (WIN_H / 3) / 2 + 16),
			pos(size_box - 16, 16), BLUE);
		}
		i++;
	}
}

void	draw_leaderboard(void)
{
	// Couleur rouge blanc et bleu
	draw_rectange(pos(0, 0), pos(WIN_W / 3, WIN_H), RED);
	draw_rectange(pos(WIN_W / 3, 0), pos(WIN_W / 3, WIN_H), LIGTH_GREY);
	draw_rectange(pos((WIN_W / 3) * 2, 0), pos(WIN_W / 3, WIN_H), BLUE);
	//bandeau gris en haut
	draw_rectange(pos(0, 0), pos(WIN_W, WIN_H / 3), LIGTH_GREY);
	// bande grise
	draw_rectange(pos(0, WIN_H / 3 - 8), pos(WIN_W, 16), DARK_GREY);
	draw_rectange(pos(WIN_W / 3 - 8, WIN_H / 3), pos(16, WIN_H), DARK_GREY);
	draw_rectange(pos((WIN_W / 3) * 2 - 8, WIN_H / 3), pos(16, WIN_H), DARK_GREY);
	draw_rectange(pos(0, WIN_H / 3), pos(16, (WIN_H / 3) * 2), DARK_GREY);
	draw_rectange(pos(WIN_W - 16, WIN_H / 3), pos(16, (WIN_H / 3) * 2), DARK_GREY);
}

void	click(void)
{
	_var()->start_click = get_clock(_var()->clock);
	_var()->click = 1;
}

int	click_update(void)
{
	if (_var()->click && get_time(_var()->start_click)> 170000)
		_var()->click = 0;
	return (0);
}

int	click_delay(void)
{
	if (_var()->click == 1)
		return(1);
	return (0);
}

void	update_key(void)
{
	if (_var()->key[left] == 1 && _player()->team > 0 && !click_delay())
	{
		click();
		_player()->team--;
		_player()->change_team = 1;
	}
	if (_var()->key[right] == 1 && _player()->team < 2 && !click_delay())
	{
		click();
		_player()->team++;
		_player()->change_team = 1;
	}
}

void	draw_pseudo_box(char	*pseudo, int i, int team)
{
	int	size;

	size = ft_strlen(pseudo) * 21;
	if (team == TEAM_VOID)
		draw_text_scale(pseudo, pos(WIN_W / 2 - size / 2, WIN_H / 3 + 64 + i * 60), pos(2, 2), colo(12, 12, 12));
	if (team == TEAM_RED)
		draw_text_scale(pseudo, pos((WIN_W / 3) / 2 - size / 2, WIN_H / 3 + 64 + i * 60), pos(2, 2), colo(12, 12, 12));
	if (team == TEAM_BLUE)
		draw_text_scale(pseudo, pos(((WIN_W / 3) * 2) + (WIN_W / 3) / 2  - size / 2, WIN_H / 3 + 64 + i * 60), pos(2, 2), colo(12, 12, 12));
}

void	draw_pseudo_box_leader(char	*pseudo, int id, int i, int team)
{
	int		size;
	t_vector2D	posp;

	pseudo = ft_strjoin(pseudo,
	ft_strjoin(": ",
	ft_strjoin(ft_itoa(_var()->o_player[id].kills),
	ft_strjoin(" / ", ft_itoa(_var()->o_player[id].deaths)))));
	size = ft_strlen(pseudo) * 21;
	if (team == TEAM_RED)
		posp = pos((WIN_W / 3) / 2 - size / 2, WIN_H / 3 + 64 + i * 60);
	if (team == TEAM_BLUE)
		posp = pos(((WIN_W / 3) * 2) + (WIN_W / 3) / 2  - size / 2, WIN_H / 3 + 64 + i * 60);
	draw_text_scale(pseudo, posp, pos(2, 2), colo(12, 12, 12));
}

int	get_ratio(int kills, int deaths)
{
	if (deaths == 0)
		return (kills);
	else
		return (kills / deaths);
}


void	sort_team(void)
{
	int	i;
	int	j;
	t_vector2D	id;
	int tmp;

	i = 0;
	while (i < _var()->n_red - 1)
	{
		j = 0;
		while (j < _var()->n_red - 1 - i)
		{
			id.x = _var()->red[j];
			id.y = _var()->red[j + 1];
			if (get_ratio(_var()->o_player[id.x].kills,
				_var()->o_player[id.x].deaths) > get_ratio(_var()->o_player
				[id.y].kills, _var()->o_player[id.y].deaths))
			{
				tmp = _var()->red[j];
				_var()->red[j] = _var()->red[j + 1];
				_var()->red[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
	i = 0;
	while (i < _var()->n_blue)
	{
		j = 0;
		while (j < _var()->n_blue - 1 - i)
		{
			id.x = _var()->blue[j];
			id.y = _var()->blue[j + 1];
			if (get_ratio(_var()->o_player[id.x].kills,
				_var()->o_player[id.x].deaths) > get_ratio(_var()->o_player
				[id.y].kills, _var()->o_player[id.y].deaths))
			{
				tmp = _var()->blue[j];
				_var()->blue[j] = _var()->blue[j + 1];
				_var()->blue[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	menu_lobby(void)
{
	int	i;

	update_key();
	draw_lobby();
	ft_put_image_to_image(*_img(), _menu()->wait,
	(t_vector2D){WIN_W / 4 - (_menu()->wait.w / 2), (WIN_H / 3) / 2 - (_menu()->wait.h / 2) - 16});
	i = 0;
	while (i < _var()->n_red)
	{
		draw_pseudo_box(_var()->o_player[_var()->red[i]].pseudo, i, TEAM_RED);
		i++;
	}
	i = 0;
	while (i < _var()->n_blue)
	{
		draw_pseudo_box(_var()->o_player[_var()->blue[i]].pseudo, i, TEAM_BLUE);
		i++;
	}
	i = 0;
	while (i < _var()->n_neutral)
	{
		draw_pseudo_box(_var()->o_player[_var()->neutral[i]].pseudo, i, TEAM_VOID);
		i++;
	}
	if (_var()->is_host == SERVER)
		draw_text_scale(ft_strjoin("ip ", ft_get_host_ip()), (t_vector2D){200, 10}
		, pos(2, 2), colo(100, 86, 68));
	else
		draw_text(_var()->ip, (t_vector2D){200, 10}, colo(100, 86, 68));
	if (_var()->is_host == SERVER && _var()->linked_players >= _var()->nb_player)
		draw_text("'Space' to start", (t_vector2D){200, 300 + (i + 2) * 60}, colo(100, 86, 68));
}

void	menu_leaderboard(void)
{
	int	i;

	draw_leaderboard();
	sort_team();
	i = 0;
	while (i < _var()->n_red)
	{
		draw_pseudo_box_leader(_var()->o_player[_var()->red[i]].pseudo, _var()->red[i], i, TEAM_RED);
		i++;
	}
	i = 0;
	while (i < _var()->n_blue)
	{
		draw_pseudo_box_leader(_var()->o_player[_var()->blue[i]].pseudo, _var()->blue[i], i, TEAM_BLUE);
		i++;
	}
}

void	menu_pseudo(void)
{
	draw_bg((char [4]){250, 200, 0, 0});
	ft_put_image_to_image(*_img(), _image()->alpha['D'], (t_vector2D){300, 300});
	draw_text("Enter your pseudo (max 16)", (t_vector2D){200, 100}, GREEN);
	draw_rectange((t_vector2D){300, 300}, (t_vector2D){50 * 16, 150}, (char [4]){0, 0, 0, 0});
	draw_text(_player()->pseudo, (t_vector2D){350, 350}, colo(100, 86, 68));
}

void	menu_ip(void)
{

	draw_bg((char [4]){250, 200, 0, 0});
	draw_text("Enter your ip (max 15)('space for '.')", (t_vector2D){100, 100}, colo(100, 86, 68));
	draw_rectange((t_vector2D){300, 300}, (t_vector2D){50 * 16, 150}, (char [4]){0, 0, 0, 0});
	draw_text(_var()->ip, (t_vector2D){350, 350}, colo(100, 86, 68));
}


/*
-Display bottoms button of menu_options.
*/
static void	menu_bot_options(void)
{
	ft_put_image_to_image(*_img(), _menu()->buttons[_var()
		->menu->o_state[3].state][_menu()->mute_m_state],
		_menu()->o_state[3].hitbox[0]);
	ft_put_image_to_image(*_img(), _menu()->buttons[_menu()
		->o_state[4].state][L_ARR], _menu()->o_state[4].hitbox[0]);
	ft_put_image_to_image(*_img(), _menu()->bar[EMPTY][BAR_LEFT],
		(t_vector2D){819 - OFFSET_X, 542 - OFFSET_Y});
	ft_put_image_to_image(*_img(), _menu()->bar[EMPTY][BAR_MID],
		(t_vector2D){912 - OFFSET_X, 542 - OFFSET_Y});
	ft_put_image_to_image(*_img(), _menu()->bar[EMPTY]
	[BAR_RIGHT], (t_vector2D){1005 - OFFSET_X, 542 - OFFSET_Y});
	ft_put_image_to_image(*_img(), _menu()->buttons[_menu()
		->o_state[5].state][R_ARR], _menu()->o_state[5].hitbox[0]);
	ft_put_image_to_image(*_img(), _menu()->buttons[_menu()
		->o_state[6].state][QUIT], _menu()->o_state[6].hitbox[0]);
}

/*
-Display option menu
*/
void	menu_option(void)
{
	ft_put_image_to_image(*_img(), _menu()->bg,
		(t_vector2D){0, 0});
	ft_put_image_to_image(*_img(), _menu()->logo,
		(t_vector2D){716 - OFFSET_X - 45, 155 - OFFSET_Y + 50});
	draw_bar_fill();
	ft_put_image_to_image(*_img(), _menu()->buttons[_menu()
		->o_state[0].state][_menu()->mute_s_state],
		_menu()->o_state[0].hitbox[0]);
	ft_put_image_to_image(*_img(), _menu()->buttons[_menu()
		->o_state[1].state][L_ARR], _menu()->o_state[1].hitbox[0]);
	ft_put_image_to_image(*_img(), _menu()->bar[EMPTY][BAR_LEFT],
		(t_vector2D){819 - OFFSET_X, 443 - OFFSET_Y});
	ft_put_image_to_image(*_img(), _menu()->bar[EMPTY][BAR_MID],
		(t_vector2D){912 - OFFSET_X, 443 - OFFSET_Y});
	ft_put_image_to_image(*_img(), _menu()->bar[EMPTY]
	[BAR_RIGHT], (t_vector2D){1005 - OFFSET_X, 443 - OFFSET_Y});
	ft_put_image_to_image(*_img(), _menu()->buttons[_menu()
		->o_state[2].state][R_ARR], _menu()->o_state[2].hitbox[0]);
	menu_bot_options();
}
