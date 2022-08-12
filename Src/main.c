#include "app.h"

int main()
{
	app_init();

	for ( ; ; ) {
		app_blink();
	}

	return 0;
}
