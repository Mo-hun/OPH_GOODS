#include <avr/io.h>
#include <util/delay.h>
#include <math.h>
#include "Interface.h"
#include "Move.h"
#include "Motor.h"
#include "Sensor.h"
#include <stdio.h>
#include <avr/interrupt.h>

void M1(void);
void M2(void);

void non_Holonomic(float Fx, float Fy, float Fw);
void HolonomicW(float f_agl, float f_speed, float fw_speed);

long Read_Encoder(unsigned char motor);
void enPose(void);

//감속 시점이 0일 경우 처음 속도 유지
//90도 회전 : 속도=50, 거리=95
void Holonomic_distance(int f_agl, int f_speed, int mm, int stop);
//왼:1, 120, 오:2, 95, 뒤=3, 240
void Correct_Pose(unsigned char DIR, unsigned char value);
//value1값에 걸리면 1 리턴 value2 값에 걸리면 2 리턴 value들에 0을 넣으면 인식 안함
unsigned char Holonomic_SENSOR(int f_agl, int f_speed, unsigned char value1, unsigned char value2, int stop, int s_stop);
//s_value=감지 할 센서
unsigned char Holonomic_PSD_BarCode_cnt(int f_agl, int f_speed, unsigned char p_num, unsigned char p_value, int stop, int s_stop, unsigned char s_value);

void CAM_protocol(unsigned char p);
void CAM_V1_Read(unsigned int x1, unsigned int x2, unsigned int y1, unsigned int y2);
void CAM_V1_XY(unsigned int x1, unsigned int x2,unsigned int y1,unsigned int y2, unsigned char obj, unsigned int Point_X, unsigned int Point_Y);
unsigned char PSD_Avoid(unsigned int mm, unsigned int s_stop);


/*
READ_SENSOR()&0x??

0x01 - 유도형 센서 1번 전면
0x02 - 유도형 센서 2번 중앙
0x04 - 광 센서 1번 왼
0x08 - 광 센서 2번 중
0x10 - 광 센서 3번 오
*/

//정의
#define Buzzer_ON()		(PORTB|=0x08)
#define Buzzer_OFF()	(PORTB&=~0x08)

#define SW1				(~PINB&0x10)
#define SW2				(~PINB&0x20)
#define SW3				(~PINB&0x40)

//변수
/*
Pose[0] : x축 이동거리
Pose[1] : y축 이동거리
Pose[2] : w축 이동거리
*/
float Pose[3]={0, };

//가감속 관련
float speed=0, next_speed=0, acc=5;
float wspeed=0, next_wspeed=0, wacc=5;

//lcd디스플레이에 출력할 때 쓰는 배열
char str[20]={0, };

//컬러 데이터를 저장할 배열
unsigned int Color_data[9][5], Color_N=0;

//P구역 선을 감지해 변수에 저장
unsigned char decision=0;

//선의 개수 저장
unsigned char Line_Num=0;

int main(void)
{

	Interface_init(); //인터페이스 초기화

	LM629_HW_Reset();

	MCU_init();	   // MCU 초기화

	Motor_init();  // Motor 드라이버 초기화

	Sensor_init();

	TCCR1A=0x00;
	TCCR1B=0x05;
	TCNT1=65392;
	//인터럽트 활성화
	TIMSK=0x04;
	//전역 인터럽트 연결
	sei();

	sprintf(str, "Loading..");
	lcd_display_str(0, 0, str);
	_delay_ms(300);
	lcd_clear_screen();

	while(1){
		if(SW1){
			M1();
			M2();
		}
		else if(SW2){
			while(1){
				putchar1(10);
				putchar1(18);

				CAM_V1_Read(0,200,0,320);
				sprintf(str,"%d %d",Color_data[0][1],Color_data[0][2]);
				lcd_display_str(0,0,str);
			}
		}
		else if(SW3){
		decision=0x08;
		Line_Num=5;

		Holonomic_SENSOR(270, 150, decision, decision, 0, 100);speed=0;StopMotion(9);
		_delay_ms(100);
		CAM_V1_XY(0, 200, 140, 200, 0, 130, 160);speed=0;
		Holonomic_distance(0, 70, 140, 0);speed=0;
		Holonomic_distance(180, 70, 140, 0);speed=0;
		Holonomic_SENSOR(270, 150, decision, decision, 0, 100);speed=0;StopMotion(9);
		_delay_ms(100);
		CAM_V1_XY(0, 200, 130, 190, 0, 130, 160);speed=0;
		Holonomic_distance(0, 70, 140, 0);speed=0;
		Holonomic_distance(180, 70, 140, 0);speed=0;
	Holonomic_SENSOR(270, 150, decision, decision, 0, 100);speed=0;StopMotion(9);
		_delay_ms(100);
		CAM_V1_XY(0, 200, 130, 190, 0, 130, 160);speed=0;
		Holonomic_distance(0, 70, 140, 0);speed=0;
		Holonomic_distance(180, 70, 140, 0);speed=0;

	Holonomic_SENSOR(270, 150, decision, decision, 0, 100);speed=0;StopMotion(9);
		_delay_ms(100);
		CAM_V1_XY(0, 200, 130, 190, 0, 130, 160);speed=0;
		Holonomic_distance(0, 70, 140, 0);speed=0;
		Holonomic_distance(180, 70, 140, 0);speed=0;

	Holonomic_SENSOR(270, 150, decision, decision, 0, 100);speed=0;StopMotion(9);
		_delay_ms(100);
		CAM_V1_XY(0, 200, 130, 190, 0, 130, 160);speed=0;
		Holonomic_distance(0, 70, 140, 0);speed=0;
		Holonomic_distance(180, 70, 140, 0);speed=0;


			StopMotion(9);
		}
	}
}

void M1(void){
	Holonomic_distance(360, 50, 95, 0);speed=0;
	Correct_Pose(2, 95);speed=0;
	decision=Holonomic_SENSOR(0, 150, 0x01, 0x08, 0, 200);speed=0;
	decision=0x01;
	display_char(0, 0, decision);
	Holonomic_distance(-1, 50, 95, 0);speed=0;
	Correct_Pose(3, 240);speed=0;
	Holonomic_PSD_BarCode_cnt(270, 200, 2, 200, 0, 0, 0);speed=0;
	Holonomic_distance(0, 70, 70, 0);speed=0;
	Correct_Pose(1, 120);speed=0;
	Line_Num=Holonomic_PSD_BarCode_cnt(90, 200, 7, 230, 0, 0, decision);speed=0;
	display_char(0, 0, Line_Num);

	//v1모드:CAM_protocol(18); 우선순위 큰거부터
	CAM_protocol(18);
	putchar1(13);
	_delay_ms(100);

	Correct_Pose(2, 95);speed=0;

	for(unsigned int i=0; i<Line_Num; i++){
		Holonomic_SENSOR(270, 150, decision, decision, 0, 100);speed=0;StopMotion(9);
		_delay_ms(100);
		CAM_V1_XY(0, 200, 130, 190, 0, 130, 160);speed=0;
		Holonomic_distance(0, 70, 140, 0);speed=0;
		Holonomic_distance(180, 70, 140, 0);speed=0;
	}

	Holonomic_PSD_BarCode_cnt(270, 200, 2, 200, 0, 0, 0);speed=0;

	StopMotion(9);
}

void M2(void){
	unsigned char select=0;
	//지우셈
	//decision=0x02;
	Correct_Pose(1, 120);speed=0;
	Correct_Pose(3, 240);speed=0;
	Holonomic_distance(90, 100, 300, 0);speed=0;

	select=PSD_Avoid(700, 100);
	if(decision == select){
		//첫 번째 블럭 사이가 맞았을 경우
		Buzzer_ON();
		_delay_ms(100);
		Buzzer_OFF();
	}
	else{
		//안맞았을 경우
		Holonomic_PSD_BarCode_cnt(180, 200, 4, 190, 0, 0, 0);speed=0;
		Correct_Pose(3, 240);speed=0;
		Holonomic_distance(90, 200, 950, 800);speed=0;
		Correct_Pose(3, 240);speed=0;
		PSD_Avoid(700, 100);
	}

	StopMotion(9);
}

ISR(TIMER1_OVF_vect){
	TCNT1=65392;

	if(next_speed>speed){
		speed+=acc;
		if(speed>next_speed)speed=next_speed;
	}
	else if(next_speed<speed){
		speed-=acc;
		if(speed<next_speed)speed=next_speed;
	}

	if(next_wspeed>wspeed){
		wspeed+=wacc;
		if(wspeed>next_wspeed)wspeed=next_wspeed;
	}
	else if(next_wspeed<wspeed){
		wspeed-=wacc;
		if(wspeed<next_wspeed)wspeed=next_wspeed;
	}
}


void non_Holonomic(float Fx, float Fy, float Fw){

	float V[3]={0,0,0};

	V[0]=( 0.056*Fx)+(0.033*Fy)+(0.14*Fw);
	V[1]=(-0.065*Fy)+(0.14*Fw);
	V[2]=(-0.056*Fx)+(0.033*Fy)+(0.14*Fw);

	SetVelocity(0, V[0]*65536);
	SetVelocity(1, V[1]*65536);
	SetVelocity(2, V[2]*65536);

	StartMotion();
}

void HolonomicW(float f_agl, float f_speed, float fw_speed){
	long Fx=0, Fy=0, Fw=0; //속도

	Fx = f_speed * cos(f_agl*0.017453);
	Fy = f_speed * sin(f_agl*0.017453);
	Fw=fw_speed;
	if(f_agl>=360||f_agl<0){
		Fx=0;
		Fy=0;
		Fw=f_speed;
		if(f_agl<0)Fw=-f_speed;
	}

	non_Holonomic(Fx,Fy,Fw);
}

long Read_Encoder(unsigned char motor){
	long en_buff=0;

	WriteCommand(motor,RDRP);	//엔코더 읽기 명령

	en_buff=(en_buff|ReadData(motor))<<8;
	en_buff=(en_buff|ReadData(motor))<<8;
	en_buff=(en_buff|ReadData(motor))<<8;
	en_buff|=ReadData(motor);

	return en_buff;
}

void enPose(void){
	long EN_data[3];

	EN_data[0]=Read_Encoder(0);
	EN_data[1]=Read_Encoder(1);
	EN_data[2]=Read_Encoder(2);

	Pose[0]=(double)(EN_data[0]-EN_data[2])/2.0/165.398;
	Pose[1]=(double)((EN_data[0]+EN_data[2])-EN_data[1])/2.0/190.986;
	//Pose[1]=(double)((EN_data[0]-EN_data[2])-EN_data[1])/191.0;
	Pose[2]=(double)(EN_data[0]+EN_data[1]+EN_data[2])/3.0/416.666;
}

void Holonomic_distance(int f_agl, int f_speed, int mm, int stop){
	double distance=0;

	WriteCommand(0,DFH);
	WriteCommand(1,DFH);
	WriteCommand(2,DFH);

	acc=5;
	next_speed=f_speed;

	while(1){
		enPose();
		if(f_agl>=0)distance=sqrt((Pose[0]*Pose[0])+(Pose[1]*Pose[1]));
		else distance=Pose[2];

		if(fabs(distance)>=mm)break;
		else if(fabs(distance)>=stop && stop){
			next_speed=100;
		}

		HolonomicW(f_agl, speed, 0);
	}
}

void Correct_Pose(unsigned char DIR, unsigned char value){
	int err=0, err1=0, err2=0;
	while(1){
		//왼쪽
		if(DIR==1){
			err1=psd_value[1]-value;
			err2=psd_value[3]-200;

			err=err1-err2;

			non_Holonomic(0,err1,(float)err*0.5);
		}
		//오른쪽
		else if(DIR==2){
			err1=value-psd_value[8];
			err2=200-psd_value[6];

			err=err1-err2;

			non_Holonomic(0,err1,(float)err*0.5);
		}
		//뒤
		else if(DIR==3){
			err1=psd_value[4]-value;
			err2=psd_value[5]-220;

			err=err1-err2;

			non_Holonomic(err1,0, (float)err*0.5);
		}

		if(fabs(err)<3 && fabs(err1)<3)break;
	}
}

unsigned char Holonomic_SENSOR(int f_agl, int f_speed, unsigned char value1, unsigned char value2, int stop, int s_stop){
	double distance=0;

	WriteCommand(0,DFH);
	WriteCommand(1,DFH);
	WriteCommand(2,DFH);

	acc=5;
	next_speed=f_speed;

	while(1){
		enPose();

		if(f_agl>=0&&f_agl<360){
			distance=sqrt((Pose[0]*Pose[0])+(Pose[1]*Pose[1]));
		}
		else {
			distance=Pose[2];
		}

		if(READ_SENSOR()&value1 && fabs(distance)>=s_stop){
			return value1;
		}
		if(READ_SENSOR()&value2 && fabs(distance)>=s_stop){
			return value2;
		}
		else if(fabs(distance)>=stop && stop){
			next_speed=100;
		}

		HolonomicW(f_agl, speed, 0);
	}
}

unsigned char Holonomic_PSD_BarCode_cnt(int f_agl, int f_speed, unsigned char p_num, unsigned char p_value, int stop, int s_stop, unsigned char s_value){
	double distance=0;
	unsigned char s_flg=0, bcnt=0;

	WriteCommand(0,DFH);
	WriteCommand(1,DFH);
	WriteCommand(2,DFH);

	acc=5;
	next_speed=f_speed;

	while(1){
		enPose();
		if(f_agl>=0)distance=sqrt((Pose[0]*Pose[0])+(Pose[1]*Pose[1]));
		else distance=Pose[2];

		if(psd_value[p_num]>=p_value &&fabs(distance)>=s_stop)break;
		else if(fabs(distance)>=stop && stop){
			next_speed=100;
		}

		HolonomicW(f_agl, speed, 0);

		if(READ_SENSOR()&s_value && !s_flg && s_value){
			Buzzer_ON();
			s_flg=1;
			++bcnt;
		}
		else if(!(READ_SENSOR()&s_value) && s_flg && s_value){
			Buzzer_OFF();
			s_flg=0;
		}
	}
	return bcnt;
}

void CAM_protocol(unsigned char p){

	putchar1(p);
	_delay_ms(1);

	getchar1();
	getchar1();
	getchar1();
	getchar1();
	getchar1();
}

void CAM_V1_Read(unsigned int x1 ,unsigned int x2, unsigned int y1, unsigned int y2){
	unsigned char i=0;
	unsigned int Color_data_buff[5];

	CAM_protocol(18); //V1 모드

	CAM_V1_EN=1;
	while(CAM_header_cnt < 2);
	CAM_V1_EN=0;
	CAM_header_cnt=0;

	CAM_buff_N=CAM_buff[1]-'0';

	Color_N=0;



	for(i=0;i<CAM_buff_N; ++i){
		Color_data_buff[0] = (CAM_buff[(i*15)+3] - '0');
		Color_data_buff[2] = (CAM_buff[(i*15)+5]-'0') * 100 +(CAM_buff[(i*15)+6]-'0') * 10 +(CAM_buff[(i*15)+7]-'0');
		Color_data_buff[1] = (CAM_buff[(i*15)+8]-'0') * 100 +(CAM_buff[(i*15)+9]-'0') * 10 +(CAM_buff[(i*15)+10]-'0');
		Color_data_buff[4] = (CAM_buff[(i*15)+11]-'0') * 100 +(CAM_buff[(i*15)+12]-'0') * 10 +(CAM_buff[(i*15)+13]-'0');
		Color_data_buff[3] = (CAM_buff[(i*15)+14]-'0') * 100 +(CAM_buff[(i*15)+15]-'0') * 10 +(CAM_buff[(i*15)+16]-'0');

		if(Color_data_buff[1] >= x1 && Color_data_buff[1] <= x2 && Color_data_buff[2] >= y1 && Color_data_buff[2] <= y2){
			Color_data[Color_N][0] = Color_data_buff[0];
			Color_data[Color_N][1] = Color_data_buff[1];
			Color_data[Color_N][2] = Color_data_buff[2];
			Color_data[Color_N][3] = Color_data_buff[3];
			Color_data[Color_N][4] = Color_data_buff[4];

			++Color_N;
		}
	}
}

void CAM_V1_XY(unsigned int x1, unsigned int x2,unsigned int y1,unsigned int y2, unsigned char obj, unsigned int Point_X, unsigned int Point_Y){
	unsigned int x=0, y=0;
	int errX=0, errY=0;



	while(1){
		CAM_V1_Read(x1,x2,y1,y2);

		x = Color_data[obj][1];
		y = Color_data[obj][2];
		errX = Point_X - x;
		errY = y - Point_Y;

		non_Holonomic(errX,errY,0);

		if(fabs(errX)<3 && fabs(errY)<3) break;
	}
}

unsigned char PSD_Avoid(unsigned int mm, unsigned int s_stop){
	int err1=0, err2=0, err=0;
	double distance=0;

	WriteCommand(0,DFH);
	WriteCommand(1,DFH);
	WriteCommand(2,DFH);

	while(1){
		if(psd_value[1]>190){
			err1=psd_value[1]-190;
		}//왼쪽 값 조정
		else err1=0;

		if(psd_value[8]>170){
			err2=170-psd_value[8];
		}
		else err2=0;

		if((READ_SENSOR()&0x02) && distance>=s_stop){
			return 0x02;
		}
		else if((READ_SENSOR()&0x07) && distance>=s_stop){
			return 0x08;
		}

		err=err1+err2;

		non_Holonomic(150, err, 0);

		enPose();

		distance=sqrt((Pose[0]*Pose[0])+(Pose[1]*Pose[1]));
		if(distance>=mm)break;
	}
}
