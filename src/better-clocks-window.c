/* better-clocks-window.c
 *
 * Copyright 2026 Mason Jennings
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
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "config.h"

#include "better-clocks-window.h"

struct _BetterClocksWindow
{
	AdwApplicationWindow parent_instance;

	/* Template widgets */
	GtkLabel *label;
	GtkLabel *current_time;
};

G_DEFINE_FINAL_TYPE(BetterClocksWindow, better_clocks_window, ADW_TYPE_APPLICATION_WINDOW)

static void
better_clocks_window_class_init(BetterClocksWindowClass *klass)
{
	GtkWidgetClass *widget_class = GTK_WIDGET_CLASS(klass);

	gtk_widget_class_set_template_from_resource(widget_class, "/io/github/masonj5002/betterclocks/better-clocks-window.ui");
	gtk_widget_class_bind_template_child(widget_class, BetterClocksWindow, label);
	gtk_widget_class_bind_template_child(widget_class, BetterClocksWindow, current_time);
}

static gboolean display_time(gpointer gptr)
{
	BetterClocksWindow *self = BETTER_CLOCKS_WINDOW(gptr);

	struct tm *time_info;
	time_t t = time(NULL);
	const int BUFFER_SIZE = 80;
	time_info = localtime(&t);
	char buffer[BUFFER_SIZE];

	strftime(buffer, BUFFER_SIZE, "%l:%M:%S %p", time_info);
	gtk_label_set_text(self->current_time, buffer);

	return TRUE;
}

static void
better_clocks_window_init(BetterClocksWindow *self)
{
	gtk_widget_init_template(GTK_WIDGET(self));

	display_time(self);
	g_timeout_add_seconds(0.25, display_time, self);
}
