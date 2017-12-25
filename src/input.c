#include "wolf3d.h"

int		key_hook(int key, t_env *e)
{
	if (key == ECHAP_KEY)
		checkout(e, "Bye bye !");
	else if (key == W_KEY || key == S_KEY)
		move(e, key);
	else if (key == A_KEY || key == D_KEY)
		strafe(e, key);
	else if (key == RIGHT_KEY || key == LEFT_KEY)
		rotate(e, key);
	else
		ft_printf("Pressed : [%d]\n", key);
	render(e);
	return (0);
}

int		key_pressed(int key, t_env *e)
{
	if (key == ECHAP_KEY)
		checkout(e, "Bye bye !");
	else if (key == W_KEY)
		e->event |= MOVE_FORWARD;
	else if (key == S_KEY)
		e->event |= MOVE_BACKWARD;
	else if (key == A_KEY)
		e->event |= STRAFE_LEFT;
	else if (key == D_KEY)
		e->event |= STRAFE_RIGHT;
	else if (key == RIGHT_KEY)
		e->event |= ROTATE_RIGHT;
	else if (key == LEFT_KEY)
		e->event |= ROTATE_LEFT;
	else
		ft_printf("Pressed : [%d]\n", key);
	return (0);
}

int		key_released(int key, t_env *e)
{
	if (key == W_KEY)
		e->event ^= MOVE_FORWARD;
	else if (key == S_KEY)
		e->event ^= MOVE_BACKWARD;
	else if (key == A_KEY)
		e->event ^= STRAFE_LEFT;
	else if (key == D_KEY)
		e->event ^= STRAFE_RIGHT;
	else if (key == RIGHT_KEY)
		e->event ^= ROTATE_RIGHT;
	else if (key == LEFT_KEY)
		e->event ^= ROTATE_LEFT;
	else
		ft_printf("Released : [%d]\n", key);
	return (1);
}

int		key_loop(t_env *e)
{
	if (e->event & MOVE_FORWARD)
		move(e, W_KEY);
	if (e->event & MOVE_BACKWARD)
	 	move(e, S_KEY);
	if (e->event & STRAFE_LEFT)
		strafe(e, A_KEY);
	if (e->event & STRAFE_RIGHT)
		strafe(e, D_KEY);
	if (e->event & ROTATE_RIGHT)
		rotate(e, RIGHT_KEY);
	if (e->event & ROTATE_LEFT)
		rotate(e, LEFT_KEY);
	render(e);
	return (1);
}
