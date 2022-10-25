/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_lobby.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 14:56:16 by denissereno       #+#    #+#             */
/*   Updated: 2022/10/25 20:24:34 by dasereno         ###   ########.fr       */
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
		printf("ici\n");
		_var()->mode = GAME_START_ONLINE;
		sync = -1;
	}
	if (send(_img()->socket, &sync, sizeof(sync), 0) < 0)
		return ;
	if (sync == -1)
		return ;
	printf("===>la %d, %d\n", sync, _var()->started);
	if (recv(_img()->socket, &sync, sizeof(sync), 0) < 0)
		return ;
	if (sync == -1)
	{
		printf("ouila\n");
		_var()->mode = GAME_START_ONLINE;
		return ;
	}
	_var()->linked_players = sync;
	while (i < _var()->linked_players)
	{
		if (recv(_img()->socket, &player, sizeof(player), 0) < 0)
			exit(1); //TODO
		_var()->o_player[player.id] = player;
		if (!(_var()->pseudo_img[player.id].img))
			_var()->pseudo_img[player.id] = create_text_img(player.pseudo);
		i++;
	}
}

void	menu_pong(void)
{
	get_pseudos();
}
