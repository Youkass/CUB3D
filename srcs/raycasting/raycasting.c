/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 19:55:08 by denissereno       #+#    #+#             */
/*   Updated: 2022/10/01 12:07:39 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	draw_rays(void)
{
	float	a_tan;

	_ray()->ra =_player()->angle - 30 * DR;
	if (_ray()->ra < 0)
		_ray()->ra += 2 * PI;
	if (_ray()->ra >= 2 * PI)
		_ray()->ra -= 2 * PI;
	for (int i = 0; i < 60; i++)
	{
		// ---------- HORIZONTAL ----------------
		a_tan = -1/tan(_ray()->ra);
		_ray()->dof = 0;
		_ray()->disH = 100000;
		_ray()->h.x = (_player()->x + 5);
		_ray()->h.y = (_player()->y + 5);
		if (_ray()->ra > PI) // if looking up
		{
			_ray()->ry = (((int)(_player()->y + 5) / _img()->scale) * _img()->scale) - 0.0001; // found the next 64px next horintozal line
			_ray()->rx = ((_player()->y + 5) - _ray()->ry) * a_tan + (_player()->x + 5);
			_ray()->yo = -_img()->scale;
			_ray()->xo = -_ray()->yo * a_tan;
			//printf("1\n");
		}
		if (_ray()->ra < PI && _ray()->ra > 0) // if looking up
		{
			_ray()->ry = (((int)(_player()->y + 5) / _img()->scale) * _img()->scale) + _img()->scale; // found the next 64px next horintozal line
			_ray()->rx = ((_player()->y + 5) - _ray()->ry) * a_tan + (_player()->x + 5);
			_ray()->yo = _img()->scale;
			_ray()->xo = -_ray()->yo * a_tan;
			//printf("%f, 2\n",  _ray()->ra);
		}
		if (_ray()->ra <= 0 || _ray()->ra == PI)
		{
			_ray()->rx = (_player()->x + 5);
			_ray()->ry = (_player()->y + 5);
			_ray()->dof = _img()->map_height;
			//printf("3\n");
		}
		while (_ray()->dof < _img()->map_height)
		{
			_ray()->mx = (int)(_ray()->rx) / _img()->scale;
			_ray()->my = (int)(_ray()->ry) / _img()->scale;
			_ray()->mp = _ray()->my * _img()->width + _ray()->mx;
			if (_ray()->mx >= 0 && _ray()->my >= 0 &&_ray()->mx < _img()->map_width && _ray()->my < _img()->map_height && 
			_img()->map[_ray()->my][_ray()->mx] == '1')
			{
				_ray()->h = (t_vector2F){_ray()->rx, _ray()->ry};
				_ray()->disH = ray_dist((t_vector2F){(_player()->x + 5), (_player()->y + 5)}, _ray()->h, _ray()->ra);
				_ray()->dof = _img()->map_height;
			}
			else
			{
				_ray()->rx += _ray()->xo;
				_ray()->ry += _ray()->yo;
				_ray()->dof++;
			}
		}
		//plot_line((_player()->x + 5), (_player()->y + 5), (int)_ray()->rx, (int)_ray()->ry, 0xFFFF0000);
		// -----   VERTICAL LINE -------

		a_tan = -tan(_ray()->ra);
		_ray()->dof = 0;
		_ray()->disV = 100000;
		_ray()->v.x = (_player()->x + 5);
		_ray()->v.y = (_player()->y + 5);
		if (_ray()->ra > P2 && _ray()->ra < P3) // if looking left
		{
			_ray()->rx = (((int)(_player()->x + 5) / _img()->scale) * _img()->scale) - 0.0001; // found the next 64px next horintozal line
			_ray()->ry = ((_player()->x + 5) - _ray()->rx) * a_tan +( _player()->y + 5);
			_ray()->xo = -_img()->scale;
			_ray()->yo = -_ray()->xo * a_tan;
		}
		if (_ray()->ra < P2 || _ray()->ra > P3) // if looking right
		{
			_ray()->rx = (((int)(_player()->x + 5) / _img()->scale) * _img()->scale) + _img()->scale; // found the next 64px next horintozal line
			_ray()->ry = ((_player()->x + 5) - _ray()->rx) * a_tan + (_player()->y + 5);
			_ray()->xo = _img()->scale;
			_ray()->yo = -_ray()->xo * a_tan;
		}
		if (_ray()->ra == 0 || _ray()->ra == PI)
		{
			_ray()->ry = (_player()->y + 5);
			_ray()->rx = (_player()->x + 5);
			_ray()->dof = _img()->map_width;
		}
		while (_ray()->dof < _img()->map_width)
		{
			//if (_ray()->mx >= 0 && _ray()->my >= 0 &&_ray()->mx < _img()->map_width && _ray()->my < _img()->map_height)
            //	printf("=> %d, %d, %c, %d, %d\n", _ray()->mx, _ray()->my, _img()->map[_ray()->my][_ray()->mx], (_player()->x + 5) / _img()->scale, _player()->y + 5 / _img()->scale);
			_ray()->mx = (int)(_ray()->rx) / _img()->scale;
			_ray()->my = (int)(_ray()->ry) / _img()->scale;
			_ray()->mp = _ray()->my * _img()->width + _ray()->mx;
			if (_ray()->mx >= 0 && _ray()->my >= 0 &&_ray()->mx < _img()->map_width && _ray()->my < _img()->map_height && 
			_img()->map[_ray()->my][_ray()->mx] == '1')
			{
				_ray()->v = (t_vector2F){_ray()->rx, _ray()->ry};
				_ray()->disV = ray_dist((t_vector2F){(_player()->x + 5), (_player()->y + 5)}, _ray()->v, _ray()->ra);
				_ray()->dof = _img()->map_width;
			}
			else
			{
				_ray()->rx += _ray()->xo;
				_ray()->ry += _ray()->yo;
				_ray()->dof++;
			}
		}
		//plot_line(_player()->x + 5, _player()->y + 5, (int)_ray()->rx, (int)_ray()->ry, _ray()->color);
		if (_ray()->disV > _ray()->disH)
		{
			_ray()->color = 0xFF2D00;
			_ray()->rx = _ray()->h.x;
			_ray()->ry = _ray()->h.y;
			_ray()->disT = _ray()->disH;
		}
		else
		{
			_ray()->color = 0xFF7254;
			_ray()->rx = _ray()->v.x;
			_ray()->ry = _ray()->v.y;
			_ray()->disT = _ray()->disV;
		}
		printf("rx = %d, ry = %d\n", (int)_ray()->rx, (int)_ray()->ry);
		//if (_ray()->ry >= 250)
		//	_ray()->ry = 50;
		plot_line(_player()->x + 5, _player()->y + 5, (int)_ray()->rx, (int)_ray()->ry, _ray()->color);

		// ----- DRAWING 3D ------
		_ray()->ca = _player()->angle - _ray()->ra;
		if (_ray()->ca < 0)
			_ray()->ca += 2 * PI;
		if (_ray()->ca > 2 * PI)
			_ray()->ca -= 2 * PI;
		_ray()->disT = _ray()->disT * cos(_ray()->ca);
		_ray()->line_h = (_img()->scale * WIN_H) / _ray()->disT;
		_ray()->line_o = 300 - _ray()->line_h / 2;
		if (_ray()->line_h > WIN_H)
			_ray()->line_h = WIN_H;
		for (int j = 0; j < 8; j++)
			plot_line(j + i * 8, _ray()->line_o, j + i * 8, _ray()->line_h + _ray()->line_o, _ray()->color);

		_ray()->ra += DR;
		if (_ray()->ra < 0)
			_ray()->ra += 2 * PI;
		if (_ray()->ra > 2 * PI)
			_ray()->ra -= 2 * PI;
		//plot_line(_player()->x, _player()->y, (int)_ray()->rx, (int)_ray()->ry, 0xFFFF0000);
	}


}
