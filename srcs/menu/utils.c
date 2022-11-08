/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 13:06:23 by denissereno       #+#    #+#             */
/*   Updated: 2022/11/07 16:55:57 by denissereno      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

/*
-Functions that make all button restart to normal state 
(normal, hover or active).
*/
void	restart_button(void)
{
	int	i;

	i = 0;
	while (i < 4)
		_menu()->s_state[i++].state = 0;
	i = 0;
	while (i < 7)
		_menu()->o_state[i++].state = 0;
}

/*
-Check if position is in the hitbox given in parameter.
*/
int	ft_hitbox(t_vector2D hitbox[4], t_vector2D pos)
{
	if (pos.x >= hitbox[0].x && pos.x <= hitbox[1].x &&
		pos.y >= hitbox[0].y && pos.y <= hitbox[2].y)
	{
		return (1);
	}
	return (0);
}

/*
-Draw a pixel if lil image on big image at rel_pos coordinate on the big from
the it coordinate of the lil image.
*/
void	draw_pixel(t_data *big, t_data lil, t_vector2D it, t_vector2D rel_pos)
{
	if (lil.addr[it.x * 4 + it.y * lil.line_length + 3] != -1)
	{
		big->addr[rel_pos.x + rel_pos.y] = lil.addr[it.x * 4
			+ it.y * lil.line_length];
		big->addr[rel_pos.x + rel_pos.y + 1] = lil.addr[it.x * 4
			+ it.y * lil.line_length + 1];
		big->addr[rel_pos.x + rel_pos.y + 2] = lil.addr[it.x * 4
			+ it.y * lil.line_length + 2];
		big->addr[rel_pos.x + rel_pos.y + 3] = lil.addr[it.x * 4
			+ it.y * lil.line_length + 3];
	}
}

void	draw_pixel_create(t_data *big, t_data lil, t_vector2D it, t_vector2D rel_pos)
{
	big->addr[rel_pos.x + rel_pos.y] = lil.addr[it.x * 4
		+ it.y * lil.line_length];
	big->addr[rel_pos.x + rel_pos.y + 1] = lil.addr[it.x * 4
		+ it.y * lil.line_length + 1];
	big->addr[rel_pos.x + rel_pos.y + 2] = lil.addr[it.x * 4
		+ it.y * lil.line_length + 2];
	big->addr[rel_pos.x + rel_pos.y + 3] = lil.addr[it.x * 4
		+ it.y * lil.line_length + 3];
}

t_data	ft_put_image_to_image_scale(t_data big, t_data lil, t_vector2D p, t_vector2D scale)
{
	t_vector2D	rel_pos[2];
	t_vector2D	it;

	rel_pos[0] = (t_vector2D){p.x * 4, p.y * big.line_length};
	rel_pos[1] = rel_pos[0];
	it = (t_vector2D){0, 0};
	if (p.x + lil.w > big.w
	|| (p.y) + lil.h > big.h)
		return (big);
	if (scale.x > 20 || scale.y > 20)
		return (big);
	while (it.y < lil.h)
	{
		it.x = 0;
		while (it.x < lil.w)
		{
			draw_pixel(&big, lil, it, rel_pos[0]);
			rel_pos[0].x += 4;
			p.x++;
			it.x += scale.x;
		}
		p.y++;
		rel_pos[0].y = p.y * big.line_length;
		rel_pos[0].x = rel_pos[1].x;
		it.y += scale.y;
	}
	return (big);
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
	t_vector2D	rel_pos[2];
	t_vector2D	it;

	rel_pos[0] = (t_vector2D){pos.x * 4, pos.y * big.line_length};
	rel_pos[1] = rel_pos[0];
	it = (t_vector2D){0, 0};
	if (pos.x + lil.w > big.w
	|| (pos.y) + lil.h > big.h)
		return (big);
	while (it.y < lil.h)
	{
		it.x = 0;
		while (it.x < lil.w)
		{
			draw_pixel(&big, lil, it, rel_pos[0]);
			rel_pos[0].x += 4;
			pos.x++;
			it.x++;
		}
		pos.y++;
		rel_pos[0].y = pos.y * big.line_length;
		rel_pos[0].x = rel_pos[1].x;
		it.y++;
	}
	return (big);
}

t_data	ft_put_image_to_image_create(t_data big, t_data lil, t_vector2D pos)
{
	t_vector2D	rel_pos[2];
	t_vector2D	it;

	rel_pos[0] = (t_vector2D){pos.x * 4, pos.y * big.line_length};
	rel_pos[1] = rel_pos[0];
	it = (t_vector2D){0, 0};
	if (pos.x + lil.w > big.w
	|| (pos.y) + lil.h > big.h)
		return (big);
	while (it.y < lil.h)
	{
		it.x = 0;
		while (it.x < lil.w)
		{
			draw_pixel_create(&big, lil, it, rel_pos[0]);
			rel_pos[0].x += 4;
			pos.x++;
			it.x++;
		}
		pos.y++;
		rel_pos[0].y = pos.y * big.line_length;
		rel_pos[0].x = rel_pos[1].x;
		it.y++;
	}
	return (big);
}


t_data	ft_put_sprite_to_images_scale(t_data big, t_data lil, t_vector2D pos, t_vector2D sp_pos, t_vector2D size, t_vector2D scale)
{
	t_vector2D	rel_pos[2];
	t_vector2D	it;
	t_vector2D	save;

	save = pos;
	if (pos.x >= big.w || pos.y >= big.h || size.x + pos.x
		> big.w || size.y + pos.y > big.h)
		return (big);
	rel_pos[0] = (t_vector2D){pos.x * 4, pos.y * big.line_length};
	rel_pos[1] = rel_pos[0];
	it = (t_vector2D){0, 0};
	if (pos.x + lil.w > big.w
	|| (pos.y) + lil.h > big.h)
		return (big);
	while (it.y < size.y)
	{
		it.x = 0;
		pos.x = save.x;
		while (it.x < size.x)
		{
			if (size.x + it.x < big.w)
				draw_pixel(&big, lil,(t_vector2D){(sp_pos.x + it.x), it.y + sp_pos.y}, rel_pos[0]);
			rel_pos[0].x += 4;
			pos.x++;
			it.x += scale.x;
		}
		pos.y++;
		rel_pos[0].y = pos.y * big.line_length;
		rel_pos[0].x = rel_pos[1].x;
		it.y += scale.y;
	}
	return (big);
}

t_data	ft_put_sprite_to_images(t_data big, t_data lil, t_vector2D pos, t_vector2D sp_pos, t_vector2D size)
{
	t_vector2D	rel_pos[2];
	t_vector2D	it;
	t_vector2D	save;

	save = pos;
	if (pos.x >= big.w || pos.y >= big.h || size.x + pos.x
		> big.w || size.y + pos.y > big.h)
		return (big);
	rel_pos[0] = (t_vector2D){pos.x * 4, pos.y * big.line_length};
	rel_pos[1] = rel_pos[0];
	it = (t_vector2D){0, 0};
	while (it.y < size.y)
	{
		it.x = 0;
		pos.x = save.x;
		while (it.x < size.x)
		{
			if (size.x + it.x < big.w)
				draw_pixel(&big, lil,(t_vector2D){(sp_pos.x + it.x), it.y + sp_pos.y}, rel_pos[0]);
			rel_pos[0].x += 4;
			pos.x++;
			it.x++;
		}
		pos.y++;
		rel_pos[0].y = pos.y * big.line_length;
		rel_pos[0].x = rel_pos[1].x;
		it.y++;
	}
	return (big);
}

void	draw_pixel_color(t_data *big, t_vector2D rel_pos, char pix[4])
{
	big->addr[rel_pos.x + rel_pos.y] = pix[0];
	big->addr[rel_pos.x + rel_pos.y + 1] = pix[1];
	big->addr[rel_pos.x + rel_pos.y + 2] = pix[2];
	big->addr[rel_pos.x + rel_pos.y + 3] = pix[3];
}

void	draw_vertical_line(t_data *img, t_vector2D pos, int h)
{
	t_vector2D	rel_pos[2];
	int			i;
	int			n;
	static char	color[2][4] = {{146, 122, 20, 0}, {103, 86, 14, 0}};

	i = 0;
	n = 0;
	rel_pos[0] = (t_vector2D){pos.x * 4, pos.y * img->line_length};
	rel_pos[1] = rel_pos[0];
	while (i < h)
	{
		if (i == h / 2)
			n++;
		draw_pixel_color(img, rel_pos[0], color[n]);
		pos.y++;
		rel_pos[0].y = pos.y * img->line_length;
		i++;
	}
}

void	draw_bar_fill(void)
{
	int	i;

	i = 0;
	while (i < (int)(_menu()->s_bar * BAR_INC))
	{
		draw_vertical_line(_img(), (t_vector2D){819 - OFFSET_X + 42
			+ i, 443 - OFFSET_Y + 36}, 27);
		i++;
	}
	i = 0;
	while (i < (int)(_menu()->m_bar * BAR_INC))
	{
		draw_vertical_line(_img(), (t_vector2D){819 - OFFSET_X + 42
			+ i, 542 - OFFSET_Y + 36}, 27);
		i++;
	}
}
