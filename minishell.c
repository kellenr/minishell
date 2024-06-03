/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:07:43 by keramos-          #+#    #+#             */
/*   Updated: 2024/06/02 18:55:29 by keramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* this function to continuously receive and process user input */
void	receive_msg(void)
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
		process_cmd(prompt);
		//free(prompt);
	}
}

int	main(int argc, char **argv, char **env)
{
	(void)argv;
	(void)env;
	if (argc != 1)
	{
		ft_printf(P_R"💢\tThis program doesn't need arguments\n"RT);
		exit(0);
	}
	ft_intro_art();
	receive_msg();
	return (0);
}
