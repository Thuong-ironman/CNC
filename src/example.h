/******************************************************************************
Finite State Machine
Project: src/example.dot
Description: Example FSM

Generated by gv_fsm ruby gem, see https://rubygems.org/gems/gv_fsm
gv_fsm version 0.3.2
Generation date: 2022-05-28 12:43:54 +0200
Generated from: src/example.dot
The finite state machine has:
  4 states
  1 transition functions
******************************************************************************/

#ifndef EXAMPLE_H
#define EXAMPLE_H
#include <stdlib.h>

// State data object
// By default set to void; override this typedef or load the proper
// header if you need
typedef struct {
  int count_idle;
  int count_run; 
}state_data_t;

// NOTHING SHALL BE CHANGED AFTER THIS LINE!

// List of states
typedef enum {
  STATE_INIT = 0,  
  STATE_IDLE,  
  STATE_RUN,  
  STATE_STOP,  
  NUM_STATES,
  NO_CHANGE
} state_t;

// State human-readable names
extern const char *state_names[];

// State function and state transition prototypes
typedef state_t state_func_t(state_data_t *data);
typedef void transition_func_t(state_data_t *data);

// State functions

// Function to be executed in state init
// valid return states: STATE_IDLE
state_t do_init(state_data_t *data);

// Function to be executed in state idle
// valid return states: NO_CHANGE, STATE_IDLE, STATE_RUN, STATE_STOP
state_t do_idle(state_data_t *data);

// Function to be executed in state run
// valid return states: NO_CHANGE, STATE_IDLE, STATE_RUN
state_t do_run(state_data_t *data);

// Function to be executed in state stop
// valid return states: NO_CHANGE
state_t do_stop(state_data_t *data);


// List of state functions
extern state_func_t *const state_table[NUM_STATES];


// Transition functions
void reset(state_data_t *data);

// Table of transition functions
extern transition_func_t *const transition_table[NUM_STATES][NUM_STATES];

// state manager
state_t run_state(state_t cur_state, state_data_t *data);

#endif
