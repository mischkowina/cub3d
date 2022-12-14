/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 09:05:21 by smischni          #+#    #+#             */
/*   Updated: 2022/12/14 17:36:49 by smischni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * Opens the .cub file and parses the information line by line, skipping
 * empty lines and checking for invalid input.
 * @param file [char *] String identifying the input file.
 * @param data [t_data *] Pointer to struct storing the input data.
*/
void	parser(char *file, t_data *data)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		ft_error(NULL, data);
	line = get_next_line(fd);
	while (line)
	{
		while (!ft_strncmp(line, "\n", ft_strlen(line)))
		{
			free(line);
			line = get_next_line(fd);
		}
		if (parse_info_type(data, line) == 1)
			break ;
		free(line);
		line = get_next_line(fd);
	}
	if (line && (!ft_strncmp(line, " ", 1) || !ft_strncmp(line, "1", 1)))
		parse_map(data, line, fd);
	else
		ft_error("Invalid or missing input in .cub file.", data);
}

/**
 * Takes a line from the input file and checks for valid identifiers for
 * wall textures or colors and calls the function to parse the respective
 * information. Returns 1 if the line does not start with one of those 
 * identifiers.
 * @param data [t_data *] Pointer to struct storing the input data.
 * @param line [char *] String containing a line from the input file.
 * @return [int] 0 if line contained a valid identifier, else 1.
*/
int	parse_info_type(t_data *data, char *line)
{
	if (line && !ft_strncmp(line, "NO ", 3))
		data->n_texture.filename = parse_texture(line, data);
	else if (line && !ft_strncmp(line, "EA ", 3))
		data->e_texture.filename = parse_texture(line, data);
	else if (line && !ft_strncmp(line, "SO ", 3))
		data->s_texture.filename = parse_texture(line, data);
	else if (line && !ft_strncmp(line, "WE ", 3))
		data->w_texture.filename = parse_texture(line, data);
	else if (line && !ft_strncmp(line, "F ", 2))
		data->col_floor = parse_color(line, data);
	else if (line && !ft_strncmp(line, "C ", 2))
		data->col_ceiling = parse_color(line, data);
	else if (line && !ft_strncmp(line, "DO ", 2))
		data->d_texture.filename = parse_texture(line, data);
	else
		return (1);
	return (0);
}

/**
 * Removes the identifier as well as the newline character from the
 * string line, returning only the path of the texture file. Also
 * checks if the texture is a .xpm file.
 * @param line [char *] String containing texture info from the input file.
 * @param data [t_data *] Pointer to struct storing the input data.
 * @return [char *] String containing the path of a texture file.
*/
char	*parse_texture(char *line, t_data *data)
{
	int		i;
	char	*str;

	i = 2;
	while (line[i] && line[i] == ' ')
		i++;
	if (!line[i] || line[i] == '\n')
		ft_error("Texture input missing", data);
	str = ft_substr(line, i, (ft_strlen(line) - 1 - i));
	if (!str)
		ft_error("Texture: ft_substr failed.", data);
	if (ft_strncmp(&str[ft_strlen(str) - 4], ".xpm", 5))
		ft_error("Textures have to be .xpm files.", data);
	return (str);
}

/**
 * Removes the identifier as well as the newline character from the
 * string line and then splits it by commas to receive 3 strings containing
 * the RGB color values. Calls determine_color_value to transform those 
 * strings into a single integer value for the color.
 * @param [char *] String containing color information from the input file.
 * @param data [t_data *] Pointer to struct storing the input data.
 * @return [int] Integer value representing the color.
*/
int	parse_color(char *line, t_data *data)
{
	int		i;
	char	**split;
	char	*tmp;

	i = 1;
	while (line[i] && line[i] == ' ')
		i++;
	if (!line[i] || line[i] == '\n')
		ft_error("Color input missing.", data);
	tmp = ft_substr(line, i, (ft_strlen(line) - 1 - i));
	split = ft_split(tmp, ',');
	free(tmp);
	if (!split || !split[0])
		ft_error("Invalid input for floor / ceiling color.", data);
	i = 0;
	while (split[i])
		i++;
	if (i != 3)
		ft_error("Invalid input for floor / ceiling color.", data);
	return (determine_color_value(split, data));
}

/**
 * Transforms the 3 strings containing color values into integers and
 * determines the single integer representation of that color.
 * @param split [char **] String array containing the three color values.
 * @param data [t_data *] Pointer to struct storing the input data.
 * @return [int] Integer value representing the color.
*/
int	determine_color_value(char **split, t_data *data)
{
	int	c[3];
	int	i;

	i = 0;
	while (split[i])
	{
		if (!str_is_digit(split[i]))
		{
			free_str_arr(split);
			ft_error("Invalid input for floor / ceiling color.", data);
		}
		c[i] = ft_atoi(split[i]);
		i++;
	}
	free_str_arr(split);
	i = 0;
	while (i < 3)
	{
		if (c[i] < 0 || c[i] > 255)
			ft_error("Invalid input for floor / ceiling color.", data);
		i++;
	}
	return (0 << 24 | c[0] << 16 | c[1] << 8 | c[2]);
}
