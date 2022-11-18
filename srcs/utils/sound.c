/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 12:10:09 by yobougre          #+#    #+#             */
/*   Updated: 2022/11/18 18:22:11 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	ft_init_menu_music(void)
{
	t_media	*media;

	media = _media();
	media->result = ma_sound_init_from_file(&(media->engine),
			"sound/menu_music.wav", 0, NULL, NULL,
			&(media->sound[MENU_MUSIC][0]));
	if (_media()->result != MA_SUCCESS)
		ft_black_hole (1);
}

void	ft_init_game_music(void)
{
	t_media	*media;

	media = _media();
	media->result = ma_sound_init_from_file(&(media->engine),
			"sound/best_symphony_cut.wav", 0, NULL, NULL,
			&(media->sound[GAME_MUSIC][SYMPH]));
	if (media->result != MA_SUCCESS)
		ft_black_hole (1);
	media->result = ma_sound_init_from_file(&(media->engine),
			"sound/Mortal_cut.wav", 0, NULL, NULL,
			&(media->sound[GAME_MUSIC][MORTAL]));
	if (media->result != MA_SUCCESS)
		ft_black_hole (1);
	printf("ici\n");
	media->result = ma_sound_init_from_file(&(media->engine),
			"sound/Ashes_cut.wav", 0, NULL, NULL,
			&(_media()->sound[GAME_MUSIC][ASHES]));
	if (media->result != MA_SUCCESS)
		ft_black_hole (1);
	media->result = ma_sound_init_from_file(&(media->engine),
			"sound/doom_cut.wav", 0, NULL, NULL,
			&(_media()->sound[GAME_MUSIC][DOOM]));
	if (media->result != MA_SUCCESS)
		ft_black_hole (1);
}

void	ft_init_round_music(void)
{
	t_media	*media;

	media = _media();
	media->result = ma_sound_init_from_file(&(media->engine),
			"sound/round_win.wav", 0, NULL, NULL,
			&(media->sound[ROUND_MUSIC][ROUND_WIN]));
	if (media->result != MA_SUCCESS)
		ft_black_hole (1);
	media->result = ma_sound_init_from_file(&(media->engine),
			"sound/round_loose.wav", 0, NULL, NULL,
			&(media->sound[ROUND_MUSIC][ROUND_LOST]));
	if (media->result != MA_SUCCESS)
		ft_black_hole (1);
	media->result = ma_sound_init_from_file(&(media->engine),
			"sound/loose_game.wav", 0, NULL, NULL,
			&(_media()->sound[ROUND_MUSIC][GAME_LOST]));
	if (media->result != MA_SUCCESS)
		ft_black_hole (1);
	media->result = ma_sound_init_from_file(&(media->engine),
			"sound/sigma_victory.wav", 0, NULL, NULL,
			&(media->sound[ROUND_MUSIC][GAME_WIN]));
	if (media->result != MA_SUCCESS)
		ft_black_hole (1);
}

void	ft_init_sound(void)
{
	int		i;
	t_media	*media;

	media = _media();
	i = 0;
	while (i < MAX_SHOT_SOUND)
	{
		media->result = ma_sound_init_from_file(&(media->engine),
				"sound/shot.wav", 0, NULL, NULL,
				&(media->shot_sound[i]));
		if (media->result != MA_SUCCESS)
			ft_black_hole (1);
		++i;
	}
}

void	ft_init_media(void)
{
	t_media	*media;

	media = _media();
	ft_init_ran();
	media->result = ma_engine_init(NULL, &(media->engine));
	if (media->result != MA_SUCCESS)
		ft_black_hole (1);
	ft_init_game_music();
	ft_init_round_music();
	ft_init_menu_music();
	ft_init_sound();
}

int	ft_check_game_music(void)
{
	int		i;
	t_media	*media;

	media = _media();
	i = 0;
	while (i < 4)
	{
		if (ma_sound_is_playing(&(media->sound[GAME_MUSIC][i])))
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
	int		i;
	t_media	*media;

	media = _media();
	i = ft_check_game_music();
	if (i > -1)
		ma_sound_stop(&(media->sound[GAME_MUSIC][i]));
	ft_start_from_start(sound);
}

int	ft_play_end_round(void)
{
	t_media	*media;

	media = _media();
	if (_var()->round_state == ROUND_END && _var()->match_finished < 0)
	{
		if (_var()->last_round_winner == _player()->team_id)
			ft_play_end_sound(&(media->sound[ROUND_MUSIC][ROUND_WIN]));
		else
			ft_play_end_sound(&(media->sound[ROUND_MUSIC][ROUND_LOST]));
		return (1);
	}
	return (0);
}

int	ft_play_end_game(void)
{
	t_media	*media;

	media = _media();
	if (_var()->match_finished > 0)
	{
		if (_team()[_player()->team]->win == NB_ROUNDS)
			ft_play_end_sound(&(media->sound[ROUND_MUSIC][GAME_WIN]));
		else
			ft_play_end_sound(&(media->sound[ROUND_MUSIC][GAME_LOST]));
		ft_init_ran();
		return (1);
	}
	return (0);
}

int	ft_check_my_team(void)
{
	if (_player()->team == TRED)
		return (TBLUE);
	else
		return (TRED);
}

static void	ft_if_game(void)
{
	t_media	*media;

	media = _media();
	if (ma_sound_is_playing(&(media->sound[MENU_MUSIC][0])))
		ma_sound_stop(&(media->sound[MENU_MUSIC][0]));
	if (_var()->alive[_player()->team] == 1
		&& _var()->alive[ft_check_my_team()] > 1)
	{
		ma_sound_stop(&(media->sound[GAME_MUSIC][_var()->ran_i]));
		ft_start_from_start(&(media->sound[GAME_MUSIC][ASHES]));
	}
	else if (_var()->alive[_player()->team] == 1
		&& _var()->alive[ft_check_my_team()] == 1)
	{
		ma_sound_stop(&(media->sound[GAME_MUSIC][_var()->ran_i]));
		ft_start_from_start(&(media->sound[GAME_MUSIC][MORTAL]));
	}
	ft_start_from_start(&(media->sound[GAME_MUSIC][_var()->ran_i]));
}

void	ft_play_music(int index)
{
	t_media	*media;

	media = _media();
	if (_menu()->mode == MENU_START || _menu()->mode == INTRO)
	{
		ft_play_end_round();
		ft_play_end_game();
		if (!ft_play_end_round() && !ft_play_end_game())
		{
			index = ft_check_game_music();
			if (index > 0)
				ma_sound_stop(&(media->sound[GAME_MUSIC][index]));
			ft_start_from_start((&(media->sound[MENU_MUSIC][0])));
		}
	}
	if (_var()->mode == GAME)
		ft_if_game();
}

void	ft_play_shot_sound(t_obj player)
{
	int		i;
	float	volume;
	float	dist;
	t_media	*media;

	media = _media();
	i = 0;
	(void)volume;
	dist = one_dist2F(posf(player.x, player.y),
			posf(_player()->x, _player()->y));
	volume = normalise_between2F(posf(0, 25), posf(0, 1), dist);
	if (dist >= 25)
		volume = 0.1;
	while (i < MAX_SHOT_SOUND)
	{
		if (!ma_sound_is_playing(&(media->shot_sound[i])))
		{
			if (player.id != _player()->id)
				ma_sound_set_volume(&(media->shot_sound[i]), 0.2);
			ma_sound_start(&(media->shot_sound[i]));
			return ;
		}
		++i;
	}
}

void	ft_play_own_shot(void)
{
	int		i;
	t_media	*media;

	media = _media();
	i = 0;
	while (i < MAX_SHOT_SOUND)
	{
		if (!ma_sound_is_playing(&(media->shot_sound[i])))
		{
			ma_sound_set_volume(&(media->shot_sound[i]), 0.2);
			ma_sound_start(&(media->shot_sound[i]));
			return ;
		}
		++i;
	}
}
