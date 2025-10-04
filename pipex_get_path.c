/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_get_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeolee <byeolee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:46:10 by byeolee           #+#    #+#             */
/*   Updated: 2025/06/30 13:47:05 by byeolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	*get_cmd_fullpath(char **paths, char *cmd)
{
	char	*tmp;
	char	*full_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*get_cmd_path(char *cmd, char **env)
{
	char	*path_env;
	char	*full_path;
	char	**paths;
	int		i;

	if (!env || cmd == NULL)
		return (NULL);
	path_env = NULL;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path_env = env[i] + 5;
			break ;
		}
		i++;
	}
	if (!path_env)
		path_env = "/usr/local/sbin:/usr/local/\
bin:/usr/sbin:/usr/bin:/sbin:/bin";
	paths = ft_split(path_env, ':');
	full_path = get_cmd_fullpath(paths, cmd);
	free_split(paths);
	return (full_path);
}

int	commands_checker(int ac, char **av, char **env, int type)
{
	int		i;
	int		j;
	char	**cmd_args;
	char	*cmd_path;

	i = 2 + type;
	j = 0;
	while (i < ac - 1)
	{
		cmd_args = ft_split_quotes(av[i]);
		cmd_path = get_cmd_path(cmd_args[0], env);
		if (!cmd_path || cmd_args[0] == NULL)
		{
			error_message(cmd_args[0], 2);
			j++;
		}
		free(cmd_path);
		free_split(cmd_args);
		i++;
	}
	if (j > 0)
		return (0);
	return (1);
}
