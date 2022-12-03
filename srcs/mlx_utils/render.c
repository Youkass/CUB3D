/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:34:23 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/03 18:53:37 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	render_health(t_vector2D a)
{
	int		i;
	char	*str;

	str = ft_strjoin(ft_itoa(_player()->health), "HP");
	i = 0;
	draw_rectangle(a, pos(102, 22), WHITE);
	while (i < _player()->health)
	{
		draw_rectangle(pos(a.x + 1 + i, a.y + 1), pos(1, 20), RED);
		i++;
	}
	draw_text_scale(str, pos(a.x + ft_strlen(str) * (42 / 4), a.y + 5),
		pos(4, 4), colo(0, 0, 0));
}

void	ft_is_not_knife(void)
{
	draw_text_scale(
		ft_strjoin(ft_itoa(_player()->full_ammo[_player()->weapon_id]),
			"/"), pos(55, 220 + _image()->ammo.h - 10), pos(3, 3), WHITE);
	draw_text_scale(ft_itoa(_player()->ammo[_player()->weapon_id]),
		pos(55 + ft_strlen("45/") * 14,
			220 + _image()->ammo.h - 8), pos(3, 3), WHITE);
	ft_put_image_to_image_scale(*_img(),
		_image()->ammo, pos(125, 220 + _image()->ammo.h - 10), posf(4, 4));
}

void	draw_death(void)
{
	char					*str;

	str = ft_strjoin("Spectating ", _var()->o_player[_player()
			->spec_id].pseudo);
	if (_player()->spectate && _player()->spec_id >= 0 && _player()->spec_id
		<= _var()->linked_players)
		draw_text(str, pos(WIN_W / 2 - ft_strlen(str), WIN_H - 100), WHITE);
	else
		draw_text("You are dead..", pos(WIN_W / 2 - 168, 300), WHITE);
}

void	ft_loop_multi(void)
{
	char	*str;

	ft_pong_client();
	player_casting();
	name_casting();
	if (_player()->team == TEAM_RED)
		str = ft_strjoin(ft_itoa(_team()[TEAM_RED]->win),
				ft_strjoin(" - ", ft_itoa(_team()[TEAM_BLUE]->win)));
	else
		str = ft_strjoin(ft_itoa(_team()[TEAM_BLUE]->win),
				ft_strjoin(" - ", ft_itoa(_team()[TEAM_RED]->win)));
	draw_text_scale(str,
		pos(WIN_W / 2 - (ft_strlen(str) * (42)) / 2, 100),
		pos(1, 1), WHITE);
	render_kill_log();
}

void	ft_if_round_end_wait(void)
{
	if (_var()->last_round_winner == TRED)
		draw_text_scale("RED WIN THE ROUND",
			pos(WIN_W / 2 - (17 * (42)) / 2, 300), pos(1, 1), RED);
	else if (_var()->last_round_winner == TBLUE)
		draw_text_scale("BLUE WIN THE ROUND",
			pos(WIN_W / 2 - (18 * (42)) / 2, 300), pos(1, 1), BLUE);
	else
		draw_text_scale(ft_itoa(_var()->last_round_winner),
			pos(WIN_W / 2 - (1 * (42)) / 2, 300), pos(1, 1), BLUE);
}
