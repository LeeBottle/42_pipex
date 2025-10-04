/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_split_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeolee <byeolee@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:19:42 by byeolee           #+#    #+#             */
/*   Updated: 2025/06/27 18:32:50 by byeolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	args_count(const char *str)
{
	int		count;
	char	quote_kind;

	count = 0;
	quote_kind = 0;
	while (*str)
	{
		while (is_space(*str))
			str++;
		if (*str == '\0')
			break ;
		count++;
		while (*str && (quote_kind || !is_space(*str)))
		{
			if (!quote_kind && is_quote(*str))
				quote_kind = *str;
			else if (quote_kind && *str == quote_kind)
				quote_kind = 0;
			str++;
		}
	}
	return (count);
}

static int	arg_length(const char *str)
{
	int		count;
	char	quote_kind;

	count = 0;
	quote_kind = 0;
	while (str[count] && (quote_kind || !is_space(str[count])))
	{
		if (!quote_kind && is_quote(str[count]))
			quote_kind = str[count++];
		else if (quote_kind && str[count] == quote_kind)
		{
			quote_kind = 0;
			count++;
		}
		else
			count++;
	}
	return (count);
}

static char	*arg_input(const char **str_ptr, char *arg)
{
	const char	*str;
	int			count;
	char		quote_kind;

	str = *str_ptr;
	count = 0;
	quote_kind = 0;
	while (*str && (quote_kind || !is_space(*str)))
	{
		if (!quote_kind && is_quote(*str))
			quote_kind = *str++;
		else if (quote_kind && *str == quote_kind)
		{
			quote_kind = 0;
			str++;
		}
		else
			arg[count++] = *str++;
	}
	arg[count] = '\0';
	*str_ptr = str;
	return (arg);
}

static char	*arg_extract(const char **str_ptr)
{
	const char	*str;
	char		*arg;
	int			len;

	str = *str_ptr;
	while (is_space(*str))
		str++;
	len = arg_length(str);
	arg = malloc(len + 1);
	if (!arg)
		return (NULL);
	arg_input(&str, arg);
	*str_ptr = str;
	return (arg);
}

char	**ft_split_quotes(const char *str)
{
	int		count;
	int		i;
	char	**result;

	count = args_count(str);
	result = malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (i < count)
	{
		result[i] = arg_extract(&str);
		if (!result[i])
		{
			while (i > 0)
				free(result[--i]);
			free(result);
			return (NULL);
		}
		i++;
	}
	result[i] = NULL;
	return (result);
}
