#include <ir/ir.h>
#include <target/util.h>
#include <stdlib.h>
#include <string.h>

static void hxg_init_state(Data* data, char** hxgInst) {
  int mp;
  sprintf(*hxgInst, "%s}", *hxgInst);
  for (mp = 0; data; data = data->next, mp++) {
    if (data->v) {
      sprintf(*hxgInst, "%s%d", *hxgInst, data->v);
    }
    sprintf(*hxgInst, "%s{", *hxgInst);
  }
  sprintf(*hxgInst, "%s=", *hxgInst);
  for (; mp != 0; mp--) {
    sprintf(*hxgInst, "%s{}", *hxgInst);
  }
  sprintf(*hxgInst, "%s{=", *hxgInst);
}

static void hxg_emit_inst(Inst* inst, char** hxgInst) {
  switch (inst->op) {
  case PUTC:
    if (inst->src.type == REG) {
      // TODO: correct handling, by using inst->reg
      sprintf(*hxgInst, "%s%d;", *hxgInst, 43); // TODO: reset to 0
    } else {
      sprintf(*hxgInst, "%s%d;", *hxgInst, inst->src.imm); // TODO: reset to 0
    }
    break;

  case EXIT:
    sprintf(*hxgInst, "%s@", *hxgInst);
    break;

  default:
    break;
//    error("oops");
  }
}

void target_hxg(Module* module) {
    char *hxgInst = (char *)malloc(sizeof(char) * 65536);
    hxg_init_state(module->data, &hxgInst);
    for (Inst *inst = module->text; inst; inst = inst->next) {
      hxg_emit_inst(inst, &hxgInst);
    }

    // TODO:
    uint len = strlen(hxgInst);
    int size = (int)((len + 2) / 2);
    for (int i = size; i < size * 2 - 1; i++) {
      for (int j = 0; j < size * 2 - i - 1; j++) { putchar(' '); }
      for (int j = 0; j < i; j++) {
        putchar('.');
        if (j != i - 1) { putchar(' '); }
      }
      emit_line("");
    }

    {
      char line[(size * 2 - 1) * 2];
      for (int i = 0; i < size * 2 - 1; i++) {
        line[i * 2] = ((int)len > i) ? hxgInst[i] : '.';
        line[i * 2 + 1] = ' ';
      }
      line[(size * 2 - 1) * 2 - 1] = '\0';
      emit_line(line);
    }

    for (int i = size * 2 - 2; i >= size; i--) {
      for (int j = 0; j < size * 2 - i - 1; j++) { putchar(' '); }
      for (int j = 0; j < i; j++) {
        putchar('.');
        if (j != i - 1) { putchar(' '); }
      }
      emit_line("");
    }
}
