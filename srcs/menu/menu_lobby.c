/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_lobby.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 14:56:16 by denissereno       #+#    #+#             */
/*   Updated: 2022/10/22 17:05:23 by denissereno      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	get_pseudos(void)
{
	int		i;
	int		j;
	char	c;
	int		id;

	i = 0;
	send(_img()->socket, _player(), sizeof(*_player()), 0);
	recv(_img()->socket, &_var()->linked_players, sizeof(id), 0);
	send(_img()->socket, &i, sizeof(i), 0);
	while (i < _var()->linked_players)
	{
		recv(_img()->socket, &id, sizeof(id), 0);
		send(_img()->socket, &j, sizeof(j), 0);
		c = 1;
		j = 0;
		while (c)
		{
			recv(_img()->socket, &c, sizeof(c), 0);
			if (id < MAX_PLAYER)
				_var()->o_player[id].pseudo[j++] = c; 
		}
		send(_img()->socket, &i, sizeof(i), 0);
		i++;
	}
}

void	menu_pong(void)
{
	int	okay;
	
	okay = 0;
	recv(_img()->socket, &okay, sizeof(int), 0);
	if (okay == -1)
	{
		if (_player()->id == 0)
			exit(0);
		send(_img()->socket, &_player()->id, sizeof(int), 0);
		recv(_img()->socket, &okay, sizeof(int), 0);
		send(_img()->socket, &_player()->id, sizeof(int), 0);
		_var()->mode = GAME;
		return ;
	}
	else
		_var()->linked_players = okay;
	send(_img()->socket, &_player()->id, sizeof(int), 0);
	recv(_img()->socket, &okay, sizeof(int), 0);
	get_pseudos();
}