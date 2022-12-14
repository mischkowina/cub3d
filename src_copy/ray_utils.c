/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apielasz <apielasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 18:10:05 by apielasz          #+#    #+#             */
/*   Updated: 2022/12/14 18:10:20 by apielasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	calculate_distance(t_data *data)
{
	if (data->cur_ray->ori == 0)
		data->cur_ray->full_dist = \
		data->cur_ray->side_dist.x - data->cur_ray->delta_dist.x;
	else
		data->cur_ray->full_dist = \
		data->cur_ray->side_dist.y - data->cur_ray->delta_dist.y;
}
