/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_lobby.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 14:56:16 by denissereno       #+#    #+#             */
/*   Updated: 2022/11/03 15:23:04 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

/* ************************************************************************** */
/* besoin de faire une refonte totale de wait_lobby:
	# constement envoyer ses propres data et le tableau de player ensuite, verifier
		du cote server que toute les datas sont bien recu et ensuite bien envoye
	# ne plus envoyer linked_player seul, le faire dans une structure contenant
		1-tableau des joueurs et leurs data
		2-linked_player
		3-n'importe quel data utile */
/* ************************************************************************** */

static void	ft_cpy_tab(t_send_server o_player)
{
	int	i;

	i = 0;
	_var()->linked_players = o_player.linked_pl;
	printf("linked : %d\n", _var()->linked_players);
	while (i < _var()->nb_player)
	{
		_var()->o_player[i] = o_player.player[i];
		++i;
	}
}

void	get_pseudos(void)
{
	int		i;
	t_send_client	player;
	t_send_server	o_player;
	
	memset(&player, 0, sizeof(player));
	ft_copy_data_before_pong(&player.player);
	if (_player()->is_start)
		player.start = 1;
	else
		player.start = 0;
	if (send(_var()->socket, &player, sizeof(player), 0) < 0)
		exit (1); //TODO
	printf("j'ai send mes data\n");
	memset(&o_player, 0, sizeof(o_player));
	if (recv(_var()->socket, &o_player, sizeof(t_send_server), 0) < 0)
		exit (1); //TODO
	printf("j'ai recu les data\n");
	memset(&_var()->o_player, 0, sizeof(_var()->o_player));
	ft_cpy_tab(o_player);
	if (o_player.start)
	{
		printf("start : %d\n", o_player.start);
		_var()->mode = GAME;
		_var()->started = 1;
		return ;
	}
	i = 0;
	while (i < _var()->linked_players && !_var()->started)
	{
		if (!(_image()->pseudo_img[i].img))
		{
			printf("pseudo : %s\n", _var()->o_player[i].pseudo);
			_image()->pseudo_img[i] = create_text_img(_var()->o_player[i].pseudo);
		}
		i++;
	}
}

void	menu_pong(void)
{
	get_pseudos();
}
