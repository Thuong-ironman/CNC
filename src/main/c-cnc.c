#include "../defines.h"
#include "../machine.h"
#include "../program.h"
#include "../block.h"
#include "../point.h"
#include "../fsm.h"

#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#if 1
 int main(int argc, char const *argv[]) {
   ccnc_state_data_t state_data = {
     .ini_file = "settings.int",
     .prog_file = argv[1],
     .machine =NULL,
     .prog = NULL
   };
  ccnc_state_t cur_state = CCNC_STATE_INIT;
  do {
    cur_state = ccnc_run_state(cur_state, &state_data);
    wait_next(machine_tq(state_data.machine)*1E9);
  } while (cur_state != CCNC_STATE_STOP);
  ccnc_run_state(cur_state, &state_data);
  return 0;
}

#else 


int main(int argc, char const *argv[]) {
  point_t *sp = NULL;
  block_t *b = NULL;
  program_t *p = NULL;
  data_t t, tt, tq, lambda, f;
  machine_t *machine = machine_new("settings.ini");
  if (!machine) {
    eprintf("Error creating machine instance\n");
    exit(EXIT_FAILURE);
  }
  tq = machine_tq(machine);

  p = program_new(argv[1]);
  if (!p) {
    eprintf("Could not create program, exiting.\n");
    exit(EXIT_FAILURE);
  }
  if (program_parse(p, machine) == EXIT_FAILURE) {
    eprintf("Could not parse program in %s, exiting.\n", argv[1]);
    exit(EXIT_FAILURE);
  }
  program_print(p, stderr);

  // main loop
  printf("n,t,tt,lambda,s,f,x,y,z\n");
  tt = 0;
  while ((b = program_next(p))) {
    if (block_type(b) == RAPID || block_type(b) > ARC_CCW) {
      continue;
    }
    eprintf("Interpolating the block %s\n", block_line(b));
    // interpolation loop
    for (t = 0; t <= block_dt(b); t += tq, tt += tq) {
      lambda = block_lambda(b, t, &f);
      sp = block_interpolate(b, lambda);
      if (!sp) continue;
      printf("%lu,%f,%f,%f,%f,%f,%f,%f,%f\n", block_n(b), t, tt,
        lambda, lambda * block_length(b), f,
        point_x(sp), point_y(sp), point_z(sp));
        machine_sync(machine);
    }
  }


  machine_free(machine);
  program_free(p);
  return 0;
}

#endif