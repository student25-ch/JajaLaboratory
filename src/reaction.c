/*
 * Jajalaboratory - 反应引擎实现
 * Copyright (C) 2024 student25-ch - GPLv3
 */
#include "reaction.h"
#include <stdio.h>
#include <string.h>

void reac_init(ReactionList *list) {
    list->count = 0;
    memset(list->items, 0, sizeof(list->items));
}

int reac_add_full(ReactionList *list, const char *name, const char *desc,
                  const char **reactants, int rc,
                  const char **products, int pc,
                  double min_temp, double max_temp,
                  int required_equip, bool exothermic, HazardLevel hazard,
                  const char **phenom_steps, int step_count) {
    if (list->count >= MAX_ITEMS) return -1;
    Reaction *r = &list->items[list->count];
    r->id = list->count + 1;
    strncpy(r->name, name, MAX_NAME - 1);
    r->name[MAX_NAME - 1] = '\0';
    strncpy(r->desc, desc, MAX_DESC - 1);
    r->desc[MAX_DESC - 1] = '\0';
    r->reactant_count = rc;
    for (int i = 0; i < rc && i < MAX_REACTANTS; i++) {
        strncpy(r->reactants[i], reactants[i], MAX_NAME - 1);
        r->reactants[i][MAX_NAME - 1] = '\0';
    }
    r->product_count = pc;
    for (int i = 0; i < pc && i < MAX_PRODUCTS; i++) {
        strncpy(r->products[i], products[i], MAX_NAME - 1);
        r->products[i][MAX_NAME - 1] = '\0';
    }
    r->min_temp = min_temp;
    r->max_temp = max_temp;
    r->required_equip = required_equip;
    r->exothermic = exothermic;
    r->hazard = hazard;
    r->phenom.step_count = step_count;
    for (int i = 0; i < step_count && i < MAX_STEPS; i++) {
        strncpy(r->phenom.steps[i], phenom_steps[i], MAX_DESC - 1);
        r->phenom.steps[i][MAX_DESC - 1] = '\0';
    }
    return list->count++;
}

int reac_add(ReactionList *list, const char *name, const char *desc,
             const char **reactants, int rc,
             const char **products, int pc,
             double min_temp, double max_temp,
             int required_equip, bool exothermic, HazardLevel hazard) {
    return reac_add_full(list, name, desc, reactants, rc, products, pc,
                         min_temp, max_temp, required_equip, exothermic,
                         hazard, NULL, 0);
}

Reaction* reac_find_by_name(ReactionList *list, const char *name) {
    for (int i = 0; i < list->count; i++)
        if (strcmp(list->items[i].name, name) == 0)
            return &list->items[i];
    return NULL;
}

void reac_list_all(const ReactionList *list) {
    printf("\n========== 反应库 (%d) ==========\n", list->count);
    for (int i = 0; i < list->count; i++) {
        const Reaction *r = &list->items[i];
        printf("[%d] %s\n", r->id, r->name);
        printf("    反应物: ");
        for (int j = 0; j < r->reactant_count; j++)
            printf("%s%s", r->reactants[j],
                   j < r->reactant_count - 1 ? " + " : "");
        printf("  ->  ");
        for (int j = 0; j < r->product_count; j++)
            printf("%s%s", r->products[j],
                   j < r->product_count - 1 ? " + " : "");
        printf("\n    条件: %.1f ~ %.1f ℃, %s, 危险:%s\n",
               r->min_temp, r->max_temp,
               r->exothermic ? "放热" : "吸热",
               hazard_str(r->hazard));
        printf("    说明: %s\n", r->desc);
        if (r->phenom.step_count > 0) {
            printf("    预期现象:\n");
            for (int k = 0; k < r->phenom.step_count; k++)
                printf("      %d) %s\n", k + 1, r->phenom.steps[k]);
        }
        printf("\n");
    }
}

ReactionResult reac_execute(Reaction *r, SubstanceList *subs,
                            EquipmentList *equips, ReactionConditions cond) {
    ReactionResult res;
    memset(&res, 0, sizeof(res));
    res.success = false;

    if (cond.temperature < r->min_temp || cond.temperature > r->max_temp) {
        snprintf(res.message, MAX_DESC,
                 "温度不满足: 需要 %.1f~%.1f℃, 当前 %.1f℃",
                 r->min_temp, r->max_temp, cond.temperature);
        res.hazard = HAZARD_LOW;
        return res;
    }

    Equipment *e = NULL;
    if (cond.equip_id > 0) {
        e = equip_find_by_id(equips, cond.equip_id);
        if (!e || !e->available) {
            snprintf(res.message, MAX_DESC, "缺少必需器材(ID=%d)", cond.equip_id);
            res.hazard = HAZARD_LOW;
            return res;
        }
        const char *react_err = equip_check_react(e);
        if (react_err) {
            snprintf(res.message, MAX_DESC, "%s", react_err);
            res.hazard = HAZARD_MEDIUM;
            return res;
        }
        if (cond.temperature > 40.0) {
            const char *heat_err = equip_check_heat(e, cond.temperature, cond.has_asbestos);
            if (heat_err) {
                snprintf(res.message, MAX_DESC, "%s", heat_err);
                res.hazard = HAZARD_HIGH;
                return res;
            }
        }
    }

    bool has_na = false;
    for (int i = 0; i < r->reactant_count; i++)
        if (strcmp(r->reactants[i], "Na") == 0) has_na = true;
    if (has_na && !cond.filtered_oil) {
        snprintf(res.message, MAX_DESC,
                 "钠表面带有煤油，必须先滤纸吸干才能反应！");
        res.hazard = HAZARD_HIGH;
        return res;
    }

    for (int i = 0; i < r->reactant_count; i++) {
        Substance *s = sub_find_by_formula(subs, r->reactants[i]);
        if (s && s->mass > 0) {
            double used = s->mass > 5.0 ? 5.0 : s->mass;
            s->mass -= used;
        }
    }

    for (int i = 0; i < r->product_count; i++) {
        Substance *p = sub_find_by_formula(subs, r->products[i]);
        if (p) {
            p->mass += 5.0;
            p->temperature = cond.temperature;
        }
    }

    res.success = true;
    res.energy_change = r->exothermic ? 50.0 : -50.0;
    res.hazard = r->hazard;
    snprintf(res.message, MAX_DESC,
             "反应成功! %s (能量 %+.1f kJ, 危险等级:%s)",
             r->exothermic ? "放热" : "吸热",
             res.energy_change, hazard_str(r->hazard));

    if (r->phenom.step_count > 0) {
        char buf[MAX_DESC] = "";
        for (int k = 0; k < r->phenom.step_count; k++) {
            size_t remain = MAX_DESC - strlen(buf) - 1;
            if (remain < 4) break;
            strncat(buf, r->phenom.steps[k], remain - 3);
            if (k < r->phenom.step_count - 1) strncat(buf, " → ", remain - strlen(buf));
        }
        strncpy(res.phenomenon, buf, MAX_DESC - 1);
        res.phenomenon[MAX_DESC - 1] = '\0';
    }
    return res;
}

void reac_free(ReactionList *list) {
    list->count = 0;
    memset(list->items, 0, sizeof(list->items));
}
