/**************************************************************************************************
  Filename:       OSAL_BaseApp.c
  Revised:        $Date: 2008-02-07 12:10:00 -0800 (Thu, 07 Feb 2008) $
  Revision:       $Revision: 16360 $

  Description:    This file contains all the settings and other functions
                  that the user should set and change.


  Copyright 2007 Texas Instruments Incorporated. All rights reserved.

  IMPORTANT: Your use of this Software is limited to those specific rights
  granted under the terms of a software license agreement between the user
  who downloaded the software, his/her employer (which must be your employer)
  and Texas Instruments Incorporated (the "License").  You may not use this
  Software unless you agree to abide by the terms of the License. The License
  limits your use, and you acknowledge, that the Software may not be modified,
  copied or distributed unless embedded on a Texas Instruments microcontroller
  or used solely and exclusively in conjunction with a Texas Instruments radio
  frequency transceiver, which is integrated into your product.  Other than for
  the foregoing purpose, you may not use, reproduce, copy, prepare derivative
  works of, modify, distribute, perform, display or sell this Software and/or
  its documentation for any purpose.

  YOU FURTHER ACKNOWLEDGE AND AGREE THAT THE SOFTWARE AND DOCUMENTATION ARE
  PROVIDED 揂S IS?WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED,
  INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY, TITLE,
  NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL
  TEXAS INSTRUMENTS OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT,
  NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER
  LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
  INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE
  OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT
  OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
  (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

  Should you have any questions regarding your right to use this Software,
  contact Texas Instruments Incorporated at www.TI.com.
**************************************************************************************************/

/*********************************************************************
 * INCLUDES
 */

#include "ZComDef.h"
#include "hal_drivers.h"
#include "OSAL.h"
#include "OSAL_Tasks.h"

#if defined ( MT_TASK )
  #include "MT.h"
  #include "MT_TASK.h"
#endif

#include "nwk.h"
#include "APS.h"
#include "ZDApp.h"
#if defined ( ZIGBEE_FREQ_AGILITY ) || defined ( ZIGBEE_PANID_CONFLICT )
  #include "ZDNwkMgr.h"
#endif
#if defined ( ZIGBEE_FRAGMENTATION )
  #include "aps_frag.h"
#endif

#include "BaseApp.h"

/*********************************************************************
 * GLOBAL VARIABLES
 */

// The order in this table must be identical to the task initialization calls below in osalInitTask.
const pTaskEventHandlerFn tasksArr[] = {      //taskArr指向了各任务事件的处理函数
  macEventLoop,                               //MAC层任务处理函数
  nwk_event_loop,                             //网络层任务处理函数
  Hal_ProcessEvent,                           //硬件抽象层任务处理函数
#if defined( MT_TASK )            
  MT_ProcessEvent,                            //调试任务处理函数 可选
#endif
  APS_event_loop,                             //APS层任务处理函数，用户不可修改
#if defined ( ZIGBEE_FRAGMENTATION )
  APSF_ProcessEvent,                    
#endif
  ZDApp_event_loop,                           //设备应用层任务处理函数，用户可以根据修改
#if defined ( ZIGBEE_FREQ_AGILITY ) || defined ( ZIGBEE_PANID_CONFLICT )
  ZDNwkMgr_event_loop,                    
#endif
  BaseApp_ProcessEvent                      //用户自己的应用层任务处理函数，用户在主文件中生成
};



//taskArr数组中每个成员都是一个指向pTaskEventHandlerFn函数的指针


const uint8 tasksCnt = sizeof( tasksArr ) / sizeof( tasksArr[0] );  //taskCnt变量保存了当前的任务个数
uint16 *tasksEvents;





/*********************************************************************
 * FUNCTIONS
 *********************************************************************/

/*********************************************************************
 * @fn      osalInitTasks
 *
 * @brief   This function invokes the initialization function for each task.
 *
 * @param   void
 *
 * @return  none
 */
void osalInitTasks( void )
{
  uint8 taskID = 0;

  
  tasksEvents = (uint16 *)osal_mem_alloc( sizeof( uint16 ) * tasksCnt); //为任务分配空间
  osal_memset( tasksEvents, 0, (sizeof( uint16 ) * tasksCnt));  //任务初始化

  macTaskInit( taskID++ );            //MAC层任务初始化 taskID = 0 任务优先级最高 
  nwk_init( taskID++ );               //网络层任务初始化 taskID = 1
  Hal_Init( taskID++ );               //硬件抽象层任务初始化  
#if defined( MT_TASK )  
  MT_TaskInit( taskID++ );            
#endif
  APS_Init( taskID++ );               //APS层任务初始化
#if defined ( ZIGBEE_FRAGMENTATION )  
  APSF_Init( taskID++ );
#endif
  ZDApp_Init( taskID++ );            //ZDAPP任务初始化,用户需要考虑
#if defined ( ZIGBEE_FREQ_AGILITY ) || defined ( ZIGBEE_PANID_CONFLICT )
  ZDNwkMgr_Init( taskID++ );
#endif
  BaseApp_Init( taskID );         //BaseApp初始化,应用协议栈例程，用户自己创建的任务是第八个任务，优先级最低
}

/*********************************************************************
*********************************************************************/
