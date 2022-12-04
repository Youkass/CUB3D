/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 18:16:58 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/04 22:25:14 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes_bonus/cub.h"

void	ft_add_sound(int index_1, int index_2, char *path)
{
	t_media	*media;
	t_list	*tmp;

	if (IS_MUSIC != 1)
		return ;
	media = _media();
	tmp = _lstmedia();
	media->result = ma_sound_init_from_file(&media->engine,
			path, 0, NULL, NULL, &media->sound[index_1][index_2]);
	if (media->result != MA_SUCCESS)
		ft_black_hole(69);
	ma_sound_set_volume(&media->sound[index_1][index_2], 0.5);
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
	int		i;
	t_media	*media;
	t_list	*tmp;

	if (IS_MUSIC != 1)
		return ;
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
		media->result = ma_sound_init_from_file(&(media->engine),
				"sound/knife_sound.wav", 0, NULL, NULL,
				&(media->knife_sound[i]));
		if (media->result != MA_SUCCESS)
			ft_black_hole (1);
		ft_lstadd_back(&tmp, ft_new_node(&media->shot_sound[i]));
		ft_lstadd_back(&tmp, ft_new_node(&media->knife_sound[i]));
		++i;
	}
}

void	ft_play_knife(void)
{
	int	i;

	i = 0;
	if (IS_MUSIC != 1)
		return ;
	while (i < MAX_SHOT_SOUND)
	{
		if (!ma_sound_is_playing(&(_media()->knife_sound[i])))
			ft_start_from_start(&(_media()->knife_sound[i]));
		++i;
	}
}
