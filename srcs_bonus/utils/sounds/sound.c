/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 12:10:09 by yobougre          #+#    #+#             */
/*   Updated: 2022/12/04 22:25:41 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes_bonus/cub.h"

static void	ft_if_game(void)
{
	t_media	*media;

	if (IS_MUSIC != 1)
		return ;
	media = _media();
	if (ma_sound_is_playing(&(media->sound[MENU_MUSIC][0])))
		ma_sound_stop(&(media->sound[MENU_MUSIC][0]));
	if (_var()->alive[ft_check_enemie_team()] == 1
		&& _var()->alive[ft_check_my_team()] == 1 && _var()->linked_players > 2)
	{
		ma_sound_stop(&(media->sound[GAME_MUSIC][ASHES]));
		ma_sound_stop(&(media->sound[GAME_MUSIC][_var()->ran_i]));
		ft_start_from_start(&(media->sound[GAME_MUSIC][MORTAL]));
	}
	else if (_var()->alive[ft_check_my_team()] == 1
		&& _var()->alive[ft_check_enemie_team()] > 1)
	{
		ma_sound_stop(&(media->sound[GAME_MUSIC][_var()->ran_i]));
		ft_start_from_start(&(media->sound[GAME_MUSIC][ASHES]));
	}
	else
	{
		ft_check_end_songs();
		ft_start_from_start(&(media->sound[GAME_MUSIC][_var()->ran_i]));
	}
}

void	ft_play_music(int index)
{
	t_media	*media;

	if (IS_MUSIC != 1)
		return ;
	media = _media();
	(void)index;
	if (_menu()->mode == MENU_LEADERBOARD)
	{
		ft_play_end_game();
		ft_init_ran();
	}
	if (_menu()->mode == MENU_START || _menu()->mode == INTRO
		|| _menu()->mode == MENU_LOBBY)
	{
		ft_check_end_songs();
		ma_sound_stop(&(media->sound[GAME_MUSIC][_var()->ran_i]));
		ft_start_from_start((&(media->sound[MENU_MUSIC][0])));
	}
	if (_var()->mode == GAME)
		ft_if_game();
}

void	play_shots_sound(t_obj player, t_media *media)
{
	int		dist;
	int		i;

	i = 0;
	if (IS_MUSIC != 1)
		return ;
	dist = one_dist2f(posf(player.x, player.y),
			posf(_player()->x, _player()->y));
	if (player.weapon_id == KNIFE)
	{
		if (dist < 3)
			ft_play_knife();
		return ;
	}
	while (i < MAX_SHOT_SOUND)
	{
		if (!ma_sound_is_playing(&(media->shot_sound[i])))
		{
			if (player.id != _player()->id)
				ma_sound_set_volume(&(media->shot_sound[i]), 0.3);
			ma_sound_start(&(media->shot_sound[i]));
			return ;
		}
		++i;
	}
}

void	ft_play_shot_sound(t_obj player)
{
	t_media	*media;

	if (IS_MUSIC != 1)
		return ;
	media = _media();
	play_shots_sound(player, media);
}

void	ft_play_own_shot(void)
{
	int		i;
	t_media	*media;

	if (IS_MUSIC != 1)
		return ;
	media = _media();
	i = 0;
	if (_player()->weapon_id == KNIFE)
	{
		ft_play_knife();
		return ;
	}
	while (i < MAX_SHOT_SOUND)
	{
		if (!ma_sound_is_playing(&(media->shot_sound[i])))
		{
			ma_sound_set_volume(&(media->shot_sound[i]), 0.4);
			ma_sound_start(&(media->shot_sound[i]));
			return ;
		}
		++i;
	}
}
