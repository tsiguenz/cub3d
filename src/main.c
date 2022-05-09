/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiguenz <tsiguenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 13:02:44 by tsiguenz          #+#    #+#             */
/*   Updated: 2022/05/09 13:02:45 by tsiguenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cube3d.h"

#ifndef TESTING

void	tear_down_mlx_session(t_data *data, int exit_code)
{
	mlx_loop_end(data->mlx.mlx);
	free_textures(data);
	mlx_destroy_image(data->mlx.mlx, data->mlx.img);
	mlx_destroy_window(data->mlx.mlx, data->mlx.mlx_win);
	mlx_destroy_display(data->mlx.mlx);
	free(data->mlx.mlx);
	free_map(&data->map);
	exit(exit_code);
}

int	render_next_frame(void *data)
{
	move(data);
	rotate(data);
	render_frame(data);
	update_mouse_gun(data);
	return (1);
	(void) data;
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 2)
	{
		ft_bzero(&data, sizeof(t_data));
		data.map = parse(argv[1]);
		if (!data.map)
			return (1);
		data.camera = init_camera();
		data.player = init_player(data.map);
		if (init_mlx(&data))
			return (free_map(&data.map) == NULL);
		if (init_textures(&data))
			tear_down_mlx_session(&data, 1);
		remove_interior_walls(&data);
		data.mouse_gun.is_activated = 0;
		render_frame(&data);
		mlx_hook(data.mlx.mlx_win, 2, 1L << 0, &handle_key_press, &data);
		mlx_hook(data.mlx.mlx_win, 3, 1L << 1, &handle_key_release, &data);
		mlx_hook(data.mlx.mlx_win, 33, 1L << 17, red_cross_handler, &data);
		mlx_loop_hook(data.mlx.mlx, render_next_frame, &data);
		mlx_loop(data.mlx.mlx);
	}
	ft_putendl_fd("Error\nBad number of arguments (./cub3d [map_name.cub]", 2);
	return (0);
}

#endif
