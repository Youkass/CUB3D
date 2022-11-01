/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_lobby.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 14:56:16 by denissereno       #+#    #+#             */
/*   Updated: 2022/10/31 16:37:02 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

int	ft_send_start(void)
{
	if (recv(_img()->socket, &(_var()->linked_players), sizeof(int), 0) < 0)
	{
		printf("recv de linked a foiré\n");
		return (1);
	}
	if (_img()->is_host == SERVER)
	{
		if (send(_img()->socket, &(_var()->started), sizeof(int), 0) < 0)
		{
			printf("send de started failed\n");
			return (1);
		}
	}
	else if (_img()->is_host == CLIENT)
	{
		if (recv(_img()->socket, &(_var()->started), sizeof(int), 0) < 0)
		{
			printf("send de started failed\n");
			return (1);
		}
	}
	return (0);
}

void	get_pseudos(void)
{
	static int	i = 0;
	static int sendo = 0;
	t_obj	player;

	if (!sendo)
	{
		memset(&player, 0, sizeof(player));
		ft_copy_data_before_pong(&player);
		if (send(_var()->socket, &player, sizeof(player), 0) < 0)
			exit (1); //TODO
		sendo = 1;
	}
	if (ft_send_start())
		exit (1); //TODO
	if (_var()->started)
		_var()->mode = GAME;
	while (i < _var()->linked_players && !_var()->started)
	{
		memset(&player, 0, sizeof(player));
		if (recv(_img()->socket, &player, sizeof(player), 0) < 0)
			exit(1); //TODO
		_var()->o_player[i] = (t_obj)player;
		if (!(_var()->pseudo_img[i].img))
			_var()->pseudo_img[i] = create_text_img(player.pseudo);
		i++;
	}
}

void	menu_pong(void)
{
	get_pseudos();
}
