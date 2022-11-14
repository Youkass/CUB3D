/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 12:10:09 by yobougre          #+#    #+#             */
/*   Updated: 2022/11/13 21:20:12 by denissereno      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	ft_init_music(void)
{
	_media()->result = ma_sound_init_from_file(&(_media()->engine),
		"sound/menu_music.wav", 0, NULL, NULL, &(_media()->sound[MENU_MUSIC][0]));
	if (_media()->result != MA_SUCCESS)
		ft_black_hole(1); //TODO
	_media()->result = ma_sound_init_from_file(&(_media()->engine),
		"sound/game_music.wav", 0, NULL, NULL, &(_media()->sound[GAME_MUSIC][0]));
	if (_media()->result != MA_SUCCESS)
		ft_black_hole(1); //TODO
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
			ft_black_hole(1); //TODO
		++i;
	}
}

void	ft_init_media(void)
{
	_media()->result = ma_engine_init(NULL, &(_media()->engine));
	if (_media()->result != MA_SUCCESS)
		ft_black_hole(1); //TODO
	ft_init_music();
	ft_init_sound();
}

void	ft_play_music(long unsigned int time, int index)
{
	(void)index;
	(void)time;
	if (_var()->mode == MENU)
	{
		ma_sound_start(&(_media()->sound[MENU_MUSIC][0]));
	}
	if (_var()->mode == GAME)
	{
		ma_sound_stop(&(_media()->sound[MENU_MUSIC][0]));
		ma_sound_start(&(_media()->sound[GAME_MUSIC][0]));
	}
}

void	ft_play_sound(int i)
{
	if (ma_sound_is_playing(&(_media()->shot_sound[i])))
		ma_sound_start(&(_media()->shot_sound[i % MAX_SHOT_SOUND]));
	else
		ma_sound_start(&(_media()->shot_sound[i]));
}
