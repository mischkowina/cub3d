#include "../cub3d.h"

void	background_music(void)
{
	pid_t pid;

	char	*args[] = {"/usr/bin/afplay", "--volume", "1", \
			"sounds/shimmering_sands.mp3", NULL};

	pid = fork();
	if (pid < 0)
		ft_error("Playing background music failed.");
	if (!pid)
	{
		execvp(args[0], args);
	}
}
