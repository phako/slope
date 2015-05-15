/*
 * Copyright (C) 2015  Elvis Teixeira
 *
 * This source code is free software: you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General
 * Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any
 * later version.
 *
 * This source code is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General
 * Public License along with this program.
 * If not, see <http://www.gnu.org/licenses/>.
 */

#include "slope/item_p.h"
#include "slope/metrics.h"
#include "slope/figure.h"
#include <stdlib.h>
#include <string.h>


void slope_item_destroy (slope_item_t *item)
{
    if (item == NULL) {
        return;
    }
    if (item->klass->destroy_fn) {
        (*item->klass->destroy_fn)(item);
    }
    if (item->name) {
        free(item->name);
    }
    free(item);
}


int slope_item_get_visible (slope_item_t *item)
{
    if (item == NULL) {
        return SLOPE_FALSE;
    }
    return item->visible;
}


void slope_item_set_visible (slope_item_t *item,
                             int visible)
{
    if (item == NULL) {
        return;
    }
    item->visible = visible;
    slope_item_notify_appearence_change(item);
}


const char* slope_item_get_name (slope_item_t *item)
{
    if (item == NULL) {
        return NULL;
    }
    return item->name;
}


void slope_item_set_name (slope_item_t *item, const char *name)
{
    if (item == NULL) {
        return;
    }
    if (item->name) {
        free(item->name);
    }
    item->name = strdup(name);
    slope_item_notify_appearence_change(item);
}


void __slope_item_draw (slope_item_t *item, cairo_t *cr,
                        const slope_metrics_t *metrics)
{
    (*item->klass->draw_fn)(item, cr, metrics);
}


slope_metrics_t* slope_item_get_metrics (slope_item_t *item)
{
    if (item == NULL) {
        return NULL;
    }
    return item->metrics;
}


slope_figure_t* slope_item_get_figure (slope_item_t *item)
{
    if (item == NULL) {
        return NULL;
    }
    return slope_metrics_get_figure(item->metrics);
}


void slope_item_notify_appearence_change (slope_item_t *item)
{
    slope_figure_t *figure = slope_item_get_figure(item);
    slope_figure_notify_appearence_change(figure, item);
}


void slope_item_notify_item_change (slope_item_t *item)
{
    slope_figure_t *figure = slope_item_get_figure(item);
    slope_figure_notify_item_change(figure, item);
}


int __slope_item_parse_color (const char *fmt)
{
    static int undefine_color=SLOPE_WHITE;
    while (*fmt) {
        if (*fmt == 'b') return SLOPE_BLACK;
        if (*fmt == 'w') return SLOPE_WHITE;
        if (*fmt == 'r') return SLOPE_RED;
        if (*fmt == 'g') return SLOPE_GREEN;
        if (*fmt == 'l') return SLOPE_BLUE;
        if (*fmt == 'y') return SLOPE_YELLOW;
        if (*fmt == 'm') return SLOPE_MAROON;
        if (*fmt == 'e') return SLOPE_GREY;
        if (*fmt == 'p') return SLOPE_PURPLE;
        if (*fmt == 'i') return SLOPE_OLIVE;
        if (*fmt == 't') return SLOPE_TEAL;
        if (*fmt == 'o') return SLOPE_ORANGE;
        if (*fmt == 'u')
        {
            ++undefine_color;
            if (undefine_color == SLOPE_LAST_COLOR)
                undefine_color=SLOPE_RED;
            return undefine_color;
        }
        ++fmt;
    }
    return SLOPE_BLACK;
}


int __slope_item_parse_scatter (const char *fmt)
{
    while (*fmt) {
        if (*fmt == '-') return SLOPE_LINE;
        if (*fmt == '*') return SLOPE_CIRCLES;
        if (*fmt == '+') return SLOPE_PLUSSES;
        ++fmt;
    }
    return SLOPE_LINE;
}

/* slope/item.c */

