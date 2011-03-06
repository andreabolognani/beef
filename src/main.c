#include <glib.h>
#include <glib-object.h>
#include <cattle/cattle.h>
#include <config.h>

gint
main (gint argc, gchar **argv)
{
	g_print ("Beef %s, using Cattle %d.%d.%d\n", VERSION,
                                                 cattle_major_version,
                                                 cattle_minor_version,
                                                 cattle_micro_version);

	return 0;
}
