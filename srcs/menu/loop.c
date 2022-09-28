/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 12:05:00 by denissereno       #+#    #+#             */
/*   Updated: 2022/09/28 18:05:56 by denissereno      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"
#include <unistd.h>

# define OFFSET_Y 128
# define OFFSET_X 230

void	restart_button(void)
{
	int	i;
	
	i = 0;
	while (i < 4)
		_var()->menu->start_state[i++] = 0;
	i = 0;
	while (i < 7)
		_var()->menu->options_state[i++] = 0;
}

/*
-Check if position is in the hitbox given in parameter.
25,15		45,15
25,25		45,25

*/
int	ft_hitbox(t_vector2D hitbox[4], t_vector2D pos)
{
	if (pos.x >= hitbox[0].x && pos.x <= hitbox[1].x && 
	pos.y >= hitbox[0].y && pos.y <= hitbox[2].y)
		return (1);
	return (0);
}

/*
-Fonction pour ecrire une image dans une plus grande image aux coordonnées
précisé en paramètre.
Pour trouver les coordonnées dans une image a partir de coordonnée réel on
doit faire : x * 4 + y * line_lenght.
rel_pos = position relative des coordonnées réel dans la grande image.
exemple : 
coordonée reel du pixel : x = 4 y = 5;
coordonée relative du pixel dans l'image sera : x = 4 * 4 + y * line_length;

On parcours dans que la width n'est pas atteinte de la petite image et on ecrit
pixel par pixel dans la grande image. Une fois la width atteinte on incremente
le y tant qu'on a pas atteint la height. On itere.
*/
t_data	ft_put_image_to_image(t_data big, t_data lil, t_vector2D pos)
{
	t_vector2D	rel_pos;
	t_vector2D	rel_pos_start;
	t_vector2D	it;

	if (pos.x >= big.width || pos.y >= big.height || lil.height +
		pos.x > big.height || lil.width + pos.y > big.width)
		return (big);
	rel_pos = (t_vector2D){pos.x * 4, pos.y * big.line_length};
	rel_pos_start = rel_pos;
	it = (t_vector2D){0, 0};
	while (it.y < lil.height)
	{
		it.x = 0;
		while (it.x < lil.width)
		{
			if (lil.addr[it.x * 4 + it.y * lil.line_length + 3] != - 1)
			{
				big.addr[rel_pos.x + rel_pos.y] = lil.addr[it.x * 4 + it.y * lil.line_length];
				big.addr[rel_pos.x + rel_pos.y + 1] = lil.addr[it.x * 4 + it.y * lil.line_length + 1];
				big.addr[rel_pos.x + rel_pos.y + 2] = lil.addr[it.x * 4 + it.y * lil.line_length + 2];
				big.addr[rel_pos.x + rel_pos.y + 3] = lil.addr[it.x * 4 + it.y * lil.line_length + 3];
			}
			rel_pos.x += 4;
			pos.x++;
			it.x++;
		}
		pos.y++;
		rel_pos.y = pos.y * big.line_length;
		rel_pos.x = rel_pos_start.x;
		it.y++;
	}
	return (big);
}

/*
-Display option menu
*/
void	menu_option(void)
{
	printf("%d\n", _var()->menu->options_state[0]);
	ft_put_image_to_image(_var()->menu->img, _var()->menu->bg, (t_vector2D){0, 0});
	ft_put_image_to_image(_var()->menu->img, _var()->menu->logo, (t_vector2D){716 - OFFSET_X - 45, 155 - OFFSET_Y + 50});
	ft_put_image_to_image(_var()->menu->img, _var()->menu->buttons[_var()->menu->options_state[0]][MUTE_S], (t_vector2D){678 - OFFSET_X, 460 - OFFSET_Y});
	ft_put_image_to_image(_var()->menu->img, _var()->menu->buttons[_var()->menu->options_state[1]][L_ARR], (t_vector2D){774 - OFFSET_X, 460 - OFFSET_Y});

	ft_put_image_to_image(_var()->menu->img, _var()->menu->bar[EMPTY][BAR_LEFT], (t_vector2D){819 - OFFSET_X, 443 - OFFSET_Y});
	ft_put_image_to_image(_var()->menu->img, _var()->menu->bar[EMPTY][BAR_MID], (t_vector2D){912 - OFFSET_X, 443 - OFFSET_Y});
	ft_put_image_to_image(_var()->menu->img, _var()->menu->bar[EMPTY][BAR_RIGHT], (t_vector2D){1005 - OFFSET_X, 443 - OFFSET_Y});

	ft_put_image_to_image(_var()->menu->img, _var()->menu->buttons[_var()->menu->options_state[2]][R_ARR], (t_vector2D){1083 - OFFSET_X, 460 - OFFSET_Y});

	ft_put_image_to_image(_var()->menu->img, _var()->menu->buttons[_var()->menu->options_state[3]][MUTE_M],(t_vector2D){ 678 - OFFSET_X, 560 - OFFSET_Y});
	ft_put_image_to_image(_var()->menu->img, _var()->menu->buttons[_var()->menu->options_state[4]][L_ARR], (t_vector2D){774 - OFFSET_X, 560 - OFFSET_Y});

	ft_put_image_to_image(_var()->menu->img, _var()->menu->bar[EMPTY][BAR_LEFT], (t_vector2D){819 - OFFSET_X, 542 - OFFSET_Y});
	ft_put_image_to_image(_var()->menu->img, _var()->menu->bar[EMPTY][BAR_MID], (t_vector2D){912 - OFFSET_X, 542 - OFFSET_Y});
	ft_put_image_to_image(_var()->menu->img, _var()->menu->bar[EMPTY][BAR_RIGHT], (t_vector2D){1005 - OFFSET_X, 542 - OFFSET_Y});

	ft_put_image_to_image(_var()->menu->img, _var()->menu->buttons[_var()->menu->options_state[5]][R_ARR], (t_vector2D){1083 - OFFSET_X, 560 - OFFSET_Y});
	ft_put_image_to_image(_var()->menu->img, _var()->menu->buttons[_var()->menu->options_state[6]][QUIT], (t_vector2D){928 - OFFSET_X - 40, 668 - OFFSET_Y});
}

/*

*/
void	check_button_state(void)
{
	if (_var()->menu->start_state[0] != 2)
		_var()->menu->start_state[0] = ft_hitbox((t_vector2D [4]){(t_vector2D){861 - OFFSET_X, 450 - OFFSET_Y}, (t_vector2D){861 - OFFSET_X + _var()->menu->buttons[NORMAL][PLAY].width , 450 - OFFSET_Y}, (t_vector2D){861 - OFFSET_X, 450 - OFFSET_Y + _var()->menu->buttons[NORMAL][PLAY].height}, (t_vector2D){861 - OFFSET_X, 450 - OFFSET_Y + _var()->menu->buttons[NORMAL][PLAY].width + _var()->menu->buttons[NORMAL][PLAY].height}}, _var()->mouse_pos);
	if (_var()->menu->start_state[1] != 2)
		_var()->menu->start_state[1] = ft_hitbox((t_vector2D [4]){(t_vector2D){861 - OFFSET_X, 550 - OFFSET_Y}, (t_vector2D){861 - OFFSET_X + _var()->menu->buttons[NORMAL][OPTIONS].width , 550 - OFFSET_Y}, (t_vector2D){861 - OFFSET_X, 550 - OFFSET_Y + _var()->menu->buttons[NORMAL][OPTIONS].height}, (t_vector2D){861 - OFFSET_X, 550 - OFFSET_Y + _var()->menu->buttons[NORMAL][OPTIONS].width + _var()->menu->buttons[NORMAL][OPTIONS].height}}, _var()->mouse_pos);
	if (_var()->menu->start_state[2] != 2)
		_var()->menu->start_state[2] = ft_hitbox((t_vector2D [4]){(t_vector2D){861 - OFFSET_X, 650 - OFFSET_Y}, (t_vector2D){861 - OFFSET_X + _var()->menu->buttons[NORMAL][OPTIONS].width , 650 - OFFSET_Y}, (t_vector2D){861 - OFFSET_X, 650 - OFFSET_Y + _var()->menu->buttons[NORMAL][OPTIONS].height}, (t_vector2D){861 - OFFSET_X, 650 - OFFSET_Y + _var()->menu->buttons[NORMAL][OPTIONS].width + _var()->menu->buttons[NORMAL][OPTIONS].height}}, _var()->mouse_pos);
	if (_var()->menu->start_state[3] != 2)
		_var()->menu->start_state[3] = ft_hitbox((t_vector2D [4]){(t_vector2D){861 - OFFSET_X, 750 - OFFSET_Y}, (t_vector2D){861 - OFFSET_X + _var()->menu->buttons[NORMAL][OPTIONS].width , 750 - OFFSET_Y}, (t_vector2D){861 - OFFSET_X, 750 - OFFSET_Y + _var()->menu->buttons[NORMAL][OPTIONS].height}, (t_vector2D){861 - OFFSET_X, 750 - OFFSET_Y + _var()->menu->buttons[NORMAL][OPTIONS].width + _var()->menu->buttons[NORMAL][OPTIONS].height}}, _var()->mouse_pos);
}

void	check_button_state_options(void)
{
	if (_var()->menu->options_state[0] != 2)
		_var()->menu->options_state[0] = ft_hitbox((t_vector2D [4]){(t_vector2D){678 - OFFSET_X, 460 - OFFSET_Y}, (t_vector2D){678 - OFFSET_X + _var()->menu->buttons[NORMAL][MUTE_S].width , 460 - OFFSET_Y}, (t_vector2D){678 - OFFSET_X, 460 - OFFSET_Y + _var()->menu->buttons[NORMAL][MUTE_S].height}, (t_vector2D){678 - OFFSET_X, 460 - OFFSET_Y + _var()->menu->buttons[NORMAL][MUTE_S].width + _var()->menu->buttons[NORMAL][MUTE_S].height}}, _var()->mouse_pos);
	if (_var()->menu->options_state[1] != 2)
		_var()->menu->options_state[1] = ft_hitbox((t_vector2D [4]){(t_vector2D){774 - OFFSET_X, 460 - OFFSET_Y}, (t_vector2D){774 - OFFSET_X + _var()->menu->buttons[NORMAL][L_ARR].width , 460 - OFFSET_Y}, (t_vector2D){774 - OFFSET_X, 460 - OFFSET_Y + _var()->menu->buttons[NORMAL][L_ARR].height}, (t_vector2D){774 - OFFSET_X, 460 - OFFSET_Y + _var()->menu->buttons[NORMAL][L_ARR].width + _var()->menu->buttons[NORMAL][L_ARR].height}}, _var()->mouse_pos);
	if (_var()->menu->options_state[2] != 2)
		_var()->menu->options_state[2] = ft_hitbox((t_vector2D [4]){(t_vector2D){1083 - OFFSET_X, 460 - OFFSET_Y}, (t_vector2D){1083 - OFFSET_X + _var()->menu->buttons[NORMAL][MUTE_S].width , 460 - OFFSET_Y}, (t_vector2D){1083 - OFFSET_X, 460 - OFFSET_Y + _var()->menu->buttons[NORMAL][MUTE_S].height}, (t_vector2D){1083 - OFFSET_X, 460 - OFFSET_Y + _var()->menu->buttons[NORMAL][MUTE_S].width + _var()->menu->buttons[NORMAL][MUTE_S].height}}, _var()->mouse_pos);
	if (_var()->menu->options_state[3] != 2)
		_var()->menu->options_state[3] = ft_hitbox((t_vector2D [4]){(t_vector2D){678 - OFFSET_X, 560 - OFFSET_Y}, (t_vector2D){678 - OFFSET_X + _var()->menu->buttons[NORMAL][MUTE_S].width , 560 - OFFSET_Y}, (t_vector2D){678 - OFFSET_X, 560 - OFFSET_Y + _var()->menu->buttons[NORMAL][MUTE_S].height}, (t_vector2D){678 - OFFSET_X, 560 - OFFSET_Y + _var()->menu->buttons[NORMAL][MUTE_S].width + _var()->menu->buttons[NORMAL][MUTE_S].height}}, _var()->mouse_pos);
	if (_var()->menu->options_state[4] != 2)
		_var()->menu->options_state[4] = ft_hitbox((t_vector2D [4]){(t_vector2D){774 - OFFSET_X, 560 - OFFSET_Y}, (t_vector2D){774 - OFFSET_X + _var()->menu->buttons[NORMAL][MUTE_S].width , 560 - OFFSET_Y}, (t_vector2D){774 - OFFSET_X, 560 - OFFSET_Y + _var()->menu->buttons[NORMAL][MUTE_S].height}, (t_vector2D){774 - OFFSET_X, 560 - OFFSET_Y + _var()->menu->buttons[NORMAL][MUTE_S].width + _var()->menu->buttons[NORMAL][MUTE_S].height}}, _var()->mouse_pos);
	if (_var()->menu->options_state[5] != 2)
		_var()->menu->options_state[5] = ft_hitbox((t_vector2D [4]){(t_vector2D){1083 - OFFSET_X, 560 - OFFSET_Y}, (t_vector2D){1083 - OFFSET_X + _var()->menu->buttons[NORMAL][MUTE_S].width , 560 - OFFSET_Y}, (t_vector2D){1083 - OFFSET_X, 560 - OFFSET_Y + _var()->menu->buttons[NORMAL][MUTE_S].height}, (t_vector2D){1083 - OFFSET_X, 560 - OFFSET_Y + _var()->menu->buttons[NORMAL][MUTE_S].width + _var()->menu->buttons[NORMAL][MUTE_S].height}}, _var()->mouse_pos);
	if (_var()->menu->options_state[6] != 2)
		_var()->menu->options_state[6] = ft_hitbox((t_vector2D [4]){(t_vector2D){928 - 40 - OFFSET_X, 668 - OFFSET_Y}, (t_vector2D){928 - 40 - OFFSET_X + _var()->menu->buttons[NORMAL][MUTE_S].width , 668 - OFFSET_Y}, (t_vector2D){928 - 40 - OFFSET_X, 668 - OFFSET_Y + _var()->menu->buttons[NORMAL][MUTE_S].height}, (t_vector2D){928 - 40 - OFFSET_X, 668 - OFFSET_Y + _var()->menu->buttons[NORMAL][MUTE_S].width + _var()->menu->buttons[NORMAL][MUTE_S].height}}, _var()->mouse_pos);
}

/*
-Display starting menu
*/
void	menu_start(void)
{
	ft_put_image_to_image(_var()->menu->img, _var()->menu->bg, (t_vector2D){0, 0});
	ft_put_image_to_image(_var()->menu->img, _var()->menu->logo, (t_vector2D){716 - OFFSET_X - 45, 155 - OFFSET_Y + 50});
	ft_put_image_to_image(_var()->menu->img, _var()->menu->buttons[_var()->menu->start_state[0]][PLAY], (t_vector2D){861 - OFFSET_X, 450 - OFFSET_Y});
	ft_put_image_to_image(_var()->menu->img, _var()->menu->buttons[_var()->menu->start_state[1]][OPTIONS], (t_vector2D){861 - OFFSET_X, 550 - OFFSET_Y});
	ft_put_image_to_image(_var()->menu->img, _var()->menu->buttons[_var()->menu->start_state[2]][CREDITS], (t_vector2D){861 - OFFSET_X, 650 - OFFSET_Y});
	ft_put_image_to_image(_var()->menu->img, _var()->menu->buttons[_var()->menu->start_state[3]][EXIT], (t_vector2D){861 - OFFSET_X, 750 - OFFSET_Y});
}

/*
-Loop for menu displaying.
*/
int	menu_loop(void)
{
	if (_var()->menu->mode == MENU_START)
		check_button_state();
	else if (_var()->menu->mode == MENU_OPTION)
		check_button_state_options();
	mlx_mouse_get_pos(_mlx()->mlx, _mlx()->mlx_win, &_var()->mouse_pos.x, &_var()->mouse_pos.y);
	if (_var()->menu->mode == MENU_START)
		menu_start();
	else if (_var()->menu->mode == MENU_OPTION)
		menu_option();
	mlx_put_image_to_window(_mlx()->mlx, _mlx()->mlx_win, _var()->menu->img.img, 0, 0);
	return (0);
}

/*
-Function for loop inputs.
*/
int	menu_hook(int keycode)
{
	int			i;
	t_enum_key	tab[1];

	i = 0;
	tab[0].id= 65307;
	tab[0].ft_hook_key = &ft_escape;
	//printf("keycode : %d\n", keycode);
	while (i < MAX_KEYS)
	{
		printf("id : %d\n",tab[i].id);
		if (tab[i].id == keycode)
			return (tab[i].ft_hook_key());
		++i;
	}
	return (0);
}

void	check_button_state_mouse(int keycode)
{
	if (keycode == 1 && ft_hitbox((t_vector2D [4]){(t_vector2D){861 - OFFSET_X, 450 - OFFSET_Y}, (t_vector2D){861 - OFFSET_X + _var()->menu->buttons[NORMAL][PLAY].width , 450 - OFFSET_Y}, (t_vector2D){861 - OFFSET_X, 450 - OFFSET_Y + _var()->menu->buttons[NORMAL][PLAY].height}, (t_vector2D){861 - OFFSET_X, 450 - OFFSET_Y + _var()->menu->buttons[NORMAL][PLAY].width + _var()->menu->buttons[NORMAL][PLAY].height}}, _var()->mouse_pos))
	{
		_var()->menu->start_state[0] = 2;
		_var()->mode = GAME;
	}
	if (keycode == 1 && ft_hitbox((t_vector2D [4]){(t_vector2D){861 - OFFSET_X, 550 - OFFSET_Y}, (t_vector2D){861 - OFFSET_X + _var()->menu->buttons[NORMAL][OPTIONS].width , 550 - OFFSET_Y}, (t_vector2D){861 - OFFSET_X, 550 - OFFSET_Y + _var()->menu->buttons[NORMAL][OPTIONS].height}, (t_vector2D){861 - OFFSET_X, 550 - OFFSET_Y + _var()->menu->buttons[NORMAL][OPTIONS].width + _var()->menu->buttons[NORMAL][OPTIONS].height}}, _var()->mouse_pos))
	{
		_var()->menu->start_state[1] = 2;
		_var()->menu->mode = MENU_OPTION;
	}
	if (keycode == 1 && ft_hitbox((t_vector2D [4]){(t_vector2D){861 - OFFSET_X, 650 - OFFSET_Y}, (t_vector2D){861 - OFFSET_X + _var()->menu->buttons[NORMAL][CREDITS].width , 650 - OFFSET_Y}, (t_vector2D){861 - OFFSET_X, 650 - OFFSET_Y + _var()->menu->buttons[NORMAL][CREDITS].height}, (t_vector2D){861 - OFFSET_X, 650 - OFFSET_Y + _var()->menu->buttons[NORMAL][CREDITS].width + _var()->menu->buttons[NORMAL][CREDITS].height}}, _var()->mouse_pos))
		_var()->menu->start_state[2] = 2;
	if (keycode == 1 && ft_hitbox((t_vector2D [4]){(t_vector2D){861 - OFFSET_X, 750 - OFFSET_Y}, (t_vector2D){861 - OFFSET_X + _var()->menu->buttons[NORMAL][EXIT].width , 750 - OFFSET_Y}, (t_vector2D){861 - OFFSET_X, 750 - OFFSET_Y + _var()->menu->buttons[NORMAL][EXIT].height}, (t_vector2D){861 - OFFSET_X, 750 - OFFSET_Y + _var()->menu->buttons[NORMAL][EXIT].width + _var()->menu->buttons[NORMAL][EXIT].height}}, _var()->mouse_pos))
	{
		_var()->menu->start_state[3] = 2;
		// TODO FREE TOUT
		exit(0);
	}
}

void	check_button_state_mouse_options(int keycode)
{
	if (keycode == 1 && ft_hitbox((t_vector2D [4]){(t_vector2D){678 - OFFSET_X, 460 - OFFSET_Y}, (t_vector2D){678 - OFFSET_X + _var()->menu->buttons[NORMAL][MUTE_S].width , 460 - OFFSET_Y}, (t_vector2D){678 - OFFSET_X, 460 - OFFSET_Y + _var()->menu->buttons[NORMAL][MUTE_S].height}, (t_vector2D){678 - OFFSET_X, 460 - OFFSET_Y + _var()->menu->buttons[NORMAL][MUTE_S].width + _var()->menu->buttons[NORMAL][MUTE_S].height}}, _var()->mouse_pos))
		_var()->menu->options_state[0] = 2;
	if (keycode == 1 && ft_hitbox((t_vector2D [4]){(t_vector2D){774 - OFFSET_X, 460 - OFFSET_Y}, (t_vector2D){774 - OFFSET_X + _var()->menu->buttons[NORMAL][L_ARR].width , 460 - OFFSET_Y}, (t_vector2D){774 - OFFSET_X, 460 - OFFSET_Y + _var()->menu->buttons[NORMAL][L_ARR].height}, (t_vector2D){774 - OFFSET_X, 460 - OFFSET_Y + _var()->menu->buttons[NORMAL][L_ARR].width + _var()->menu->buttons[NORMAL][L_ARR].height}}, _var()->mouse_pos))
		_var()->menu->options_state[1] = 2;
	if (keycode == 1 && ft_hitbox((t_vector2D [4]){(t_vector2D){1083 - OFFSET_X, 460 - OFFSET_Y}, (t_vector2D){1083 - OFFSET_X + _var()->menu->buttons[NORMAL][MUTE_S].width , 460 - OFFSET_Y}, (t_vector2D){1083 - OFFSET_X, 460 - OFFSET_Y + _var()->menu->buttons[NORMAL][MUTE_S].height}, (t_vector2D){1083 - OFFSET_X, 460 - OFFSET_Y + _var()->menu->buttons[NORMAL][MUTE_S].width + _var()->menu->buttons[NORMAL][MUTE_S].height}}, _var()->mouse_pos))
		_var()->menu->options_state[2] = 2;
	if (keycode == 1 && ft_hitbox((t_vector2D [4]){(t_vector2D){678 - OFFSET_X, 560 - OFFSET_Y}, (t_vector2D){678 - OFFSET_X + _var()->menu->buttons[NORMAL][MUTE_S].width , 560 - OFFSET_Y}, (t_vector2D){678 - OFFSET_X, 560 - OFFSET_Y + _var()->menu->buttons[NORMAL][MUTE_S].height}, (t_vector2D){678 - OFFSET_X, 560 - OFFSET_Y + _var()->menu->buttons[NORMAL][MUTE_S].width + _var()->menu->buttons[NORMAL][MUTE_S].height}}, _var()->mouse_pos))
		_var()->menu->options_state[3] = 2;
	if (keycode == 1 && ft_hitbox((t_vector2D [4]){(t_vector2D){774 - OFFSET_X, 560 - OFFSET_Y}, (t_vector2D){774 - OFFSET_X + _var()->menu->buttons[NORMAL][MUTE_S].width , 560 - OFFSET_Y}, (t_vector2D){774 - OFFSET_X, 560 - OFFSET_Y + _var()->menu->buttons[NORMAL][MUTE_S].height}, (t_vector2D){774 - OFFSET_X, 560 - OFFSET_Y + _var()->menu->buttons[NORMAL][MUTE_S].width + _var()->menu->buttons[NORMAL][MUTE_S].height}}, _var()->mouse_pos))
		_var()->menu->options_state[4] = 2;
	if (keycode == 1 && ft_hitbox((t_vector2D [4]){(t_vector2D){1083 - OFFSET_X, 560 - OFFSET_Y}, (t_vector2D){1083 - OFFSET_X + _var()->menu->buttons[NORMAL][MUTE_S].width , 560 - OFFSET_Y}, (t_vector2D){1083 - OFFSET_X, 560 - OFFSET_Y + _var()->menu->buttons[NORMAL][MUTE_S].height}, (t_vector2D){1083 - OFFSET_X, 560 - OFFSET_Y + _var()->menu->buttons[NORMAL][MUTE_S].width + _var()->menu->buttons[NORMAL][MUTE_S].height}}, _var()->mouse_pos))
		_var()->menu->options_state[5] = 2;
	if (keycode == 1 && ft_hitbox((t_vector2D [4]){(t_vector2D){928 - 40 - OFFSET_X, 668 - OFFSET_Y}, (t_vector2D){928 - 40 - OFFSET_X + _var()->menu->buttons[NORMAL][MUTE_S].width , 668 - OFFSET_Y}, (t_vector2D){928 - 40 - OFFSET_X, 668 - OFFSET_Y + _var()->menu->buttons[NORMAL][MUTE_S].height}, (t_vector2D){928 - 40 - OFFSET_X, 668 - OFFSET_Y + _var()->menu->buttons[NORMAL][MUTE_S].width + _var()->menu->buttons[NORMAL][MUTE_S].height}}, _var()->mouse_pos))
	{
		_var()->menu->options_state[6] = 2;
		_var()->menu->mode = MENU_START;
		restart_button();
	}
}


/*
-Function for menu mouse inputs.
*/
int	menu_mouse_hook(int keycode)
{
	if (_var()->menu->mode == MENU_START)
		check_button_state_mouse(keycode);
	if (_var()->menu->mode == MENU_OPTION)
		check_button_state_mouse_options(keycode);
	return (0);
}