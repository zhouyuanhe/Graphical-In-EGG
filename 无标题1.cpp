//基础动画二：简单平移动画
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

///工具类。电阻电容二极管程序逻辑里仅形状不同，其它属性相同。在此仅使用flag用来区分
class tools{
public:
	int x;
	int y;
	float size; //按照比例扩大或缩小
	//默认颜色为 0x0 0x0 0x0 即黑色。
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

//磁力吸附频繁使用的函数，在此包装成类
class Magnetic{
	public:
		int place = 0;		//-1左侧 1右侧
		int id = 0;			//匹配的标志号
		int move_ment_1=0;	//内侧
		int move_ment_2=0;	//外侧
		Magnetic(){
			place = 0;
			move_ment_1 = 0;
			move_ment_2 = 0;
			place = 0;	
			id = 0;
		}
		//三种工具的偏移 flag: 0-电阻 1-电容 2-二极管
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
//绘制三种工具函数 flag: 0-电阻 1-电容 2-二极管
void drawtools(int x,int y,int flag,int R= 0, int l =1,int G= 0,int B= 0) {
	setlinewidth(l);
	setcolor(EGERGB(R, G, B));
	switch (flag) {
	case 0:
		//电阻
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
		//二极管
		line(x-dioX,y+dioY,x-dioX,y-dioY);
		line(x-dioX,y-dioY,x+dioX,y);
		line(x-dioX,y+dioY,x+dioX,y);
		line(x+dioX,y+dioY,x+dioX,y-dioY);
		line(x-5*dioX,y,x-dioX,y);
		line(x+5*dioX,y,x+dioX,y);
	case 3:
		//直线
		line(x-halfLine,y,x+halfLine,y);
		break;
	default:
		break;
	}
}

//背景文字，仅提示
void drawText(string s){
	//左下角一片文字区域
	setcolor(BLACK);
	setlinewidth(1);
	line(0,700,1200,700);
	setfont(24,0,"宋体");
	outtextrect(50,750,200,1000,s.c_str());
	for(int i =0;i<4;i++){
		drawtools(buttonX+buttonX_Space*i,buttonY,i);
	}

}


//绘制连线
void createLine(int x1,int y1,int x2,int y2,int R= 0, int G = 0,int B = 0,int l =1){
	setcolor(EGERGB(R, G, B));
	setlinewidth(l);
	line(x1,y1,x2,y2);
}

//判断是否在空间节点上,若在节点上，就高亮+吸附并返回节点的数值

Magnetic isONNode(int tool_num,tools tool[30],mouse_msg MouseMsg){
	//从1开始，需要用0表示未检测到
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


//存数据到文件
void save_data(int tools_num,tools tool[30],int line_num,a_line lines[30]){
	ofstream fout;				//文件的读写，用法同cin和cout
	fout.open("save2.txt",ios::out);//打开存在本地的文档
	cout<<"存数据"<<endl;
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
//从文件读数据
void load_data(int &tools_num,tools tool[30],int &line_num,a_line lines[30]){
	ifstream  fin;				//文件的读写，用法同cin和cout
	fin.open("save2.txt",ios::in);//打开存在本地的文档
	cout<<"取数据"<<endl;
	
	if(!fin.is_open()){
		cerr<<"cannot open the file";
	}	
	//申请读空间：
	string buf;    		//就是临时申请一个 1024大的读空间（又叫buffer)，并且初始化为0。
	//读文件信息，依次写入到两张表里
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

//鼠标选择了四种功能中的一个
mouse_msg choseTools(
	int &flag,int &flag_draw,int &flag_chose,
	int &tool_num,tools tools_location[30],
	int &line_num,int &line_state,a_line lines[30],
	int &save_load,int color
	){
	//鼠标选择的工具-1-未选择 0-电阻 1-电容 2-二极管 3-直线
	//int flag_draw = 0;	//绘制状态标志 0-未绘制，1-在绘制
	mouse_msg MouseMsg;
	Magnetic move;
	
	MouseMsg = getmouse();//鼠标事件会把画面卡住、绘制与鼠标相关的事件代码应该写于此前。
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
			//画原件，就保存鼠标第一个位置
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
				//画左节点 保存第一个点
				move = isONNode(tool_num,tools_location,MouseMsg);
				
				if(move.place!=0){

					lines[line_num].x1 = tools_location[move.id].x+move.place*move.move_ment_2;
					lines[line_num].y1 = tools_location[move.id].y;
				}
				else{
					lines[line_num].x1 = MouseMsg.x;
					lines[line_num].y1 = MouseMsg.y;
				}
				
				line_state =2;		//进入绘制直线有节点状态
				//cout<<"节点数："<<line_num<<endl;
				
			}
			else if(line_state == 2){
				//画右节点 保存第二个点
				//cout<<"正在保存第二个节点"<<endl;
				
				move = isONNode(tool_num,tools_location,MouseMsg);
				
				if(move.place!=0){

					lines[line_num].x2 = tools_location[move.id].x+move.place*move.move_ment_2;
					lines[line_num].y2 = tools_location[move.id].y;
				}
				else{
					lines[line_num].x2 = MouseMsg.x;
					lines[line_num].y2 = MouseMsg.y;
				}
				line_num+=1;		//画完了，直线数+1
				line_state =0;		//进入绘制直线有节点状态
				flag_draw = 0;
			}
		}
		else if(MouseMsg.is_right()){flag_draw = 0;line_state =0;}
	}
	return MouseMsg;

}

void mainloop(){
	int flag_Move = -1;			//鼠标移动选择的工具-1-未选择 0-电阻 1-电容 2-二极管
	int flag_Chose = -1;		//鼠标点击选择的工具-1-未选择 0-电阻 1-电容 2-二极管 3-直线
	int flag_draw = 0;			//绘制状态标志 0-未绘制，1-在绘制
	int isLeftChose = false;	//判断鼠标现在是不是应该处于绘制状态。
	int tool_num = 0;			//记录三种工具的总数量
	int line_state = 0;			//绘制直线的状态，0-未绘制 1-绘制第一个点 2绘制第二个点
	tools tools_location[30];	//最多保存三十个，工具。
	int line_num = 0;			//直线的条数
	a_line lines[30];			//最多保存三十条线。
	int save_load=0;			//存取标志 0-未按下 1-读 2-写
	int color = 0;				//颜色记录标志，用来绘制不同颜色的电阻，时间关系只做黑红两色区分
	Magnetic move;
	mouse_msg MouseMsg;
	for ( ; is_run(); delay_fps(120) ){
		//清屏，重新在新的位置绘图图像
		cleardevice();
		setbkcolor(WHITE);
		setlinewidth(1);
		setfont(24,0,"宋体");
		setcolor(EGERGB(0XFF, 0X0, 0X0));
		if(save_load==1)setcolor(EGERGB(0X0, 0XFF, 0X0));
		outtextrect(0,25,100,25,"保存数据");
		setcolor(EGERGB(0XFF, 0X0, 0X0));
		if(save_load==2)setcolor(EGERGB(0X0, 0XFF, 0X0));
		outtextrect(0,50,100,25,"输入数据");
		
		if (keystate(VK_NUMPAD1))
		{
			// 小键盘数字1键按下了
			color = 0;
		}
		if (keystate(VK_NUMPAD2))
		{
			// 小键盘数字2键按下了
			color = 1;
		}
		if(color == 0){
			setcolor(EGERGB(0X0, 0X0, 0X0));
			outtextrect(50,650,200,25,"当前颜色黑色");}
		else if(color == 1){
			setcolor(EGERGB(0XFF, 0X0, 0X0));
			outtextrect(5,650,200,25,"当前颜色红色");}
		
		
		
		if(flag_Move>=0)drawtools(buttonX+buttonX_Space*flag_Move,buttonY,flag_Move,0xFF,5);//绘制鼠标选中的红色高亮标志
		switch (flag_Move) {
		case -1: drawText("请选择元器件进行绘制");break;
		case 0:	drawText("电阻");	break;
		case 1:	drawText("电容");	break;
		case 2:	drawText("二极管");break;
		case 3:	drawText("电线");break;
		default:break;
		}
		//===============================================================
		//选中直线之后动态画线
		if(flag_draw ==1){
			if(line_state ==1)drawText("左键确认放置\n右键取消放置\n正在绘制第一个点\n试着鼠标移动到已放置的元器件两端");
			//cout<<MouseMsg.x<<"  "<<MouseMsg.y<<endl;
			move = isONNode(tool_num,tools_location,MouseMsg);
			if(line_state ==2){
				//定位直线第二个点时的磁吸直线
				if(move.place!=0)createLine(lines[line_num].x1,lines[line_num].y1,tools_location[move.id].x + move.place*move.move_ment_2,tools_location[move.id].y);
				//定位直线第二个点时的跟随鼠标的线
				else createLine(lines[line_num].x1,lines[line_num].y1,MouseMsg.x,MouseMsg.y);
			}
			else if(line_state ==1)
				//定位第一个点时候的准星
					if(move.place==0){
					createLine(MouseMsg.x,MouseMsg.y,MouseMsg.x,MouseMsg.y,0xFF,0,0,5);
					createLine(MouseMsg.x+20,MouseMsg.y,MouseMsg.x-20,MouseMsg.y,0,0,0,1);
					createLine(MouseMsg.x,MouseMsg.y+20,MouseMsg.x,MouseMsg.y-20,0,0,0,1);
				}
		//================================================================
				//绘制其它工具
			if(flag_Chose<3)
				drawtools(MouseMsg.x,MouseMsg.y,flag_Chose);
			string s="鼠标左键点击绘制\n鼠标右键取消绘制\n已选中";
			switch (flag_Chose) {
				case 0:	s+="电阻\n元器件上限30\n按键盘选颜色1.黑色2.红色";break;
				case 1:	s+="电容\n元器件上限30\n按键盘选颜色1.黑色2.红色";break;
				case 2:	s+="二极管\n元器件上限30\n按键盘选颜色1.黑色2.红色";break;
				case 3:	s+="电线\n试试吧鼠标移动到元器件的两端";break;
				default:break;
			}
			drawText(s);
		}
		
		
		for(int i=0;i<tool_num;i++){
			//将保存的工具画出来
			//cout<<"此时应该画工具:"<<i<<tools_location[i].x<<" "<<tools_location[i].y<<" "<<tools_location[i].flag<<endl;
			drawtools(tools_location[i].x,tools_location[i].y,tools_location[i].flag,
				tools_location[i].R,1,tools_location[i].G,tools_location[i].B
				);
		}

		for(int i=0;i<line_num;i++){
			//cout<<"此时应该画直线"<<endl;
			createLine(lines[i].x1,lines[i].y1,lines[i].x2,lines[i].y2);
		}
		MouseMsg = choseTools(
			flag_Move,flag_draw,flag_Chose,	//全局绘制状态
			tool_num,tools_location,		//工具绘制状态
			line_num,line_state,lines,		//直线绘制状态
			save_load,color
			);//读取鼠标选中的标志。
	}
}

int main(void){	
	setinitmode(INIT_ANIMATION);
	initgraph(1200, 960);
	randomize();
	// 程序主循环
	mainloop();
	// 关闭绘图设备
	closegraph();
	return 0;
}
