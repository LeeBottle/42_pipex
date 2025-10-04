/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeolee <byeolee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:19:07 by byeolee           #+#    #+#             */
/*   Updated: 2025/06/30 12:43:44 by byeolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_message(char *input, int type)
{
	if (type == 1)
	{
		write(2, "zsh: no such file or directory: ", 32);
		write(2, input, ft_strlen(input));
		write(2, "\n", 1);
	}
	if (type == 2)
	{
		write(2, "zsh: command not found: ", 24);
		write(2, input, ft_strlen(input));
		write(2, "\n", 1);
	}
}

void	setup_process(int ac, int *pipefd)
{
	if (ac < 5 || ac > 5)
	{
		write(2, "zsh: parse error near '\\n'\n", 28);
		exit(1);
	}
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(1);
	}
}

char	*get_cmd_fullpath(char **paths, char *cmd)
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

void	pipe_func(char *cmd, char **env, int infile, int outfile)
{
	char	**cmd_args;
	char	*cmd_path;

	cmd_args = ft_split_quotes(cmd);
	if (dup2(infile, STDIN_FILENO) == -1)
	{
		perror("dup2 infile");
		exit(1);
	}
	if (dup2(outfile, STDOUT_FILENO) == -1)
	{
		perror("dup2 outfile");
		exit(1);
	}
	cmd_path = get_cmd_path(cmd_args[0], env);
	if (!cmd_path || cmd_args[0] == NULL)
	{
		error_message(cmd_args[0], 2);
		free_split(cmd_args);
		exit(127);
	}
	execve(cmd_path, cmd_args, env);
	free(cmd_path);
	free_split(cmd_args);
	exit(0);
}
