/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 18:16:30 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/04 22:27:07 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes_bonus/cub.h"

void	ft_init_media(void)
{
	t_media	*media;

	if (IS_MUSIC != 1)
		return ;
	printf("salut\n");
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
