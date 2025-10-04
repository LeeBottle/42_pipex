/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeolee <byeolee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:17:50 by byeolee           #+#    #+#             */
/*   Updated: 2025/06/30 13:43:56 by byeolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	single_process(char **av, char **env)
{
	int		infile;
	int		outfile;
	pid_t	pid;

	infile = open(av[1], O_RDONLY);
	if (infile < 0)
	{
		error_message(av[1], 1);
		infile = open("/dev/null", O_RDONLY);
		if (infile < 0)
			exit(1);
	}
	outfile = open(av[3], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile < 0)
	{
		perror("outfile");
		close(infile);
		exit(1);
	}
	pid = solo_process(av[2], env, infile, outfile);
	close(infile);
	close(outfile);
	waitpid(pid, NULL, 0);
}

static void	processes(int ac, char **av, char **env)
{
	int		i;
	int		pipefd[2];
	int		prev_read;
	pid_t	*pid;

	if (!commands_checker(ac, av, env, 0))
		return ;
	pid = malloc(sizeof(pid_t) * (ac - 3));
	if (!pid)
		return ;
	pipe(pipefd);
	pid[0] = child_process(av, env, pipefd);
	prev_read = pipefd[0];
	i = 3;
	while (i < ac - 2)
	{
		pipe(pipefd);
		pid[i - 2] = middle_process(av[i], env, prev_read, pipefd);
		prev_read = pipefd[0];
		i++;
	}
	pid[i - 2] = parents_process(av[ac - 2], env, prev_read, av[ac - 1]);
	free_pid(pipefd, pid, ac - 3);
}

int	main(int ac, char **av, char **env)
{
	if (ac < 4)
		exit(1);
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
		here_doc_process(ac, av, env);
	else if (ac == 4)
		single_process(av, env);
	else
		processes(ac, av, env);
	exit(0);
}
