/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   click.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 00:53:24 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/04 20:14:39 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub.h"

void	click(void)
{
	_var()->start_click = get_clock(_var()->clock);
	_var()->click = 1;
}

int	click_update(void)
{
	if (_var()->click && get_time(_var()->start_click) > 170000)
		_var()->click = 0;
	return (0);
}

int	click_delay(void)
{
	if (_var()->click == 1)
		return (1);
	return (0);
}

int	is_neutral(void)
{
	int	i;
	int	nb[2];

	i = 0;
	nb[0] = 0;
	nb[1] = 0;
	while (i < _var()->linked_players)
	{
		if (_var()->o_player[i].team == TEAM_VOID)
			return (0);
		else if (_var()->o_player[i].team == TEAM_BLUE)
			nb[0]++;
		else
			nb[1]++;
		i++;
	}
	if (!(_var()->linked_players % 2) && nb[0] == nb[1])
		return (1);
	return (0);
}
