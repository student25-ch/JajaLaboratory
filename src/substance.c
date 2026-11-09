/*
 * Jajalaboratory - 物质管理实现
 * Copyright (C) 2024 student25-ch - GPLv3
 */
#include "substance.h"
#include <stdio.h>
#include <string.h>

const char* state_str(MatterState s) {
    switch (s) {
        case STATE_SOLID:   return "固态";
        case STATE_LIQUID:  return "液态";
        case STATE_GAS:     return "气态";
        case STATE_AQUEOUS: return "水溶液";
        default:            return "未知";
    }
}

const char* hazard_str(HazardLevel h) {
    switch (h) {
        case HAZARD_NONE:    return "无";
        case HAZARD_LOW:     return "低";
        case HAZARD_MEDIUM:  return "中";
        case HAZARD_HIGH:    return "高";
        case HAZARD_EXTREME: return "极高";
        default:             return "未知";
    }
}

void sub_init(SubstanceList *list) {
    list->count = 0;
    memset(list->items, 0, sizeof(list->items));
}

int sub_add_full(SubstanceList *list, const char *formula, const char *name,
                 MatterState state, HazardLevel hazard, double mass,
                 double density, double mp, const char *storage, bool is_metal) {
    if (list->count >= MAX_ITEMS) return -1;
    Substance *s = &list->items[list->count];
    s->id = list->count + 1;
    strncpy(s->formula, formula, MAX_NAME - 1);
    s->formula[MAX_NAME - 1] = '\0';
    strncpy(s->name, name, MAX_NAME - 1);
    s->name[MAX_NAME - 1] = '\0';
    s->state = state;
    s->hazard = hazard;
    s->mass = mass;
    s->temperature = 25.0;
    s->density = density;
    s->melting_point = mp;
    if (storage) {
        strncpy(s->storage, storage, MAX_NAME - 1);
        s->storage[MAX_NAME - 1] = '\0';
    }
    s->is_metal = is_metal;
    return list->count++;
}

int sub_add(SubstanceList *list, const char *formula, const char *name,
            MatterState state, HazardLevel hazard, double mass) {
    return sub_add_full(list, formula, name, state, hazard, mass,
                        1.0, -1, "", false);
}

Substance* sub_find_by_formula(SubstanceList *list, const char *formula) {
    for (int i = 0; i < list->count; i++)
        if (strcmp(list->items[i].formula, formula) == 0)
            return &list->items[i];
    return NULL;
}

Substance* sub_find_by_name(SubstanceList *list, const char *name) {
    for (int i = 0; i < list->count; i++)
        if (strcmp(list->items[i].name, name) == 0)
            return &list->items[i];
    return NULL;
}

void sub_list_all(const SubstanceList *list) {
    printf("\n========== 物质清单 (%d) ==========\n", list->count);
    printf("%-4s %-10s %-14s %-6s %-4s %-8s %-8s %s\n",
           "ID", "化学式", "名称", "状态", "危险", "质量g", "温度℃", "备注");
    for (int i = 0; i < list->count; i++) {
        const Substance *s = &list->items[i];
        char note[128] = "";
        if (s->is_metal) strcat(note, "[金属] ");
        if (s->storage[0]) { strcat(note, "[保存:"); strcat(note, s->storage); strcat(note, "] "); }
        if (s->melting_point > 0) { char t[32]; snprintf(t, 32, "[熔点%.0f℃]", s->melting_point); strcat(note, t); }
        printf("%-4d %-10s %-14s %-6s %-4s %-8.2f %-8.1f %s\n",
               s->id, s->formula, s->name, state_str(s->state),
               hazard_str(s->hazard), s->mass, s->temperature, note);
    }
}

void sub_free(SubstanceList *list) {
    list->count = 0;
    memset(list->items, 0, sizeof(list->items));
}
