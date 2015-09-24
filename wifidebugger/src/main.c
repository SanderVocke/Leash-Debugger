/*  ------------------------------------------------------------
    Copyright(C) 2015 MindTribe Product Engineering, Inc.
    All Rights Reserved.

    Author:     Sander Vocke, MindTribe Product Engineering
                <sander@mindtribe.com>

    Target(s):  ISO/IEC 9899:1999 (target independent)
    --------------------------------------------------------- */


#include <stdio.h>
#include <stdint.h>

//HW/Driverlib from CC3200 SDK
#include "hw_types.h"
#include "hw_ints.h"
#include "hw_memmap.h"
#include "hw_common_reg.h"
#include "interrupt.h"
#include "hw_apps_rcm.h"
#include "prcm.h"
#include "rom.h"
#include "rom_map.h"
#include "prcm.h"
#include "gpio.h"
#include "utils.h"

//TI interface layer code and pin config file
#include "gpio_if.h"
#include "uart_al.h"
#include "pin_mux_config.h"

//FreeRTOS
#include "FreeRTOS.h"
#include "task.h"
#include "portmacro.h"

//Project includes
#include "cc3200_icepick.h"
#include "cc3200_jtagdp.h"
#include "cc3200_core.h"
#include "jtag_scan.h"
#include "error.h"
#include "misc_hal.h"
#include "gdb_helpers.h"
#include "serialsock.h"
#include "target_al.h"
#include "cc3200.h"
#include "common/log.h"
#include "gdbserver.h"
#include "wifi.h"
#include "led.h"
#include "switch.h"

extern void (* const g_pfnVectors[])(void);

static int BoardInit(void);
static int OSInit(void);

int main(void)
{
    BoardInit();
    mem_log_clear();
    OSInit();

    unsigned int startAP = GetUserSwitch(AP_SWITCH); //If switch pressed, start in AP mode later

    InitSockets();
    if(gdbserver_init(&TS_GDBSocketPutChar, &TS_GDBSocketGetChar, &TS_GDBSocketRXCharAvailable, &cc3200_interface)
            == RET_FAILURE) WAIT_ERROR(ERROR_UNKNOWN);
    if(WifiInit(startAP) == RET_FAILURE) WAIT_ERROR(ERROR_UNKNOWN);

    //add task for WiFi
    xTaskCreate(Task_Wifi,
            "WiFi",
            WIFI_TASK_STACK_SIZE/sizeof(portSTACK_TYPE),
            0,
            WIFI_TASK_PRIORITY,
            0);

    //add task for GDBServer
    xTaskCreate(gdbserver_loop_task,
            "GDBServer Loop",
            GDBSERVER_TASK_STACK_SIZE/sizeof(portSTACK_TYPE),
            0,
            GDBSERVER_TASK_PRIORITY,
            0);


    //start FreeRTOS scheduler
    vTaskStartScheduler();

    return RET_SUCCESS;
}

static int BoardInit(void)
{
    //init vector table
    MAP_IntVTableBaseSet((unsigned long)&g_pfnVectors[0]);

    MAP_IntMasterEnable();
    MAP_IntEnable(FAULT_SYSTICK);

    PRCMCC3200MCUInit();

    PinMuxConfig();

    InitLED();

    //UART terminal
    UartInit();

    return RET_SUCCESS;
}

static int OSInit(void)
{
    return RET_SUCCESS;
}
