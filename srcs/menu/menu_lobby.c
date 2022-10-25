/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_lobby.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 14:56:16 by denissereno       #+#    #+#             */
/*   Updated: 2022/10/24 16:03:49 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	get_pseudos(void)
{
	int		i;
	int		j;
	char	c;
	int		id;
	t_obj	player;

	i = 0;
	memset(&player, 0, sizeof(player));
	ft_copy_data_before_pong(&player);
	send(_img()->socket, &player, sizeof(player), 0);
	recv(_img()->socket, &_var()->linked_players, sizeof(id), 0);
	send(_img()->socket, &i, sizeof(i), 0);
	while (i < _var()->linked_players)
	{
		j = 0;
		recv(_img()->socket, &id, sizeof(id), 0);
		send(_img()->socket, &j, sizeof(j), 0);
		c = 1;
		while (c)
		{
			recv(_img()->socket, &c, sizeof(c), 0);
			if (id < MAX_PLAYER)
				_var()->o_player[id].pseudo[j++] = c; 
		}
		if (_var()->pseudo_img[id].img == NULL)
			_var()->pseudo_img[id] = create_text_img(_var()->o_player[id].pseudo);
		send(_img()->socket, &i, sizeof(i), 0);
		i++;
	}
}

void	menu_pong(void)
{
	int	okay;
	t_obj	player;

	memset(&player, 0, sizeof(player));
	ft_copy_data_before_pong(&player);
	okay = 0;
	recv(_img()->socket, &okay, sizeof(okay), 0);
	if (okay == -1)
	{
		if (_player()->id == 0)
			exit(0);
		send(_img()->socket, &player.id, sizeof(player.id), 0);
		recv(_img()->socket, &okay, sizeof(int), 0);
		send(_img()->socket, &player.id, sizeof(player.id), 0);
		_var()->mode = GAME;
		return ;
	}
	else
		_var()->linked_players = okay;
	send(_img()->socket, &player.id, sizeof(player.id), 0);
	recv(_img()->socket, &okay, sizeof(okay), 0);
	get_pseudos();
}