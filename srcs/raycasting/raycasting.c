/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 19:55:08 by denissereno       #+#    #+#             */
/*   Updated: 2022/10/06 00:21:25 by denissereno      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	init_ray(t_raycasting *r)
{
	r->draw_end = 0;
	r->draw_start = 0;
	r->cam.x = 2 * (r->x / (double)WIN_H - 0.8);
	r->dir.x =  r->pl.dx + (r->pl.plane.x * r->cam.x);
	r->dir.y =  r->pl.dy + (r->pl.plane.y * r->cam.x);
	r->map = (t_vector2D){(r->pl.x + 0.5), (r->pl.y + 0.5)};
	if (r->dir.y == 0)
		r->delta.x = 0;
	else if (r->dir.x == 0)
		r->delta.x = 1;
	else
		r->delta.x = fabs(1 / r->dir.x);
	if (r->dir.x == 0)
		r->delta.y = 0;
	else if (r->dir.y == 0)
		r->delta.y = 1;
	else
		r->delta.y = fabs(1 / r->dir.y);
}

/*
This calcultate the step size of x and y movement it's always between -1 and 1
beacause we are in a normalised tile world {pos player x = 1.5 mean that we
are in 1x tile of the map}.

The side_dist is the distance between the current pos to the next X side. So we
calculate the offset of the player onto his tile {_player{)->x + 0.5}} - _ray{}->map.x}.
Map.x is the current tile of player {example : 4} and {player{}.x +0.5 }is the actual
real position in this tile {example : 4.57}. So the offset on x axis is :
4.57 - 4 = 0.57.

The delta X value is normalize between 0 and 1 because of the direction of the 
X ray. If its totally straight it will be 1 or -1 because we have a step of 1 to
acces of 1 side to the other side of the cell. But if the ray_dir is not straight
we dont travel 1 by 1 to each side of x cell because of the inclinaison of
the camera. So we calculate the delta by : fabs{1 / _ray{}->dir.x} that give
us the % between 0 and 1 of the direction of the camera and we know the step
to access to another side of X.

And now we multiply the last result by delta so now side_dist.x = to the next
side of the cell that we are in. 

And its the same for y axis.
*/

void	init_dda(t_raycasting *r)
{
	r->hit = 0;
	if (r->dir.x < 0)
	{
		r->step.x = -1;
		r->side_dist.x = (((r->pl.x + 0.5)) - r->map.x)
		* r->delta.x;

	}
	else
	{
		r->step.x = 1;
		r->side_dist.x = (r->map.x + 1 - ((r->pl.x + 0.5)))
		* r->delta.x;
	}
	if (r->dir.y < 0)
	{
		r->step.y = -1;
		r->side_dist.y = ((r->pl.y + 0.5) - r->map.y)
		* r->delta.y;
	}
	else
	{
		r->step.y = 1;
		r->side_dist.y = (r->map.y + 1 - (r->pl.y + 0.5))
		* r->delta.y;
	}
}

/*
Now we have to raycasting until we touch a map obstacle. So while its not
touched we check if side_dist.x < side_dist.y or superior.

Check dda.png in the root folder.

Like in the drawing we have a red line that show the ray. The blue line is the
first offset to start at x side and the orange if for the y side. This is what we calculate
on _ray{}->side_dist.
So we start after that. The green and yello line is one unit of x and y and the
green dots are the X side intersection with the ray and yellow is for the y one.

So we check at the second green dot. Here side_dist->x will be equal to the first 
green dot to this dot here and side_dist-> y will be equal to the first yellow 
dot to the next one. So side_dist->y is superior than side_dist->x so we
know that the next cell we will check is at x+ 1. When we will encounter
the next yellow dot, side_dist->y will be inferior to side_dist->x because the next
green dot is after. So this time we will go cell y + 1.

So when we encounter a '1' we stop the dda and we have the coordinate of the
ray finishing.
*/

void	dda(t_raycasting *r)
{
	while (!r->hit)
	{
		if (r->side_dist.x < r->side_dist.y)
		{
			r->side_dist.x += r->delta.x;
			r->map.x += r->step.x;
			r->side = 0;
		}
		else
		{
			r->side_dist.y += r->delta.y;
			r->map.y += r->step.y;
			r->side = 1;
		}
		if (r->map.y < _img()->map_height && r->map.y >= 0 &&
			r->map.x < _img()->map_width && r->map.x >= 0
			&& _img()->map[r->map.y][r->map.x] == '1') // ! Possible crash si pas de mur ( rajouter condition pour break)
			r->hit = 1;
	}
}

void	compute_drawing_data(t_raycasting *r)
{

	if (r->side == 0)
		r->perp_wall_dist = (r->side_dist.x - r->delta.x);
	else
		r->perp_wall_dist = (r->side_dist.y - r->delta.y);
	r->line_h = (int)(WIN_H / r->perp_wall_dist);
	r->draw_start = -r->line_h / 2 + WIN_H / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;
	r->draw_end = r->line_h / 2 + WIN_H / 2;
	if (r->draw_end > WIN_H)
		r->draw_end = WIN_H - 1;
	if (r->side == 0)
		r->wall_x = (r->pl.y + 0.5) + r->perp_wall_dist * r->dir.y;
	else
		r->wall_x = (r->pl.x + 0.5) + r->perp_wall_dist * r->dir.x;
	r->wall_x -= floor(r->wall_x);
}

void	draw_wall(t_raycasting *r)
{
	r->tex.x = (int){r->wall_x * 64.0};
	if (r->side == 0 && r->dir.x > 0)
		r->tex.x = 64 - r->tex.x - 1;
	else if (r->side == 1 && r->dir.y < 0)
		r->tex.x = 64 - r->tex.x - 1;
	r->y = r->draw_start;
	while(r->y < r->draw_end)
	{
		r->tex_step = r->y * _var()->menu->wall.line_length - WIN_H
		* _var()->menu->wall.line_length / 2 + r->line_h * _var()->menu->wall.line_length / 2;
		r->tex.y = ((r->tex_step * _var()->menu->wall.height) / r->line_h)
			/ _var()->menu->wall.line_length;
		r->color = (int)_var()->menu->wall.addr[(r->tex.y * _var()->menu->wall.line_length)  + (r->tex.x * 4)];
		if(r->side == 1)
			r->color = (r->color >> 1) & 8355711;
		_img()->addr[r->y * _img()->line_length + r->x * 4] = _var()->menu->wall.addr[(r->tex.y * _var()->menu->wall.line_length)  + (r->tex.x * 4)];
		_img()->addr[(r->y * _img()->line_length + r->x * 4) + 1] = _var()->menu->wall.addr[((r->tex.y * _var()->menu->wall.line_length)  + (r->tex.x * 4)) + 1];
		_img()->addr[(r->y * _img()->line_length + r->x * 4) + 2] = _var()->menu->wall.addr[((r->tex.y * _var()->menu->wall.line_length)  + (r->tex.x * 4)) + 2];
		_img()->addr[(r->y * _img()->line_length + r->x * 4) + 3] = _var()->menu->wall.addr[((r->tex.y * _var()->menu->wall.line_length)  + (r->tex.x * 4)) + 3];
		r->y++;
	}
}

typedef struct	s_ray_th
{
	t_vector2D	start_end;
	int			i;
	t_obj		pl;
}	t_ray_th;

void	*ray_draw(void *t)
{
	t_ray_th	r;

	r = *(t_ray_th *)t;
	_ray()[r.i]->x = r.start_end.x;
	_ray()[r.i]->pl = r.pl;
	while (_ray()[r.i]->x < r.start_end.y)
	{
		init_ray(_ray()[r.i]);
		init_dda(_ray()[r.i]);
		dda(_ray()[r.i]);
		if (_ray()[r.i]->hit == 0)
			continue ;
		compute_drawing_data(_ray()[r.i]);
		draw_wall(_ray()[r.i]);
		_var()->zbuffer[_ray()[r.i]->x] = _ray()[r.i]->perp_wall_dist;
		_ray()[r.i]->x++;
	}
	return (NULL);
}

/*
-Algorithm to draw raycasting.
*/

void	draw_rays(void)
{
	static t_ray_th	r[TH_RAY];
	static int		started = 0;

	if (!started)
	{
		for (int i = 0; i < TH_RAY; i++)
		{
			r[i].start_end = (t_vector2D){ (WIN_W / TH_RAY) * i, (WIN_W / TH_RAY) * (i + 1)};
			r[i].i = i;
		}
	}
	for (int i = 0; i < TH_RAY; i++)
	{
		r[i].pl = *_player();
		pthread_create(&_var()->th[i], NULL, ray_draw, &r[i]);
	}
	for (int i = 0; i < TH_RAY; i++)
		pthread_join(_var()->th[i], NULL);
}

/*
Algo dont draw sky for nothing.

We take the highest y pixel write by the raycasting algorithm and to draw the next
sky draw sky from the y stocked to the bottom.                                                                                                                                                                        
*/