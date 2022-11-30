/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 12:10:09 by yobougre          #+#    #+#             */
/*   Updated: 2022/11/30 12:22:52 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	ft_add_sound(int index_1, int index_2, char *path)
{
	if (IS_MUSIC != 1)
		return ;
	t_media	*media;
	t_list	*tmp;

	media = _media();
	tmp = _lstmedia();
	media->result = ma_sound_init_from_file(&media->engine,
			path, 0, NULL, NULL, &media->sound[index_1][index_2]);
	if (media->result != MA_SUCCESS)
		ft_black_hole(69);
	ft_lstadd_back(&tmp, ft_new_node(&media->sound[index_1][index_2]));
}

void	ft_init_game_music(void)
{
	if (IS_MUSIC != 1)
		return ;
	ft_add_sound(MENU_SOUND, BUTTON, "sound/button_sound.wav");
	ft_add_sound(GAME_SOUND, 0, "sound/knife_sound.wav");
	ft_add_sound(GAME_SOUND, 1, "sound/reload_sound.wav");
	ft_add_sound(MENU_MUSIC, 0, "sound/menu_music.wav");
	ft_add_sound(GAME_MUSIC, SYMPH, "sound/best_symphony_cut.wav");
	ft_add_sound(GAME_MUSIC, MORTAL, "sound/Mortal_cut.wav");
	ft_add_sound(GAME_MUSIC, ASHES, "sound/Ashes_cut.wav");
	ft_add_sound(GAME_MUSIC, DOOM, "sound/doom_cut.wav");
	ft_add_sound(ROUND_MUSIC, ROUND_WIN, "sound/round_win.wav");
	ft_add_sound(ROUND_MUSIC, ROUND_LOST, "sound/round_loose.wav");
	ft_add_sound(ROUND_MUSIC, GAME_LOST, "sound/loose_game.wav");
	ft_add_sound(ROUND_MUSIC, GAME_WIN, "sound/sigma_victory.wav");
}

void	ft_init_sound(void)
{
	if (IS_MUSIC != 1)
		return ;
	int		i;
	t_media	*media;
	t_list	*tmp;

	media = _media();
	tmp = _lstmedia();
	i = 0;
	while (i < MAX_SHOT_SOUND)
	{
		media->result = ma_sound_init_from_file(&(media->engine),
				"sound/shot.wav", 0, NULL, NULL,
				&(media->shot_sound[i]));
		if (media->result != MA_SUCCESS)
			ft_black_hole (1);
		ft_lstadd_back(&tmp, ft_new_node(&media->shot_sound[i]));
		++i;
	}
}

void	ft_init_media(void)
{
	t_media	*media;
	
	if (IS_MUSIC != 1)
		return ;
	media = _media();
	ft_init_ran();
	media->result = ma_engine_init(NULL, &(media->engine));
	if (media->result != MA_SUCCESS)
		ft_black_hole (1);
	ft_init_game_music();
	ft_init_sound();
}

int	ft_check_game_music(void)
{
	int		i;
	t_media	*media;

	if (IS_MUSIC != 1)
		return (0);
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
	if (IS_MUSIC != 1)
		return ;
	srand(time(NULL));
	_var()->ran_i = rand() % 2;
}

void	ft_start_from_start(ma_sound *sound)
{
	if (IS_MUSIC != 1)
		return ;
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

	if (IS_MUSIC != 1)
		return ;
	media = _media();
	i = ft_check_game_music();
	if (i > -1)
		ma_sound_stop(&(media->sound[GAME_MUSIC][i]));
	ft_start_from_start(sound);
}

int	ft_play_end_round(void)
{
	t_media	*media;

	if (IS_MUSIC != 1)
		return (0);
	media = _media();
	if (_var()->round_state == ROUND_END && _var()->match_finished < 0)
	{
		ma_sound_stop(&(media->sound[GAME_MUSIC][_var()->ran_i]));
		if (_var()->last_round_winner != ft_check_my_team())
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

	if (IS_MUSIC != 1)
		return (0);
	media = _media();
	if (_var()->match_finished > 0)
	{
		if (_var()->last_round_winner == ft_check_my_team())
			ft_play_end_sound(&(media->sound[ROUND_MUSIC][GAME_WIN]));
		else
			ft_play_end_sound(&(media->sound[ROUND_MUSIC][GAME_LOST]));
		return (1);
	}
	return (0);
}

void	ft_check_end_songs(void)
{
	t_media	*media;

	if (IS_MUSIC != 1)
		return ;
	media = _media();
	if (ma_sound_is_playing(&(media->sound[ROUND_MUSIC][GAME_WIN])))
		ma_sound_stop(&(media->sound[ROUND_MUSIC][GAME_WIN]));
	if (ma_sound_is_playing(&(media->sound[ROUND_MUSIC][GAME_LOST])))
		ma_sound_stop(&(media->sound[ROUND_MUSIC][GAME_LOST]));
	if (ma_sound_is_playing(&(media->sound[ROUND_MUSIC][ROUND_WIN])))
		ma_sound_stop(&(media->sound[ROUND_MUSIC][ROUND_WIN]));
	if (ma_sound_is_playing(&(media->sound[ROUND_MUSIC][ROUND_LOST])))
		ma_sound_stop(&(media->sound[ROUND_MUSIC][ROUND_LOST]));
}

int	ft_check_enemie_team(void)
{
	if (IS_MUSIC != 1)
		return (0);
	if (_player()->team == TEAM_RED)
		return (TBLUE);
	else
		return (TRED);
}

int	ft_check_my_team(void)
{
	if (IS_MUSIC != 1)
		return (0);
	if (_player()->team == TEAM_RED)
		return (TRED);
	else
		return (TBLUE);
}

static void	ft_if_game(void)
{
	t_media	*media;

	if (IS_MUSIC != 1)
		return ;
	media = _media();
	if (ma_sound_is_playing(&(media->sound[MENU_MUSIC][0])))
		ma_sound_stop(&(media->sound[MENU_MUSIC][0]));
	if (_var()->alive[ft_check_enemie_team()] == 1
		&& _var()->alive[ft_check_my_team()] == 1 && _var()->nb_player > 2)
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
	if ( _menu()->mode == MENU_LEADERBOARD)
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

void	ft_play_shot_sound(t_obj player)
{
	int		i;
	float	volume;
	float	dist;
	t_media	*media;

	if (IS_MUSIC != 1)
		return ;
	media = _media();
	i = 0;
	(void)volume;
	dist = one_dist2f(posf(player.x, player.y),
			posf(_player()->x, _player()->y));
	volume = normalise_between2f(posf(0, 25), posf(0, 1), dist);
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

	if (IS_MUSIC != 1)
		return ;
	media = _media();
	i = 0;
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
