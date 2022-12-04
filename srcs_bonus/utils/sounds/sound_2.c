/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 18:15:56 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/04 20:14:39 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes_bonus/cub.h"

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
	if (ma_sound_is_playing(&(media->sound[GAME_MUSIC][ASHES])))
		ma_sound_stop(&(media->sound[GAME_MUSIC][ASHES]));
	if (ma_sound_is_playing(&(media->sound[GAME_MUSIC][MORTAL])))
		ma_sound_stop(&(media->sound[GAME_MUSIC][MORTAL]));
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
