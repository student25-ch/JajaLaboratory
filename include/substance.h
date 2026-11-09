/*
 * Jajalaboratory - 物质管理
 * Copyright (C) 2024 student25-ch - GPLv3
 */
#ifndef SUBSTANCE_H
#define SUBSTANCE_H

#include "common.h"

typedef struct {
    Substance items[MAX_ITEMS];
    int count;
} SubstanceList;

void sub_init(SubstanceList *list);
int  sub_add_full(SubstanceList *list, const char *formula, const char *name,
                  MatterState state, HazardLevel hazard, double mass,
                  double density, double mp, const char *storage, bool is_metal);
int  sub_add(SubstanceList *list, const char *formula, const char *name,
             MatterState state, HazardLevel hazard, double mass);
Substance* sub_find_by_formula(SubstanceList *list, const char *formula);
Substance* sub_find_by_name(SubstanceList *list, const char *name);
void sub_list_all(const SubstanceList *list);
const char* state_str(MatterState s);
const char* hazard_str(HazardLevel h);
void sub_free(SubstanceList *list);

#endif
