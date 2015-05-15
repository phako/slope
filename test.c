
#include "build/config.h"
#if SLOPE_GTK
#  include <slope/gtk.h>
#else
#  include <slope/slope.h>
#endif /* SLOPE_GTK */

#include <math.h>
#include <stdlib.h>

#define N 100

int main(int argc, char *argv[])
{
    /* generate some data */
    const double step = 2.0*M_PI/N;
    double x[N], y1[N], y2[N], y3[N], y4[N];
    int k;
    for (k=0; k<N; k++) {
        x[k] = k*step;
        y1[k] = sin(x[k]);
        y2[k] = y1[k] + 0.2*((double)rand())/RAND_MAX - 0.1;
        y3[k] = cos(x[k]);
        y4[k] = y3[k] + 0.2*((double)rand())/RAND_MAX - 0.1;
    }

    slope_figure_t *chart = slope_chart_create("Sine + random noise", "phase", "amplitude");
    slope_chart_add_plot(chart, x, y1, N, "sine", "u-");
    slope_chart_add_plot(chart, x, y2, N, "noise sin", "u+");
    slope_chart_add_plot(chart, x, y3, N, "cos", "u-");
    slope_chart_add_plot(chart, x, y4, N, "noise cos", "u+");

    #if SLOPE_GTK
    /* put the figure in a gtk widget */
    gtk_init(&argc,&argv);
    GtkWidget *window = slope_create_window(chart, "Data and Model");
    gtk_widget_show_all(window);
    gtk_main();
    #else
    /* save the chart in a png figure */
    slope_figure_write_to_png(chart, "figure.png", 800, 500);
    #endif /* SLOPE_GTK */

    slope_chart_destroy(chart);
    return 0;
}
