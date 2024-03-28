
#include "test_task.h"
#include "delay.h"
#include "FreeRTOS.h"
#include "task.h"
#include "judge.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "usart.h"
#include "stdarg.h"
#include "judge.h"


uint8_t UI_Seq=0;	//包序号


extern  robot_status_t robot_status;


uint16_t  robot_id=5;
uint16_t	operator_ID=0x0105;
/**
  * @brief  通过自己的ID，返回对应操作手客户端ID
  * @param  void
  * @retval 
  * @attention  
  */
int Operator_ID(void)
{
	uint8_t Operator_id;
	if(robot_status.robot_id < 10)        //红方
	{
		Operator_id = robot_status.robot_id + 0x0100 ;
	}
	else if (robot_status.robot_id > 10)  //蓝方
	{
		Operator_id = robot_status.robot_id + 0x0064 ;
	}
	return Operator_id;
}





void UI_graphic(graphic_data_struct_t* graphic_data_struct, uint8_t name[3],uint32_t operate,uint32_t graphic ,uint32_t layer,uint32_t color,uint32_t width,uint32_t start_x,uint32_t start_y,uint32_t end_x,uint32_t end_y )
{	
	for(int i=0;i<3;i++)
		graphic_data_struct->graphic_name[i]=name[i];
	
	graphic_data_struct->operate_tpye=operate;
	graphic_data_struct->graphic_tpye=graphic;
	graphic_data_struct->layer=layer;
	graphic_data_struct->color=color;

	graphic_data_struct->width=width;
	graphic_data_struct->start_x=start_x;
	graphic_data_struct->start_y=start_y;
	graphic_data_struct->end_x=end_x;
	graphic_data_struct->end_y=end_y;
}



void UI_Line(interaction_figure_t* graphic_data_struct, uint8_t name[3],       \
	uint32_t operate,uint32_t layer,uint32_t color,           \
	uint32_t width,uint32_t start_x,uint32_t start_y,uint32_t end_x,uint32_t end_y )
{	
	for(int i=0;i<3;i++)
	graphic_data_struct->figure_name[i]=name[i];
	
	graphic_data_struct->operate_tpye=operate;
	graphic_data_struct->figure_tpye=UI_Graph_Line;
	graphic_data_struct->layer=layer;
	graphic_data_struct->color=color;

	graphic_data_struct->details_a = 0;
	graphic_data_struct->details_b = 0;
	
	graphic_data_struct->width=width;
	graphic_data_struct->start_x=start_x;
	graphic_data_struct->start_y=start_y;
	
	graphic_data_struct->details_c=0;
	graphic_data_struct->details_d=end_x;
	graphic_data_struct->details_e=end_y;
}


void UI_Rectangle(interaction_figure_t* graphic_data_struct, uint8_t name[3],            \
	uint32_t operate,uint32_t graphic ,uint32_t layer,uint32_t color,                       \
	uint32_t width,uint32_t start_x,uint32_t start_y,       \
	uint32_t end_x,uint32_t end_y)
{	
	for(int i=0;i<3;i++)
	graphic_data_struct->figure_name[i]=name[i];
	
	graphic_data_struct->operate_tpye=operate;
	graphic_data_struct->figure_tpye=UI_Graph_Rectangle;
	graphic_data_struct->layer=layer;
	graphic_data_struct->color=color;

	graphic_data_struct->details_a = 0;
	graphic_data_struct->details_b = 0;
	
	graphic_data_struct->width=width;
	graphic_data_struct->start_x=start_x;
	graphic_data_struct->start_y=start_y;
	
	
	graphic_data_struct->details_c=0;
	graphic_data_struct->details_d=end_x;
	graphic_data_struct->details_e=end_y;
}


void UI_Circle(interaction_figure_t* graphic_data_struct, uint8_t name[3],	\
	uint32_t operate,uint32_t graphic ,uint32_t layer,uint32_t color,	\
	uint32_t width,uint32_t start_x,uint32_t start_y,uint32_t radius )
{	
	for(int i=0;i<3;i++)
	graphic_data_struct->figure_name[i]=name[i];
	
	graphic_data_struct->operate_tpye=operate;
	graphic_data_struct->figure_tpye=UI_Graph_Circle;
	graphic_data_struct->layer=layer;
	graphic_data_struct->color=color;

	graphic_data_struct->details_a = 0;
	graphic_data_struct->details_b = 0;
	
	graphic_data_struct->width=width;
	graphic_data_struct->start_x=start_x;
	graphic_data_struct->start_y=start_y;
	
	graphic_data_struct->details_c=radius;
	graphic_data_struct->details_d=0;
	graphic_data_struct->details_e=0;
}

void UI_Ellipse(interaction_figure_t* graphic_data_struct, uint8_t name[3],            \
	uint32_t operate,uint32_t graphic ,uint32_t layer,uint32_t color,                       \
	uint32_t width,uint32_t start_x,uint32_t start_y,       \
	uint32_t XHalfAxis,uint32_t YHalfAxis)
{	
	for(int i=0;i<3;i++)
	graphic_data_struct->figure_name[i]=name[i];
	
	graphic_data_struct->operate_tpye=operate;
	graphic_data_struct->figure_tpye=UI_Graph_Ellipse;
	graphic_data_struct->layer=layer;
	graphic_data_struct->color=color;

	graphic_data_struct->details_a = 0;
	graphic_data_struct->details_b = 0;
	
	graphic_data_struct->width=width;
	graphic_data_struct->start_x=start_x;
	graphic_data_struct->start_y=start_y;
	
	
	graphic_data_struct->details_c=0;
	graphic_data_struct->details_d=XHalfAxis;
	graphic_data_struct->details_e=YHalfAxis;
}

void UI_Arc(interaction_figure_t* graphic_data_struct, uint8_t name[3],	\
	uint32_t operate,uint32_t layer,uint32_t color,	\
	uint32_t start_angle,uint32_t end_angle,uint32_t width,	\
	uint32_t start_x,uint32_t start_y,uint32_t XHalfAxis,uint32_t YHalfAxis )
{	
	for(int i=0;i<3;i++)
	graphic_data_struct->figure_name[i]=name[i];
	
	graphic_data_struct->operate_tpye=operate;
	graphic_data_struct->figure_tpye=UI_Graph_Arc;
	graphic_data_struct->layer=layer;
	graphic_data_struct->color=color;

	graphic_data_struct->details_a = start_angle;
	graphic_data_struct->details_b = end_angle;
	
	graphic_data_struct->width=width;
	graphic_data_struct->start_x=start_x;
	graphic_data_struct->start_y=start_y;
	
	graphic_data_struct->details_c=0;
	graphic_data_struct->details_d=XHalfAxis;
	graphic_data_struct->details_e=YHalfAxis;
}

void UI_Float(interaction_figure_t* graphic_data_struct, uint8_t name[3],	\
	uint32_t operate, uint32_t layer,uint32_t color,	\
	uint32_t size,uint32_t width,uint32_t start_x,uint32_t start_y,float Data )
{	
	uint32_t data=0;
	for(int i=0;i<3;i++)
	graphic_data_struct->figure_name[i]=name[i];
	
	graphic_data_struct->operate_tpye=operate;
	graphic_data_struct->figure_tpye=UI_Graph_Float;
	graphic_data_struct->layer=layer;
	graphic_data_struct->color=color;

	graphic_data_struct->details_a = size;
	graphic_data_struct->details_b = 0;
	
	graphic_data_struct->width=width;
	graphic_data_struct->start_x=start_x;
	graphic_data_struct->start_y=start_y;
	
	data=Data*1000;
	graphic_data_struct->details_c= data			&0x0000003f;
	graphic_data_struct->details_d= (data>>10)&0x0000007f;
	graphic_data_struct->details_e= (data>>21)&0x0000007f;
}

void UI_Int(interaction_figure_t* graphic_data_struct, uint8_t name[3],	\
	uint32_t operate, uint32_t layer,uint32_t color,	\
	uint32_t size,uint32_t width,uint32_t start_x,uint32_t start_y,uint32_t Data  )
{	
	for(int i=0;i<3;i++)
	graphic_data_struct->figure_name[i]=name[i];
	
	graphic_data_struct->operate_tpye=operate;
	graphic_data_struct->figure_tpye=UI_Graph_Int;
	graphic_data_struct->layer=layer;
	graphic_data_struct->color=color;
	
	graphic_data_struct->details_a=size;
	graphic_data_struct->details_b = 0;
	
	graphic_data_struct->width=width;
	graphic_data_struct->start_x=start_x;
	graphic_data_struct->start_y=start_y;
	
	graphic_data_struct->details_c= Data			&0x0000003f;
	graphic_data_struct->details_d= (Data>>10)&0x0000007f;
	graphic_data_struct->details_e= (Data>>21)&0x0000007f ;
}

void UI_Char(ext_client_custom_character_t* string_data_struct, uint8_t name[3],          \
	uint32_t operate, uint32_t layer,uint32_t color,     \
	uint32_t size,uint32_t length,uint32_t width,uint32_t start_x,uint32_t start_y,uint8_t* Data )
{	
	for(int i=0;i<3;i++)
	string_data_struct->grapic_data_struct.figure_name[i]=name[i];
	
	string_data_struct->grapic_data_struct.operate_tpye=operate;
	string_data_struct->grapic_data_struct.figure_tpye=UI_Graph_Char;
	string_data_struct->grapic_data_struct.layer=layer;
	string_data_struct->grapic_data_struct.color=color;
	
	string_data_struct->grapic_data_struct.details_a = size;
	string_data_struct->grapic_data_struct.details_b = length;
	
	string_data_struct->grapic_data_struct.width=width;
	string_data_struct->grapic_data_struct.start_x=start_x;
	string_data_struct->grapic_data_struct.start_y=start_y;
	
	string_data_struct->grapic_data_struct.details_c=0;
	string_data_struct->grapic_data_struct.details_d=0;
	string_data_struct->grapic_data_struct.details_e=0;
	
	for(int i=0;i<length;i++)
	string_data_struct->data[i]=Data[i];
}

/*
客户端绘制图形

输入参数
				cnt	输入几个图像，1，2，5，7
				...	graphic_data_struct_t类型的图片类型
*/

void UI_Graphic_ReFresh(int cnt,...)
{
	ext_Send_User_Data_t	ShowData;			//客户端信息
	graphic_data_struct_t graphic_data;
	uint8_t* client_Data;
	uint8_t CliendTxBuffer[SEND_MAX_LEN];
	
	va_list UI;
	va_start(UI,cnt);
	
//	ShowData.txFrameHeader.SOF = UI_SOF;
//	ShowData.txFrameHeader.data_length =6+cnt*15;
//	ShowData.txFrameHeader.seq = UI_Seq;
	
	CliendTxBuffer[0]=UI_SOF;CliendTxBuffer[1]=(6+cnt*15)&0x00ff;CliendTxBuffer[2]=((6+cnt*15)>>8)&0x00ff;CliendTxBuffer[3]=UI_Seq;
	
//	memcpy(CliendTxBuffer, &ShowData,LEN_HEADER-1);//写入帧头数据							//该函数把uint_8当uingt_16写入
	Append_CRC8_Check_Sum(CliendTxBuffer, LEN_HEADER);//写入帧头CRC8校验码
	ShowData.CmdID = ROBOT_COMMUNICATION_ID;
	
	
	switch(cnt+0x0100)//数据段内容的ID
	{
		case UI_Data_ID_Draw1:ShowData.dataFrameHeader.data_cmd_id=UI_Data_ID_Draw1;break;
		case UI_Data_ID_Draw2:ShowData.dataFrameHeader.data_cmd_id=UI_Data_ID_Draw2;break;
		case UI_Data_ID_Draw5:ShowData.dataFrameHeader.data_cmd_id=UI_Data_ID_Draw5;break;
		case UI_Data_ID_Draw7:ShowData.dataFrameHeader.data_cmd_id=UI_Data_ID_Draw7;break;
	
	}
	
	
	ShowData.dataFrameHeader.send_ID 	 = robot_id ;//发送者的ID
	ShowData.dataFrameHeader.receiver_ID = operator_ID;//客户端的ID，只能为发送者机器人对应的客户端
	
	memcpy(CliendTxBuffer+LEN_HEADER, &ShowData.CmdID, LEN_CMDID+LEN_DATAFH);//写入数据
	
	for(int i=0;i<cnt;i++)
	{
		graphic_data=va_arg (UI,graphic_data_struct_t);
		client_Data=(uint8_t*)&graphic_data;
		for(int t=0;t<15;t++)
		{
			CliendTxBuffer[LEN_HEADER+LEN_CMDID+LEN_DATAFH+i*15+t]=client_Data[t];
		}
	}
	
	
	Append_CRC16_Check_Sum(CliendTxBuffer,LEN_HEADER+LEN_CMDID+LEN_DATAFH+cnt*15+LEN_TAIL);//写入数据段CRC16帧尾校验码	

	while(HAL_UART_Transmit(&huart3, CliendTxBuffer, LEN_HEADER+LEN_CMDID+LEN_DATAFH+cnt*15+LEN_TAIL, 1000)!=HAL_OK);      //发数据  5+2+6+数据+2
	
	UI_Seq++;
	
	va_end(UI);
	
	

}

/*
客户端绘制字符图形

输入参数
				string_data_struct_t_	字符串数据结构体
*/

void UI_Char_ReFresh(ext_client_custom_character_t* string_data_struct)
{
	ext_Send_User_Data_t	ShowData;
	uint8_t CliendTxBuffer[SEND_MAX_LEN];
	uint8_t*	string_data;
//	ShowData.txFrameHeader.SOF = UI_SOF;
//	ShowData.txFrameHeader.data_length =6+45;
//	ShowData.txFrameHeader.seq = UI_Seq;
	
	CliendTxBuffer[0]=UI_SOF;
	CliendTxBuffer[1]=(6+45)&0x00ff;
	CliendTxBuffer[2]=((6+45)>>8)&0x00ff;
	CliendTxBuffer[3]=UI_Seq;

	Append_CRC8_Check_Sum(CliendTxBuffer, LEN_HEADER);//写入帧头CRC8校验码
	ShowData.CmdID = ROBOT_COMMUNICATION_ID;
	ShowData.dataFrameHeader.data_cmd_id=UI_Data_ID_DrawChar;
	ShowData.dataFrameHeader.send_ID 	 = robot_id ;//发送者的ID
	ShowData.dataFrameHeader.receiver_ID = operator_ID;//客户端的ID，只能为发送者机器人对应的客户端
	
	memcpy(CliendTxBuffer+LEN_HEADER, &ShowData.CmdID, LEN_CMDID+LEN_DATAFH);//写入数据
	
	string_data=(uint8_t*)string_data_struct;
	for(int i=0;i<45;i++)
	{
		CliendTxBuffer[LEN_HEADER+LEN_CMDID+LEN_DATAFH+i]=string_data[i];
	}
	
	Append_CRC16_Check_Sum(CliendTxBuffer,LEN_HEADER+LEN_CMDID+LEN_DATAFH+45+LEN_TAIL);//写入数据段CRC16帧尾校验码	

	while(HAL_UART_Transmit(&huart3, CliendTxBuffer, LEN_HEADER+LEN_CMDID+LEN_DATAFH+45+LEN_TAIL, 1000)!=HAL_OK);      //发数据  5+2+6+数据+2
	
	UI_Seq++;
}


/*
删除图片

输入参数
				
				operate								0：空操作，1：删除图层，2：删除全部
				layer									图层
*/

void UI_Del(uint8_t operate,uint8_t layer)
{
	ext_Send_User_Data_t	ShowData;
	uint8_t CliendTxBuffer[SEND_MAX_LEN];
//	ShowData.txFrameHeader.SOF = UI_SOF;
//	ShowData.txFrameHeader.data_length =8;
//	ShowData.txFrameHeader.seq = UI_Seq;
	CliendTxBuffer[0]=UI_SOF;CliendTxBuffer[1]=(8)&0x00ff;CliendTxBuffer[2]=((8)>>8)&0x00ff;CliendTxBuffer[3]=UI_Seq;
	
	Append_CRC8_Check_Sum(CliendTxBuffer, LEN_HEADER);//写入帧头CRC8校验码
	ShowData.CmdID = ROBOT_COMMUNICATION_ID;
	
	
	ShowData.dataFrameHeader.data_cmd_id=UI_Data_ID_Del;
	ShowData.dataFrameHeader.send_ID 	 = robot_id;//发送者的ID
	ShowData.dataFrameHeader.receiver_ID = operator_ID;//客户端的ID，只能为发送者机器人对应的客户端
	
	memcpy(CliendTxBuffer+LEN_HEADER, &ShowData.CmdID, LEN_CMDID+LEN_DATAFH);//写入数据
	
	CliendTxBuffer[LEN_HEADER+LEN_CMDID+LEN_DATAFH]=operate;
	CliendTxBuffer[LEN_HEADER+LEN_CMDID+LEN_DATAFH+1]=layer;
	
	Append_CRC16_Check_Sum(CliendTxBuffer,LEN_HEADER+LEN_CMDID+LEN_DATAFH+2+LEN_TAIL);//写入数据段CRC16帧尾校验码
	
	while(HAL_UART_Transmit(&huart3, CliendTxBuffer,LEN_HEADER+LEN_CMDID+LEN_DATAFH+2+LEN_TAIL, 1000)!=HAL_OK);      //发数据  5+2+6+数据+2
	
	UI_Seq++;
}


interaction_figure_t	G1;
interaction_figure_t	G2;
interaction_figure_t G3;
ext_client_custom_character_t	G4;
interaction_figure_t G5;
UI_Graph7_t UI_Graph7;


/* 中央标尺高度变量 */
uint16_t y01 = 455;
uint16_t y02 = 420;
uint16_t y03 = 280;
uint16_t y04 = 230;

uint8_t UI_Capacitance=30;
float Capacitance_X;
float X = 1850.0f;

interaction_figure_t	G10;
interaction_figure_t	G11;
interaction_figure_t	G12;
interaction_figure_t	G13;
interaction_figure_t	G14;
interaction_figure_t	G15;
interaction_figure_t	G16;

interaction_figure_t	G20;
void test_task(void *argument)
{
		uint16_t UI_PushUp_Counter = 261;
    while(1)
    {		
//			UI_PushUp_Counter++;

//		if(UI_PushUp_Counter % 321 == 0)
//		{
//			UI_Line(&G10, "008", UI_Graph_Add, 0, UI_Color_Green, 1,  900,   y03,  940,   y03); //第三行左横线
//			UI_Line(&G11, "009", UI_Graph_Add, 0, UI_Color_Green, 5,  959,   y03,  960,   y03); //第三行中心点
//			UI_Line(&G12, "010", UI_Graph_Add, 0, UI_Color_Green, 1,  980,   y03, 1020,   y03); //第三行右横线
//			UI_Line(&G13, "011", UI_Graph_Add, 0, UI_Color_Green, 1,  930,   y04,  950,   y04); //第四行左横线
//			UI_Line(&G14, "012", UI_Graph_Add, 0, UI_Color_Green, 5,  959,   y04,  960,   y04); //第四行中心点
//			UI_Line(&G15, "013", UI_Graph_Add, 0, UI_Color_Green, 1,  970,   y04,  990,   y04); //第四行右横线
//			UI_Line(&G16, "014", UI_Graph_Add, 0, UI_Color_Green, 1,  960,y04-10,  960,y04-30); //第四行下竖线
//			UI_Graphic_ReFresh(7,G10,G11,G12,G13,G14,G15,G16);
//			UI_Graphic_ReFresh(2,G10,G11);
//			HAL_Delay(20);
//			UI_Graphic_ReFresh(2,G12,G13);
//			HAL_Delay(20);
//			UI_Graphic_ReFresh(2,G14,G15);
//			HAL_Delay(20);
//			UI_Graphic_ReFresh(1,G16);
//			HAL_Delay(20);
//			continue;
//		}		
//		if(UI_PushUp_Counter % 10 == 0)
			UI_Line(&G20, "202", UI_Graph_Add, 2, UI_Color_Orange, 20, Capacitance_X, 334, 1870, 334);
			UI_Graphic_ReFresh(1,G20);
			while(1)
			{
//			{				
			Capacitance_X  = X - 4.1f * UI_Capacitance;
			if(50 < UI_Capacitance && UI_Capacitance <= 100) UI_Line(&G20, "202", UI_Graph_Change, 2, UI_Color_Green , 20, Capacitance_X, 334, 1870, 334);
			if(35 < UI_Capacitance && UI_Capacitance <=  50) UI_Line(&G20, "202", UI_Graph_Change, 2, UI_Color_Yellow, 20, Capacitance_X, 334, 1870, 334);
			if(0  < UI_Capacitance && UI_Capacitance <=  35) UI_Line(&G20, "202", UI_Graph_Change, 2, UI_Color_Orange, 20, Capacitance_X, 334, 1870, 334);
			UI_Graphic_ReFresh(1,G20);
			
//				continue;
//			}
				
			vTaskDelay(TRANSMIT_SHOW_DATA_TIME);       //35ms一次
			}
    }
}



