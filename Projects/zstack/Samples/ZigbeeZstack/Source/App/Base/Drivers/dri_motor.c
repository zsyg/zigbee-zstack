#define DRI_MOTOR_C_

/* ------------------------------------------------------------------------------------------------
 *                                          Includes
 * ------------------------------------------------------------------------------------------------
 */
#include "dri_motor.h"
/**************************************************************************************************
 * @fn          Motor_Init
 * @brief       P0.6、P0.7、P1.0、P1.1电机端口初始化
 * @param       无
 * @return      无
 **************************************************************************************************
 */
void Motor_Init(void)
{
  P0SEL &= ~0xC0;   //H桥上桥：P0.6、P0.7设置为通用I/O口
  P1SEL &= ~0x03;   //H桥下桥：P1.0、P1.1设置为通用I/O口
  P0DIR |= 0xC0;    //设置为输出
  P1DIR |= 0x03;
}

/**************************************************************************************************
 * @fn          Motor_H1ON
 * @brief       开启H1桥、关闭H2桥
 * @param       无
 * @return      无
 **************************************************************************************************
 */
void Motor_H1ON(void)
{
  Motor_H1H2OFF();
  P0_6 = 0;
  P0_7 = 1;
  P1_1 = 1;
  P1_0 = 0;
}






/**************************************************************************************************
 * @fn          Motor_H2ON
 * @brief       开启H2桥、关闭H1桥
 * @param       无
 * @return      无
 **************************************************************************************************
 */
void Motor_H2ON(void)
{
  Motor_H1H2OFF();
  P0_6 = 1;
  P0_7 = 0;
  P1_1 = 0;
  P1_0 = 1;
}






/**************************************************************************************************
 * @fn          Motor_H1H2OFF
 * @brief       关闭H1、H2桥
 * @param       无
 * @return      无
 **************************************************************************************************
 */
void Motor_H1H2OFF(void)
{
  P0_6 = 1;
  P0_7 = 1;
  P1_1 = 0;
  P1_0 = 0;
}