/*
 * Jajalaboratory - 化学实验室模拟器
 * common.h - 公共定义
 *
 * Copyright (C) 2024 student25-ch
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NAME 64
#define MAX_DESC 512
#define MAX_ITEMS 256
#define MAX_PHASES 8
#define MAX_REACTANTS 4
#define MAX_PRODUCTS 6
#define MAX_STEPS 16

/* 物质状态 */
typedef enum {
    STATE_SOLID = 0,
    STATE_LIQUID,
    STATE_GAS,
    STATE_AQUEOUS
} MatterState;

/* 危险等级 */
typedef enum {
    HAZARD_NONE = 0,
    HAZARD_LOW,
    HAZARD_MEDIUM,
    HAZARD_HIGH,
    HAZARD_EXTREME
} HazardLevel;

/* 器材类型 */
typedef enum {
    EQUIP_CONTAINER = 0,
    EQUIP_HEATING,
    EQUIP_MEASURE,
    EQUIP_MIXER,
    EQUIP_TOOL,
    EQUIP_SUPPORT,
    EQUIP_SEPARATOR,
    EQUIP_GAS
} EquipmentType;

/* 加热方式约束 */
typedef enum {
    HEAT_NONE = 0,
    HEAT_DIRECT,
    HEAT_INDIRECT
} HeatMode;

/* 器材真实约束 */
typedef struct {
    HeatMode heat_mode;
    bool can_react;
    bool needs_stand;
    bool is_measuring;
    double max_liquid_pct;
    bool is_glassware;
} EquipConstraints;

/* 器材定义 */
typedef struct {
    int id;
    char name[MAX_NAME];
    char desc[MAX_DESC];
    EquipmentType type;
    double capacity;
    double max_temp;
    bool available;
    EquipConstraints c;
} Equipment;

/* 化学物质定义 */
typedef struct {
    int id;
    char formula[MAX_NAME];
    char name[MAX_NAME];
    MatterState state;
    HazardLevel hazard;
    double mass;
    double temperature;
    double density;
    double melting_point;
    char storage[MAX_NAME];
    bool is_metal;
} Substance;

/* 反应现象步骤 */
typedef struct {
    int step_count;
    char steps[MAX_STEPS][MAX_DESC];
} Phenomenon;

/* 反应定义 */
typedef struct {
    int id;
    char name[MAX_NAME];
    char desc[MAX_DESC];
    char reactants[MAX_REACTANTS][MAX_NAME];
    int reactant_count;
    char products[MAX_PRODUCTS][MAX_NAME];
    int product_count;
    double min_temp;
    double max_temp;
    int required_equip;
    bool exothermic;
    HazardLevel hazard;
    Phenomenon phenom;
} Reaction;

/* 反应条件 */
typedef struct {
    double temperature;
    int equip_id;
    bool has_asbestos;
    bool filtered_oil;
    bool catalyst_present;
} ReactionConditions;

/* 反应结果 */
typedef struct {
    bool success;
    char message[MAX_DESC];
    char phenomenon[MAX_DESC];
    double energy_change;
    HazardLevel hazard;
} ReactionResult;

#endif /* COMMON_H */
