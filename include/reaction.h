/*
 * Jajalaboratory - 反应引擎
 * Copyright (C) 2024 student25-ch - GPLv3
 */
#ifndef REACTION_H
#define REACTION_H

#include "common.h"
#include "equipment.h"
#include "substance.h"

typedef struct {
    Reaction items[MAX_ITEMS];
    int count;
} ReactionList;

void reac_init(ReactionList *list);
int  reac_add_full(ReactionList *list, const char *name, const char *desc,
                   const char **reactants, int rc,
                   const char **products, int pc,
                   double min_temp, double max_temp,
                   int required_equip, bool exothermic, HazardLevel hazard,
                   const char **phenom_steps, int step_count);
int  reac_add(ReactionList *list, const char *name, const char *desc,
              const char **reactants, int rc,
              const char **products, int pc,
              double min_temp, double max_temp,
              int required_equip, bool exothermic, HazardLevel hazard);
Reaction* reac_find_by_name(ReactionList *list, const char *name);
void reac_list_all(const ReactionList *list);
ReactionResult reac_execute(Reaction *r, SubstanceList *subs,
                            EquipmentList *equips, ReactionConditions cond);
void reac_free(ReactionList *list);

#endif
