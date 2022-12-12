#include "../cub3d.h"

void	play_sound(char *sound)
{
	pid_t pid;
	
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
	pid_t pid;
	
	char	*args[] = {"/usr/bin/killall", "afplay", NULL};
	pid = fork();
	if (!pid)
		execvp(args[0], args);
}