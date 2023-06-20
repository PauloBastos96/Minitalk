/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:31:58 by paulorod          #+#    #+#             */
/*   Updated: 2023/06/20 12:40:00 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*Join received character to final string*/
char	*join_char(char *str, char c)
{
	char	*join;
	char	character[2];

	if (!str)
		str = ft_calloc(sizeof(char *), 1);
	character[0] = c;
	character[1] = 0;
	join = ft_strjoin(str, character);
	free(str);
	str = NULL;
	return (join);
}

/*Print message*/
void	print_message(char *str, pid_t pid)
{
	ft_printf("%s\n", str);
	free(str);
	kill(pid, SIGUSR2);
}

/*Receive signals from clients as binary (SIGUSR1 = 0s & SIGUSR2 = 1s)
Convert the signals to characters and print them*/
static void	receive_data(int signum, siginfo_t *info, void *context)
{
	static int		i = 0;
	static char		*str = NULL;
	static char		character;

	(void)context;
	character |= (signum == SIGUSR2);
	if (++i == 8)
	{
		i = 0;
		if (!character)
		{
			print_message(str, info->si_pid);
			str = NULL;
			return ;
		}
		str = join_char(str, character);
		character = 0;
	}
	else
		character <<= 1;
}

/*Initialize server*/
int	main(void)
{
	struct sigaction	sa;

	ft_printf("Server started with PID: %s%i%s\n", CYAN, getpid(), RESET);
	sa.sa_sigaction = receive_data;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		ft_printf("%s[ERROR] Failed to assign signal handlers!%s\n", RED, RESET);
		return (1);
	}
	while (true)
		pause();
	return (0);
}
