#include <stdio.h>
#include <stdbool.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "acsi.pio.h"

#define LED_BUILTIN 25;

int main() {
  stdio_init_all();

  PIO pio = pio0;
  uint state_machine_id = 0;
  uint offset = pio_add_program(pio, &hello_program);

  acsi_cmd_program_init(pio, state_machine_id, offset, LED_BUILTIN, 1);

  while(1) {
    //do nothing
  }
}