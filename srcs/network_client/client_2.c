/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 18:54:09 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/03 21:13:56 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	restart_round(void)
{
	init_player_team();
}

void	render_kill_log(void)
{
	int		i;
	t_list	*tmp;
	t_elem	*log;

	tmp = _log()->log;
	i = 0;
	while (tmp && i < 5)
	{
		log = (t_elem *)tmp->content;
		if (_var()->o_player[log->ids[0]].team == TEAM_RED)
			draw_text_scale(
				ft_strjoin(_var()->o_player[log->ids[0]].pseudo, ft_strjoin(
						" killed ", _var()->o_player[log->ids[1]].pseudo)),
				pos(250, 10 + i * 20), pos(4, 4), (char [4]){0, 34, 250, 250});
		else
			draw_text_scale(
				ft_strjoin(_var()->o_player[log->ids[0]].pseudo, ft_strjoin(
						" killed ", _var()->o_player[log->ids[1]].pseudo)),
				pos(250, 10 + i * 20), pos(4, 4),
				(char [4]){255, 154, 0, 250});
		tmp = tmp->next;
		i++;
	}
}

void	update_health(int i, t_send_server_game serv)
{
	if (serv.player[i].is_shooting > 0 && i != _player()->id)
		ft_play_shot_sound(serv.player[i]);
	if (serv.player[i].shooted.shoot > 0 && serv.player[i].shooted.id
		== _player()->id)
	{
		if (serv.player[i].shooted.shoot == 1)
			_player()->health -= _weapon()[serv.player[i].weapon_id]->power;
		else if (serv.player[i].shooted.shoot == 2)
			_player()->health -= _weapon()[serv.player[i].weapon_id]->headshot;
		else if (serv.player[i].shooted.shoot == 3)
			_player()->health -= _weapon()[serv.player[i].weapon_id]->footshot;
		_player()->hitted = 1;
		_var()->start_hit = get_clock(_var()->clock);
	}
}

void	get_data(int i, t_send_server_game serv)
{
	int	j;

	j = 0;
	update_health(i, serv);
	if (serv.player[i].shooted.shoot > 0 && i == _player()->id)
	{
		_player()->shooted.shoot = 0;
		_player()->shooted.id = -1;
	}
	if (serv.player[i].team == TEAM_BLUE && !serv.player[i].is_dead)
		_var()->alive[TBLUE]++;
	if (serv.player[i].team == TEAM_RED && !serv.player[i].is_dead)
		_var()->alive[TRED]++;
	if (_var()->o_player[i].kills < serv.player[i].kills)
		ft_lstadd_back(&_log()->log, ft_lstnew((void *)new_log(serv.player
				[i].id, serv.player[i].kill_round[serv.player[i].nr - 1])));
	while (j < serv.player[i].shoot_n)
	{
		_var()->o_player[i].shott[j] = serv.player[i].shott[j];
		_var()->o_player[i].shott[j].pos = serv.player[i].shott[j].pos;
		++j;
	}
	_var()->o_player[i] = serv.player[i];
}

void	ft_round_handling(int *incremented, t_send_server_game serv)
{
	if (_var()->round_state == ROUND_WAIT_START)
	{
		replace_player();
		init_player_team();
	}
	if (_var()->round_state == ROUND_START)
	{
		*incremented = 0;
		_var()->freeze = 0;
	}
	if (_var()->match_finished)
	{
		_var()->mode = MENU;
		_menu()->mode = MENU_LEADERBOARD;
		_var()->freeze = 0;
		*incremented = 0;
	}
	if (serv.restart == 1)
	{
		restart_player();
		_var()->mode = MENU;
		_menu()->mode = MENU_LOBBY;
		_var()->freeze = 0;
	}
}
