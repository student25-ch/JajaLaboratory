/*
 * Jajalaboratory - 器材管理
 * Copyright (C) 2024 student25-ch - GPLv3
 */
#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include "common.h"

typedef struct {
    Equipment items[MAX_ITEMS];
    int count;
} EquipmentList;

void equip_init(EquipmentList *list);
int  equip_add_full(EquipmentList *list, const char *name, const char *desc,
                    EquipmentType type, double cap, double max_temp,
                    HeatMode hm, bool can_react, bool needs_stand,
                    bool is_measuring, double max_liquid_pct);
int  equip_add(EquipmentList *list, const char *name, const char *desc,
               EquipmentType type, double cap, double max_temp);
Equipment* equip_find_by_name(EquipmentList *list, const char *name);
Equipment* equip_find_by_id(EquipmentList *list, int id);
void equip_list_all(const EquipmentList *list);
const char* equip_type_str(EquipmentType t);
const char* heat_mode_str(HeatMode m);
const char* equip_check_heat(Equipment *e, double temp, bool has_asbestos);
const char* equip_check_react(Equipment *e);
void equip_free(EquipmentList *list);

#endif
