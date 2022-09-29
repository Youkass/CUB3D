/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 19:55:08 by denissereno       #+#    #+#             */
/*   Updated: 2022/09/29 22:29:29 by denissereno      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"


float degToRad(int a) { return a*M_PI/180.0;}
int FixAng(int a){ if(a>359){ a-=360;} if(a<0){ a+=360;} return a;}

//void draw_rays()
//{	
// int r,mx,my,mp,dof,side; float vx,vy,rx,ry,ra,xo,yo,disV,disH; 
// (void)side;
// (void)vx;
// (void)disH;
// (void)disV;
// (void)vy;
// ra=FixAng(_player()->angle+30);                                                              //ray set back 30 degrees
 
// for(r=0;r<60;r++)
// {
//  //---Vertical--- 
//  dof=0; side=0; disV=100000;
//  float Tan=tan(degToRad(ra));
//       if(cos(degToRad(ra))> 0.001){ rx=(((int)_player()->x>>6)<<6)+64;      ry=(_player()->x-rx)*Tan+_player()->y; xo= 64; yo=-xo*Tan;}//looking left
//  else if(cos(degToRad(ra))<-0.001){ rx=(((int)_player()->x>>6)<<6) -0.0001; ry=(_player()->x-rx)*Tan+_player()->y; xo=-64; yo=-xo*Tan;}//looking right
//  else { rx=_player()->x; ry=_player()->y; dof=8;}                                                  //looking up or down. no hit  

//  while(dof<8) 
//  { 
//   mx=(int)(rx)>>6; my=(int)(ry)>>6; mp=my*_img()->width+mx;                     
//   if(mp>0 && mp<_img()->width*_img()->height && _img()->map[my][mx]==1){ dof=8; disV=cos(degToRad(ra))*(rx-_player()->x)-sin(degToRad(ra))*(ry-_player()->y);}//hit         
//   else{ rx+=xo; ry+=yo; dof+=1;}                                               //check next horizontal
//  } 
//  vx=rx; vy=ry;

//  //---Horizontal---
//  dof=0; disH=100000;
//  Tan=1.0/Tan; 
//       if(sin(degToRad(ra))> 0.001){ ry=(((int)_player()->y>>6)<<6) -0.0001; rx=(_player()->y-ry)*Tan+_player()->x; yo=-64; xo=-yo*Tan;}//looking up 
//  else if(sin(degToRad(ra))<-0.001){ ry=(((int)_player()->y>>6)<<6)+64;      rx=(_player()->y-ry)*Tan+_player()->x; yo= 64; xo=-yo*Tan;}//looking down
//  else{ rx=_player()->x; ry=_player()->y; dof=8;}                                                   //looking straight left or right
 
//  while(dof<8) 
//  { 
//   mx=(int)(rx)>>6; my=(int)(ry)>>6; mp=my*_img()->width+mx;                          
//   if(mp>0 && mp<_img()->width*_img()->height && _img()->map[my][mx] == '1'){ dof=8; disH=cos(degToRad(ra))*(rx-_player()->x)-sin(degToRad(ra))*(ry-_player()->y);}//hit         
//   else{ rx+=xo; ry+=yo; dof+=1;}                                               //check next horizontal
//  } 
  
////  if(disV<disH){ rx=vx; ry=vy; disH=disV; glColor3f(0,0.6,0);}  
//  plot_line(_player()->x,_player()->y, rx,ry);               //horizontal hit first    
////  int ca=FixAng(pa-ra); disH=disH*cos(degToRad(ca));                            //fix fisheye 
////  int lineH = (mapS*320)/(disH); if(lineH>320){ lineH=320;}                     //line height and limit
////  int lineOff = 160 - (lineH>>1);                                               //line offset
  
////  glLineWidth(8);glBegin(GL_LINES);glVertex2i(r*8+530,lineOff);glVertex2i(r*8+530,lineOff+lineH);glEnd();//draw vertical wall  

//  ra=FixAng(ra-1);                                                              //go to next ray
// }
//}//-----------------------------------------------------------------------------



void	draw_rays(void)
{
	float	a_tan;

	_ray()->ra =_player()->angle;
	for (int i = 0; i < 1; i++)
	{
		// check horizontal lines
		a_tan = -1/tan(_ray()->ra);
		_ray()->dof = 0;
		if (_ray()->ra > PI) // if looking up
		{
			_ray()->ry = (((int)_player()->y / _img()->scale) << _img()->scale) - 0.0001; // found the next 64px next horintozal line
			_ray()->rx = (_player()->y - _ray()->ry) * a_tan + _player()->x;
			_ray()->yo = -_img()->scale;
			_ray()->xo = -_ray()->yo * a_tan;
		}
		if (_ray()->ra < PI) // if looking up
		{
			_ray()->ry = (((int)_player()->y >>  _img()->scale) << _img()->scale) + _img()->scale; // found the next 64px next horintozal line
			_ray()->rx = (_player()->y - _ray()->ry) * a_tan + _player()->x;
			_ray()->yo = _img()->scale;
			_ray()->xo = -_ray()->yo * a_tan;
		}
		if (_ray()->ra == 0 || _ray()->ra == PI)
		{
			_ray()->rx = _player()->x;
			_ray()->ry = _player()->y;
			_ray()->dof = 8;
		}
		while (_ray()->dof < 8)
		{
               printf("%d, %d\n", _ray()->mx, _ray()->my);
			_ray()->mx = (int)(_ray()->rx) / _img()->scale;
			_ray()->my = (int)(_ray()->ry) / _img()->scale;
			_ray()->mp = _ray()->my * _img()->width + _ray()->mx;
			if (_ray()->mx >= 0 && _ray()->my >= 0 &&_ray()->mx < _img()->map_width && _ray()->my < _img()->map_height && 
			_img()->map[_ray()->my][_ray()->mx] == '1')
				_ray()->dof = 8;
			else
			{
				_ray()->rx += _ray()->xo;
				_ray()->ry += _ray()->yo;
				_ray()->dof++;
			}
		}
		plot_line(_player()->x, _player()->y, (int)_ray()->rx, (int)_ray()->ry);
	}
}