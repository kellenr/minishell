/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fibarros <fibarros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 15:00:54 by fibarros          #+#    #+#             */
/*   Updated: 2024/07/08 16:33:12 by fibarros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

// // Function prototypes for tests
// void test_init_env(void);
// void test_create_env_node(void);
// void test_add_env_node(void);
// void test_init_arr_and_list(void);

void print_env_list(t_env *env_list) 
{
	while (env_list) {
		printf("%s=%s\n", env_list->name, env_list->value);
		env_list = env_list->next;
	}
}

// int main(void) 
// {
// 	test_init_env();
// 	// test_create_env_node();
// 	// test_add_env_node();
// 	// test_init_arr_and_list();

// 	return 0;
// }

// void test_init_env(void) 
// {
// 	t_cmd cmd;
// 	char *envp[] = {"PATH=/usr/bin", "HOME=/home/user", "SHELL=/bin/bash", NULL};

// 	cmd.env = NULL;
// 	cmd.env_list = NULL;

// 	if (init_env(&cmd, envp) == NULL) {
// 		printf("test_init_env: Environment initialized successfully.\n");
// 		printf("test_init_env: Environment variables:\n");
// 		for (int i = 0; cmd.env[i]; i++) {
// 			printf("%s\n", cmd.env[i]);
// 		}
// 		printf("test_init_env: Environment list:\n");
// 		print_env_list(cmd.env_list);
// 	} else {
// 		printf("test_init_env: Failed to initialize environment.\n");
// 	}
// 	free_env(&cmd);
// }

// void test_create_env_node(void)
// {
// 	const char *env_str = "TEST_VAR=test_value";
// 	t_env *node = create_env_node(env_str);
// 	if (node) {
// 		printf("test_create_env_node: Node created successfully.\n");
// 		printf("Name: %s, Value: %s\n", node->name, node->value);
// 		free(node->name);
// 		free(node->value);
// 		free(node);
// 	} else {
// 		printf("test_create_env_node: Failed to create node.\n");
// 	}
// }

// void test_add_env_node(void) 
// {
// 	t_env *env_list = NULL;
// 	t_env *node1 = create_env_node("VAR1=value1");
// 	t_env *node2 = create_env_node("VAR2=value2");
// 	t_env *node3 = create_env_node("VAR3=value3");

// 	if (node1 && node2 && node3) {
// 		add_env_node(&env_list, node1);
// 		add_env_node(&env_list, node2);
// 		add_env_node(&env_list, node3);

// 		printf("test_add_env_node: Nodes added to list:\n");
// 		print_env_list(env_list);
// 	} else {
// 		printf("test_add_env_node: Failed to create nodes for list.\n");
// 	}

// 	// Free the list
// 	free_env_list(env_list);
// }

// void test_init_arr_and_list(void) 
// {
// 	t_cmd cmd;
// 	char *envp[] = {"USER=me", "HOME=/home/me", "SHELL=/bin/sh", NULL};

// 	cmd.env = NULL;
// 	cmd.env_list = NULL;

// 	if (init_env(&cmd, envp) == NULL) {
// 		printf("test_init_arr_and_list: Array and list initialized successfully.\n");
// 		printf("test_init_arr_and_list: Environment variables:\n");
// 		for (int i = 0; cmd.env[i]; i++) {
// 			printf("%s\n", cmd.env[i]);
// 		}
// 		printf("test_init_arr_and_list: Environment list:\n");
// 		print_env_list(cmd.env_list);
// 	} else {
// 		printf("test_init_arr_and_list: Failed to initialize array and list.\n");
// 	}

// 	free_env(&cmd);
// }
