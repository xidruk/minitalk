#include "g_utils.h"


// init_ss : init signal struct
// signal_h : signal holder
// set_data_ts : set data to send 

int get_data_len(char *data)
{
	int _data_len;

	_data_len = 0;
	if (!data)
		return (0);
	while (data[_data_len])
		_data_len++;
	return (_data_len);
}

sgs_holder *init_ss(void)
{
	sgs_holder *signal_h;

	signal_h = malloc(sizeof(sgs_holder));
	if (!signal_h)
		return (NULL);
	signal_h->data_t0_send = NULL;
	signal_h->data_received = NULL;
	signal_h->current_ss = 0;
	signal_h->fsgls = 0;
	signal_h->data_size_s = 0;
	signal_h->data_size_r = 0;
	signal_h->proc_id = 0;

	return (signal_h);
}


int update_received_data(sgs_holder *signal_h, char c)
{
    if (!signal_h)
        return (0);
    signal_h->data_received = stack_0f_bytes(signal_h->data_received, c);
    if (!signal_h->data_received)
        return (0);
    signal_h->data_size_r++;

    if (signal_h->data_size_r == signal_h->data_size_s)
        signal_h->fsgls = 1;

    return (1);
}

int set_data_ts(sgs_holder *signal_h, char *data)
{
	if (!signal_h || !data)
		return (0);
	signal_h->data_t0_send = data;
	signal_h->data_size_s = get_data_len(data);

	return (1);
}

void cleanup_signal_holder(sgs_holder *signal_h)
{
    if (!signal_h)
        return;
    if (signal_h->data_received)
        free(signal_h->data_received);
    free(signal_h);
}

int is_transmission_complete(sgs_holder *signal_h)
{
    if (!signal_h)
        return (0);
    return (signal_h->fsgls && signal_h->data_size_r == signal_h->data_size_s);
}

int set_process_id(sgs_holder *signal_h, int pid)
{
    if (!signal_h || pid <= 0)
        return (0);
    signal_h->proc_id = pid;
    return (1);
}

void reset_signal_state(sgs_holder *signal_h)
{
    if (!signal_h)
        return;
    signal_h->current_ss = 0;
}
