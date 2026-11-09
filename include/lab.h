/*
 * Jajalaboratory - 实验室主控制
 * Copyright (C) 2024 student25-ch - GPLv3
 */
#ifndef LAB_H
#define LAB_H

#include "common.h"
#include "equipment.h"
#include "substance.h"
#include "reaction.h"

typedef struct {
    EquipmentList equips;
    SubstanceList subs;
    ReactionList  reactions;
    char lab_name[MAX_NAME];
} Laboratory;

void lab_init(Laboratory *lab);
void lab_load_default_equipment(Laboratory *lab);
void lab_load_default_substances(Laboratory *lab);
void lab_load_default_reactions(Laboratory *lab);
void lab_load_data_file(Laboratory *lab, const char *path);
void lab_menu(Laboratory *lab);
void lab_free(Laboratory *lab);

#endif
