/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:07:43 by keramos-          #+#    #+#             */
/*   Updated: 2024/08/11 16:25:05 by keramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile __sig_atomic_t	g_signal = 0;

void	receive_msg(t_msh *msh)
{
	char	*prompt;

	while (1)
	{
		handle_signals();
		prompt = read_input();
		if (!prompt)
		{
			ft_printf("Exit\n");
			break ;
		}
		process_cmd(prompt, msh);
		free(prompt);
	}
}

/* Added init_msh function because of updating the environment*/
int	main(int argc, char **argv, char **env)
{
	t_msh	*msh;

	(void)argv;
	msh = ft_calloc(1, sizeof(t_msh));
	if (!msh)
		ft_error("Memory allocation error");
	init_msh(env, msh);
	if (argc != 1)
	{
		ft_printf(P_R"💢\tThis program doesn't need arguments\n"RT);
		exit(0);
	}
	ft_intro_art();
	receive_msg(msh);
	free_all(msh);
	rl_clear_history();
	return (0);
}

int	init_msh(char **env, t_msh *msh)
{
	int	i;

	msh->env = ft_calloc((array_len(env) + 1), sizeof(char *));
	if (!msh->env)
	{
		ft_error("Memory allocation error");
		return (1);
	}
	i = 0;
	while (env[i])
	{
		msh->env[i] = ft_strdup(env[i]);
		if (!msh->env[i])
		{
			free_array(msh->env, i);
			return (1);
		}
		i++;
	}
	msh->env[i] = NULL;
	msh->heredoc_flag = 0;
	return (0);
}

void	free_all(t_msh *msh)
{
	free_msh(msh);
}
