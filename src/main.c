/*
 * Jajalaboratory - 程序入口
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
#include "lab.h"
#include <stdio.h>

int main(void) {
    printf("\n");
    printf("╔══════════════════════════════════════════╗\n");
    printf("║          Jajalaboratory v2.0             ║\n");
    printf("║    化学实验室模拟器 (含器材真实约束)     ║\n");
    printf("║    Author: student25-ch  License: GPLv3  ║\n");
    printf("╚══════════════════════════════════════════╝\n");

    Laboratory lab;
    lab_init(&lab);
    lab_load_default_equipment(&lab);
    lab_load_default_substances(&lab);
    lab_load_default_reactions(&lab);
    lab_load_data_file(&lab, "data/reagents.txt");

    printf("\n实验室已初始化:\n");
    printf("  - 器材: %d 件\n", lab.equips.count);
    printf("  - 物质: %d 种\n", lab.subs.count);
    printf("  - 反应: %d 个\n", lab.reactions.count);

    lab_menu(&lab);
    lab_free(&lab);
    return 0;
}
