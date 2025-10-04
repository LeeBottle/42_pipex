/* ************************************************************************** */
/*`                                                                        */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeolee <byeolee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:36:53 by byeolee           #+#    #+#             */
/*   Updated: 2025/02/07 11:30:57 by byeolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	textstatic_has_newline(char *textstatic)
{
	int	i;

	i = 0;
	if (!textstatic)
		return (0);
	while (textstatic[i])
	{
		if (textstatic[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static void	textstatic_update(char **textstatic, char *buffer)
{
	char	*temp;

	temp = ft_strjoin(*textstatic, buffer);
	if (!temp)
	{
		free(*textstatic);
		*textstatic = NULL;
		return ;
	}
	free(*textstatic);
	*textstatic = temp;
}

static void	textfd_reading(int fd, char **textstatic)
{
	ssize_t	bytesread;
	char	*buffer;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return ;
	while (1)
	{
		bytesread = read(fd, buffer, BUFFER_SIZE);
		if (bytesread < 0)
		{
			free(*textstatic);
			*textstatic = NULL;
			break ;
		}
		if (bytesread == 0)
			break ;
		buffer[bytesread] = '\0';
		if (!*textstatic)
			*textstatic = ft_strdup("");
		textstatic_update(textstatic, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
}

static void	textstatic_save(char **textstatic, char **textreturn)
{
	char	*temp;
	int		i;

	if (!textstatic || !*textstatic)
		return ;
	i = 0;
	while ((*textstatic)[i] != '\n' && (*textstatic)[i] != '\0')
		i++;
	if ((*textstatic)[i] == '\n')
	{
		*textreturn = ft_substr(*textstatic, 0, i + 1);
		temp = ft_substr(*textstatic, i + 1, ft_strlen(*textstatic) - (i + 1));
	}
	else
	{
		*textreturn = ft_substr(*textstatic, 0, ft_strlen(*textstatic));
		temp = NULL;
	}
	free(*textstatic);
	*textstatic = temp;
	if (!temp)
		*textstatic = NULL;
}

char	*get_next_line(int fd)
{
	static char	*textstatic;
	char		*textreturn;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!textstatic_has_newline(textstatic))
		textfd_reading(fd, &textstatic);
	if (!textstatic || *textstatic == '\0')
	{
		free(textstatic);
		textstatic = NULL;
		return (NULL);
	}
	textstatic_save(&textstatic, &textreturn);
	return (textreturn);
}
