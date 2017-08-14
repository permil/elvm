#include <ir/ir.h>
#include <target/util.h>
#include <stdlib.h>

static void hxg_init_state(Data* data, char** hxgInst) {
  for (int mp = 0; data; data = data->next, mp++) {
    if (data->v) {
      sprintf(*hxgInst, "%s, %d", *hxgInst, data->v);
    }
  }
}

void target_hxg(Module* module) {
    char *hxgInst = (char *)malloc(sizeof(char) * 65536);
    hxg_init_state(module->data, &hxgInst);
    emit_line(hxgInst);
}
