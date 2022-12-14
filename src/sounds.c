/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sounds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 10:38:00 by smischni          #+#    #+#             */
/*   Updated: 2022/12/14 10:39:41 by smischni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	play_sound(char *sound)
{
	pid_t	pid;
	char	*args[5];

	args[0] = "/usr/bin/afplay";
	args[1] = "--volume";
	args[2] = "1";
	args[3] = sound;
	args[4] = NULL;
	pid = fork();
	if (!pid)
		execvp(args[0], args);
}

void	kill_music(void)
{
	pid_t	pid;
	char	*args[3];

	args[0] = "/usr/bin/killall";
	args[1] = "afplay";
	args[2] = NULL;
	pid = fork();
	if (!pid)
		execvp(args[0], args);
}
