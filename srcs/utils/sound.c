/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 12:10:09 by yobougre          #+#    #+#             */
/*   Updated: 2022/11/13 18:43:53 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	ft_init_music(void)
{
	_media()->result = ma_sound_init_from_file(&(_media()->engine),
		"sound/menu_music.wav", 0, NULL, NULL, &(_media()->sound[MENU_MUSIC][0]));
	if (_media()->result != MA_SUCCESS)
		ft_black_hole (1); //TODO
	_media()->result = ma_sound_init_from_file(&(_media()->engine),
		"sound/best_symphony_cut.wav", 0, NULL, NULL, &(_media()->sound[GAME_MUSIC][0]));
	if (_media()->result != MA_SUCCESS)
		ft_black_hole (1); //TODO
}

void	ft_init_sound(void)
{
	int	i;

	i = 0;
	while (i < MAX_SHOT_SOUND)
	{
		_media()->result = ma_sound_init_from_file(&(_media()->engine),
				"sound/shot.wav", 0, NULL, NULL,
					&(_media()->shot_sound[i]));
		if (_media()->result != MA_SUCCESS)
			ft_black_hole (1); //TODO
		++i;
	}
}

void	ft_init_media(void)
{
	_media()->result = ma_engine_init(NULL, &(_media()->engine));
	if (_media()->result != MA_SUCCESS)
		ft_black_hole (1); //TODO
	ft_init_music();
	ft_init_sound();
}

void	ft_play_music(long unsigned int time, int index)
{
	(void)index;
	(void)time;
	if (_var()->mode == MENU)
	{
		if (!ma_sound_is_playing(&(_media()->sound[MENU_MUSIC][0])))
		{
			printf("je lance menu music\n");
			ma_sound_start(&(_media()->sound[MENU_MUSIC][0]));
		}
	}
	if (_var()->mode == GAME)
	{
		if (ma_sound_is_playing(&(_media()->sound[MENU_MUSIC][0])))
			ma_sound_stop(&(_media()->sound[MENU_MUSIC][0]));
		if (!ma_sound_is_playing(&(_media()->sound[GAME_MUSIC][0])))
			ma_sound_start(&(_media()->sound[GAME_MUSIC][0]));
	}
}

void	ft_play_shot_sound(t_obj player)
{
	int		i;
	float	volume;
	float	dist;

	i = 0;
	dist = one_dist2F(posf(player.x, player.y), posf(_player()->x, _player()->y));
	volume = normalise_between2F(posf(0, 25), posf(0, 1), dist);
	if (dist >= 25)
		volume = 0.1;
	while (i < MAX_SHOT_SOUND)
	{
		if (!ma_sound_is_playing(&(_media()->shot_sound[i])))
		{
			if (player.id != _player()->id)
				ma_sound_set_volume(&(_media()->shot_sound[i]), volume);
			ma_sound_start(&(_media()->shot_sound[i]));
			return ;
		}
		++i;
	}
}

void	ft_play_own_shot(void)
{
	int		i;

	i = 0;
	while (i < MAX_SHOT_SOUND)
	{
		if (!ma_sound_is_playing(&(_media()->shot_sound[i])))
		{
			ma_sound_start(&(_media()->shot_sound[i]));
			return ;
		}
		++i;
	}
}
