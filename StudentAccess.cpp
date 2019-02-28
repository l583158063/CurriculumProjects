#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

struct date //出生日期
{
	int year;
	int month;
	int day;
};

struct student
{
	BOOL delTag;	//学生信息是否被删除的标志，初始化为FALSE，若被删除则赋值为TRUE
	char num[20];			//学号
	char name[12];			//姓名
	char sex[4];			//性别
	struct date birthday;	//出生日期
	int age;				//年龄
	char addr[50];			//籍贯
	char dept[50];			//系别
	char major[30];			//专业
	char classs[30];		//班级
	char phone[20];			//电话
}stu;

void gotoxy(int x, int y);//光标定位,光标定位函数SetConsoleCursorPosition是左上角位置是0,0然后向左向下延伸
void Insert(FILE *fp);//添加模块
void Delete(FILE *fp);//删除模块，删除一名指定学生的信息
void Search(FILE *fp);//查找模块，按学号和姓名的两种不同查找方式
void Modify(student *pS, FILE *fp, long pf);//修改模块，修改一名学生的一个信息
void Browse(FILE *fp);//浏览模块，向屏幕输出所有（未被删除）的学生信息
void Empty(FILE *fp);//清空模块，将数据库清空
void FirstUse(FILE *fp);//首次使用该系统时调用
void menuAdmin(FILE *fp);//管理员菜单
void menuVisit(FILE *fp);//访客菜单

char sign = 'y';//是否首次管理员登录的标记
int find;//记录选择的是管理员还是访客，管理员为1，访客为2
FILE *fp;

int main()
{
	char sword[3] = { '>', ' ', ' '};
	int switch_on;//首页游标菜单的按键记录
	int a = 0;//游标菜单的选择标志
	int first = 1;//判断是否第一次使用该系统
	char password[8] = "123456";
	char input[8];
	int i;
	system("color 3F");
	printf("password = 123456");
	Sleep(1000);
	system("cls");
	do {
		fflush(stdin);
		system("cls");
		gotoxy(4, 0);
		printf("\n\n\n\n\t\t***********欢迎来到学生学籍管理系统***********");
		printf("\n\t\t||                                          ||");
		printf("\n\t\t||                 请先登录                 ||");
		printf("\n\t\t||                                          ||");
		printf("\n\t\t||                 %c管理员                  ||", sword[0]);
		printf("\n\t\t||                  %c访客                   ||", sword[1]);
		printf("\n\t\t||                                          ||");
		printf("\n\t\t||                  %c退出                   ||", sword[2]);
		printf("\n\t\t||                                          ||");
		printf("\n\t\t**********************************************");
		switch_on = getch();
		switch (switch_on)
		{
		case 80:                       //按“↑”switch_on加一
			a++;
			break;
		case 72:                       //按“↓”switch_on减一
			a--;
			break;
		case 13:                       //按下回车时选择功能
			if (0 == a)                 //选择管理员
			{
				find = 1;
				while (TRUE)
				{
					system("cls");
					fflush(stdin);
					gotoxy(6, 11);//移动光标
					printf("请输入6位密码：");//密码是123456
					fgets(input, sizeof(input), stdin);
					for (i = 0; input[i] != '\n'; i++)
					{
						;//移动下标至字符数组尾部
					}
					input[i] = '\0';//fgets不会将'\n'自动换成'\0'
					if (strcmp(input, password) == 0)
					{
						system("cls");
						gotoxy(6, 11);
						printf("Welcome!\n");
						Sleep(1000);
						break;//跳出输入密码的循环
					}
					else
					{
						system("cls");
						gotoxy(6, 11);
						printf("密码错误！请再次输入！\n");
						Sleep(1000);
					}
				}
				gotoxy(7, 11);
				printf("如果是首次使用该系统，我们将会在工程目录下,");
				gotoxy(8, 11);
				printf("创建一个新的文本文件。原有的文本文件将会被覆盖！");
				gotoxy(9, 11);
				printf("请问是否是第一次使用该学生学籍管理系统（y/n）：");
				scanf(" %c", &sign);
				getchar();
				if ('y' == sign)//首次使用该系统
				{
					FirstUse(fp);
				}
				menuAdmin(fp);//进入管理员菜单
			}
			else if (-2 == a || 1 == a)//选择访客
			{
				find = 2;
				menuVisit(fp);//进入访客菜单
			}
			else                       //选择退出
			{
				exit(0);
			}
			break;
		default:
			break;
		}
		a = a % 3;//游标选择标志0，±1，±2分别对应不同的选项
		switch (a)
		{
		case 1:
		case -2://箭头在“访客”位置
			sword[0] = ' ';
			sword[1] = '>';
			sword[2] = ' ';
			break;
		case -1:
		case 2://箭头在“退出”位置
			sword[0] = ' ';
			sword[1] = ' ';
			sword[2] = '>';
			break;
		case 0://箭头在“管理员”位置
			sword[0] = '>';
			sword[1] = ' ';
			sword[2] = ' ';
			break;
		default:
			break;
		}
	} while (TRUE);
	return 0;
}

void gotoxy(int x, int y)//移动光标,光标定位函数SetConsoleCursorPosition是左上角位置是0,0然后向左向下延伸
{
	COORD pos;
	pos.X = 2 * y;
	pos.Y = x;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void Insert(FILE *fp)//添加模块
{
	if ((fp = fopen("Access.bin", "ab+")) == NULL)//在文本内容尾部添加信息
	{
		printf("\n打开文件失败！");
		Sleep(1000);
		return;
	}
	do {
		system("cls");
		fflush(stdin);
		printf("[添加信息]\n");
		printf("请输入一名学生的信息，输入学号时输入“-1”可以结束输入。\n");
		printf("学号：");
		gets_s(stu.num);
		if (stu.num[0] == '-')
		{
			fclose(fp);
			printf("【输入结束】");
			Sleep(1000);
			menuAdmin(fp);//输入结束返回管理员菜单
		}
		stu.delTag = FALSE;//添加的每一个学生都是未被删除的
		printf("姓名：");
		gets_s(stu.name);
		printf("性别（男/女）：");
		gets_s(stu.sex);
		printf("出生日期(xxxx/xx/xx)：");
		scanf("%d/%d/%d", &stu.birthday.year, &stu.birthday.month, &stu.birthday.day);
		printf("年龄：");
		scanf("%d", &stu.age);
		getchar();
		printf("籍贯：");
		gets_s(stu.addr);
		printf("系别：");
		gets_s(stu.dept);
		printf("专业：");
		gets_s(stu.major);
		printf("班级：");
		gets_s(stu.classs);
		printf("电话：");
		gets_s(stu.phone);
		//输一个写一个
		if (stu.num[0] != '\0'&&stu.name[0] != '\0')
		{
			if (fwrite(&stu, sizeof(struct student), 1, fp) != 1)
			{
				printf("文件写入错误！");
			}
		}
	} while (TRUE);
}

void Delete(FILE *fp)//删除模块
{
	char choose;
	long pf[10];//最多存10个重复的学生信息结构体文件内首地址
	int n;//判断是否多个有重复的学生信息
	int i;
	char s[20];
	do {
		n = 0;
		system("cls");
		printf("请输入要删除学生的学号（输入“-1”返回)：");
		scanf(" %s", s);
		if ('-' == s[0])
		{
			menuAdmin(fp);
		}
		if ((fp = fopen("Access.bin", "rb+")) == NULL)//用"rb+"才能从文件中间修改内容
		{
			printf("\n打开文件失败！");
			Sleep(1000);
			return;
		}
		i = 0;
		fread(&stu, sizeof(struct student), 1, fp);
		while (!feof(fp))
		{
			if (TRUE != stu.delTag && strcmp(stu.num, s) == 0)//比较学生信息和输入的学号
			{
				if (i < 10)//最多存10个重名的学生
				{
					pf[i] = ftell(fp) - sizeof(struct student);//如果读到符合的信息，则获取该信息结构体首地址
				}
				printf("第%d位：\n", i + 1);
				printf("学号：%s\n", stu.num);
				printf("姓名：%s\n", stu.name);
				printf("性别：%s\n", stu.sex);
				printf("出生日期：%d/%d/%d\n",
					stu.birthday.year, stu.birthday.month, stu.birthday.day);
				printf("年龄：%d\n", stu.age);
				printf("籍贯：%s\n", stu.addr);
				printf("系别：%s\n", stu.dept);
				printf("专业：%s\n", stu.major);
				printf("班级：%s\n", stu.classs);
				printf("电话：%s\n\n", stu.phone);
				n++;
				i++;
			}
			fread(&stu, sizeof(struct student), 1, fp);
		}
		if (0 == n)
		{
			printf("没有找到该学号所对应的学生。请问是否输入：y.是；n.返回上一级菜单  [ ]\b\b");
			fflush(stdin);
			choose = getchar();
			getchar();
			switch (choose)
			{
			case 'y'://重新查找
				continue;
				break;
			case 'n'://返回上一级菜单
				switch (find)
				{
				case 1:
					menuAdmin(fp);
					break;
				case 2:
					menuVisit(fp);
					break;
				}
				break;
			default:
				printf("choose值不合理");
				Sleep(1000);
				break;
			}
		}
		else if (1 == find && 1 == n)//找到了一名对应学号学生的信息
		{
			do {
				fseek(fp, -1 * sizeof(struct student), SEEK_CUR);//移动文件位置指针到要修改的学生信息首地址
			} while (ftell(fp) != pf[0]);
			fread(&stu, sizeof(struct student), 1, fp);//保存要删除的学生信息到缓存数组
			printf("\n请问是否要删除该学生的信息？（y/n）[ ]\b\b");
			scanf(" %c", &choose);
			getchar();
			if ('y' == choose)
			{
				memset(&stu, '\0', sizeof(struct student));//将结构体赋值为空
				stu.delTag = TRUE;//标记为被删除
				do {
					fseek(fp, -1 * sizeof(struct student), SEEK_CUR);//移动文件位置指针到要删除的学生信息首地址
				} while (ftell(fp) != pf[0]);
				if (fwrite(&stu, sizeof(struct student), 1, fp) != 1)//直接覆盖写入一堆空字符
				{
					printf("文件写入错误！");
				}
				printf("【删除成功】");
			}			
			else
			{
				printf("【没有删除】");
			}
			Sleep(1000);
		}
		else if (1 == find && 1 < n)//找到同学号的同学，显然是输入的时候有错误
		{
			//最多存10个相同学号的同学
			printf("\n找到多名相同学号的同学，");
			do {
				printf("请问要删除第几位学生的信息（输入“-1”返回上一级）：[   ]\b\b\b");
				scanf("%d", &i);
				getchar();
				if (-1 == i)
				{
					continue;
				}
				i--;//数组下标减一
				memset(&stu, '\0', sizeof(struct student));//将结构体赋值为空
				stu.delTag = TRUE;//标记为被删除
				do {
					fseek(fp, -1 * sizeof(struct student), SEEK_CUR);//移动文件位置指针到要删除的学生信息首地址
				} while (ftell(fp) != pf[i]);
				if (fwrite(&stu, sizeof(struct student), 1, fp) != 1)//直接覆盖写入一堆空字符
				{
					printf("文件写入错误！");
				}
				printf("【删除成功】");
				Sleep(500);
				printf("\n请问是否继续删除？（y/n）[ ]\b\b");
				scanf(" %c", &choose);
				getchar();
				if ('n' == choose)
				{
					break;
				}
			} while (TRUE);
		}
		fclose(fp);
	} while (TRUE);
}

void Search(FILE *fp)//查找模块，内含修改模块，考虑重复查找的问题
{
	long pf[10];//获得文件内容位置指针，同名时最多存10位同名学生
	int choose1;
	char choose2;
	char s[20];
	student search;//查找班级时所要比对的信息
	int n;//重名人数
	int i;
	do {
		system("cls");
		fflush(stdin);
		printf("请选择查找方式：1.按学号查找；2.按姓名查找；3.查找班级；0.返回上一级菜单  [ ]\b\b");
		do {
			if (!scanf("%d", &choose1))
			{
				while (getchar() == '\n');
				printf("\n输入错误请重新输入：[ ]\b\b");
			}
		} while (0 > choose1 && 3 < choose1);
		getchar();
		n = 0;
		switch (choose1)
		{
		//按学号查找
		case 1:
			printf("\n请输入学号（输入“-1”返回上一级）：");
			scanf(" %s", s);
			if (strcmp("-1", s) == 0)
			{
				continue;
			}
			system("cls");
			if ((fp = fopen("Access.bin", "rb+")) == NULL)//用"rb+"才能从文件中间修改内容
			{
				printf("\n打开文件失败！");
				Sleep(1000);
				return;
			}
			i = 0;
			fread(&stu, sizeof(struct student), 1, fp);
			while (!feof(fp))
			{
				if (TRUE != stu.delTag && strcmp(stu.num, s) == 0)//比较学生信息和输入的学号
				{
					if (i < 10)//最多存10个重名的学生
					{
						pf[i] = ftell(fp) - sizeof(struct student);//如果读到符合的信息，则获取该信息结构体首地址
					}
					if (0 < i)
					{
						printf("\n第%d位相同：\n", i + 1);//若有学号相同的的学生将输出位次
					}
					printf("学号：%s\n", stu.num);
					printf("姓名：%s\n", stu.name);
					printf("性别：%s\n", stu.sex);
					printf("出生日期：%d/%d/%d\n",
						stu.birthday.year, stu.birthday.month, stu.birthday.day);
					printf("年龄：%d\n", stu.age);
					printf("籍贯：%s\n", stu.addr);
					printf("系别：%s\n", stu.dept);
					printf("专业：%s\n", stu.major);
					printf("班级：%s\n", stu.classs);
					printf("电话：%s\n\n", stu.phone);
					n++;
					i++;
				}
				fread(&stu, sizeof(struct student), 1, fp);
			}
			if (0 == n)
			{
				printf("没有找到该学号所对应的学生。请问是否重新查找：y.是；n.返回上一级菜单  [ ]\b\b");
				fflush(stdin);
				choose2 = getchar();
				getchar();
				switch (choose2)
				{
				case 'y'://重新查找
					Search(fp);
					break;
				case 'n'://返回上一级菜单
					switch (find)
					{
					case 1:
						menuAdmin(fp);
						break;
					case 2:
						menuVisit(fp);
						break;
					}
					break;
				default:
					break;
				}
			}
			else if (1 == find && 1 == n)//找到了一名对应学号学生的信息
			{
				do {
					fseek(fp, -1 * sizeof(struct student), SEEK_CUR);//移动文件位置指针到要修改的学生信息首地址
				} while (ftell(fp) != pf[0]);
				fread(&stu, sizeof(struct student), 1, fp);//保存要修改的学生信息到缓存数组
				printf("\n请问是否要修改该学生的信息（y/n）  [ ]\b\b");
				getchar();
				choose2 = getchar();
				if ('y' == choose2)
				{
					Modify(&stu, fp, pf[0]);
				}
			}
			else if (1 == find && 1 < n)//找到同学号的同学，显然是输入的时候有错误
			{
				printf("\n找到多名相同学号的同学，请修改其中一名以确保学号独立性");
				//最多存10个相同学号的同学
				printf("\n请问要修改第几位学生的信息（输入“-1”返回上一级）：[   ]\b\b\b");
				scanf("%d", &i);
				getchar();
				if (-1 == i)
				{
					continue;
				}
				i--;//数组下标减一
				do {
					fseek(fp, -1 * sizeof(struct student), SEEK_CUR);//移动文件位置指针到要修改的学生信息首地址
				} while (ftell(fp) != pf[i]);
				fread(&stu, sizeof(struct student), 1, fp);//保存要修改的学生信息到缓存数组
				Modify(&stu, fp, pf[i]);
			}
			else if (2 == find && 1 == n)//访客查询学号的结果：查到了一名同学
			{
				printf("\n按任意键返回...");
				getch();
			}
			else//考虑访客登录时看到多名学号相同的同学
			{
				printf("\n有多名相同学号的同学！");
				Sleep(1000);
			}
			fclose(fp);
			break;

		//按姓名查找
		case 2:
			printf("\n请输入姓名（输入“-1”返回上一级）：");
			scanf(" %s", s);
			if (strcmp("-1", s) == 0)
			{
				continue;
			}
			system("cls");
			if ((fp = fopen("Access.bin", "rb+")) == NULL)//用"rb+"才能从文件中间修改内容
			{
				printf("\n打开文件失败！");
				Sleep(1000);
				return;
			}
			i = 0;
			fread(&stu, sizeof(struct student), 1, fp);
			while (!feof(fp))
			{
				if (TRUE != stu.delTag && strcmp(stu.name, s) == 0)//比较学生信息和输入的学号
				{
					if (i < 10)//最多存10个重名的学生
					{
						pf[i] = ftell(fp) - sizeof(struct student);//如果读到符合的信息，则获取该信息结构体首地址
					}
					printf("第%d位：\n", i + 1);
					printf("学号：%s\n", stu.num);
					printf("姓名：%s\n", stu.name);
					printf("性别：%s\n", stu.sex);
					printf("出生日期：%d/%d/%d\n",
						stu.birthday.year, stu.birthday.month, stu.birthday.day);
					printf("年龄：%d\n", stu.age);
					printf("籍贯：%s\n", stu.addr);
					printf("系别：%s\n", stu.dept);
					printf("专业：%s\n", stu.major);
					printf("班级：%s\n", stu.classs);
					printf("电话：%s\n\n", stu.phone);
					n++;
					i++;
				}
				fread(&stu, sizeof(struct student), 1, fp);
			}
			if (0 == n)
			{
				printf("\n没有叫做 %s 的学生。按任意键返回...");
				getch();
			}
			else if (1 == find && 1 < n)			//选择要修改的同学，输入位次，作为参数传入Modify()
			{
				printf("\n请问要修改第几位学生的信息（输入“-1”返回上一级）：[   ]\b\b\b");
				scanf("%d", &i);
				getchar();
				if (-1 == i)
				{
					continue;
				}
				i--;//数组下标减一
				do {
					fseek(fp, -1 * sizeof(struct student), SEEK_CUR);//移动文件位置指针到要修改的学生信息首地址
				} while (ftell(fp) != pf[i]);
				fread(&stu, sizeof(struct student), 1, fp);//保存要修改的学生信息到缓存数组
				Modify(&stu, fp, pf[i]);
			}
			else if (2 == find)
			{
				printf("\n按任意键返回...");
				getch();
			}
			fclose(fp);
			break;

		//查看班级
		//【改进：可以在后面选择是否修改其中一位同学的信息，太累了，不想做了】】】】】】】】
		case 3:
			printf("\n请输入系别（输入“-1”返回上一级）：");
			scanf(" %s", &search.dept);
			if (strcmp("-1", search.dept) == 0)
			{
				continue;
			}
			printf("\n请输入专业（输入“-1”返回上一级）：");
			scanf(" %s", &search.major);
			if (strcmp("-1", search.major) == 0)
			{
				continue;
			}
			printf("\n请输入“x班”（输入“-1”返回上一级）：");
			scanf(" %s", &search.classs);
			if (strcmp("-1", search.classs) == 0)
			{
				continue;
			}
			system("cls");
			if ((fp = fopen("Access.bin", "rb")) == NULL)
			{
				printf("\n打开文件失败！");
				Sleep(1000);
				return;
			}
			fread(&stu, sizeof(struct student), 1, fp);//①
			while (!feof(fp))
			{
				if (TRUE != stu.delTag
					&& strcmp(stu.dept, search.dept) == 0
					&& strcmp(stu.major, search.major) == 0
					&& strcmp(stu.classs, search.classs) == 0)
				{
					printf("学号：%s\n", stu.num);//输出同班学生信息
					printf("姓名：%s\n", stu.name);
					printf("性别：%s\n", stu.sex);
					printf("出生日期：%d/%d/%d\n",
						stu.birthday.year, stu.birthday.month, stu.birthday.day);
					printf("年龄：%d\n", stu.age);
					printf("籍贯：%s\n", stu.addr);
					printf("系别：%s\n", stu.dept);
					printf("专业：%s\n", stu.major);
					printf("班级：%s\n", stu.classs);
					printf("电话：%s\n\n", stu.phone);
					n++;
				}
				fread(&stu, sizeof(struct student), 1, fp);//接①：先判断是否读到文件尾，再输出到屏幕
			}
			printf("【%s%s%s 总共有 %d 名学生】", search.dept, search.major, search.classs, n);
			fclose(fp);
			printf("\n\n按任意键返回上一级......");
			getch();
			break;
		//返回上一级菜单
		case 0:
			switch (find)
			{
			case 1:
				menuAdmin(fp);
				break;
			case 2:
				menuVisit(fp);
				break;
			}
			break;
		default:
			printf("\nchoose1的值不合理");
			Sleep(1000);
			break;
		}
	} while (TRUE);
}

void Modify(student *pS, FILE *fp, long pf)//单项修改模块
{
	student temp;//缓存修改前的信息
	char choose1, choose2;
	int switch_on;
	do {
		temp = stu;
		printf("\n【请输入想要修改信息的序号】\n1.学号\n2.姓名\n3.性别\n4.出生日期\n5.年龄\n6.籍贯\n7.系别\n8.专业\n9.班级\n10.电话 \n0.返回\n请输入[   ]\b\b\b");
		scanf("%d", &switch_on);
		getchar();
		switch (switch_on)
		{
		case 1://修改学号
			printf("\n学号：");
			scanf(" %s", &(pS->num));
			break;
		case 2://修改姓名
			printf("\n姓名：");
			scanf(" %s", &(pS->name));
			break;
		case 3://修改性别
			printf("\n性别：");
			scanf(" %s", &(pS->sex));
			break;
		case 4://修改出生日期
			printf("\n出生日期(xxxx/xx/xx)：");
			scanf("%d/%d/%d", &(pS->birthday.year), &(pS->birthday.month), &(pS->birthday.day));
			fflush(stdin);
			break;
		case 5://修改年龄
			printf("\n年龄：");
			scanf("%d", &(pS->age));
			break;
		case 6://修改籍贯
			printf("\n籍贯：");
			scanf(" %s", &(pS->addr));
			break;
		case 7://修改系别
			printf("\n系别：");
			scanf(" %s", &(pS->dept));
			break;
		case 8://修改专业
			printf("\n专业：");
			scanf(" %s", &(pS->major));
			break;
		case 9://修改班级
			printf("\n班级：");
			scanf(" %s", &(pS->classs));
			break;
		case 10://修改电话
			printf("\n电话：");
			scanf(" %s", &(pS->phone));
			break;
		case 0:
			return;
			break;
		default:
			break;
		}
		printf("\n修改后：\n");
		printf("学号：%s\n", stu.num);
		printf("姓名：%s\n", stu.name);
		printf("性别：%s\n", stu.sex);
		printf("出生日期：%d/%d/%d\n",
			stu.birthday.year, stu.birthday.month, stu.birthday.day);
		printf("年龄：%d\n", stu.age);
		printf("籍贯：%s\n", stu.addr);
		printf("系别：%s\n", stu.dept);
		printf("专业：%s\n", stu.major);
		printf("班级：%s\n", stu.classs);
		printf("电话：%s\n\n", stu.phone);
		//确定修改？
		printf("\n确定修改？（y/n）[ ]\b\b");
		scanf(" %c", &choose1);
		if ('y' == choose1 && stu.num[0] != '\0' && stu.name[0] != '\0')
		{
			do {
				fseek(fp, -1 * sizeof(struct student), SEEK_CUR);//移动文件位置指针到要修改的学生信息首地址
			} while (ftell(fp) != pf);
			if (fwrite(&stu, sizeof(struct student), 1, fp) != 1)//直接覆盖写入
			{
				printf("文件写入错误！");
			}
		}
		else
		{
			printf("\n没有进行修改");
			stu = temp;
		}
		printf("\n是否结束所有修改？（y/n）[ ]\b\b");
		scanf(" %c", &choose2);
		if ('y' == choose2)
		{
			return;
		}
		fflush(stdin);
	} while (TRUE);
}

void Browse(FILE *fp)//浏览模块
{
	int n = 0;//学生总数
	system("cls");
	if ((fp = fopen("Access.bin", "rb")) == NULL)
	{
		printf("\n打开文件失败！");
		Sleep(1000);
		return;
	}
	fread(&stu, sizeof(struct student), 1, fp);//①
	while (!feof(fp))
	{
		if (TRUE != stu.delTag)//输出没有被删除的学生信息
		{
			printf("学号：%s\n", stu.num);
			printf("姓名：%s\n", stu.name);
			printf("性别：%s\n", stu.sex);
			printf("出生日期：%d/%d/%d\n",
				stu.birthday.year, stu.birthday.month, stu.birthday.day);
			printf("年龄：%d\n", stu.age);
			printf("籍贯：%s\n", stu.addr);
			printf("系别：%s\n", stu.dept);
			printf("专业：%s\n", stu.major);
			printf("班级：%s\n", stu.classs);
			printf("电话：%s\n\n", stu.phone);
			n++;
		}
		fread(&stu, sizeof(struct student), 1, fp);//接①：先判断是否读到文件尾，再输出到屏幕
	}
	printf("【该数据库内总共有 %d 名学生】", n);
	printf("\n\n按任意键返回管理员菜单......");
	getch();
	fclose(fp);
	switch (find)
	{
	case 1:
		menuAdmin(fp);
		break;
	case 2:
		menuVisit(fp);
		break;
	default:
		break;
	}
}

void Empty(FILE *fp)//清空模块
{
	char choose;
	fflush(stdin);
	system("cls");
	printf("请再次确认是否要清空数据库！输入（y/n）：[ ]\b\b");
	choose = getchar();
	if ('y' == choose)
	{
		fp = fopen("Access.bin", "wb");
		if (fp == NULL)
		{
			printf("\n打开文件失败！");
			Sleep(1000);
			return;
		}
		fclose(fp);
		printf("\n【您清空了数据库】");
	}
	else
	{
		printf("\n【您没有清空数据库】");
	}
	printf("\n返回管理员菜单...");
	Sleep(1000);
	menuAdmin(fp);
}

void FirstUse(FILE *fp)//第一次使用管理员登陆
{
	fp = fopen("Access.bin", "wb");
	if (fp == NULL)
	{
		printf("\n打开文件失败！");
		Sleep(1000);
		return;
	}
	fclose(fp);
	Insert(fp);
}

void menuAdmin(FILE *fp)//管理员菜单
{
	int switch_on;
	system("cls");
	do {
		system("cls");
		fflush(stdin);
		gotoxy(4, 0);
		printf("\t\t**********************************************");
		printf("\n\t\t||              您现在是管理员              ||");
		printf("\n\t\t||                                          ||");
		printf("\n\t\t||                 1.添加                   ||");
		printf("\n\t\t||                 2.删除                   ||");
		printf("\n\t\t||                 3.查找                   ||");
		printf("\n\t\t||                 4.浏览                   ||");
		printf("\n\t\t||                 5.清空                   ||");
		printf("\n\t\t||                                          ||");
		printf("\n\t\t||                 0.返回                   ||");
		printf("\n\t\t||                                          ||");
		printf("\n\t\t**********************************************");
		printf("\n\t\t若要修改一名学生的某一项信息，请选择[3].查找");
		printf("\n\t\t>>请输入序号选择功能[ ]\b\b");
		scanf("%d", &switch_on);
		getchar();
		if (switch_on < 0 || switch_on > 5)
		{
			printf("\n输入错误！请重新输入！");
			fflush(stdin);
			Sleep(500);
		}
		else
		{
			//fflush(stdin);
			break;
		}
	} while(TRUE);
	switch (switch_on)
	{
	case 1://添加模块
		printf("\n\n\t\t您选择了[添加]");
		fflush(stdin);
		Sleep(500);
		Insert(fp);
		break;
	case 2://删除模块
		printf("\n\n\t\t您选择了[删除]");
		fflush(stdin);
		Sleep(500);
		Delete(fp);
		break;
	case 3://查找模块
		printf("\n\n\t\t您选择了[查找]");
		fflush(stdin);
		Sleep(500);
		Search(fp);
		break;
	case 4://浏览模块
		printf("\n\n\t\t您选择了[浏览]");
		fflush(stdin);
		Sleep(500);
		Browse(fp);
		break;
	case 5://清空模块
		printf("\n\n\t\t您选择了[清空]");
		fflush(stdin);
		Sleep(500);
		Empty(fp);
		break;
	case 0://返回
		fflush(stdin);
		Sleep(500);
		main();
		break;
	default:
		break;
	}
	system("cls");
}

void menuVisit(FILE *fp)//访客菜单
{
	int switch_on;
	do {
		system("cls");
		fflush(stdin);
		gotoxy(4, 0);
		printf("\t\t**********************************************");
		printf("\n\t\t||               您现在是访客               ||");
		printf("\n\t\t||                                          ||");
		printf("\n\t\t||                 1.查找                   ||");
		printf("\n\t\t||                 2.浏览                   ||");
		printf("\n\t\t||                                          ||");
		printf("\n\t\t||                 0.返回                   ||");
		printf("\n\t\t||                                          ||");
		printf("\n\t\t**********************************************");
		printf("\n\t\t>>请输入序号选择功能[ ]\b\b");
		scanf("%d", &switch_on);
		if (switch_on < 0 || switch_on > 2)
		{
			printf("\n输入错误！请重新输入！");
			fflush(stdin);
			Sleep(500);
		}
		else
		{
			getchar();
			break;
		}
	} while (TRUE);
	switch (switch_on)
	{
	case 1://查找模块
		printf("\n\n\t\t您选择了[查找]");
		fflush(stdin);
		Sleep(500);
		Search(fp);
		break;
	case 2://浏览模块
		printf("\n\n\t\t您选择了[浏览]");
		fflush(stdin);
		Sleep(500);
		Browse(fp);
		break;

	case 0://返回
		fflush(stdin);
		Sleep(500);
		main();
		break;
	default:
		break;
	}
	system("cls");
}
