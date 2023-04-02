#include <stdio.h>
#include <glib.h>

int main(void)
{
	GPtrArray* data = g_ptr_array_new ();
	long temp = get_stock_from_yahoo ("068400.K", "01", "01", "2010", "01", "10", "2014", data);
	printf ("HTTP CODE : %ld\n", temp);
	return 0;
}
