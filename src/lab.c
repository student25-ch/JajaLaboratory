/*
 * Jajalaboratory - 实验室主控制实现
 * Copyright (C) 2024 student25-ch - GPLv3
 */
#include "lab.h"
#include <stdio.h>
#include <string.h>

static bool lab_equips_loaded = false;
static bool lab_subs_loaded = false;
static bool lab_reacs_loaded = false;

void lab_init(Laboratory *lab) {
    strncpy(lab->lab_name, "Jajalaboratory", MAX_NAME - 1);
    lab->lab_name[MAX_NAME - 1] = '\0';
    equip_init(&lab->equips);
    sub_init(&lab->subs);
    reac_init(&lab->reactions);
}

void lab_load_default_equipment(Laboratory *lab) {
    if (lab_equips_loaded) return;
    lab_equips_loaded = true;
    EquipmentList *E = &lab->equips;
    equip_add_full(E, "试管",   "标准玻璃试管",       EQUIP_CONTAINER, 20, 500, HEAT_DIRECT,   true,  false, false, 0.33);
    equip_add_full(E, "烧杯",   "100mL玻璃烧杯",      EQUIP_CONTAINER,100, 400, HEAT_INDIRECT, true,  false, false, 0.50);
    equip_add_full(E, "锥形瓶", "250mL锥形瓶",        EQUIP_CONTAINER,250, 400, HEAT_INDIRECT, true,  false, false, 0.50);
    equip_add_full(E, "蒸发皿", "蒸发皿（可直接加热）",EQUIP_CONTAINER, 50, 600, HEAT_DIRECT,   true,  false, false, 0.50);
    equip_add_full(E, "坩埚",   "瓷坩埚",             EQUIP_CONTAINER, 30, 1000,HEAT_DIRECT,   true,  false, false, 0.50);
    equip_add_full(E, "量筒",   "50mL量筒（不可加热）",EQUIP_MEASURE,   50, 100, HEAT_NONE,     false, false, true,  0.0);
    equip_add_full(E, "集气瓶", "集气瓶（不可加热）",  EQUIP_GAS,      250, 200, HEAT_NONE,     false, false, false, 0.0);
    equip_add_full(E, "水槽",   "水槽（排水集气）",    EQUIP_GAS,      500, 100, HEAT_NONE,     false, false, false, 0.0);
    equip_add_full(E, "导管",   "玻璃导管",           EQUIP_GAS,        0, 400, HEAT_NONE,     false, false, false, 0.0);
    equip_add_full(E, "燃烧匙", "燃烧匙（可直接加热）",EQUIP_TOOL,       0, 600, HEAT_DIRECT,   true,  false, false, 0.0);
    equip_add_full(E, "酒精灯", "标准酒精灯",         EQUIP_HEATING,    0, 600, HEAT_NONE,     false, false, false, 0.0);
    equip_add_full(E, "石棉网", "隔热石棉网",         EQUIP_SUPPORT,    0, 800, HEAT_NONE,     false, false, false, 0.0);
    equip_add_full(E, "铁架台", "支撑铁架台",         EQUIP_SUPPORT,    0,   0, HEAT_NONE,     false, false, false, 0.0);
    equip_add_full(E, "试管夹", "金属试管夹",         EQUIP_TOOL,       0, 800, HEAT_NONE,     false, false, false, 0.0);
    equip_add_full(E, "坩埚钳", "坩埚钳",             EQUIP_TOOL,       0,1000, HEAT_NONE,     false, false, false, 0.0);
    equip_add_full(E, "玻璃棒", "搅拌用玻璃棒",       EQUIP_MIXER,      0, 300, HEAT_NONE,     false, false, false, 0.0);
    equip_add_full(E, "温度计", "温度计（不可搅拌）",  EQUIP_MEASURE,    0, 200, HEAT_NONE,     false, false, true,  0.0);
    equip_add_full(E, "药匙",   "取药匙",             EQUIP_TOOL,       0,   0, HEAT_NONE,     false, false, false, 0.0);
    equip_add_full(E, "镊子",   "金属镊子",           EQUIP_TOOL,       0,   0, HEAT_NONE,     false, false, false, 0.0);
    equip_add_full(E, "滴管",   "胶头滴管",           EQUIP_TOOL,       5, 100, HEAT_NONE,     false, false, false, 0.0);
    equip_add_full(E, "漏斗",   "普通漏斗",           EQUIP_SEPARATOR, 50, 200, HEAT_NONE,     false, false, false, 0.0);
    equip_add_full(E, "长颈漏斗","长颈漏斗",          EQUIP_SEPARATOR, 50, 200, HEAT_NONE,     false, false, false, 0.0);
    equip_add_full(E, "分液漏斗","分液漏斗",          EQUIP_SEPARATOR,100, 200, HEAT_NONE,     false, false, false, 0.0);
    equip_add_full(E, "电子天平","精密天平",          EQUIP_MEASURE,    0,  50, HEAT_NONE,     false, false, true,  0.0);
    equip_add_full(E, "研钵",   "研磨用研钵",         EQUIP_TOOL,      50, 100, HEAT_NONE,     false, false, false, 0.0);
    equip_add_full(E, "洗气瓶", "气体洗气瓶",         EQUIP_GAS,      100, 200, HEAT_NONE,     false, false, false, 0.0);
    equip_add_full(E, "培养皿", "培养皿",             EQUIP_CONTAINER, 50, 150, HEAT_NONE,     true,  false, false, 0.0);
}

void lab_load_default_substances(Laboratory *lab) {
    if (lab_subs_loaded) return;
    lab_subs_loaded = true;
    SubstanceList *S = &lab->subs;
    sub_add_full(S, "H2O",   "水",       STATE_LIQUID,  HAZARD_NONE,   1000, 1.00,   0,   "",      false);
    sub_add_full(S, "HCl",   "盐酸",     STATE_AQUEOUS, HAZARD_HIGH,    500, 1.18,   0,   "",      false);
    sub_add_full(S, "H2SO4", "硫酸",     STATE_LIQUID,  HAZARD_EXTREME, 300, 1.84,   10,  "",      false);
    sub_add_full(S, "NaOH",  "氢氧化钠", STATE_SOLID,   HAZARD_HIGH,    500, 2.13, 318,   "",      false);
    sub_add_full(S, "Ca(OH)2","氢氧化钙",STATE_SOLID,   HAZARD_LOW,     500, 2.24, 580,   "",      false);
    sub_add_full(S, "NaCl",  "氯化钠",   STATE_SOLID,   HAZARD_NONE,    500, 2.16, 801,   "",      false);
    sub_add_full(S, "Na2CO3","碳酸钠",   STATE_SOLID,   HAZARD_LOW,     300, 2.54, 851,   "",      false);
    sub_add_full(S, "CuSO4", "硫酸铜",   STATE_SOLID,   HAZARD_MEDIUM,  200, 3.60, 200,   "",      false);
    sub_add_full(S, "CaCO3", "碳酸钙",   STATE_SOLID,   HAZARD_NONE,    500, 2.71,1339,   "",      false);
    sub_add_full(S, "KMnO4", "高锰酸钾", STATE_SOLID,   HAZARD_MEDIUM,  100, 2.70, 240,   "",      false);
    sub_add_full(S, "KClO3", "氯酸钾",   STATE_SOLID,   HAZARD_HIGH,    100, 2.32, 356,   "",      false);
    sub_add_full(S, "MnO2",  "二氧化锰", STATE_SOLID,   HAZARD_LOW,     100, 5.03, 535,   "",      false);
    sub_add_full(S, "H2O2",  "过氧化氢", STATE_LIQUID,  HAZARD_MEDIUM,  200, 1.45,  -1,   "",      false);
    sub_add_full(S, "Fe",    "铁",       STATE_SOLID,   HAZARD_LOW,     300, 7.87,1538,   "",      true);
    sub_add_full(S, "Zn",    "锌",       STATE_SOLID,   HAZARD_MEDIUM,  200, 7.14, 420,   "",      true);
    sub_add_full(S, "Cu",    "铜",       STATE_SOLID,   HAZARD_NONE,    300, 8.96,1085,   "",      true);
    sub_add_full(S, "Mg",    "镁",       STATE_SOLID,   HAZARD_HIGH,    100, 1.74, 650,   "",      true);
    sub_add_full(S, "Na",    "钠",       STATE_SOLID,   HAZARD_EXTREME,  50, 0.97,  98,   "煤油", true);
    sub_add_full(S, "CuO",   "氧化铜",   STATE_SOLID,   HAZARD_LOW,     200, 6.31,1326,   "",      false);
    sub_add_full(S, "AgNO3", "硝酸银",   STATE_SOLID,   HAZARD_HIGH,    100, 4.35, 212,   "",      false);
    sub_add_full(S, "AgCl",  "氯化银",   STATE_SOLID,   HAZARD_LOW,       0, 5.56, 455,   "",      false);
    sub_add_full(S, "CO2",   "二氧化碳", STATE_GAS,     HAZARD_LOW,     100, 1.98,-78,    "",      false);
    sub_add_full(S, "O2",    "氧气",     STATE_GAS,     HAZARD_MEDIUM,  100, 1.43,-218,   "",      false);
    sub_add_full(S, "H2",    "氢气",     STATE_GAS,     HAZARD_EXTREME, 100, 0.09,-259,   "",      false);
    sub_add_full(S, "Na2O2","过氧化钠",  STATE_SOLID,   HAZARD_HIGH,      0, 2.81, 460,   "",      false);
    sub_add_full(S, "Na2SO4","硫酸钠",   STATE_SOLID,   HAZARD_LOW,       0, 2.66, 884,   "",      false);
    sub_add_full(S, "Cu(OH)2","氢氧化铜",STATE_SOLID,   HAZARD_LOW,       0, 3.37, 80,    "",      false);
    sub_add_full(S, "FeSO4", "硫酸亚铁", STATE_SOLID,   HAZARD_MEDIUM,    0, 2.84, 64,    "",      false);
    sub_add_full(S, "Fe2O3", "氧化铁",   STATE_SOLID,   HAZARD_LOW,       0, 5.24,1565,   "",      false);
    sub_add_full(S, "NaClO", "次氯酸钠", STATE_AQUEOUS, HAZARD_MEDIUM,    0, 1.10,   0,   "",      false);
    sub_add_full(S, "P",     "红磷",     STATE_SOLID,   HAZARD_HIGH,    100, 2.34, 590,   "",      false);
    sub_add_full(S, "S",     "硫粉",     STATE_SOLID,   HAZARD_MEDIUM,  100, 2.07, 115,   "",      false);
    sub_add_full(S, "C",     "木炭",     STATE_SOLID,   HAZARD_LOW,     100, 2.20,3500,   "",      false);
    sub_add_full(S, "MgO",   "氧化镁",   STATE_SOLID,   HAZARD_LOW,       0, 3.58,2852,   "",      false);
    sub_add_full(S, "P2O5",  "五氧化二磷",STATE_SOLID,  HAZARD_HIGH,      0, 2.39, 340,   "",      false);
}

void lab_load_default_reactions(Laboratory *lab) {
    if (lab_reacs_loaded) return;
    lab_reacs_loaded = true;
    ReactionList *R = &lab->reactions;

    {
        const char *r[] = {"KMnO4"}; const char *p[] = {"O2"};
        const char *ph[] = {
            "紫黑色固体逐渐减少",
            "导管口有气泡冒出",
            "用排水法可收集到无色气体",
            "带火星木条复燃，证明是氧气"
        };
        reac_add_full(R, "加热高锰酸钾制氧", "实验室制氧经典方法",
                      r, 1, p, 1, 200, 300, 6, false, HAZARD_MEDIUM, ph, 4);
    }
    {
        const char *r[] = {"KClO3", "MnO2"}; const char *p[] = {"O2"};
        const char *ph[] = {
            "白色固体与黑色粉末混合",
            "加热后导管口连续冒出气泡",
            "带火星木条复燃"
        };
        reac_add_full(R, "氯酸钾制氧", "MnO2 作催化剂",
                      r, 2, p, 1, 200, 300, 6, false, HAZARD_MEDIUM, ph, 3);
    }
    {
        const char *r[] = {"H2O2", "MnO2"}; const char *p[] = {"O2"};
        const char *ph[] = {
            "加入黑色 MnO2 后立即产生大量气泡",
            "反应剧烈，液体温度升高",
            "带火星木条复燃"
        };
        reac_add_full(R, "过氧化氢制氧", "常温制氧，MnO2 催化",
                      r, 2, p, 1, 15, 40, 2, true, HAZARD_MEDIUM, ph, 3);
    }
    {
        const char *r[] = {"CaCO3", "HCl"}; const char *p[] = {"CO2", "H2O"};
        const char *ph[] = {
            "白色固体表面产生大量气泡",
            "固体逐渐溶解",
            "燃着木条伸入集气瓶熄灭"
        };
        reac_add_full(R, "石灰石与盐酸制二氧化碳", "实验室制 CO2",
                      r, 2, p, 2, 10, 60, 2, true, HAZARD_LOW, ph, 3);
    }
    {
        const char *r[] = {"Zn", "H2SO4"}; const char *p[] = {"H2"};
        const char *ph[] = {
            "锌粒表面产生气泡",
            "锌粒逐渐溶解",
            "点燃收集到的气体有爆鸣声"
        };
        reac_add_full(R, "锌与稀硫酸制氢", "实验室制 H2",
                      r, 2, p, 1, 20, 60, 2, true, HAZARD_HIGH, ph, 3);
    }
    {
        const char *r[] = {"Na", "H2O"}; const char *p[] = {"NaOH", "H2"};
        const char *ph[] = {
            "钠浮在水面上（密度小于水）",
            "钠熔成闪亮的小球（反应放热，钠熔点低）",
            "小球在水面四处游动（氢气推动）",
            "发出嘶嘶声（反应剧烈）",
            "小球逐渐消失",
            "滴有酚酞的溶液变红（生成 NaOH）"
        };
        reac_add_full(R, "钠与水反应", "浮、熔、游、响、红",
                      r, 2, p, 2, 15, 40, 2, true, HAZARD_EXTREME, ph, 6);
    }
    {
        const char *r[] = {"Na", "O2"}; const char *p[] = {"Na2O2"};
        const char *ph[] = {
            "钠先熔化成小球",
            "然后剧烈燃烧，发出黄色火焰",
            "生成淡黄色固体（过氧化钠 Na2O2）",
            "注意：不是白色氧化钠"
        };
        reac_add_full(R, "钠在空气中加热", "黄色火焰，生成淡黄色固体",
                      r, 2, p, 1, 200, 400, 6, true, HAZARD_HIGH, ph, 4);
    }
    {
        const char *r[] = {"Na", "CuSO4", "H2O"};
        const char *p[] = {"Cu(OH)2", "H2", "Na2SO4"};
        const char *ph[] = {
            "钠先与水反应产生气泡",
            "同时生成蓝色絮状沉淀 Cu(OH)2",
            "不会置换出单质铜",
            "溶液蓝色变浅"
        };
        reac_add_full(R, "钠与硫酸铜溶液", "钠先与水反应，不置换铜",
                      r, 3, p, 3, 15, 40, 2, true, HAZARD_EXTREME, ph, 4);
    }
    {
        const char *r[] = {"Fe", "CuSO4"}; const char *p[] = {"Cu", "FeSO4"};
        const char *ph[] = {
            "铁钉表面附上一层红色物质",
            "蓝色溶液逐渐变浅绿色",
            "铁钉逐渐变细"
        };
        reac_add_full(R, "铁置换铜", "铁钉浸入硫酸铜溶液",
                      r, 2, p, 2, 20, 100, 2, false, HAZARD_LOW, ph, 3);
    }
    {
        const char *r[] = {"Mg", "O2"}; const char *p[] = {"MgO"};
        const char *ph[] = {
            "镁条剧烈燃烧",
            "发出耀眼的白光",
            "生成白色固体 MgO",
            "放出大量热"
        };
        reac_add_full(R, "镁条燃烧", "耀眼白光，白色固体",
                      r, 2, p, 1, 400, 700, 10, true, HAZARD_HIGH, ph, 4);
    }
    {
        const char *r[] = {"P", "O2"}; const char *p[] = {"P2O5"};
        const char *ph[] = {
            "红磷剧烈燃烧",
            "产生大量白烟",
            "生成白色固体 P2O5",
            "冷却后打开止水夹，水倒吸入瓶内约 1/5"
        };
        reac_add_full(R, "红磷燃烧测氧气含量", "白烟，测定空气组成",
                      r, 2, p, 1, 200, 500, 10, true, HAZARD_MEDIUM, ph, 4);
    }
    {
        const char *r[] = {"CuO", "H2"}; const char *p[] = {"Cu", "H2O"};
        const char *ph[] = {
            "黑色氧化铜逐渐变为红色",
            "试管口有水珠生成"
        };
        reac_add_full(R, "氢气还原氧化铜", "黑色变红，有水生成",
                      r, 2, p, 2, 150, 300, 6, false, HAZARD_MEDIUM, ph, 2);
    }
    {
        const char *r[] = {"HCl", "NaOH"}; const char *p[] = {"NaCl", "H2O"};
        const char *ph[] = {
            "无明显外观变化",
            "溶液温度略微升高",
            "用 pH 试纸检测 pH 逐渐接近 7"
        };
        reac_add_full(R, "酸碱中和", "盐酸与氢氧化钠中和",
                      r, 2, p, 2, 10, 80, 2, true, HAZARD_MEDIUM, ph, 3);
    }
    {
        const char *r[] = {"AgNO3", "NaCl"}; const char *p[] = {"AgCl"};
        const char *ph[] = {
            "立即出现白色沉淀",
            "沉淀不溶于稀硝酸"
        };
        reac_add_full(R, "氯化银沉淀", "硝酸银与氯化钠",
                      r, 2, p, 1, 10, 60, 2, false, HAZARD_LOW, ph, 2);
    }
    {
        const char *r[] = {"NaOH", "CuSO4"}; const char *p[] = {"Cu(OH)2", "Na2SO4"};
        const char *ph[] = {
            "立即生成蓝色絮状沉淀 Cu(OH)2",
            "溶液蓝色变浅"
        };
        reac_add_full(R, "氢氧化钠与硫酸铜", "蓝色絮状沉淀",
                      r, 2, p, 2, 10, 60, 2, false, HAZARD_LOW, ph, 2);
    }
    {
        const char *r[] = {"H2", "O2"}; const char *p[] = {"H2O"};
        const char *ph[] = {
            "点燃时发出爆鸣声",
            "剧烈反应，可能产生爆炸",
            "生成水"
        };
        reac_add_full(R, "氢氧爆鸣", "爆鸣声，生成水",
                      r, 2, p, 1, 20, 500, 1, true, HAZARD_EXTREME, ph, 3);
    }
}

void lab_load_data_file(Laboratory *lab, const char *path) {
    FILE *f = fopen(path, "r");
    if (!f) return;
    char line[512];
    while (fgets(line, sizeof(line), f)) {
        if (line[0] == '#' || line[0] == '\n') continue;
        line[strcspn(line, "\n")] = 0;
        if (strncmp(line, "EQUIP|", 6) == 0) {
            if (lab->equips.count >= MAX_ITEMS) break;
            char name[MAX_NAME], desc[MAX_DESC], type[MAX_NAME];
            int cap_i = 0, temp_i = 0, heat_i = 0, react_i = 0;
            sscanf(line + 6, "%63[^|]|%255[^|]|%63[^|]|%d|%d|%d|%d",
                   name, desc, type, &cap_i, &temp_i, &heat_i, &react_i);
            if (equip_find_by_name(&lab->equips, name)) continue;
            EquipmentType et = EQUIP_CONTAINER;
            if (strcmp(type, "MEASURE") == 0) et = EQUIP_MEASURE;
            else if (strcmp(type, "HEATING") == 0) et = EQUIP_HEATING;
            else if (strcmp(type, "TOOL") == 0) et = EQUIP_TOOL;
            else if (strcmp(type, "SUPPORT") == 0) et = EQUIP_SUPPORT;
            else if (strcmp(type, "SEPARATOR") == 0) et = EQUIP_SEPARATOR;
            else if (strcmp(type, "GAS") == 0) et = EQUIP_GAS;
            HeatMode hm = (HeatMode)heat_i;
            equip_add_full(&lab->equips, name, desc, et,
                           (double)cap_i, (double)temp_i,
                           hm, react_i != 0, false, false, 0.5);
        } else if (strncmp(line, "SUB|", 4) == 0) {
            if (lab->subs.count >= MAX_ITEMS) break;
            char formula[MAX_NAME], name[MAX_NAME], state[MAX_NAME], haz[MAX_NAME];
            double mass = 0;
            sscanf(line + 4, "%63[^|]|%63[^|]|%63[^|]|%63[^|]|%lf",
                   formula, name, state, haz, &mass);
            if (sub_find_by_formula(&lab->subs, formula)) continue;
            MatterState ms = STATE_SOLID;
            if (strcmp(state, "LIQUID") == 0) ms = STATE_LIQUID;
            else if (strcmp(state, "GAS") == 0) ms = STATE_GAS;
            else if (strcmp(state, "AQUEOUS") == 0) ms = STATE_AQUEOUS;
            HazardLevel hl = HAZARD_NONE;
            if (strcmp(haz, "LOW") == 0) hl = HAZARD_LOW;
            else if (strcmp(haz, "MEDIUM") == 0) hl = HAZARD_MEDIUM;
            else if (strcmp(haz, "HIGH") == 0) hl = HAZARD_HIGH;
            else if (strcmp(haz, "EXTREME") == 0) hl = HAZARD_EXTREME;
            sub_add_full(&lab->subs, formula, name, ms, hl, mass,
                         1.0, -1, "", false);
        }
    }
    fclose(f);
}

void lab_menu(Laboratory *lab) {
    int choice;
    while (1) {
        printf("\n");
        printf("╔══════════════════════════════════════════╗\n");
        printf("║      %-10s - 化学实验室       ║\n", lab->lab_name);
        printf("╠══════════════════════════════════════════╣\n");
        printf("║  1. 查看器材清单                         ║\n");
        printf("║  2. 查看物质清单                         ║\n");
        printf("║  3. 查看反应库                           ║\n");
        printf("║  4. 执行反应                             ║\n");
        printf("║  5. 添加物质                             ║\n");
        printf("║  6. 调整物质温度                         ║\n");
        printf("║  7. 器材能力检查                         ║\n");
        printf("║  0. 退出                                 ║\n");
        printf("╚══════════════════════════════════════════╝\n");
        printf("请选择: ");
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            continue;
        }
        getchar();

        switch (choice) {
            case 1: equip_list_all(&lab->equips); break;
            case 2: sub_list_all(&lab->subs); break;
            case 3: reac_list_all(&lab->reactions); break;
            case 4: {
                char rname[MAX_NAME];
                printf("输入反应名称: ");
                if (!fgets(rname, MAX_NAME, stdin)) break;
                rname[strcspn(rname, "\n")] = 0;
                Reaction *r = reac_find_by_name(&lab->reactions, rname);
                if (!r) { printf("未找到反应\n"); break; }

                ReactionConditions cond;
                memset(&cond, 0, sizeof(cond));

                printf("输入当前温度(℃): ");
                if (scanf("%lf", &cond.temperature) != 1) { while (getchar() != '\n'); break; }

                printf("输入所用器材 ID（参考清单，0=无）: ");
                if (scanf("%d", &cond.equip_id) != 1) { while (getchar() != '\n'); break; }

                printf("是否垫石棉网？(1是 0否): ");
                int t = 0; if (scanf("%d", &t) != 1) { while (getchar() != '\n'); break; }
                cond.has_asbestos = (t == 1);

                printf("反应物是否已滤干煤油？(1是 0否): ");
                t = 0; if (scanf("%d", &t) != 1) { while (getchar() != '\n'); break; }
                cond.filtered_oil = (t == 1);
                getchar();

                ReactionResult res = reac_execute(r, &lab->subs,
                                                  &lab->equips, cond);
                printf("\n>>> 结果: %s\n", res.success ? "[成功]" : "[失败]");
                printf(">>> %s\n", res.message);
                if (res.success && res.phenomenon[0])
                    printf(">>> 现象: %s\n", res.phenomenon);
                break;
            }
            case 5: {
                char formula[MAX_NAME], name[MAX_NAME];
                double mass;
                int state, hazard;
                printf("化学式: ");
                if (!fgets(formula, MAX_NAME, stdin)) break;
                formula[strcspn(formula, "\n")] = 0;
                printf("名称: ");
                if (!fgets(name, MAX_NAME, stdin)) break;
                name[strcspn(name, "\n")] = 0;
                printf("状态(0固1液2气3溶液): ");
                if (scanf("%d", &state) != 1) { while (getchar() != '\n'); break; }
                printf("危险(0无1低2中3高4极高): ");
                if (scanf("%d", &hazard) != 1) { while (getchar() != '\n'); break; }
                printf("质量(g): ");
                if (scanf("%lf", &mass) != 1) { while (getchar() != '\n'); break; }
                getchar();
                sub_add(&lab->subs, formula, name,
                        (MatterState)state, (HazardLevel)hazard, mass);
                printf("添加成功\n");
                break;
            }
            case 6: {
                char formula[MAX_NAME];
                double temp;
                printf("物质化学式: ");
                if (!fgets(formula, MAX_NAME, stdin)) break;
                formula[strcspn(formula, "\n")] = 0;
                Substance *s = sub_find_by_formula(&lab->subs, formula);
                if (!s) { printf("未找到该物质\n"); break; }
                printf("新温度(℃): ");
                if (scanf("%lf", &temp) != 1) { while (getchar() != '\n'); break; }
                getchar();
                s->temperature = temp;
                printf("%s 温度已设置为 %.1f℃\n", s->name, temp);
                break;
            }
            case 7: {
                int id;
                printf("输入器材 ID: ");
                if (scanf("%d", &id) != 1) { while (getchar() != '\n'); break; }
                getchar();
                Equipment *e = equip_find_by_id(&lab->equips, id);
                if (!e) { printf("未找到器材\n"); break; }
                printf("\n器材: %s\n", e->name);
                printf("  加热方式: %s\n", heat_mode_str(e->c.heat_mode));
                printf("  耐温: %.0f℃\n", e->max_temp);
                printf("  可作反应容器: %s\n", e->c.can_react ? "是" : "否");
                printf("  是量器: %s\n", e->c.is_measuring ? "是" : "否");
                printf("  需铁架台: %s\n", e->c.needs_stand ? "是" : "否");
                break;
            }
            case 0:
                printf("再见!\n");
                return;
            default:
                printf("无效选择\n");
        }
    }
}

void lab_free(Laboratory *lab) {
    equip_free(&lab->equips);
    sub_free(&lab->subs);
    reac_free(&lab->reactions);
    lab_equips_loaded = false;
    lab_subs_loaded = false;
    lab_reacs_loaded = false;
}
