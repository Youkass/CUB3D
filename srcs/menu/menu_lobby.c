/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_lobby.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 14:56:16 by denissereno       #+#    #+#             */
/*   Updated: 2022/11/02 15:32:53 by yobougre         ###   ########.fr       */
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

static int	ft_is_start(void)
{
	int	i;

	i = 0;
	printf("linked player : %d\n", _var()->linked_players);
	while (i < _var()->linked_players)
	{
		printf("je passe bien dans cette boucle\n");
		if (_var()->o_player[i].is_start)
			printf("ce player veut start : %d\n", _var()->o_player[i].id);
		if (!_var()->o_player[i].is_start)
			return (printf("pourquoi ?\n"), 1);
		++i;
	}
	printf("i launch de the game\n");
	_var()->mode = GAME;
	_var()->started = 1;
	return (0);
}

static void	ft_cpy_tab(t_obj *o_player)
{
	int	i;

	i = 0;
	while (i < _var()->linked_players)
	{
		_var()->o_player[i] = o_player[i];
		++i;
	}
}

void	get_pseudos(void)
{
	int		i;
	t_obj	player;
	t_obj	o_player[MAX_PLAYER];
	
	memset(&player, 0, sizeof(player));
	ft_copy_data_before_pong(&player);
	if (send(_var()->socket, &player, sizeof(player), 0) < 0)
		exit (1); //TODO
	if (recv(_var()->socket, &(_var()->linked_players), sizeof(int), 0) < 0)
		exit (1);//TODO
	memset(&o_player, 0, sizeof(o_player));
	if (recv(_var()->socket, &o_player, sizeof(o_player), 0) < 0)
		exit (1); //TODO
	memset(&_var()->o_player, 0, sizeof(_var()->o_player));
	ft_cpy_tab(o_player);
	if (!ft_is_start())
	{
		printf("je sors de get_pseudos\n");
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
