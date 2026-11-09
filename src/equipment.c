/*
 * Jajalaboratory - 器材管理实现
 * Copyright (C) 2024 student25-ch - GPLv3
 */
#include "equipment.h"
#include <stdio.h>
#include <string.h>

const char* equip_type_str(EquipmentType t) {
    switch (t) {
        case EQUIP_CONTAINER: return "容器";
        case EQUIP_HEATING:   return "加热";
        case EQUIP_MEASURE:   return "测量";
        case EQUIP_MIXER:     return "搅拌";
        case EQUIP_TOOL:      return "工具";
        case EQUIP_SUPPORT:   return "支撑";
        case EQUIP_SEPARATOR: return "分离";
        case EQUIP_GAS:       return "气体";
        default:              return "未知";
    }
}

const char* heat_mode_str(HeatMode m) {
    switch (m) {
        case HEAT_NONE:     return "不可加热";
        case HEAT_DIRECT:   return "可直接加热";
        case HEAT_INDIRECT: return "需垫石棉网";
        default:            return "未知";
    }
}

void equip_init(EquipmentList *list) {
    list->count = 0;
    memset(list->items, 0, sizeof(list->items));
}

int equip_add_full(EquipmentList *list, const char *name, const char *desc,
                   EquipmentType type, double cap, double max_temp,
                   HeatMode hm, bool can_react, bool needs_stand,
                   bool is_measuring, double max_liquid_pct) {
    if (list->count >= MAX_ITEMS) return -1;
    Equipment *e = &list->items[list->count];
    e->id = list->count + 1;
    strncpy(e->name, name, MAX_NAME - 1);
    e->name[MAX_NAME - 1] = '\0';
    strncpy(e->desc, desc, MAX_DESC - 1);
    e->desc[MAX_DESC - 1] = '\0';
    e->type = type;
    e->capacity = cap;
    e->max_temp = max_temp;
    e->available = true;
    e->c.heat_mode = hm;
    e->c.can_react = can_react;
    e->c.needs_stand = needs_stand;
    e->c.is_measuring = is_measuring;
    e->c.max_liquid_pct = max_liquid_pct;
    e->c.is_glassware = (type == EQUIP_CONTAINER || type == EQUIP_MEASURE ||
                         type == EQUIP_SEPARATOR || type == EQUIP_GAS);
    return list->count++;
}

int equip_add(EquipmentList *list, const char *name, const char *desc,
              EquipmentType type, double cap, double max_temp) {
    return equip_add_full(list, name, desc, type, cap, max_temp,
                          HEAT_NONE, true, false, false, 0.0);
}

Equipment* equip_find_by_name(EquipmentList *list, const char *name) {
    for (int i = 0; i < list->count; i++)
        if (strcmp(list->items[i].name, name) == 0)
            return &list->items[i];
    return NULL;
}

Equipment* equip_find_by_id(EquipmentList *list, int id) {
    for (int i = 0; i < list->count; i++)
        if (list->items[i].id == id)
            return &list->items[i];
    return NULL;
}

void equip_list_all(const EquipmentList *list) {
    printf("\n========== 器材清单 (%d) ==========\n", list->count);
    printf("%-4s %-14s %-8s %-8s %-10s %s\n",
           "ID", "名称", "类型", "加热", "耐温℃", "约束");
    for (int i = 0; i < list->count; i++) {
        const Equipment *e = &list->items[i];
        char cons[128] = "";
        if (!e->c.can_react) strcat(cons, "[不可反应] ");
        if (e->c.is_measuring) strcat(cons, "[量器] ");
        if (e->c.needs_stand) strcat(cons, "[需铁架台] ");
        printf("%-4d %-14s %-8s %-8s %-10.1f %s\n",
               e->id, e->name, equip_type_str(e->type),
               heat_mode_str(e->c.heat_mode), e->max_temp, cons);
    }
}

const char* equip_check_heat(Equipment *e, double temp, bool has_asbestos) {
    if (!e) return "器材不存在";
    if (e->c.heat_mode == HEAT_NONE)
        return "该器材不能加热（量筒/集气瓶/水槽等）";
    if (temp > e->max_temp && e->max_temp > 0)
        return "超过器材耐温上限";
    if (e->c.heat_mode == HEAT_INDIRECT && !has_asbestos)
        return "需要垫石棉网才能加热（烧杯/烧瓶/锥形瓶）";
    return NULL;
}

const char* equip_check_react(Equipment *e) {
    if (!e) return "器材不存在";
    if (e->c.is_measuring)
        return "量器不能用作反应容器";
    if (!e->c.can_react)
        return "该器材不能用作反应容器";
    return NULL;
}

void equip_free(EquipmentList *list) {
    list->count = 0;
    memset(list->items, 0, sizeof(list->items));
}
