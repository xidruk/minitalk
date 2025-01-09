#ifndef G_UTILS_HEADER
#define G_UTILS_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

/*
FILE MAP :
-> current_ss : current signal state; 
-> fsgls : final signal state;
-> 
->
->

*/

typedef unsigned int uint_dt;
typedef unsigned long long int ulint_dt;
typedef long long int lint_dt;
typedef char s_dt;
typedef int int_dt;
typedef void Nothing;


typedef struct signal_s_holder
{
	s_dt *data_t0_send;
	s_dt *data_received;
	int_dt current_ss;
	int_dt fsgls;
	int_dt data_size_s;
	int_dt data_size_r;
	int_dt proc_id;
} sgs_holder;


// functions !

char *stack_0f_bytes(char *co_of_bytes, char c);


// signal handler struct funcs 

int get_data_len(char *data);
sgs_holder *init_ss(void);
int update_received_data(sgs_holder *signal_h, char c);
int set_data_ts(sgs_holder *signal_h, char *data);
void cleanup_signal_holder(sgs_holder *signal_h);
int is_transmission_complete(sgs_holder *signal_h);
int set_process_id(sgs_holder *signal_h, int pid);
void reset_signal_state(sgs_holder *signal_h);

#endif
