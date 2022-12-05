/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 16:43:03 by yobougre          #+#    #+#             */
/*   Updated: 2022/12/05 19:37:43 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

int	intersects(t_circle circle, t_rect rect)
{
	t_vector2F	circle_dist;
	float		corner;

	circle_dist.x = fabs(circle.x - rect.x);
	circle_dist.y = fabs(circle.y - rect.y);
	if (circle_dist.x > (rect.width / 2 + circle.radius))
		return (0);
	if (circle_dist.y > (rect.height / 2 + circle.radius))
		return (0);
	if (circle_dist.x <= (rect.width / 2))
		return (1);
	if (circle_dist.y <= (rect.height / 2))
		return (1);
	corner = pow((circle_dist.x - rect.width / 2), 2)
		+ pow((circle_dist.y - rect.height / 2), 2);
	return (corner <= (pow(circle.radius, 2)));
}

void	get_directional_texture(void)
{
	int	degree;

	if (_ray()->side == 0)
	{
		degree = atan2(_ray()->dir.x, _ray()->dir.y) * 180 / PI;
		if (degree < 0)
			degree += 360;
		if (degree < 180)
			_ray()->tex_i = 3;
		else
			_ray()->tex_i = 1;
		_ray()->perp_wall_dist = (_ray()->side_dist.x - _ray()->delta.x);
	}
	else
	{
		degree = atan2(_ray()->dir.y, _ray()->dir.x) * 180 / PI;
		if (degree < 0)
			degree += 360;
		if (degree > 180)
			_ray()->tex_i = 0;
		else
			_ray()->tex_i = 2;
		_ray()->perp_wall_dist = (_ray()->side_dist.y - _ray()->delta.y);
	}
}

void	compute_drawing_data(void)
{
	get_directional_texture();
	_ray()->line_h = (int)(WIN_H / _ray()->perp_wall_dist);
	_ray()->draw_start = (-_ray()->line_h / 2 + WIN_H / 2);
	if (_ray()->draw_start < 0)
		_ray()->draw_start = 0;
	_ray()->draw_end = (_ray()->line_h / 2 + WIN_H / 2);
	if (_ray()->draw_end > WIN_H)
		_ray()->draw_end = WIN_H - 1;
	if (_ray()->side == 0)
		_ray()->wall_x = (_player()->y + 0.5) + _ray()->perp_wall_dist
		* _ray()->dir.y;
	else
		_ray()->wall_x = (_player()->x + 0.5) + _ray()->perp_wall_dist
		* _ray()->dir.x;
	_ray()->wall_x -= floor(_ray()->wall_x);
}

void	draw_wall(void)
{
	int	y;

	_ray()->tex.x = (int){_ray()->wall_x * 64.0};
	if (_ray()->side == 0 && _ray()->dir.x > 0)
		_ray()->tex.x = 64 - _ray()->tex.x - 1;
	else if (_ray()->side == 1 && _ray()->dir.y < 0)
		_ray()->tex.x = 64 - _ray()->tex.x - 1;
	_ray()->tex_step = 1.0 * 64 / _ray()->line_h;
	_ray()->tex_pos = (_ray()->draw_start - WIN_H / 2 + _ray()->line_h / 2)
	* _ray()->tex_step;
	y = _ray()->draw_start;
	while (y < _ray()->draw_end)
	{
		_ray()->tex.y = (int)_ray()->tex_pos & (128 - 1);
		_ray()->tex_pos += _ray()->tex_step;
		ft_put_pixel(_img(), &_var()->dir[_ray()->tex_i], (t_vector2D){
			_ray()->x, y}, (t_vector2D){_ray()->tex.x, _ray()->tex.y});
		y++;
	}
}

void	draw_rays(void)
{
	_ray()->x = 0;
	while (_ray()->x < WIN_W)
	{
		init_ray();
		init_dda();
		dda();
		compute_drawing_data();
		draw_wall();
		_ray()->x++;
	}
}
