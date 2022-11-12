///* ************************************************************************** */
///*                                                                            */
///*                                                        :::      ::::::::   */
///*   new_raycaster.c                                    :+:      :+:    :+:   */
///*                                                    +:+ +:+         +:+     */
///*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
///*                                                +#+#+#+#+#+   +#+           */
///*   Created: 2022/11/05 19:10:12 by denissereno       #+#    #+#             */
///*   Updated: 2022/11/05 19:35:45 by denissereno      ###   ########.fr       */
///*                                                                            */
///* ************************************************************************** */

//#include "../includes/cub.h"

//void	ft_draw_wall2(t_obj wall, t_vector2D pos)
//{
//	t_int	var;

//	var.i = 0;
//	while (var.i < _var()->scale) 
//	{
//		var.j = 0;
//		while (var.j < _var()->scale)
//		{
//			if (is_neighbor(pos))
//				ft_put_pixel_color(_img(), (char [4]){0, 89, 22, 0}, (int)wall.x + var.i,  (int)wall.y + var.j);
//			else
//				ft_put_pixel_color(_img(), (char [4]){0, 15, 255, 0}, (int)wall.x + var.i,  (int)wall.y + var.j);
//			if (var.j == 0 || var.j == _var()->scale - 1 || var.i == 0 ||
//			var.i == _var()->scale - 1)
//				ft_put_pixel_color(_img(), (char [4]){0, 0, 0, 0}, wall.x + var.i,  wall.y + var.j);
//			var.j++;
//		}
//		var.i++;
//	}
//}

//void	ft_draw_floor2(t_obj wall)
//{
//	t_int	var;

//	var.i = 0;
//	while (var.i < _var()->scale) 
//	{
//		var.j = 0;
//		while (var.j < _var()->scale)
//		{
//			ft_put_pixel_color(_img(), (char [4]){255, 255, 255, 0}, (int)wall.x + var.i, (int)wall.y + var.j);
//			if (var.j == 0 || var.j == _var()->scale - 1 || var.i == 0 ||
//			var.i == _var()->scale - 1)
//				ft_put_pixel_color(_img(), (char [4]){0, 0, 0, 0}, (int)wall.x + var.i, (int)wall.y + var.j);
//			var.j++;
//		}
//		var.i++;
//	}
//}

//void	ft_draw_map2(void)
//{
//	t_int		var;
//	t_vector2D	p_pos;

//	var.i = 0;
//	while (var.i < _var()->map_height)
//	{
//		var.j = 0;
//		while (var.j < _var()->map_width)
//		{
//			if (_var()->coord_map[var.i][var.j].id == WALL)
//				ft_draw_wall2(_var()->coord_map[var.i][var.j], (t_vector2D){var.j, var.i});
//			if (_var()->coord_map[var.i][var.j].id == MAP)
//				ft_draw_floor2(_var()->coord_map[var.i][var.j]);
//			if (_var()->coord_map[var.i][var.j].id == PLAYER)
//			{
//				p_pos = (t_vector2D){var.j, var.i};
//				ft_draw_floor2(_var()->coord_map[p_pos.y][p_pos.x]);
//			}
//			var.j++;
//		}
//		var.i++;
//	}
//	DrawCircle(ft_return_xp(), ft_return_yp(), ft_return_radius(), 0xFFFF0000);
//	plot_line(ft_first_vector(), ft_scnd_vector(), 0xcf34eb);
//	//DrawCircle(ft_return_xp_2(), ft_return_yp_2(), ft_return_radius_2(), 0xFFFF0000);
//	mlx_put_image_to_window(_mlx()->mlx, _mlx()->mlx_win, _img()->img, 0, 0);
//}

//void	raycast()
//{
//	ft_draw_map2();
//}