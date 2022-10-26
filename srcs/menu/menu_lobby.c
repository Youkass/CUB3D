/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_lobby.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 14:56:16 by denissereno       #+#    #+#             */
/*   Updated: 2022/10/26 20:22:53 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	get_pseudos(void)
{
	static int	i = 0;
	static int sendo = 0;
	int 	sync;
	t_obj	player;

	sync = 0;
	if (!sendo)
	{
		memset(&player, 0, sizeof(player));
		ft_copy_data_before_pong(&player);
		send(_img()->socket, &player, sizeof(player), 0);
		sendo = 1;
	}
	if (_img()->is_host == SERVER && _var()->started == 1)
	{
		_var()->mode = GAME_START_ONLINE;
		sync = -1;
	}
	if (send(_img()->socket, &sync, sizeof(sync), 0) < 0)
		return ;
	if (sync == -1)
		return ;
	if (recv(_img()->socket, &sync, sizeof(sync), 0) < 0)
		return ;
	if (sync == -1)
	{
		_var()->mode = GAME_START_ONLINE;
		return ;
	}
	else
		_var()->linked_players = sync;
	while (i < _var()->linked_players && _var()->started < 1)
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
	get_pseudos();
}
