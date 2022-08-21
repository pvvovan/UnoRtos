#include "app.h"

#include <FreeRTOS.h>
#include <task.h>


#define TASK_PRIORITY			( tskIDLE_PRIORITY + 3 )

/* The period between executions of the check task. */
#define mainCHECK_PERIOD				( ( TickType_t ) 500 / portTICK_PERIOD_MS )


static void vErrorChecks( void *pvParameters )
{
	static volatile unsigned long ulDummyVariable = 3UL;

	/* The parameters are not used. */
	( void ) pvParameters;

	/* Cycle for ever, delaying then checking all the other tasks are still
	 * operating without error. */
	for( ;; )
	{
		vTaskDelay( mainCHECK_PERIOD );

		/* Perform a bit of 32bit maths to ensure the registers used by the
		 * integer tasks get some exercise. The result here is not important -
		 * see the demo application documentation for more info. */
		ulDummyVariable *= 3;
		app_blink();
	}
}

static void sendmsg( void *pvParameters )
{
	(void)pvParameters;

	for ( ; ; ) {
		vTaskDelay( mainCHECK_PERIOD / 2 );
		app_sendmsg();
	}
}

void echo_uart2(void);
static void task_uart2(void *pvParameters)
{
	(void)pvParameters;
	for ( ; ; ) {
		vTaskDelay(mainCHECK_PERIOD / 10);
		echo_uart2();
	}
}

int main()
{
	app_init();

	/* Create the tasks defined within this file. */
	xTaskCreate(vErrorChecks, "blink", configMINIMAL_STACK_SIZE, NULL, TASK_PRIORITY, NULL);
	xTaskCreate(sendmsg, "send", configMINIMAL_STACK_SIZE, NULL, TASK_PRIORITY, NULL);
	xTaskCreate(task_uart2, "echo", configMINIMAL_STACK_SIZE, NULL, TASK_PRIORITY, NULL);

	/* In this port, to use preemptive scheduler define configUSE_PREEMPTION
	 * as 1 in portmacro.h.  To use the cooperative scheduler define
	 * configUSE_PREEMPTION as 0. */
	vTaskStartScheduler();

	for ( ; ; ) {
		app_blink();
	}

	return 0;
}

void vApplicationIdleHook( void )
{
	/* Do nothing in idle task */
}
