/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_process_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeolee <byeolee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 10:52:02 by byeolee           #+#    #+#             */
/*   Updated: 2025/06/30 13:28:47 by byeolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

pid_t	solo_process(char *cmd, char **env, int infile, int outfile)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		exit(1);
	if (pid == 0)
	{
		pipe_func(cmd, env, infile, outfile);
		perror("execve failed");
		exit(1);
	}
	return (pid);
}

pid_t	child_process(char **av, char **env, int *pipefd)
{
	int		infile;
	pid_t	pid;

	infile = open(av[1], O_RDONLY);
	if (infile < 0)
	{
		error_message(av[1], 1);
		infile = open("/dev/null", O_RDONLY);
		if (infile < 0)
		{
			close(infile);
			exit(1);
		}
	}
	pid = fork();
	if (pid < 0)
		exit(1);
	if (pid == 0)
	{
		close(pipefd[0]);
		pipe_func(av[2], env, infile, pipefd[1]);
	}
	close(infile);
	close(pipefd[1]);
	return (pid);
}

pid_t	middle_process(char *cmd, char **env, int prev_read, int *pipefd)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		exit(1);
	if (pid == 0)
	{
		close(pipefd[0]);
		pipe_func(cmd, env, prev_read, pipefd[1]);
	}
	close(prev_read);
	close(pipefd[1]);
	return (pid);
}

pid_t	parents_process(char *cmd, char **env, int prev_read, char *name)
{
	int		outfile;
	pid_t	pid;

	outfile = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile < 0)
	{
		perror("outfile");
		close(prev_read);
		exit(1);
	}
	pid = fork();
	if (pid < 0)
		exit(1);
	if (pid == 0)
		pipe_func(cmd, env, prev_read, outfile);
	close(prev_read);
	close(outfile);
	return (pid);
}
