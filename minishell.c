/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fibarros <fibarros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:07:43 by keramos-          #+#    #+#             */
/*   Updated: 2024/07/10 15:04:01 by fibarros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* this function to continuously receive and process user input */
void	receive_msg(t_msh *msh)
{
	char	*prompt;

	while (1)
	{
		prompt = read_input();
		if (!prompt)
		{
			ft_printf("Exit\n");
			break ;
		}
		process_cmd(prompt, msh);
	}
}

/* Added init_msh function because of updating the environment*/

int	main(int argc, char **argv, char **env)
{
	t_msh	*msh;

	(void)argv;
	msh = calloc(1, sizeof(t_msh));
	if (!msh)
		ft_error("Memory allocation error");
	init_msh(env, msh);
	if (argc != 1)
	{
		ft_printf(P_R"💢\tThis program doesn't need arguments\n"RT);
		exit(0);
	}
	ft_intro_art();
	// receive_msg(&msh);
	receive_msg(msh);
	// free msh here
	return (0);
}

int	init_msh(char **env, t_msh *msh)
{
	int	i;

	msh->env = ft_calloc((array_len(env) + 1), sizeof(char *));
	i = 0;
	if (!msh->env)
		ft_error("Memory allocation error");
	while (env[i])
	{
		msh->env[i] = ft_strdup(env[i]);
		if (!msh->env[i])
			return (-1);
		i++;
	}
	msh->env[i] = NULL;
	return (0);
}
