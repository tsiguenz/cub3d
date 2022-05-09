/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiguenz <tsiguenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 13:02:25 by tsiguenz          #+#    #+#             */
/*   Updated: 2022/05/09 13:02:26 by tsiguenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cube3d.h"

unsigned int	calc_pixel_colour(const t_data *data, const t_ray *ray, int cnt)
{
	int				x;
	int				y;
	unsigned int	colour;
	t_img			*tex;

	colour = 0;
	tex = get_texture(data, ray);
	x = calc_pixel_index_x(ray, tex, data);
	y = calc_pixel_index_y(ray, cnt, tex);
	if (x >= 0 && y >= 0)
		colour = get_pixel_color_from_texture(x, y, tex);
	return (colour);
}

t_img	*get_texture(const t_data *data, const t_ray *ray)
{
	t_img	*tex;

	tex = data->map->texture[TEXTURE_NO];
	if (ray->wall_orientation == 'E')
		tex = data->map->texture[TEXTURE_EA];
	if (ray->wall_orientation == 'W')
		tex = data->map->texture[TEXTURE_WE];
	if (ray->wall_orientation == 'S')
		tex = data->map->texture[TEXTURE_SO];
	return (tex);
}

unsigned int	get_pixel_color_from_texture(int x, int y, const t_img *tex)
{
	unsigned int	colour;
	char			*current;

	current = &tex->data[x * tex->bpp / 8 + tex->width * y * tex->bpp / 8];
	colour = current[3] << 24 | current[2] << 16 | current[1] << 8 | current[0];
	return (colour);
}

int	calc_pixel_index_x(const t_ray *ray, const t_img *tex, const t_data *data)
{
	int	x;

	if (ray->wall_orientation == 'S')
		x = (int)((float)(ray->x_intersection_world % \
		(int)TILE_SIZE) / TILE_SIZE * ((float) tex->width));
	if (ray->wall_orientation == 'N')
		x = (int)((float)((int)((float)data->map->width \
		* TILE_SIZE - ray->x_intersection_world) % \
		(int)TILE_SIZE) / TILE_SIZE * ((float) tex->width));
	if (ray->wall_orientation == 'W')
		x = (int)((float)(ray->y_intersection_world % \
		(int)TILE_SIZE) / TILE_SIZE * ((float) tex->width));
	if (ray->wall_orientation == 'E')
		x = (int)((float)((int)((float)data->map->height \
		* TILE_SIZE - ray->y_intersection_world) % \
		(int) TILE_SIZE) / TILE_SIZE * ((float) tex->width));
	return (x);
}

int	calc_pixel_index_y(const t_ray *ray, int cnt, const t_img *tex)
{
	int	y;
	int	clipped_headroom;
	int	wall_height_screen_coordinates;

	wall_height_screen_coordinates = \
		ray->y_max_screen_coordinates - ray->y_min_screen;
	clipped_headroom = \
		ray->y_min_clipped_screen - ray->y_min_screen;
	y = (int)((float)tex->height \
		/ (float)wall_height_screen_coordinates \
		* ((float)cnt + (float) clipped_headroom));
	return (y);
}
