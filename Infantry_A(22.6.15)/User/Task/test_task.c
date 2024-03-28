
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

/*
UI结构体录入字符串

输入参数
				string_data_struct 打印字符串数据结构体
				name[3]	图片名字
				operate	图片操作
				layer		图片层数
				color		颜色
				size		字体大小	
				length	字符长度
				width		线条宽度
				start_x	开始x坐标
				start_y	开始y坐标
				Data		字符串数据
*/
void UI_char(string_data_struct_t_* string_data_struct, uint8_t name[3],uint32_t operate, uint32_t layer,uint32_t color,uint32_t size,uint32_t length,uint32_t width,uint32_t start_x,uint32_t start_y,uint8_t* Data )
{	
	for(int i=0;i<3;i++)
		string_data_struct->graphic_data_struct.graphic_name[i]=name[i];
	
	string_data_struct->graphic_data_struct.operate_tpye=operate;
	string_data_struct->graphic_data_struct.graphic_tpye=UI_Graph_Char;
	string_data_struct->graphic_data_struct.layer=layer;
	string_data_struct->graphic_data_struct.color=color;
	
	string_data_struct->graphic_data_struct.start_angle=size;
	string_data_struct->graphic_data_struct.end_angle=length;
	string_data_struct->graphic_data_struct.width=width;
	string_data_struct->graphic_data_struct.start_x=start_x;
	string_data_struct->graphic_data_struct.start_y=start_y;
	
	for(int i=0;i<length;i++)
		string_data_struct->show_Data[i]=Data[i];
}

/*
UI结构体录入浮点数

输入参数
				float_data_struct_t		浮点数数据结构体
				name[3]	图片名字
				operate	图片操作
				layer		图片层数
				color		颜色
				size		字体大小	
				sign_bit 小数点有效位置
				width		线条宽度
				start_x	开始x坐标
				start_y	开始y坐标
				Data		浮点数数据
*/
//void UI_float(float_data_struct_t* float_data_struct, uint8_t name[3],uint32_t operate, uint32_t layer,uint32_t color,uint32_t size,uint32_t sign_bit,uint32_t width,uint32_t start_x,uint32_t start_y,float Data )
//{	
//	for(int i=0;i<3;i++)
//		float_data_struct->graphic_name[i]=name[i];
//	
//	float_data_struct->operate_tpye=operate;
//	float_data_struct->graphic_tpye=UI_Graph_Float;
//	float_data_struct->layer=layer;
//	float_data_struct->color=color;
//	
//	float_data_struct->start_angle=size;
//	float_data_struct->end_angle=sign_bit;
//	float_data_struct->width=width;
//	float_data_struct->start_x=start_x;
//	float_data_struct->start_y=start_y;
//	float_data_struct->graph_Float=Data;
//}

void UI_float(graphic_data_struct_t* graphic_data_struct, uint8_t name[3],uint32_t operate, uint32_t layer,uint32_t color,uint32_t size,uint32_t sign_bit,uint32_t width,uint32_t start_x,uint32_t start_y,float Data )
{	
	uint32_t data=0;
	for(int i=0;i<3;i++)
		graphic_data_struct->graphic_name[i]=name[i];
	
	graphic_data_struct->operate_tpye=operate;
	graphic_data_struct->graphic_tpye=UI_Graph_Float;
	graphic_data_struct->layer=layer;
	graphic_data_struct->color=color;
	
	graphic_data_struct->start_angle=size;
	graphic_data_struct->end_angle=sign_bit;
	graphic_data_struct->width=width;
	graphic_data_struct->start_x=start_x;
	graphic_data_struct->start_y=start_y;
	
	data=Data*1000;
	graphic_data_struct->radius= data			&0x0000003f;
	graphic_data_struct->end_x= (data>>10)&0x0000007f;
	graphic_data_struct->end_y= (data>>21)&0x0000007f;
}



/*
UI结构体录入整型

输入参数
				int_data_struct_t		整形数据结构体
				name[3]	图片名字
				operate	图片操作
				layer		图片层数
				color		颜色
				size		字体大小	
				width		线条宽度
				start_x	开始x坐标
				start_y	开始y坐标
				Data		整形数据
*/
void UI_int(graphic_data_struct_t* graphic_data_struct, uint8_t name[3],uint32_t operate, uint32_t layer,uint32_t color,uint32_t size,uint32_t width,uint32_t start_x,uint32_t start_y,uint32_t Data  )
{	
	for(int i=0;i<3;i++)
		graphic_data_struct->graphic_name[i]=name[i];
	
	graphic_data_struct->operate_tpye=operate;
	graphic_data_struct->graphic_tpye=UI_Graph_Float;
	graphic_data_struct->layer=layer;
	graphic_data_struct->color=color;
	
	graphic_data_struct->start_angle=size;
	graphic_data_struct->width=width;
	graphic_data_struct->start_x=start_x;
	graphic_data_struct->start_y=start_y;
	
	graphic_data_struct->radius= Data			&0x0000003f;
	graphic_data_struct->end_x= (Data>>10)&0x0000007f;
	graphic_data_struct->end_y= (Data>>21)&0x0000007f ;
}
//void UI_int(int_data_struct_t* int_data_struct, uint8_t name[3],uint32_t operate, uint32_t layer,uint32_t color,uint32_t size,uint32_t width,uint32_t start_x,uint32_t start_y,int Data  )
//{	
//	for(int i=0;i<3;i++)
//		int_data_struct->graphic_name[i]=name[i];
//	
//	int_data_struct->operate_tpye=operate;
//	int_data_struct->graphic_tpye=UI_Graph_Float;
//	int_data_struct->layer=layer;
//	int_data_struct->color=color;
//	
//	int_data_struct->start_angle=size;
//	int_data_struct->width=width;
//	int_data_struct->start_x=start_x;
//	int_data_struct->start_y=start_y;
//	int_data_struct->graph_int=Data;
//}


/*
UI结构体录入图像

输入参数
				graphic_data_struct_t		图片数据结构体
				name[3]	图片名字
				operate	图片操作
				graphic	图片类型（直线，椭圆，矩形）
				layer		图片层数
				color		颜色
				width		线条宽度
				start_x	直线（开始x坐标）	矩形（开始x坐标）		椭圆（圆心x坐标）
				start_y	直线（开始y坐标）	矩形（开始y坐标）		椭圆（圆心y坐标）
				end_x		直线（终点x坐标）	矩形（对角线x坐标）	椭圆（x半轴长度）
				end_y		直线（终点y坐标）	矩形（对角线y坐标）	椭圆（y半轴长度）
*/
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

/*
UI结构体录入圆

输入参数
				graphic_data_struct_t		图片数据结构体
				name[3]	图片名字
				operate	图片操作
				layer		图片层数
				color		颜色
				width		线条宽度
				start_x	圆心x坐标
				start_y	圆心y坐标
				radius	半径
		
				
*/
void UI_circle(graphic_data_struct_t* graphic_data_struct, uint8_t name[3],uint32_t operate,uint32_t graphic ,uint32_t layer,uint32_t color,uint32_t width,uint32_t start_x,uint32_t start_y,uint32_t radius )
{	
	for(int i=0;i<3;i++)
		graphic_data_struct->graphic_name[i]=name[i];
	
	graphic_data_struct->operate_tpye=operate;
	graphic_data_struct->graphic_tpye=UI_Graph_Circle;
	graphic_data_struct->layer=layer;
	graphic_data_struct->color=color;

	graphic_data_struct->width=width;
	graphic_data_struct->start_x=start_x;
	graphic_data_struct->start_y=start_y;
	graphic_data_struct->radius=radius;
}


/*
UI结构体录入圆弧

输入参数
				graphic_data_struct_t 图片数据结构体
				name[3]	图片名字
				operate	图片操作
				layer		图片层数
				color		颜色
				width		线条宽度
				start_angle 圆弧开始角度
				end_angle		圆弧结束角度
				start_x	圆心x坐标
				start_y	圆心y坐标
				end_x		x半轴长度
				end_y		y半轴长度
*/
void UI_arc(graphic_data_struct_t* graphic_data_struct, uint8_t name[3],uint32_t operate,uint32_t layer,uint32_t color,uint32_t start_angle,uint32_t end_angle,uint32_t width,uint32_t start_x,uint32_t start_y,uint32_t end_x,uint32_t end_y )
{	
	for(int i=0;i<3;i++)
		graphic_data_struct->graphic_name[i]=name[i];
	
	graphic_data_struct->operate_tpye=operate;
	graphic_data_struct->graphic_tpye=UI_Graph_Arc;
	graphic_data_struct->layer=layer;
	graphic_data_struct->color=color;

	graphic_data_struct->start_angle=start_angle;
	graphic_data_struct->end_angle=end_angle;
	graphic_data_struct->width=width;
	graphic_data_struct->start_x=start_x;
	graphic_data_struct->start_y=start_y;
	graphic_data_struct->end_x=end_x;
	graphic_data_struct->end_y=end_y;
}

/*
客户端绘制图形

输入参数
				cnt	输入几个图像，1，2，5，7
				...	graphic_data_struct_t类型的图片类型
*/

void UI_graphic_ReFresh(int cnt,...)
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

void UI_char_ReFresh(string_data_struct_t_* string_data_struct)
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


graphic_data_struct_t	G1;
graphic_data_struct_t	G2;
graphic_data_struct_t G3;
string_data_struct_t_	G4;
graphic_data_struct_t G5;
void test_task(void *argument)
{


    while(1)
    {		

			UI_graphic(&G1,"1",UI_Graph_ADD,UI_Graph_Line,1,UI_Color_Main,4,0,0,500,500);
			UI_graphic(&G2,"2",UI_Graph_ADD,UI_Graph_Line,2,UI_Color_Main,4,600,600,1000,200);
			UI_graphic_ReFresh(2,G1,G2);
			UI_graphic(&G3,"3",UI_Graph_ADD,UI_Graph_Rectangle,1,UI_Color_Main,4,200,200,1500,500);
			UI_graphic_ReFresh(1,G3);
			UI_char(&G4,"4",UI_Graph_ADD,1,UI_Color_Main,4,3,3,1000,500,"ABC");
			UI_char_ReFresh(&G4);
			
			vTaskDelay(TRANSMIT_SHOW_DATA_TIME);       //35ms一次
    }
}



