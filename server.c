// server.c
#include "g_utils.h"

static sgs_holder *g_holder = NULL;

static void handle_bit(int signum)
{
    static unsigned char byte = 0;
    static int bits_received = 0;
    
    // Add bit to current byte
    if (signum == SIGUSR1)
        byte = byte | (1 << (7 - bits_received));
    
    bits_received++;
    
    // When byte is complete
    if (bits_received == 8)
    {
        update_received_data(g_holder, byte);
        bits_received = 0;
        byte = 0;
    }
    
    // Send acknowledgment to client
    kill(g_holder->proc_id, SIGUSR1);
}

int main(int argc, char **argv)
{
    g_holder = init_ss();
    if (!g_holder)
        return (1);
        
    printf("Server PID: %d\n", getpid());
    
    // Set signal handlers
    signal(SIGUSR1, handle_bit);
    signal(SIGUSR2, handle_bit);
    
    // Wait for signals
    while (1)
    {
        pause();
        if (g_holder->fsgls)
        {
            printf("Received message: %s\n", g_holder->data_received);
            break;
        }
    }
    
    cleanup_signal_holder(g_holder);
    return (0);
}
