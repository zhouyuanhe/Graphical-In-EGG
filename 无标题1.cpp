//��������������ƽ�ƶ���
#include <graphics.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;



#define resX 40
#define resY 20
#define capX 20
#define capY 30
#define dioX 16
#define dioY 24
#define halfLine 80
#define buttonX 400
#define buttonY 800
#define buttonX_Space 200

///�����ࡣ������ݶ����ܳ����߼������״��ͬ������������ͬ���ڴ˽�ʹ��flag��������
class tools{
public:
	int x;
	int y;
	float size; //���ձ����������С
	//Ĭ����ɫΪ 0x0 0x0 0x0 ����ɫ��
	int R = 0x0;
	int G = 0x0;
	int B = 0x0;
	int flag;
	tools()	{
		x = 50;
		y = 20;
		size = 1;
	}
	tools(int a,int b,int flag_){
		x = a;
		y = b;
		flag = flag_;
	}
};
class a_line{
	public:
		int x1;
		int y1;
		int x2;
		int y2;
		a_line(){
			x1 = 50;
			y1 = 20;
			x2 = 500;
			y2 = 200;
		}
		a_line(int a,int b,int c,int d){
			x1 = a;
			y1 = b;
			x2 = c;
			y2 = d;
		}
};

//��������Ƶ��ʹ�õĺ������ڴ˰�װ����
class Magnetic{
	public:
		int place = 0;		//-1��� 1�Ҳ�
		int id = 0;			//ƥ��ı�־��
		int move_ment_1=0;	//�ڲ�
		int move_ment_2=0;	//���
		Magnetic(){
			place = 0;
			move_ment_1 = 0;
			move_ment_2 = 0;
			place = 0;	
			id = 0;
		}
		//���ֹ��ߵ�ƫ�� flag: 0-���� 1-���� 2-������
		Magnetic(int a,int flag){
			place =a;
			switch (flag) {
				case 0:	move_ment_1 = resX;move_ment_2 = 2*resX;	break;
				case 1:	move_ment_1 = capX;move_ment_2 = 5*capX;	break;
				case 2:	move_ment_1 = dioX;move_ment_2 = 5*dioX;	break;
				default:move_ment_1 = 0;move_ment_1 = 0;			break;
			}
		}
		void Get(int flag){
			switch (flag){
				case 0:	move_ment_1 = resX;move_ment_2 = 2*resX;	break;
				case 1:	move_ment_1 = capX;move_ment_2 = 5*capX;	break;
				case 2:	move_ment_1 = dioX;move_ment_2 = 5*dioX;	break;
				default:move_ment_1 = 0;move_ment_1 = 0;			break;
			}
		}
};
//�������ֹ��ߺ��� flag: 0-���� 1-���� 2-������
void drawtools(int x,int y,int flag,int R= 0, int l =1,int G= 0,int B= 0) {
	setlinewidth(l);
	setcolor(EGERGB(R, G, B));
	switch (flag) {
	case 0:
		//����
		line(x-2*resX,y,x-resX,y);
		rectangle(x-resX,y-resY,x+resX,y+resY);
		line(x+resX,y,x+2*resX,y);
		break;
	case 1:
		line(x-capX,y+capY,x-capX,y-capY);
		line(x+capX,y+capY,x+capX,y-capY);
		line(x-5*capX,y,x-capX,y);
		line(x+5*capX,y,x+capX,y);
		break;
	case 2:
		//������
		line(x-dioX,y+dioY,x-dioX,y-dioY);
		line(x-dioX,y-dioY,x+dioX,y);
		line(x-dioX,y+dioY,x+dioX,y);
		line(x+dioX,y+dioY,x+dioX,y-dioY);
		line(x-5*dioX,y,x-dioX,y);
		line(x+5*dioX,y,x+dioX,y);
	case 3:
		//ֱ��
		line(x-halfLine,y,x+halfLine,y);
		break;
	default:
		break;
	}
}

//�������֣�����ʾ
void drawText(string s){
	//���½�һƬ��������
	setcolor(BLACK);
	setlinewidth(1);
	line(0,700,1200,700);
	setfont(24,0,"����");
	outtextrect(50,750,200,1000,s.c_str());
	for(int i =0;i<4;i++){
		drawtools(buttonX+buttonX_Space*i,buttonY,i);
	}

}


//��������
void createLine(int x1,int y1,int x2,int y2,int R= 0, int G = 0,int B = 0,int l =1){
	setcolor(EGERGB(R, G, B));
	setlinewidth(l);
	line(x1,y1,x2,y2);
}

//�ж��Ƿ��ڿռ�ڵ���,���ڽڵ��ϣ��͸���+���������ؽڵ����ֵ

Magnetic isONNode(int tool_num,tools tool[30],mouse_msg MouseMsg){
	//��1��ʼ����Ҫ��0��ʾδ��⵽
	Magnetic move;	
	
	for(int i = 0;i < tool_num;i++){
		move.Get(tool[i].flag);
		if (
			MouseMsg.x > tool[i].x -move.move_ment_2&& 
			MouseMsg.x < tool[i].x -move.move_ment_1&&
			MouseMsg.y > tool[i].y -20&& 
			MouseMsg.y < tool[i].y +20){
			move.Get(tool[i].flag);
			createLine(tool[i].x -move.move_ment_2,tool[i].y,tool[i].x -move.move_ment_1,tool[i].y,0xFF,0,0,5);
			move.id = i;
			move.place = -1;
			
			return move;
		}
		else if(
			MouseMsg.x > tool[i].x +move.move_ment_1&& 
			MouseMsg.x < tool[i].x +move.move_ment_2&&
			MouseMsg.y > tool[i].y -20&& 
			MouseMsg.y < tool[i].y +20){
			Magnetic move(-1,i);
			move.Get(tool[i].flag);
			createLine(tool[i].x +move.move_ment_2,tool[i].y,tool[i].x +move.move_ment_1,tool[i].y,0xFF,0,0,5);
			move.id = i;
			move.place = 1;
			return move;
		}
	}
	return move;
}


//�����ݵ��ļ�
void save_data(int tools_num,tools tool[30],int line_num,a_line lines[30]){
	ofstream fout;				//�ļ��Ķ�д���÷�ͬcin��cout
	fout.open("save2.txt",ios::out);//�򿪴��ڱ��ص��ĵ�
	cout<<"������"<<endl;
	fout << tools_num<< endl;
	for(int i=0;i<tools_num;i++){
		fout<<tool[i].flag<<" "
		<<tool[i].x<<" "
		<<tool[i].y<<" "
		<<tool[i].R<<" "
		<<tool[i].G<<" "
		<<tool[i].B<<" "
		<<tool[i].size<<" "
		<< endl;
	}
	fout << line_num<< endl;
	for(int i=0;i<line_num;i++){
		fout<<lines[i].x1<<" "
		<<lines[i].y1<<" "
		<<lines[i].x2<<" "
		<<lines[i].y2<<" "
		<< endl;
	}
	fout.close();
}
//���ļ�������
void load_data(int &tools_num,tools tool[30],int &line_num,a_line lines[30]){
	ifstream  fin;				//�ļ��Ķ�д���÷�ͬcin��cout
	fin.open("save2.txt",ios::in);//�򿪴��ڱ��ص��ĵ�
	cout<<"ȡ����"<<endl;
	
	if(!fin.is_open()){
		cerr<<"cannot open the file";
	}	
	//������ռ䣺
	string buf;    		//������ʱ����һ�� 1024��Ķ��ռ䣨�ֽ�buffer)�����ҳ�ʼ��Ϊ0��
	//���ļ���Ϣ������д�뵽���ű���
	int f_ts = -1;
	int f_ls = -1;
	int f_tnum = -1;
	int f_lnum = -1;
	int line =0;
	fin >> buf;
	tools_num =  atoi(buf.c_str());
	for(int i=0;i<tools_num;i++){
		fin>>tool[i].flag>>tool[i].x>>tool[i].y>>tool[i].R>>tool[i].G>>tool[i].B>>tool[i].size;
	}
	fin>>line_num;
	for(int i=0;i<line_num;i++){
		fin>>lines[i].x1>>lines[i].y1>>lines[i].x2>>lines[i].y2;
		//cout<<lines[i].x1<<lines[i].y1<<lines[i].x2<<lines[i].y2;
	}
	
}

//���ѡ�������ֹ����е�һ��
mouse_msg choseTools(
	int &flag,int &flag_draw,int &flag_chose,
	int &tool_num,tools tools_location[30],
	int &line_num,int &line_state,a_line lines[30],
	int &save_load,int color
	){
	//���ѡ��Ĺ���-1-δѡ�� 0-���� 1-���� 2-������ 3-ֱ��
	//int flag_draw = 0;	//����״̬��־ 0-δ���ƣ�1-�ڻ���
	mouse_msg MouseMsg;
	Magnetic move;
	
	MouseMsg = getmouse();//����¼���ѻ��濨ס�������������ص��¼�����Ӧ��д�ڴ�ǰ��
	flag = -1;
	int flag_isdown = 0;
	for(int i =0;i<4;i++){
		if (MouseMsg.x > buttonX+buttonX_Space*i - resX && 
			MouseMsg.x <buttonX+buttonX_Space*i+resX &&
			MouseMsg.y > buttonY-resY && 
			MouseMsg.y <buttonY+resY ){
			flag =i;
			if(MouseMsg.is_down() && flag_draw==0){
				//cout<<i;
				flag_chose = i;
				flag_draw = 1;
				flag_isdown = 1;
				if(flag_chose ==3)line_state=1;

			}
			break;
		}
	}
	for(int i=1;i<=2;i++)
		if (MouseMsg.x > 0 && 
			MouseMsg.x <100 &&
			MouseMsg.y > 25*i && 
			MouseMsg.y <25*i+25 ){
			save_load =i;
			break;
			}
	if(MouseMsg.is_down() && save_load==1){
		save_data(tool_num,tools_location,line_num,lines);
		save_load =-1;
		
	}
	else if(MouseMsg.is_down() && save_load==2){
		load_data(tool_num,tools_location,line_num,lines);
		save_load =-1;
	}
		
		
	
	if(MouseMsg.is_down() &&flag_draw == 1 && flag_isdown ==0){
		//cout<<MouseMsg.is_left()<<" "<<flag_chose <<" "<<line_state<<endl;
		if(MouseMsg.is_left()&& flag_chose < 3){
			//��ԭ�����ͱ�������һ��λ��
			tools_location[tool_num].x =  MouseMsg.x;
			tools_location[tool_num].y =  MouseMsg.y;
			tools_location[tool_num].flag =  flag_chose;
			if(color == 1)
				tools_location[tool_num].R = 0XFF;
			if(color == 0)
				tools_location[tool_num].R = 0X0;
			tool_num+=1;
			flag_draw = 0;
		}
		else if(MouseMsg.is_left()&& flag_chose == 3 && line_state > 0){
			if(line_state == 1){
				//����ڵ� �����һ����
				move = isONNode(tool_num,tools_location,MouseMsg);
				
				if(move.place!=0){

					lines[line_num].x1 = tools_location[move.id].x+move.place*move.move_ment_2;
					lines[line_num].y1 = tools_location[move.id].y;
				}
				else{
					lines[line_num].x1 = MouseMsg.x;
					lines[line_num].y1 = MouseMsg.y;
				}
				
				line_state =2;		//�������ֱ���нڵ�״̬
				//cout<<"�ڵ�����"<<line_num<<endl;
				
			}
			else if(line_state == 2){
				//���ҽڵ� ����ڶ�����
				//cout<<"���ڱ���ڶ����ڵ�"<<endl;
				
				move = isONNode(tool_num,tools_location,MouseMsg);
				
				if(move.place!=0){

					lines[line_num].x2 = tools_location[move.id].x+move.place*move.move_ment_2;
					lines[line_num].y2 = tools_location[move.id].y;
				}
				else{
					lines[line_num].x2 = MouseMsg.x;
					lines[line_num].y2 = MouseMsg.y;
				}
				line_num+=1;		//�����ˣ�ֱ����+1
				line_state =0;		//�������ֱ���нڵ�״̬
				flag_draw = 0;
			}
		}
		else if(MouseMsg.is_right()){flag_draw = 0;line_state =0;}
	}
	return MouseMsg;

}

void mainloop(){
	int flag_Move = -1;			//����ƶ�ѡ��Ĺ���-1-δѡ�� 0-���� 1-���� 2-������
	int flag_Chose = -1;		//�����ѡ��Ĺ���-1-δѡ�� 0-���� 1-���� 2-������ 3-ֱ��
	int flag_draw = 0;			//����״̬��־ 0-δ���ƣ�1-�ڻ���
	int isLeftChose = false;	//�ж���������ǲ���Ӧ�ô��ڻ���״̬��
	int tool_num = 0;			//��¼���ֹ��ߵ�������
	int line_state = 0;			//����ֱ�ߵ�״̬��0-δ���� 1-���Ƶ�һ���� 2���Ƶڶ�����
	tools tools_location[30];	//��ౣ����ʮ�������ߡ�
	int line_num = 0;			//ֱ�ߵ�����
	a_line lines[30];			//��ౣ����ʮ���ߡ�
	int save_load=0;			//��ȡ��־ 0-δ���� 1-�� 2-д
	int color = 0;				//��ɫ��¼��־���������Ʋ�ͬ��ɫ�ĵ��裬ʱ���ϵֻ���ں���ɫ����
	Magnetic move;
	mouse_msg MouseMsg;
	for ( ; is_run(); delay_fps(120) ){
		//�������������µ�λ�û�ͼͼ��
		cleardevice();
		setbkcolor(WHITE);
		setlinewidth(1);
		setfont(24,0,"����");
		setcolor(EGERGB(0XFF, 0X0, 0X0));
		if(save_load==1)setcolor(EGERGB(0X0, 0XFF, 0X0));
		outtextrect(0,25,100,25,"��������");
		setcolor(EGERGB(0XFF, 0X0, 0X0));
		if(save_load==2)setcolor(EGERGB(0X0, 0XFF, 0X0));
		outtextrect(0,50,100,25,"��������");
		
		if (keystate(VK_NUMPAD1))
		{
			// С��������1��������
			color = 0;
		}
		if (keystate(VK_NUMPAD2))
		{
			// С��������2��������
			color = 1;
		}
		if(color == 0){
			setcolor(EGERGB(0X0, 0X0, 0X0));
			outtextrect(50,650,200,25,"��ǰ��ɫ��ɫ");}
		else if(color == 1){
			setcolor(EGERGB(0XFF, 0X0, 0X0));
			outtextrect(5,650,200,25,"��ǰ��ɫ��ɫ");}
		
		
		
		if(flag_Move>=0)drawtools(buttonX+buttonX_Space*flag_Move,buttonY,flag_Move,0xFF,5);//�������ѡ�еĺ�ɫ������־
		switch (flag_Move) {
		case -1: drawText("��ѡ��Ԫ�������л���");break;
		case 0:	drawText("����");	break;
		case 1:	drawText("����");	break;
		case 2:	drawText("������");break;
		case 3:	drawText("����");break;
		default:break;
		}
		//===============================================================
		//ѡ��ֱ��֮��̬����
		if(flag_draw ==1){
			if(line_state ==1)drawText("���ȷ�Ϸ���\n�Ҽ�ȡ������\n���ڻ��Ƶ�һ����\n��������ƶ����ѷ��õ�Ԫ��������");
			//cout<<MouseMsg.x<<"  "<<MouseMsg.y<<endl;
			move = isONNode(tool_num,tools_location,MouseMsg);
			if(line_state ==2){
				//��λֱ�ߵڶ�����ʱ�Ĵ���ֱ��
				if(move.place!=0)createLine(lines[line_num].x1,lines[line_num].y1,tools_location[move.id].x + move.place*move.move_ment_2,tools_location[move.id].y);
				//��λֱ�ߵڶ�����ʱ�ĸ���������
				else createLine(lines[line_num].x1,lines[line_num].y1,MouseMsg.x,MouseMsg.y);
			}
			else if(line_state ==1)
				//��λ��һ����ʱ���׼��
					if(move.place==0){
					createLine(MouseMsg.x,MouseMsg.y,MouseMsg.x,MouseMsg.y,0xFF,0,0,5);
					createLine(MouseMsg.x+20,MouseMsg.y,MouseMsg.x-20,MouseMsg.y,0,0,0,1);
					createLine(MouseMsg.x,MouseMsg.y+20,MouseMsg.x,MouseMsg.y-20,0,0,0,1);
				}
		//================================================================
				//������������
			if(flag_Chose<3)
				drawtools(MouseMsg.x,MouseMsg.y,flag_Chose);
			string s="�������������\n����Ҽ�ȡ������\n��ѡ��";
			switch (flag_Chose) {
				case 0:	s+="����\nԪ��������30\n������ѡ��ɫ1.��ɫ2.��ɫ";break;
				case 1:	s+="����\nԪ��������30\n������ѡ��ɫ1.��ɫ2.��ɫ";break;
				case 2:	s+="������\nԪ��������30\n������ѡ��ɫ1.��ɫ2.��ɫ";break;
				case 3:	s+="����\n���԰�����ƶ���Ԫ����������";break;
				default:break;
			}
			drawText(s);
		}
		
		
		for(int i=0;i<tool_num;i++){
			//������Ĺ��߻�����
			//cout<<"��ʱӦ�û�����:"<<i<<tools_location[i].x<<" "<<tools_location[i].y<<" "<<tools_location[i].flag<<endl;
			drawtools(tools_location[i].x,tools_location[i].y,tools_location[i].flag,
				tools_location[i].R,1,tools_location[i].G,tools_location[i].B
				);
		}

		for(int i=0;i<line_num;i++){
			//cout<<"��ʱӦ�û�ֱ��"<<endl;
			createLine(lines[i].x1,lines[i].y1,lines[i].x2,lines[i].y2);
		}
		MouseMsg = choseTools(
			flag_Move,flag_draw,flag_Chose,	//ȫ�ֻ���״̬
			tool_num,tools_location,		//���߻���״̬
			line_num,line_state,lines,		//ֱ�߻���״̬
			save_load,color
			);//��ȡ���ѡ�еı�־��
	}
}

int main(void){	
	setinitmode(INIT_ANIMATION);
	initgraph(1200, 960);
	randomize();
	// ������ѭ��
	mainloop();
	// �رջ�ͼ�豸
	closegraph();
	return 0;
}
