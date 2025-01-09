// client.c
#include "g_utils.h"

static sgs_holder *g_holder = NULL;

static void handle_response(int signum)
{
    if (signum == SIGUSR1)
        g_holder->current_ss = 1;
}

static void send_bits(unsigned char byte)
{
    int bit_index;
    
    bit_index = 7;
    while (bit_index >= 0)
    {
        g_holder->current_ss = 0;
        
        // Send bit
        if ((byte >> bit_index) & 1)
            kill(g_holder->proc_id, SIGUSR1);
        else
            kill(g_holder->proc_id, SIGUSR2);
            
        // Wait for server acknowledgment
        while (g_holder->current_ss == 0)
            usleep(50);
            
        bit_index--;
    }
}

int main(int argc, char **argv)
{
    int i;
    
    if (argc != 3)
        return (write(2, "Usage: ./client server_pid string\n", 33), 1);
    
    g_holder = init_ss();
    if (!g_holder)
        return (1);
    
    // Setup signal handler for server response
    signal(SIGUSR1, handle_response);
    
    // Set server PID and string to send
    if (!set_process_id(g_holder, atoi(argv[1])))
        return (1);
    if (!set_data_ts(g_holder, argv[2]))
        return (1);
    
    // Send string byte by byte
    i = 0;
    while (g_holder->data_t0_send[i])
    {
        send_bits(g_holder->data_t0_send[i]);
        i++;
    }
    
    cleanup_signal_holder(g_holder);
    return (0);
}
