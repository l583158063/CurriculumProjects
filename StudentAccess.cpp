#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

struct date //��������
{
	int year;
	int month;
	int day;
};

struct student
{
	BOOL delTag;	//ѧ����Ϣ�Ƿ�ɾ���ı�־����ʼ��ΪFALSE������ɾ����ֵΪTRUE
	char num[20];			//ѧ��
	char name[12];			//����
	char sex[4];			//�Ա�
	struct date birthday;	//��������
	int age;				//����
	char addr[50];			//����
	char dept[50];			//ϵ��
	char major[30];			//רҵ
	char classs[30];		//�༶
	char phone[20];			//�绰
}stu;

void gotoxy(int x, int y);//��궨λ,��궨λ����SetConsoleCursorPosition�����Ͻ�λ����0,0Ȼ��������������
void Insert(FILE *fp);//���ģ��
void Delete(FILE *fp);//ɾ��ģ�飬ɾ��һ��ָ��ѧ������Ϣ
void Search(FILE *fp);//����ģ�飬��ѧ�ź����������ֲ�ͬ���ҷ�ʽ
void Modify(student *pS, FILE *fp, long pf);//�޸�ģ�飬�޸�һ��ѧ����һ����Ϣ
void Browse(FILE *fp);//���ģ�飬����Ļ������У�δ��ɾ������ѧ����Ϣ
void Empty(FILE *fp);//���ģ�飬�����ݿ����
void FirstUse(FILE *fp);//�״�ʹ�ø�ϵͳʱ����
void menuAdmin(FILE *fp);//����Ա�˵�
void menuVisit(FILE *fp);//�ÿͲ˵�

char sign = 'y';//�Ƿ��״ι���Ա��¼�ı��
int find;//��¼ѡ����ǹ���Ա���Ƿÿͣ�����ԱΪ1���ÿ�Ϊ2
FILE *fp;

int main()
{
	char sword[3] = { '>', ' ', ' '};
	int switch_on;//��ҳ�α�˵��İ�����¼
	int a = 0;//�α�˵���ѡ���־
	int first = 1;//�ж��Ƿ��һ��ʹ�ø�ϵͳ
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
		printf("\n\n\n\n\t\t***********��ӭ����ѧ��ѧ������ϵͳ***********");
		printf("\n\t\t||                                          ||");
		printf("\n\t\t||                 ���ȵ�¼                 ||");
		printf("\n\t\t||                                          ||");
		printf("\n\t\t||                 %c����Ա                  ||", sword[0]);
		printf("\n\t\t||                  %c�ÿ�                   ||", sword[1]);
		printf("\n\t\t||                                          ||");
		printf("\n\t\t||                  %c�˳�                   ||", sword[2]);
		printf("\n\t\t||                                          ||");
		printf("\n\t\t**********************************************");
		switch_on = getch();
		switch (switch_on)
		{
		case 80:                       //��������switch_on��һ
			a++;
			break;
		case 72:                       //��������switch_on��һ
			a--;
			break;
		case 13:                       //���»س�ʱѡ����
			if (0 == a)                 //ѡ�����Ա
			{
				find = 1;
				while (TRUE)
				{
					system("cls");
					fflush(stdin);
					gotoxy(6, 11);//�ƶ����
					printf("������6λ���룺");//������123456
					fgets(input, sizeof(input), stdin);
					for (i = 0; input[i] != '\n'; i++)
					{
						;//�ƶ��±����ַ�����β��
					}
					input[i] = '\0';//fgets���Ὣ'\n'�Զ�����'\0'
					if (strcmp(input, password) == 0)
					{
						system("cls");
						gotoxy(6, 11);
						printf("Welcome!\n");
						Sleep(1000);
						break;//�������������ѭ��
					}
					else
					{
						system("cls");
						gotoxy(6, 11);
						printf("����������ٴ����룡\n");
						Sleep(1000);
					}
				}
				gotoxy(7, 11);
				printf("������״�ʹ�ø�ϵͳ�����ǽ����ڹ���Ŀ¼��,");
				gotoxy(8, 11);
				printf("����һ���µ��ı��ļ���ԭ�е��ı��ļ����ᱻ���ǣ�");
				gotoxy(9, 11);
				printf("�����Ƿ��ǵ�һ��ʹ�ø�ѧ��ѧ������ϵͳ��y/n����");
				scanf(" %c", &sign);
				getchar();
				if ('y' == sign)//�״�ʹ�ø�ϵͳ
				{
					FirstUse(fp);
				}
				menuAdmin(fp);//�������Ա�˵�
			}
			else if (-2 == a || 1 == a)//ѡ��ÿ�
			{
				find = 2;
				menuVisit(fp);//����ÿͲ˵�
			}
			else                       //ѡ���˳�
			{
				exit(0);
			}
			break;
		default:
			break;
		}
		a = a % 3;//�α�ѡ���־0����1����2�ֱ��Ӧ��ͬ��ѡ��
		switch (a)
		{
		case 1:
		case -2://��ͷ�ڡ��ÿ͡�λ��
			sword[0] = ' ';
			sword[1] = '>';
			sword[2] = ' ';
			break;
		case -1:
		case 2://��ͷ�ڡ��˳���λ��
			sword[0] = ' ';
			sword[1] = ' ';
			sword[2] = '>';
			break;
		case 0://��ͷ�ڡ�����Ա��λ��
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

void gotoxy(int x, int y)//�ƶ����,��궨λ����SetConsoleCursorPosition�����Ͻ�λ����0,0Ȼ��������������
{
	COORD pos;
	pos.X = 2 * y;
	pos.Y = x;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void Insert(FILE *fp)//���ģ��
{
	if ((fp = fopen("Access.bin", "ab+")) == NULL)//���ı�����β�������Ϣ
	{
		printf("\n���ļ�ʧ�ܣ�");
		Sleep(1000);
		return;
	}
	do {
		system("cls");
		fflush(stdin);
		printf("[�����Ϣ]\n");
		printf("������һ��ѧ������Ϣ������ѧ��ʱ���롰-1�����Խ������롣\n");
		printf("ѧ�ţ�");
		gets_s(stu.num);
		if (stu.num[0] == '-')
		{
			fclose(fp);
			printf("�����������");
			Sleep(1000);
			menuAdmin(fp);//����������ع���Ա�˵�
		}
		stu.delTag = FALSE;//��ӵ�ÿһ��ѧ������δ��ɾ����
		printf("������");
		gets_s(stu.name);
		printf("�Ա���/Ů����");
		gets_s(stu.sex);
		printf("��������(xxxx/xx/xx)��");
		scanf("%d/%d/%d", &stu.birthday.year, &stu.birthday.month, &stu.birthday.day);
		printf("���䣺");
		scanf("%d", &stu.age);
		getchar();
		printf("���᣺");
		gets_s(stu.addr);
		printf("ϵ��");
		gets_s(stu.dept);
		printf("רҵ��");
		gets_s(stu.major);
		printf("�༶��");
		gets_s(stu.classs);
		printf("�绰��");
		gets_s(stu.phone);
		//��һ��дһ��
		if (stu.num[0] != '\0'&&stu.name[0] != '\0')
		{
			if (fwrite(&stu, sizeof(struct student), 1, fp) != 1)
			{
				printf("�ļ�д�����");
			}
		}
	} while (TRUE);
}

void Delete(FILE *fp)//ɾ��ģ��
{
	char choose;
	long pf[10];//����10���ظ���ѧ����Ϣ�ṹ���ļ����׵�ַ
	int n;//�ж��Ƿ������ظ���ѧ����Ϣ
	int i;
	char s[20];
	do {
		n = 0;
		system("cls");
		printf("������Ҫɾ��ѧ����ѧ�ţ����롰-1������)��");
		scanf(" %s", s);
		if ('-' == s[0])
		{
			menuAdmin(fp);
		}
		if ((fp = fopen("Access.bin", "rb+")) == NULL)//��"rb+"���ܴ��ļ��м��޸�����
		{
			printf("\n���ļ�ʧ�ܣ�");
			Sleep(1000);
			return;
		}
		i = 0;
		fread(&stu, sizeof(struct student), 1, fp);
		while (!feof(fp))
		{
			if (TRUE != stu.delTag && strcmp(stu.num, s) == 0)//�Ƚ�ѧ����Ϣ�������ѧ��
			{
				if (i < 10)//����10��������ѧ��
				{
					pf[i] = ftell(fp) - sizeof(struct student);//����������ϵ���Ϣ�����ȡ����Ϣ�ṹ���׵�ַ
				}
				printf("��%dλ��\n", i + 1);
				printf("ѧ�ţ�%s\n", stu.num);
				printf("������%s\n", stu.name);
				printf("�Ա�%s\n", stu.sex);
				printf("�������ڣ�%d/%d/%d\n",
					stu.birthday.year, stu.birthday.month, stu.birthday.day);
				printf("���䣺%d\n", stu.age);
				printf("���᣺%s\n", stu.addr);
				printf("ϵ��%s\n", stu.dept);
				printf("רҵ��%s\n", stu.major);
				printf("�༶��%s\n", stu.classs);
				printf("�绰��%s\n\n", stu.phone);
				n++;
				i++;
			}
			fread(&stu, sizeof(struct student), 1, fp);
		}
		if (0 == n)
		{
			printf("û���ҵ���ѧ������Ӧ��ѧ���������Ƿ����룺y.�ǣ�n.������һ���˵�  [ ]\b\b");
			fflush(stdin);
			choose = getchar();
			getchar();
			switch (choose)
			{
			case 'y'://���²���
				continue;
				break;
			case 'n'://������һ���˵�
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
				printf("chooseֵ������");
				Sleep(1000);
				break;
			}
		}
		else if (1 == find && 1 == n)//�ҵ���һ����Ӧѧ��ѧ������Ϣ
		{
			do {
				fseek(fp, -1 * sizeof(struct student), SEEK_CUR);//�ƶ��ļ�λ��ָ�뵽Ҫ�޸ĵ�ѧ����Ϣ�׵�ַ
			} while (ftell(fp) != pf[0]);
			fread(&stu, sizeof(struct student), 1, fp);//����Ҫɾ����ѧ����Ϣ����������
			printf("\n�����Ƿ�Ҫɾ����ѧ������Ϣ����y/n��[ ]\b\b");
			scanf(" %c", &choose);
			getchar();
			if ('y' == choose)
			{
				memset(&stu, '\0', sizeof(struct student));//���ṹ�帳ֵΪ��
				stu.delTag = TRUE;//���Ϊ��ɾ��
				do {
					fseek(fp, -1 * sizeof(struct student), SEEK_CUR);//�ƶ��ļ�λ��ָ�뵽Ҫɾ����ѧ����Ϣ�׵�ַ
				} while (ftell(fp) != pf[0]);
				if (fwrite(&stu, sizeof(struct student), 1, fp) != 1)//ֱ�Ӹ���д��һ�ѿ��ַ�
				{
					printf("�ļ�д�����");
				}
				printf("��ɾ���ɹ���");
			}			
			else
			{
				printf("��û��ɾ����");
			}
			Sleep(1000);
		}
		else if (1 == find && 1 < n)//�ҵ�ͬѧ�ŵ�ͬѧ����Ȼ�������ʱ���д���
		{
			//����10����ͬѧ�ŵ�ͬѧ
			printf("\n�ҵ�������ͬѧ�ŵ�ͬѧ��");
			do {
				printf("����Ҫɾ���ڼ�λѧ������Ϣ�����롰-1��������һ������[   ]\b\b\b");
				scanf("%d", &i);
				getchar();
				if (-1 == i)
				{
					continue;
				}
				i--;//�����±��һ
				memset(&stu, '\0', sizeof(struct student));//���ṹ�帳ֵΪ��
				stu.delTag = TRUE;//���Ϊ��ɾ��
				do {
					fseek(fp, -1 * sizeof(struct student), SEEK_CUR);//�ƶ��ļ�λ��ָ�뵽Ҫɾ����ѧ����Ϣ�׵�ַ
				} while (ftell(fp) != pf[i]);
				if (fwrite(&stu, sizeof(struct student), 1, fp) != 1)//ֱ�Ӹ���д��һ�ѿ��ַ�
				{
					printf("�ļ�д�����");
				}
				printf("��ɾ���ɹ���");
				Sleep(500);
				printf("\n�����Ƿ����ɾ������y/n��[ ]\b\b");
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

void Search(FILE *fp)//����ģ�飬�ں��޸�ģ�飬�����ظ����ҵ�����
{
	long pf[10];//����ļ�����λ��ָ�룬ͬ��ʱ����10λͬ��ѧ��
	int choose1;
	char choose2;
	char s[20];
	student search;//���Ұ༶ʱ��Ҫ�ȶԵ���Ϣ
	int n;//��������
	int i;
	do {
		system("cls");
		fflush(stdin);
		printf("��ѡ����ҷ�ʽ��1.��ѧ�Ų��ң�2.���������ң�3.���Ұ༶��0.������һ���˵�  [ ]\b\b");
		do {
			if (!scanf("%d", &choose1))
			{
				while (getchar() == '\n');
				printf("\n����������������룺[ ]\b\b");
			}
		} while (0 > choose1 && 3 < choose1);
		getchar();
		n = 0;
		switch (choose1)
		{
		//��ѧ�Ų���
		case 1:
			printf("\n������ѧ�ţ����롰-1��������һ������");
			scanf(" %s", s);
			if (strcmp("-1", s) == 0)
			{
				continue;
			}
			system("cls");
			if ((fp = fopen("Access.bin", "rb+")) == NULL)//��"rb+"���ܴ��ļ��м��޸�����
			{
				printf("\n���ļ�ʧ�ܣ�");
				Sleep(1000);
				return;
			}
			i = 0;
			fread(&stu, sizeof(struct student), 1, fp);
			while (!feof(fp))
			{
				if (TRUE != stu.delTag && strcmp(stu.num, s) == 0)//�Ƚ�ѧ����Ϣ�������ѧ��
				{
					if (i < 10)//����10��������ѧ��
					{
						pf[i] = ftell(fp) - sizeof(struct student);//����������ϵ���Ϣ�����ȡ����Ϣ�ṹ���׵�ַ
					}
					if (0 < i)
					{
						printf("\n��%dλ��ͬ��\n", i + 1);//����ѧ����ͬ�ĵ�ѧ�������λ��
					}
					printf("ѧ�ţ�%s\n", stu.num);
					printf("������%s\n", stu.name);
					printf("�Ա�%s\n", stu.sex);
					printf("�������ڣ�%d/%d/%d\n",
						stu.birthday.year, stu.birthday.month, stu.birthday.day);
					printf("���䣺%d\n", stu.age);
					printf("���᣺%s\n", stu.addr);
					printf("ϵ��%s\n", stu.dept);
					printf("רҵ��%s\n", stu.major);
					printf("�༶��%s\n", stu.classs);
					printf("�绰��%s\n\n", stu.phone);
					n++;
					i++;
				}
				fread(&stu, sizeof(struct student), 1, fp);
			}
			if (0 == n)
			{
				printf("û���ҵ���ѧ������Ӧ��ѧ���������Ƿ����²��ң�y.�ǣ�n.������һ���˵�  [ ]\b\b");
				fflush(stdin);
				choose2 = getchar();
				getchar();
				switch (choose2)
				{
				case 'y'://���²���
					Search(fp);
					break;
				case 'n'://������һ���˵�
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
			else if (1 == find && 1 == n)//�ҵ���һ����Ӧѧ��ѧ������Ϣ
			{
				do {
					fseek(fp, -1 * sizeof(struct student), SEEK_CUR);//�ƶ��ļ�λ��ָ�뵽Ҫ�޸ĵ�ѧ����Ϣ�׵�ַ
				} while (ftell(fp) != pf[0]);
				fread(&stu, sizeof(struct student), 1, fp);//����Ҫ�޸ĵ�ѧ����Ϣ����������
				printf("\n�����Ƿ�Ҫ�޸ĸ�ѧ������Ϣ��y/n��  [ ]\b\b");
				getchar();
				choose2 = getchar();
				if ('y' == choose2)
				{
					Modify(&stu, fp, pf[0]);
				}
			}
			else if (1 == find && 1 < n)//�ҵ�ͬѧ�ŵ�ͬѧ����Ȼ�������ʱ���д���
			{
				printf("\n�ҵ�������ͬѧ�ŵ�ͬѧ�����޸�����һ����ȷ��ѧ�Ŷ�����");
				//����10����ͬѧ�ŵ�ͬѧ
				printf("\n����Ҫ�޸ĵڼ�λѧ������Ϣ�����롰-1��������һ������[   ]\b\b\b");
				scanf("%d", &i);
				getchar();
				if (-1 == i)
				{
					continue;
				}
				i--;//�����±��һ
				do {
					fseek(fp, -1 * sizeof(struct student), SEEK_CUR);//�ƶ��ļ�λ��ָ�뵽Ҫ�޸ĵ�ѧ����Ϣ�׵�ַ
				} while (ftell(fp) != pf[i]);
				fread(&stu, sizeof(struct student), 1, fp);//����Ҫ�޸ĵ�ѧ����Ϣ����������
				Modify(&stu, fp, pf[i]);
			}
			else if (2 == find && 1 == n)//�ÿͲ�ѯѧ�ŵĽ�����鵽��һ��ͬѧ
			{
				printf("\n�����������...");
				getch();
			}
			else//���Ƿÿ͵�¼ʱ��������ѧ����ͬ��ͬѧ
			{
				printf("\n�ж�����ͬѧ�ŵ�ͬѧ��");
				Sleep(1000);
			}
			fclose(fp);
			break;

		//����������
		case 2:
			printf("\n���������������롰-1��������һ������");
			scanf(" %s", s);
			if (strcmp("-1", s) == 0)
			{
				continue;
			}
			system("cls");
			if ((fp = fopen("Access.bin", "rb+")) == NULL)//��"rb+"���ܴ��ļ��м��޸�����
			{
				printf("\n���ļ�ʧ�ܣ�");
				Sleep(1000);
				return;
			}
			i = 0;
			fread(&stu, sizeof(struct student), 1, fp);
			while (!feof(fp))
			{
				if (TRUE != stu.delTag && strcmp(stu.name, s) == 0)//�Ƚ�ѧ����Ϣ�������ѧ��
				{
					if (i < 10)//����10��������ѧ��
					{
						pf[i] = ftell(fp) - sizeof(struct student);//����������ϵ���Ϣ�����ȡ����Ϣ�ṹ���׵�ַ
					}
					printf("��%dλ��\n", i + 1);
					printf("ѧ�ţ�%s\n", stu.num);
					printf("������%s\n", stu.name);
					printf("�Ա�%s\n", stu.sex);
					printf("�������ڣ�%d/%d/%d\n",
						stu.birthday.year, stu.birthday.month, stu.birthday.day);
					printf("���䣺%d\n", stu.age);
					printf("���᣺%s\n", stu.addr);
					printf("ϵ��%s\n", stu.dept);
					printf("רҵ��%s\n", stu.major);
					printf("�༶��%s\n", stu.classs);
					printf("�绰��%s\n\n", stu.phone);
					n++;
					i++;
				}
				fread(&stu, sizeof(struct student), 1, fp);
			}
			if (0 == n)
			{
				printf("\nû�н��� %s ��ѧ���������������...");
				getch();
			}
			else if (1 == find && 1 < n)			//ѡ��Ҫ�޸ĵ�ͬѧ������λ�Σ���Ϊ��������Modify()
			{
				printf("\n����Ҫ�޸ĵڼ�λѧ������Ϣ�����롰-1��������һ������[   ]\b\b\b");
				scanf("%d", &i);
				getchar();
				if (-1 == i)
				{
					continue;
				}
				i--;//�����±��һ
				do {
					fseek(fp, -1 * sizeof(struct student), SEEK_CUR);//�ƶ��ļ�λ��ָ�뵽Ҫ�޸ĵ�ѧ����Ϣ�׵�ַ
				} while (ftell(fp) != pf[i]);
				fread(&stu, sizeof(struct student), 1, fp);//����Ҫ�޸ĵ�ѧ����Ϣ����������
				Modify(&stu, fp, pf[i]);
			}
			else if (2 == find)
			{
				printf("\n�����������...");
				getch();
			}
			fclose(fp);
			break;

		//�鿴�༶
		//���Ľ��������ں���ѡ���Ƿ��޸�����һλͬѧ����Ϣ��̫���ˣ��������ˡ���������������
		case 3:
			printf("\n������ϵ�����롰-1��������һ������");
			scanf(" %s", &search.dept);
			if (strcmp("-1", search.dept) == 0)
			{
				continue;
			}
			printf("\n������רҵ�����롰-1��������һ������");
			scanf(" %s", &search.major);
			if (strcmp("-1", search.major) == 0)
			{
				continue;
			}
			printf("\n�����롰x�ࡱ�����롰-1��������һ������");
			scanf(" %s", &search.classs);
			if (strcmp("-1", search.classs) == 0)
			{
				continue;
			}
			system("cls");
			if ((fp = fopen("Access.bin", "rb")) == NULL)
			{
				printf("\n���ļ�ʧ�ܣ�");
				Sleep(1000);
				return;
			}
			fread(&stu, sizeof(struct student), 1, fp);//��
			while (!feof(fp))
			{
				if (TRUE != stu.delTag
					&& strcmp(stu.dept, search.dept) == 0
					&& strcmp(stu.major, search.major) == 0
					&& strcmp(stu.classs, search.classs) == 0)
				{
					printf("ѧ�ţ�%s\n", stu.num);//���ͬ��ѧ����Ϣ
					printf("������%s\n", stu.name);
					printf("�Ա�%s\n", stu.sex);
					printf("�������ڣ�%d/%d/%d\n",
						stu.birthday.year, stu.birthday.month, stu.birthday.day);
					printf("���䣺%d\n", stu.age);
					printf("���᣺%s\n", stu.addr);
					printf("ϵ��%s\n", stu.dept);
					printf("רҵ��%s\n", stu.major);
					printf("�༶��%s\n", stu.classs);
					printf("�绰��%s\n\n", stu.phone);
					n++;
				}
				fread(&stu, sizeof(struct student), 1, fp);//�Ӣ٣����ж��Ƿ�����ļ�β�����������Ļ
			}
			printf("��%s%s%s �ܹ��� %d ��ѧ����", search.dept, search.major, search.classs, n);
			fclose(fp);
			printf("\n\n�������������һ��......");
			getch();
			break;
		//������һ���˵�
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
			printf("\nchoose1��ֵ������");
			Sleep(1000);
			break;
		}
	} while (TRUE);
}

void Modify(student *pS, FILE *fp, long pf)//�����޸�ģ��
{
	student temp;//�����޸�ǰ����Ϣ
	char choose1, choose2;
	int switch_on;
	do {
		temp = stu;
		printf("\n����������Ҫ�޸���Ϣ����š�\n1.ѧ��\n2.����\n3.�Ա�\n4.��������\n5.����\n6.����\n7.ϵ��\n8.רҵ\n9.�༶\n10.�绰 \n0.����\n������[   ]\b\b\b");
		scanf("%d", &switch_on);
		getchar();
		switch (switch_on)
		{
		case 1://�޸�ѧ��
			printf("\nѧ�ţ�");
			scanf(" %s", &(pS->num));
			break;
		case 2://�޸�����
			printf("\n������");
			scanf(" %s", &(pS->name));
			break;
		case 3://�޸��Ա�
			printf("\n�Ա�");
			scanf(" %s", &(pS->sex));
			break;
		case 4://�޸ĳ�������
			printf("\n��������(xxxx/xx/xx)��");
			scanf("%d/%d/%d", &(pS->birthday.year), &(pS->birthday.month), &(pS->birthday.day));
			fflush(stdin);
			break;
		case 5://�޸�����
			printf("\n���䣺");
			scanf("%d", &(pS->age));
			break;
		case 6://�޸ļ���
			printf("\n���᣺");
			scanf(" %s", &(pS->addr));
			break;
		case 7://�޸�ϵ��
			printf("\nϵ��");
			scanf(" %s", &(pS->dept));
			break;
		case 8://�޸�רҵ
			printf("\nרҵ��");
			scanf(" %s", &(pS->major));
			break;
		case 9://�޸İ༶
			printf("\n�༶��");
			scanf(" %s", &(pS->classs));
			break;
		case 10://�޸ĵ绰
			printf("\n�绰��");
			scanf(" %s", &(pS->phone));
			break;
		case 0:
			return;
			break;
		default:
			break;
		}
		printf("\n�޸ĺ�\n");
		printf("ѧ�ţ�%s\n", stu.num);
		printf("������%s\n", stu.name);
		printf("�Ա�%s\n", stu.sex);
		printf("�������ڣ�%d/%d/%d\n",
			stu.birthday.year, stu.birthday.month, stu.birthday.day);
		printf("���䣺%d\n", stu.age);
		printf("���᣺%s\n", stu.addr);
		printf("ϵ��%s\n", stu.dept);
		printf("רҵ��%s\n", stu.major);
		printf("�༶��%s\n", stu.classs);
		printf("�绰��%s\n\n", stu.phone);
		//ȷ���޸ģ�
		printf("\nȷ���޸ģ���y/n��[ ]\b\b");
		scanf(" %c", &choose1);
		if ('y' == choose1 && stu.num[0] != '\0' && stu.name[0] != '\0')
		{
			do {
				fseek(fp, -1 * sizeof(struct student), SEEK_CUR);//�ƶ��ļ�λ��ָ�뵽Ҫ�޸ĵ�ѧ����Ϣ�׵�ַ
			} while (ftell(fp) != pf);
			if (fwrite(&stu, sizeof(struct student), 1, fp) != 1)//ֱ�Ӹ���д��
			{
				printf("�ļ�д�����");
			}
		}
		else
		{
			printf("\nû�н����޸�");
			stu = temp;
		}
		printf("\n�Ƿ���������޸ģ���y/n��[ ]\b\b");
		scanf(" %c", &choose2);
		if ('y' == choose2)
		{
			return;
		}
		fflush(stdin);
	} while (TRUE);
}

void Browse(FILE *fp)//���ģ��
{
	int n = 0;//ѧ������
	system("cls");
	if ((fp = fopen("Access.bin", "rb")) == NULL)
	{
		printf("\n���ļ�ʧ�ܣ�");
		Sleep(1000);
		return;
	}
	fread(&stu, sizeof(struct student), 1, fp);//��
	while (!feof(fp))
	{
		if (TRUE != stu.delTag)//���û�б�ɾ����ѧ����Ϣ
		{
			printf("ѧ�ţ�%s\n", stu.num);
			printf("������%s\n", stu.name);
			printf("�Ա�%s\n", stu.sex);
			printf("�������ڣ�%d/%d/%d\n",
				stu.birthday.year, stu.birthday.month, stu.birthday.day);
			printf("���䣺%d\n", stu.age);
			printf("���᣺%s\n", stu.addr);
			printf("ϵ��%s\n", stu.dept);
			printf("רҵ��%s\n", stu.major);
			printf("�༶��%s\n", stu.classs);
			printf("�绰��%s\n\n", stu.phone);
			n++;
		}
		fread(&stu, sizeof(struct student), 1, fp);//�Ӣ٣����ж��Ƿ�����ļ�β�����������Ļ
	}
	printf("�������ݿ����ܹ��� %d ��ѧ����", n);
	printf("\n\n����������ع���Ա�˵�......");
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

void Empty(FILE *fp)//���ģ��
{
	char choose;
	fflush(stdin);
	system("cls");
	printf("���ٴ�ȷ���Ƿ�Ҫ������ݿ⣡���루y/n����[ ]\b\b");
	choose = getchar();
	if ('y' == choose)
	{
		fp = fopen("Access.bin", "wb");
		if (fp == NULL)
		{
			printf("\n���ļ�ʧ�ܣ�");
			Sleep(1000);
			return;
		}
		fclose(fp);
		printf("\n������������ݿ⡿");
	}
	else
	{
		printf("\n����û��������ݿ⡿");
	}
	printf("\n���ع���Ա�˵�...");
	Sleep(1000);
	menuAdmin(fp);
}

void FirstUse(FILE *fp)//��һ��ʹ�ù���Ա��½
{
	fp = fopen("Access.bin", "wb");
	if (fp == NULL)
	{
		printf("\n���ļ�ʧ�ܣ�");
		Sleep(1000);
		return;
	}
	fclose(fp);
	Insert(fp);
}

void menuAdmin(FILE *fp)//����Ա�˵�
{
	int switch_on;
	system("cls");
	do {
		system("cls");
		fflush(stdin);
		gotoxy(4, 0);
		printf("\t\t**********************************************");
		printf("\n\t\t||              �������ǹ���Ա              ||");
		printf("\n\t\t||                                          ||");
		printf("\n\t\t||                 1.���                   ||");
		printf("\n\t\t||                 2.ɾ��                   ||");
		printf("\n\t\t||                 3.����                   ||");
		printf("\n\t\t||                 4.���                   ||");
		printf("\n\t\t||                 5.���                   ||");
		printf("\n\t\t||                                          ||");
		printf("\n\t\t||                 0.����                   ||");
		printf("\n\t\t||                                          ||");
		printf("\n\t\t**********************************************");
		printf("\n\t\t��Ҫ�޸�һ��ѧ����ĳһ����Ϣ����ѡ��[3].����");
		printf("\n\t\t>>���������ѡ����[ ]\b\b");
		scanf("%d", &switch_on);
		getchar();
		if (switch_on < 0 || switch_on > 5)
		{
			printf("\n����������������룡");
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
	case 1://���ģ��
		printf("\n\n\t\t��ѡ����[���]");
		fflush(stdin);
		Sleep(500);
		Insert(fp);
		break;
	case 2://ɾ��ģ��
		printf("\n\n\t\t��ѡ����[ɾ��]");
		fflush(stdin);
		Sleep(500);
		Delete(fp);
		break;
	case 3://����ģ��
		printf("\n\n\t\t��ѡ����[����]");
		fflush(stdin);
		Sleep(500);
		Search(fp);
		break;
	case 4://���ģ��
		printf("\n\n\t\t��ѡ����[���]");
		fflush(stdin);
		Sleep(500);
		Browse(fp);
		break;
	case 5://���ģ��
		printf("\n\n\t\t��ѡ����[���]");
		fflush(stdin);
		Sleep(500);
		Empty(fp);
		break;
	case 0://����
		fflush(stdin);
		Sleep(500);
		main();
		break;
	default:
		break;
	}
	system("cls");
}

void menuVisit(FILE *fp)//�ÿͲ˵�
{
	int switch_on;
	do {
		system("cls");
		fflush(stdin);
		gotoxy(4, 0);
		printf("\t\t**********************************************");
		printf("\n\t\t||               �������Ƿÿ�               ||");
		printf("\n\t\t||                                          ||");
		printf("\n\t\t||                 1.����                   ||");
		printf("\n\t\t||                 2.���                   ||");
		printf("\n\t\t||                                          ||");
		printf("\n\t\t||                 0.����                   ||");
		printf("\n\t\t||                                          ||");
		printf("\n\t\t**********************************************");
		printf("\n\t\t>>���������ѡ����[ ]\b\b");
		scanf("%d", &switch_on);
		if (switch_on < 0 || switch_on > 2)
		{
			printf("\n����������������룡");
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
	case 1://����ģ��
		printf("\n\n\t\t��ѡ����[����]");
		fflush(stdin);
		Sleep(500);
		Search(fp);
		break;
	case 2://���ģ��
		printf("\n\n\t\t��ѡ����[���]");
		fflush(stdin);
		Sleep(500);
		Browse(fp);
		break;

	case 0://����
		fflush(stdin);
		Sleep(500);
		main();
		break;
	default:
		break;
	}
	system("cls");
}
