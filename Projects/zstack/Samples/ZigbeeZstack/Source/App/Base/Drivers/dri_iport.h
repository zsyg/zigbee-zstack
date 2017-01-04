#ifndef DRI_IPORT_H_
#define DRI_IPORT_H_

/* ------------------------------------------------------------------------------------------------
 *                                          Includes
 * ------------------------------------------------------------------------------------------------
 */
#include<ioCC2530.h>

/* ------------------------------------------------------------------------------------------------
 *                                      variable
 * ------------------------------------------------------------------------------------------------
 */



/* ------------------------------------------------------------------------------------------------
 *                                          Define
 * ------------------------------------------------------------------------------------------------
 */

/*IPORT�˿ڶ���*/
#define RST         P0_1                    //�͵�ƽ��λ��Ч
#define FUNCTION    P0_4                    //Ĭ������£�TCP Server��TCP Client�������ӽ���ʱ����͵�ƽ�����ӶϿ�ʱ����ߵ�ƽ               




/* ------------------------------------------------------------------------------------------------
 *                                          Prototypes
 * ------------------------------------------------------------------------------------------------
 */
void Iport_Init(void);


/**************************************************************************************************
 */
#endif