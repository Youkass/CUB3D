/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_lobby.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 14:56:16 by denissereno       #+#    #+#             */
/*   Updated: 2022/11/01 16:20:11 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

int	ft_send_start(void)
{
	if (_var()->is_host == SERVER)
	{
		if (send(_var()->socket, &(_var()->started), sizeof(int), 0) < 0)
		{
			printf("send de started failed\n");
			return (1);
		}
	}
	else if (_var()->is_host == CLIENT)
	{
		if (recv(_var()->socket, &(_var()->started), sizeof(int), 0) < 0)
		{
			printf("send de started failed\n");
			return (1);
		}
	}
	return (0);
}

int	ft_before_start(void)
{
	static int	i = 0;
	static int sendo = 0;
	t_obj	player;
	
	if (!sendo)
	{
		memset(&player, 0, sizeof(player));
		ft_copy_data_before_pong(&player);
		if (send(_var()->socket, &player, sizeof(player), 0) < 0)
			return (1); //TODO
		sendo = 1;
		printf("j'ai send mes data au serveur\n");
	}
	while (i < _var()->linked_players && !_var()->started)
	{
		printf("je passe dans la while i : %d\n", i);
		memset(&player, 0, sizeof(player));
		if (recv(_var()->socket, &player, sizeof(player), 0) < 0)
			return (1); //TODO
		_var()->o_player[i] = player;
		if (!(_image()->pseudo_img[i].img))
			_image()->pseudo_img[i] = create_text_img(player.pseudo);
		i++;
	}
	return (0);
}

void	get_pseudos(void)
{
	static int	flag = 0;

	if (recv(_var()->socket, &(_var()->linked_players), sizeof(int), 0) < 0)
		exit(1);//TODO
	printf("j'ai recv linked et il vaut : %d\n", _var()->linked_players);
	if (_var()->linked_players <= _var()->nb_player && !flag)
	{
		if (_var()->linked_players == _var()->nb_player)
			++flag;
		if (ft_before_start())
			exit(1); //TODO
	}
	else
	{
		if (ft_send_start())
			exit (1); //TODO
		if (_var()->started)
			_var()->mode = GAME;
	}
}

void	menu_pong(void)
{
	get_pseudos();
}
