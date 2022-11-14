/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobougre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 12:10:09 by yobougre          #+#    #+#             */
/*   Updated: 2022/11/14 15:29:06 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	ft_init_menu_music(void)
{
	_media()->result = ma_sound_init_from_file(&(_media()->engine),
		"sound/menu_music.wav", 0, NULL, NULL,
			&(_media()->sound[MENU_MUSIC][0]));
	if (_media()->result != MA_SUCCESS)
		ft_black_hole (1); //TODO
}

void	ft_init_game_music(void)
{
	_media()->result = ma_sound_init_from_file(&(_media()->engine),
		"sound/best_symphony_cut.wav", 0, NULL, NULL,
			&(_media()->sound[GAME_MUSIC][SYMPH]));
	if (_media()->result != MA_SUCCESS)
		ft_black_hole (1); //TODO
	_media()->result = ma_sound_init_from_file(&(_media()->engine),
		"sound/Mortal_cut.wav", 0, NULL, NULL,
			&(_media()->sound[GAME_MUSIC][MORTAL]));
	if (_media()->result != MA_SUCCESS)
		ft_black_hole (1); //TODO
	printf("ici\n");
	_media()->result = ma_sound_init_from_file(&(_media()->engine),
		"sound/Ashes_cut.wav", 0, NULL, NULL,
			&(_media()->sound[GAME_MUSIC][ASHES]));
	if (_media()->result != MA_SUCCESS)
		ft_black_hole (1); //TODO
	_media()->result = ma_sound_init_from_file(&(_media()->engine),
		"sound/doom_cut.wav", 0, NULL, NULL,
			&(_media()->sound[GAME_MUSIC][DOOM]));
	if (_media()->result != MA_SUCCESS)
		ft_black_hole (1); //TODO
}

void	ft_init_round_music(void)
{
	_media()->result = ma_sound_init_from_file(&(_media()->engine),
		"sound/round_win.wav", 0, NULL, NULL,
			&(_media()->sound[ROUND_MUSIC][ROUND_WIN]));
	if (_media()->result != MA_SUCCESS)
		ft_black_hole (1); //TODO
	_media()->result = ma_sound_init_from_file(&(_media()->engine),
		"sound/round_loose.wav", 0, NULL, NULL,
			&(_media()->sound[ROUND_MUSIC][ROUND_LOST]));
	if (_media()->result != MA_SUCCESS)
		ft_black_hole (1); //TODO
	_media()->result = ma_sound_init_from_file(&(_media()->engine),
		"sound/loose_game.wav", 0, NULL, NULL,
			&(_media()->sound[ROUND_MUSIC][GAME_LOST]));
	if (_media()->result != MA_SUCCESS)
		ft_black_hole (1); //TODO
	_media()->result = ma_sound_init_from_file(&(_media()->engine),
		"sound/sigma_victory.wav", 0, NULL, NULL,
			&(_media()->sound[ROUND_MUSIC][GAME_WIN]));
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
	ft_init_ran();
	_media()->result = ma_engine_init(NULL, &(_media()->engine));
	if (_media()->result != MA_SUCCESS)
		ft_black_hole (1); //TODO
	ft_init_game_music();
	ft_init_round_music();
	ft_init_menu_music();
	ft_init_sound();
}

int	ft_check_game_music(void)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (ma_sound_is_playing(&(_media()->sound[GAME_MUSIC][i])))
			return (i);
		++i;
	}
	return (-1);
}

void	ft_init_ran(void)
{
	srand(time(NULL));
	_var()->ran_i = rand() % 2;
}

void	ft_start_from_start(ma_sound *sound)
{
	if (!ma_sound_is_playing(sound))
	{
		ma_sound_set_start_time_in_pcm_frames(sound, 0);
		ma_sound_start(sound);
	}
}

void	ft_play_end_sound(ma_sound *sound)
{
	int	i;

	i = ft_check_game_music();
	if (i > -1)
		ma_sound_stop(&(_media()->sound[GAME_MUSIC][i]));
	ft_start_from_start(sound);
}

void	ft_play_end_round(void)
{
	if (_var()->round_state == ROUND_END)
	{
		if (_var()->last_round_winner == _player()->team_id)
			ft_play_end_sound(&(_media()->sound[ROUND_MUSIC][ROUND_WIN]));
		else
			ft_play_end_sound(&(_media()->sound[ROUND_MUSIC][ROUND_LOST]));
	}
}

void	ft_play_end_game(void)
{
	if (_var()->match_finished > 0)
	{
		if (_team()[_player()->team]->win == NB_ROUNDS)
			ft_play_end_sound(&(_media()->sound[ROUND_MUSIC][GAME_WIN]));
		else
			ft_play_end_sound(&(_media()->sound[ROUND_MUSIC][GAME_LOST]));
	}
}

void	ft_play_music(int index)
{
	if (_var()->mode == MENU)
	{
		index = ft_check_game_music();
		if (index > 0)
			ma_sound_stop(&(_media()->sound[GAME_MUSIC][index]));
		ft_start_from_start((&(_media()->sound[MENU_MUSIC][0])));
	}
	if (_var()->mode == GAME)
	{
		if (ma_sound_is_playing(&(_media()->sound[MENU_MUSIC][0])))
			ma_sound_stop(&(_media()->sound[MENU_MUSIC][0]));
		ft_start_from_start(&(_media()->sound[GAME_MUSIC][_var()->ran_i]));
		ft_play_end_round();
		ft_play_end_game();
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
