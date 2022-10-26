/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_lobby.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 14:56:16 by denissereno       #+#    #+#             */
/*   Updated: 2022/10/26 17:53:11 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	get_pseudos(void)
{
	static int		i = 0;
	t_obj			player;

	memset(&player, 0, sizeof(player));
	ft_copy_data_before_pong(&player);
	send(_img()->socket, &player, sizeof(player), 0);
	recv(_img()->socket, &_var()->linked_players, sizeof(int), 0);
	while (i < _var()->linked_players)
	{
		if (recv(_img()->socket, &player, sizeof(player), 0) < 0)
			exit(1); //TODO
		_var()->o_player[i] = player;
		if (!(_var()->pseudo_img[i].img))
			_var()->pseudo_img[i] = create_text_img(player.pseudo);
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
