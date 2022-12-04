/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 18:15:41 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/04 18:16:59 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

/*===========================================================================*/
/*THE FUNCTION ABOVE AND OVER NEED TO BE IN THE SAME FILE				  	 */
/*===========================================================================*/

void	draw_lobby(void)
{
	int			size_box;
	t_vector2D	size_box_minus;

	size_box = _menu()->wait.w / _var()->nb_player;
	size_box_minus = pos(size_box - 16, 16);
	draw_rectangle(pos(0, 0), pos(WIN_W / 3, WIN_H),
		(char [4]){0, 34, 250, 250});
	draw_rectangle(pos(WIN_W / 3, 0), pos(WIN_W / 3, WIN_H),
		(char [4]){100, 100, 100, 250});
	draw_rectangle(pos((WIN_W / 3) * 2, 0), pos(WIN_W / 3, WIN_H),
		(char [4]){255, 154, 0, 250});
	draw_rectangle(pos(0, 0), pos(WIN_W, WIN_H / 3),
		(char [4]){100, 100, 100, 250});
	draw_rectangle(pos(0, WIN_H / 3 - 8), pos(WIN_W, 16),
		(char [4]){71, 71, 71, 250});
	draw_rectangle(pos(WIN_W / 3 - 8, WIN_H / 3), pos(16, WIN_H),
		(char [4]){71, 71, 71, 250});
	draw_rectangle(pos((WIN_W / 3) * 2 - 8, WIN_H / 3), pos(16, WIN_H),
		(char [4]){71, 71, 71, 250});
	draw_rectangle(pos(0, WIN_H / 3), pos(16, (WIN_H / 3) * 2),
		(char [4]){71, 71, 71, 250});
	draw_rectangle(pos(WIN_W - 16, WIN_H / 3), pos(16, (WIN_H / 3) * 2),
		(char [4]){71, 71, 71, 250});
	ft_draw_lobby(size_box, size_box_minus);
}

void	draw_leaderboard(void)
{
	draw_rectangle(pos(0, 0), pos(WIN_W / 3, WIN_H),
		(char [4]){0, 34, 250, 250});
	draw_rectangle(pos(WIN_W / 3, 0), pos(WIN_W / 3, WIN_H),
		(char [4]){100, 100, 100, 250});
	draw_rectangle(pos((WIN_W / 3) * 2, 0), pos(WIN_W / 3, WIN_H),
		(char [4]){255, 154, 0, 250});
	draw_rectangle(pos(0, 0), pos(WIN_W, WIN_H / 3),
		(char [4]){100, 100, 100, 250});
	draw_rectangle(pos(0, WIN_H / 3 - 8), pos(WIN_W, 16),
		(char [4]){71, 71, 71, 250});
	draw_rectangle(pos(WIN_W / 3 - 8, WIN_H / 3), pos(16, WIN_H),
		(char [4]){71, 71, 71, 250});
	draw_rectangle(pos((WIN_W / 3) * 2 - 8, WIN_H / 3), pos(16, WIN_H),
		(char [4]){71, 71, 71, 250});
	draw_rectangle(pos(0, WIN_H / 3), pos(16, (WIN_H / 3) * 2),
		(char [4]){71, 71, 71, 250});
	draw_rectangle(pos(WIN_W - 16, WIN_H / 3), pos(16, (WIN_H / 3) * 2),
		(char [4]){71, 71, 71, 250});
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
		draw_text_scale(pseudo, pos(WIN_W / 2 - size / 2, WIN_H / 3
				+ 64 + i * 60), pos(2, 2), (char [4]){12, 12, 12, 100});
	if (team == TEAM_RED)
		draw_text_scale(pseudo, pos((WIN_W / 3) / 2 - size / 2, WIN_H / 3
				+ 64 + i * 60), pos(2, 2), (char [4]){12, 12, 12, 100});
	if (team == TEAM_BLUE)
		draw_text_scale(pseudo,
			pos(((WIN_W / 3) * 2) + (WIN_W / 3) / 2 - size / 2, WIN_H / 3
				+ 64 + i * 60), pos(2, 2), (char [4]){12, 12, 12, 100});
}

void	draw_pseudo_box_leader(char	*pseudo, int id, int i, int team)
{
	int			size;
	t_vector2D	posp;

	pseudo = ft_strjoin(pseudo,
			ft_strjoin(": ",
				ft_strjoin(ft_itoa(_var()->o_player[id].kills),
					ft_strjoin(" / ", ft_itoa(_var()->o_player[id].deaths)))));
	size = ft_strlen(pseudo) * 21;
	if (team == TEAM_RED)
		posp = pos((WIN_W / 3) / 2 - size / 2, WIN_H / 3 + 64 + i * 60);
	if (team == TEAM_BLUE)
		posp = pos(((WIN_W / 3) * 2) + (WIN_W / 3) / 2 - size / 2,
				WIN_H / 3 + 64 + i * 60);
	draw_text_scale(pseudo, posp, pos(2, 2), (char [4]){12, 12, 12, 100});
}
