#include <gtk/gtk.h>

#include "utility.h"

gint g_array_length (GArray *array)
{
    int i = 0;
    
    while (g_array_index (array, gpointer, i))
    {
        i++;
    }
    
    return i;
}
