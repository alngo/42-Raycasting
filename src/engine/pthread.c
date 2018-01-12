#include "wolf3d.h"

static void		thread_init_data(t_env *e, t_thread_data data[NUM_THREADS])
{
	int		i;
	int		diff;
	int		ret;
	int		start;

	i = 0;
	start = 0;
	diff = WIDTH / NUM_THREADS;
	ret = WIDTH % NUM_THREADS;
	while (i < NUM_THREADS)
	{
		data[i].e = e;
		data[i].id = i;
		data[i].start = start;
		data[i].stop = start + diff;
		start = data[i].stop;
		i++;
	}
	data[i - 1].stop += ret;
}

static void		*thread_render_part(void *data)
{
	t_thread_data	*arg;
	int		stop;
	int		x;

	arg = (t_thread_data *)data;
	x = arg->start;
	stop = arg->stop;
	while (x < stop)
	{
		ray_cast(arg->e, x, arg->id);
		line_cast(arg->e, x, arg->id);
		floor_cast(arg->e, x, arg->id);
		x++;
	}
	pthread_exit(NULL);
}

static void		thread_create(t_env *e, t_thread *t)
{
	int		i;
	int		ret;

	thread_init_data(e, t->thread_data);
	pthread_attr_init(&t->attr);
	pthread_attr_setdetachstate(&t->attr, PTHREAD_CREATE_JOINABLE);
	i = 0;
	while (i < NUM_THREADS)
	{
		ret = pthread_create(&t->thread[i], &t->attr, thread_render_part, &t->thread_data[i]);
		if (ret)
			checkout(e, "pthread_create() error.");
		i++;
	}
	pthread_attr_destroy(&t->attr);
}

static void		thread_join(t_env *e, t_thread *t)
{
	int		i;
	int		ret;

	i = 0;
	while (i < NUM_THREADS)
	{
		ret = pthread_join(t->thread[i], &t->status);
		if (ret)
			checkout(e, "pthread_join() error.");
		i++;
	}
}

void			thread_process(t_env *e, t_thread *t)
{
	thread_create(e, t);
	thread_join(e, t);
}
