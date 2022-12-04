/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 18:15:41 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/04 18:16:19 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

int	get_ratio(int kills, int deaths)
{
	if (deaths == 0)
		return (kills);
	else
		return (kills / deaths);
}

static void	ft_sort_team(t_vector2D id, int tmp)
{
	int	i;
	int	j;

	i = 0;
	while (i < _var()->n_blue)
	{
		j = 0;
		while (j < _var()->n_blue - 1 - i)
		{
			id.x = _var()->blue[j];
			id.y = _var()->blue[j + 1];
			if (get_ratio(_var()->o_player[id.x].kills,
					_var()->o_player[id.x].deaths)
				> get_ratio(_var()->o_player
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

void	sort_team(void)
{
	int			i;
	int			j;
	t_vector2D	id;
	int			tmp;

	i = -1;
	while (i++ < _var()->n_red - 1)
	{
		j = -1;
		while (j++ < _var()->n_red - 1 - i)
		{
			id.x = _var()->red[j];
			id.y = _var()->red[j + 1];
			if (get_ratio(_var()->o_player[id.x].kills,
					_var()->o_player[id.x].deaths)
				> get_ratio(_var()->o_player
					[id.y].kills, _var()->o_player[id.y].deaths))
			{
				tmp = _var()->red[j];
				_var()->red[j] = _var()->red[j + 1];
				_var()->red[j + 1] = tmp;
			}
		}
	}
	ft_sort_team(id, tmp);
}

static void	ft_draw_pseudo_team(int limite, int team_id, int *team)
{
	int	i;

	i = 0;
	while (i < limite)
	{
		draw_pseudo_box(_var()->o_player[team[i]].pseudo, i, team_id);
		i++;
	}
}

void	menu_lobby(void)
{
	update_key();
	draw_lobby();
	ft_put_image_to_image(*_img(), _menu()->wait,
		(t_vector2D){WIN_W / 4 - (_menu()->wait.w / 2),
		(WIN_H / 3) / 2 - (_menu()->wait.h / 2) - 16});
	ft_draw_pseudo_team(_var()->n_red, TEAM_RED, _var()->red);
	ft_draw_pseudo_team(_var()->n_blue, TEAM_BLUE, _var()->blue);
	ft_draw_pseudo_team(_var()->n_neutral, TEAM_VOID, _var()->neutral);
	if (_var()->is_host == SERVER)
		draw_text_scale(ft_strjoin("ip ", ft_get_host_ip()),
			(t_vector2D){200, 10}, pos(2, 2), (char [4]){238, 238, 238, 250});
	else
		draw_text(_var()->ip, (t_vector2D){200, 10},
			(char [4]){238, 238, 238, 250});
	if (_var()->is_host == SERVER && is_neutral())
	{
		draw_text_scale("press (Space) to start", pos(WIN_W / 2 - 462,
				WIN_H - 150), pos(2, 2), (char [4]){238, 238, 238, 250});
	}
}
