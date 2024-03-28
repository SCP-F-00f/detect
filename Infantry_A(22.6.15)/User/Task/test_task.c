/**
 * @Copyright(C),
 * @FileName:.c
 * @Author: HongYuJia 
 * @Teammate��
 * @Version: V3.0
 * @Date:2021.4.13
 * @Description:   ԭ��Ϊ�����������ڼ�ػ���������״̬��
 * 					����������ʾ�ͻ��˽����Զ�����Ϣ��δ���ƺã�
 * 					��Ҫ���ԣ������²���ϵͳЭ�����㣬�п�Դ���빩�ο������ͣ�
 * @Note:       
 * @Others: 
**/
#include "test_task.h"
#include "delay.h"
#include "FreeRTOS.h"
#include "task.h"
#include "judge.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "usart.h"
extern robot_status_t robot_status;
/**
  * @brief  ͨ���Լ���ID�����ض�Ӧ�����ֿͻ���ID
  * @param  void
  * @retval 
  * @attention  
  */
int Operator_ID(void)
{
	uint8_t Operator_id;
	if(robot_status.robot_id < 10)        //�췽
	{
		Operator_id = robot_status.robot_id + 0x0100 ;
	}
	else if (robot_status.robot_id > 10)  //����
	{
		Operator_id = robot_status.robot_id + 0x0064 ;
	}
	return Operator_id;
}
/**
  * @brief  �ڿͻ�����ʾ������
  * @param  void
  * @retval 
  * @attention  
  */
void Display_float(graphic_data_struct_t *configure, float num)             
{
	configure->graphic_name[0] = 0;
	configure->operate_tpye = 1;
	configure->graphic_tpye = 5;
	configure->layer = 1;
	configure->color = 7;
	
	configure->start_angle = 5;
	configure->end_angle = 2;
	configure->width = 3;
	configure->start_x = 1;
	configure->start_y = 1;
	// configure->radius = num >>22;
	// configure->end_x = num >>11;
	configure->end_y = num;
}

/**
  * @brief  �ڿͻ�����ʾ������
  * @param  void
  * @retval 
  * @attention  
  */
void Display_int(string_data_struct_t *configure, int32_t num)
{
	configure->string_name[0] = 1;
	configure->operate_tpye = 1;
	configure->graphic_tpye = 6;
	configure->layer = 1;
	configure->color = 7;

	configure->start_angle = 5;
	configure->end_angle = NULL;
	configure->width = 3;
	configure->start_x = 1;
	configure->start_y = 1;
//	configure->stringdata = num;
}

/**
  * @brief  �ڿͻ�����ʾ�ַ�
  * @param  void
  * @retval 
  * @attention  
  */
void Display_char(void)
{
	;
}

/**
  * @brief  �ϴ��Զ�������
  * @param  void
  * @retval void    
  * @attention    ���ݴ��,�����ɺ�ͨ�����ڷ��͵�����ϵͳ       *hyj
  *          �˺����ɽ����ݴ��͵������ֽ�����ʾ��δ���ã���ѧ����ʱ�������󣡣�
  */
uint8_t CliendTxBuffer[SEND_MAX_LEN];



//2024
//ext_Send_User_Data_t      ShowData;			//�ͻ�����Ϣ
//void Show_User_Data(void)
//{	
//	ShowData.txFrameHeader.SOF = 0xA5;
//	ShowData.txFrameHeader.data_length = sizeof(robot_interaction_data_t) + sizeof(string_data_struct_t);       //client_custom_data_t
//	ShowData.txFrameHeader.seq = 0;
//	memcpy(CliendTxBuffer, &ShowData.txFrameHeader, sizeof(frame_header_struct_t));//д��֡ͷ����
//	Append_CRC8_Check_Sum(CliendTxBuffer, sizeof(frame_header_struct_t));//д��֡ͷCRC8У����
//	
//	ShowData.CmdID = ROBOT_COMMUNICATION_ID;
//	
//	ShowData.dataFrameHeader.data_cmd_id = 0x0101;//���ݶ����ݵ�ID
//	ShowData.dataFrameHeader.sender_id 	 = robot_status.robot_id ;//�����ߵ�ID
//	ShowData.dataFrameHeader.receiver_id = Operator_ID();//�ͻ��˵�ID��ֻ��Ϊ�����߻����˶�Ӧ�Ŀͻ���
//	
//	/*- �Զ������� -******��ʱ�ģ���ѧ���Կ���Ҫʲô *hyj */
//	// ShowData.clientData.data1 = 11.11;
//	// ShowData.clientData.data2 = 22.22;
//	// ShowData.clientData.data3 = 33.33;
//	// ShowData.clientData.data4 = 44;
//Display_int(&ShowData.clientData.user_data,111);
//	/*--------------*/
//	//���д�����ݶ�
//	memcpy(	
//			CliendTxBuffer + 5, 
//			(uint8_t*)&ShowData.CmdID, 
//			(sizeof(ShowData.CmdID)+ sizeof(ShowData.dataFrameHeader)+ sizeof(ShowData.clientData))
//		  );			
//			
//	Append_CRC16_Check_Sum(CliendTxBuffer,sizeof(ShowData));//д�����ݶ�CRC16֡βУ����	

//	// HAL_UART_Transmit_IT(&huart3 ,(uint8_t*)CliendTxBuffer,sizeof(CliendTxBuffer));
//	HAL_UART_Transmit(&huart3, CliendTxBuffer, sizeof(CliendTxBuffer), 1000);      //������  
//}
#define CRC08_INIT (0xff)
#define CRC16_INIT (0xffff)

extern uint16_t CRC16_TAB[256];
extern uint8_t CRC8_TAB[256];

uint8_t CRC08_Calculate(uint8_t *Data, uint32_t Lenth /* Without check code lenth 1 */)
{
	uint8_t CheckCode = CRC08_INIT;
	while (Lenth --) CheckCode = CRC8_TAB[CheckCode ^ *Data ++];
	return CheckCode;
}

uint32_t CRC08_Verify(uint8_t *Data, uint32_t Lenth /* With check code lenth 1 */)
{
	if(Data == NULL || Lenth <= 2) return 0;
  return CRC08_Calculate(Data, Lenth - 1) == Data[Lenth - 1];
}

uint32_t CRC08_Append(uint8_t *Data, uint32_t Lenth /* With check code lenth 1 */)
{
	if(Data == NULL || Lenth <= 2) return 0;
	Data[Lenth- 1] = CRC08_Calculate(Data, Lenth - 1);
	return 1;
}

uint16_t CRC16_Calculate(uint8_t *Data, uint32_t Lenth /* Without check code lenth 2 */)
{
	uint16_t CheckCode = CRC16_INIT;
	if(Data == NULL) return 0xFFFF;
	while(Lenth --) CheckCode = CheckCode >> 8 ^ CRC16_TAB[(CheckCode ^ (uint16_t)*Data ++) & 0x00ff];
	return CheckCode;
}

uint32_t CRC16_Verify(uint8_t *Data, uint32_t Lenth /* With check code lenth 2 */)
{
	if(Data == NULL || Lenth <= 2) return 0;
	uint16_t Expected = CRC16_Calculate(Data, Lenth - 2);
	return (Expected & 0xff) == Data[Lenth - 2] && ((Expected >> 8) & 0xff) == Data[Lenth - 1];
}

uint32_t CRC16_Append(uint8_t *Data, uint32_t Lenth /* With check code lenth 2 */)
{
	if(Data == NULL || Lenth <= 2) return 0;
	uint16_t CheckCode = CRC16_Calculate(Data, Lenth - 2);
	Data[Lenth - 2] = CheckCode >> 0;
	Data[Lenth - 1] = CheckCode >> 8;
	return 1;
}






void UI_PushUp_Graphs(uint8_t Counter /* 1,2,5,7 */, void *Graphs /* ��Counter��һ�µ�UI_Graphx�ṹ��ͷָ�� */, uint8_t RobotID)
{
	UI_Graph1_t *Graph = (UI_Graph1_t *)Graphs; //����ֻ��һ������ͼ��
	
	/* ��� frame_header */
	Graph->Referee_Transmit_Header.SOF  = 0xA5;
	     if(Counter == 1) Graph->Referee_Transmit_Header.data_length = 6 + 1 * 15;
	else if(Counter == 2) Graph->Referee_Transmit_Header.data_length = 6 + 2 * 15;
	else if(Counter == 5) Graph->Referee_Transmit_Header.data_length = 6 + 5 * 15;
	else if(Counter == 7) Graph->Referee_Transmit_Header.data_length = 6 + 7 * 15;
	Graph->Referee_Transmit_Header.seq  = Graph->Referee_Transmit_Header.seq + 1;
	Graph->Referee_Transmit_Header.CRC8 = CRC08_Calculate((uint8_t *)(&Graph->Referee_Transmit_Header), 4);
	
	/* ��� cmd_id */
	Graph->CMD_ID = ROBOT_COMMUNICATION_ID;
	
	/* ��� student_interactive_header */
	     if(Counter == 1) Graph->Interactive_Header.data_cmd_id = UI_DataID_Draw1;
	else if(Counter == 2) Graph->Interactive_Header.data_cmd_id = UI_DataID_Draw2;
	else if(Counter == 5) Graph->Interactive_Header.data_cmd_id = UI_DataID_Draw5;
	else if(Counter == 7) Graph->Interactive_Header.data_cmd_id = UI_DataID_Draw7;
	Graph->Interactive_Header.sender_id   = RobotID ;      //��ǰ������ID
	Graph->Interactive_Header.receiver_id = RobotID + 256; //��Ӧ������ID
	
	/* ��� frame_tail ��CRC16 */
	     if(Counter == 1)
	{
		UI_Graph1_t *Graph1 = (UI_Graph1_t *)Graphs;
		Graph1->CRC16 = CRC16_Calculate((uint8_t *)Graph1, sizeof(UI_Graph1_t) - 2);
	}
	else if(Counter == 2)
	{
		UI_Graph2_t *Graph2 = (UI_Graph2_t *)Graphs;
		Graph2->CRC16 = CRC16_Calculate((uint8_t *)Graph2, sizeof(UI_Graph2_t) - 2);
	}
	else if(Counter == 5)
	{
		UI_Graph5_t *Graph5 = (UI_Graph5_t *)Graphs;
		Graph5->CRC16 = CRC16_Calculate((uint8_t *)Graph5, sizeof(UI_Graph5_t) - 2);
	}
	else if(Counter == 7)
	{
		UI_Graph7_t *Graph7 = (UI_Graph7_t *)Graphs;
		Graph7->CRC16 = CRC16_Calculate((uint8_t *)Graph7, sizeof(UI_Graph7_t) - 2);
	}
	
	/* ʹ�ô���PushUp������ϵͳ */
	     if(Counter == 1) HAL_UART_Transmit(&huart3, (uint8_t *)Graph, sizeof(Graph), sizeof(UI_Graph1_t));
	else if(Counter == 2) HAL_UART_Transmit(&huart3, (uint8_t *)Graph, sizeof(Graph),sizeof(UI_Graph2_t));
	else if(Counter == 5) HAL_UART_Transmit(&huart3, (uint8_t *)Graph, sizeof(Graph),sizeof(UI_Graph5_t));
	else if(Counter == 7) HAL_UART_Transmit(&huart3, (uint8_t *)Graph, sizeof(Graph),sizeof(UI_Graph7_t));
}


//	// HAL_UART_Transmit_IT(&huart3 ,(uint8_t*)CliendTxBuffer,sizeof(CliendTxBuffer));
//	HAL_UART_Transmit(&huart3, CliendTxBuffer, sizeof(CliendTxBuffer), 1000);      //������  


/* ����UIר�ýṹ�� */
UI_Graph1_t UI_Graph1;
UI_Graph2_t UI_Graph2;
UI_Graph5_t UI_Graph5;
UI_Graph7_t UI_Graph7;
UI_String_t UI_String;
UI_Delete_t UI_Delete;



void test_task(void *argument)
{
    while(1)
    {		
//		Show_User_Data();
			UI_Draw_Line(&UI_Graph5.Graphic[0], "101", UI_Graph_Add, 1, UI_Color_Yellow, 2,  630,   30,  780,  100);
			UI_Draw_Line(&UI_Graph5.Graphic[1], "102", UI_Graph_Add, 1, UI_Color_Yellow, 2,  780,  100,  930,  100);
			UI_Draw_Line(&UI_Graph5.Graphic[2], "103", UI_Graph_Add, 1, UI_Color_Yellow, 2,  990,  100, 1140,  100);
			UI_Draw_Line(&UI_Graph5.Graphic[3], "104", UI_Graph_Add, 1, UI_Color_Yellow, 2, 1140,  100, 1290,   30);
			UI_Draw_Line(&UI_Graph5.Graphic[4], "105", UI_Graph_Add, 1, UI_Color_Yellow, 5,  959,  100,  960,  100);
			UI_PushUp_Graphs(5, &UI_Graph5, Robot_ID_Red_Infantry5);
			
		vTaskDelay(TRANSMIT_SHOW_DATA_TIME);       //35msһ��
    }
}



