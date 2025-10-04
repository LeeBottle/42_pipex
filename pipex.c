/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeolee <byeolee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:17:50 by byeolee           #+#    #+#             */
/*   Updated: 2025/06/27 16:53:16 by byeolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	int		pipefd[2];
	pid_t	pid[2];

	setup_process(ac, pipefd);
	pid[0] = child_process(av, env, pipefd);
	pid[1] = parents_process(av, env, pipefd);
	close_all(pipefd, pid);
	exit(0);
}
