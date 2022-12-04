/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 18:07:21 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/04 20:14:39 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub.h"

static int	ft_chk_put(t_data lil, t_vector2D p, t_vector2F scale)
{
	t_data	big;

	big = *_img();
	if (p.x + lil.w * scale.x > big.w || (p.y) + lil.h * scale.y > big.h)
		return (1);
	if (scale.x > 20 || scale.y > 20)
		return (1);
	return (0);
}

t_data	ft_put_img_to_img_scale(t_data b, t_data l, t_vector2D p, t_vector2F s)
{
	t_vector2D	rel_pos[2];
	t_vector2F	it;

	ft_init_rel2(rel_pos, &it, p);
	if (ft_chk_put(l, p, s))
		return (b);
	while (it.y < l.h)
	{
		it.x = 0;
		while (it.x < l.w)
		{
			if (p.x > 0 && p.y > 0 && rel_pos[0].x >= 0 && rel_pos[0].y > 0
				&& rel_pos[0].x < WIN_W * 4 && rel_pos[0].y < WIN_H
				* _img()->line_length)
				draw_pixel(&b, l, pos((int)it.x, (int)it.y), rel_pos[0]);
			rel_pos[0].x += 4;
			p.x++;
			it.x += s.x;
		}
		p.y++;
		rel_pos[0].y = p.y * b.line_length;
		rel_pos[0].x = rel_pos[1].x;
		it.y += s.y;
	}
	return (b);
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
	if (pos.x + lil.w > big.w || (pos.y) + lil.h > big.h)
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
	if (pos.x + lil.w > big.w || (pos.y) + lil.h > big.h)
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

int	ft_chk_sprite(t_vector2D *it, t_vector2D pos, t_vector2D s, t_vector2D *r)
{
	t_data		big;

	big = *_img();
	*it = (t_vector2D){0, 0};
	r[0] = (t_vector2D){pos.x * 4, pos.y * big.line_length};
	r[1] = r[0];
	if (pos.x >= big.w || pos.y >= big.h || s.x + pos.x
		> big.w || s.y + pos.y > big.h)
		return (1);
	return (0);
}
