#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define FILE_PATH "c:/Users/��/Desktop/sample.txt"
#define OUTPUT_PATH "c:/Users/��/Desktop/output.txt"

//ѧ���ṹ��
typedef struct
{
	int id;
	int grade;
	char name[20];
	char answer[36];

}STUDENT;

//���ѧ����ary_studnet����
STUDENT *ary_student;

//number of students
int num = 0;

//�ļ���ȡ�ʹ�ֶ�ִֻ��һ��
int single = 0;
int gradeSingle = 0;

//��Ŵ�����Ľṹ��
typedef struct
{
	char answer[36];
}ANSWERS;

ANSWERS answers;


//���ļ�����
void readFile()
{
	int count = 0;
	char temp;

	FILE *fptr1;

	//�ļ���ַ����ͬ�������޸ĸõ�ַ
	if ((fptr1 = fopen(FILE_PATH, "r")) == NULL)
	{
		printf("\nConnot open file!\n");
		getchar();
		exit(1);
	}

	//count
	while (!feof(fptr1))
	{

		temp = fgetc(fptr1);

		if (temp == '\n')
		{
			num++;
			if (fgetc(fptr1) == '\n')
			{
				break;
			}

		}
	}

	ary_student = (STUDENT*)malloc(sizeof(STUDENT)* num);

	fseek(fptr1, 0, SEEK_SET);

	while (!feof(fptr1))
	{
		fscanf(fptr1, "%d%s%s", &ary_student[count].id, &ary_student[count].name, &ary_student[count].answer);
		count++;
	}

	fclose(fptr1);
}

//ͳ����౻ѡ�𰸺���
char mostChosen(int n/*���*/)
{
	int i, j;


	//ABCD���ֵĴ���
	int numA = 0;
	int numB = 0;
	int numC = 0;
	int numD = 0;

	int max = 0;

	char result;
	char *answers;

	answers = (char*)malloc(num*sizeof(char));

	//����n��Ĵ�ͳ�Ʒ���answers����
	for (i = 0; i < num; i++)
	{
		answers[i] = ary_student[i].answer[n];
	}

	for (j = 0; j < 35; j++)
	{
		if (answers[j] == 'A')	numA++;
		if (answers[j] == 'B')	numB++;
		if (answers[j] == 'C')	numC++;
		if (answers[j] == 'D')	numD++;
	}

	result = 'A';
	max = numA;

	if (numB > max)
	{
		result = 'B';
	}
	if (numC > max)
	{
		result = 'C';
	}
	if (numD > max)
	{
		result = 'D';
	}

	return result;
}

//�鿴�𰸺���
void viewAnswer()
{
	int i, j;

	//ÿ����Ƶ��
	int result[36];

	for (i = 0; i < 35; i++)
	{
		result[i] = 0;
	}


	for (i = 0; i < 35; i++)
	{
		answers.answer[i] = mostChosen(i);
	}

	system("CLS");

	printf("\n\n���ݴ������ͳ�Ƴ��Ĳο���:	\n");
	printf("\n");
	for (i = 0; i < 35; i++)
	{
		printf("%c", answers.answer[i]);
	}
	printf("\n\n");
	//����ÿ���˵�ÿ������
	for (i = 0; i < num; i++)
	{
		for (j = 0; j < 35; j++)
		{
			if (ary_student[i].answer[j] == answers.answer[j])
			{
				result[j]++;
			}
		}
	}
	printf("\n\n�ο��𰸱�ѡƵ��:\n\n");
	for (j = 0; j < 35; j++)
	{
		printf("��%d��: %d��\n", j + 1, result[j]);
	}

	system("pause");
	return main();
}

//�ľ�
void grading()
{
	int count = 0;
	int i, j;


	//�ҳ��ο���
	for (i = 0; i < 35; i++)
	{
		answers.answer[i] = mostChosen(i);
	}


	//����ÿ���˵�ÿ������
	for (i = 0; i < num; i++)
	{
		for (j = 0; j < 35; j++)
		{
			if (ary_student[i].answer[j] == answers.answer[j])
			{
				if (j >= 0 && j <= 15) {
					count += 2;
				}
				if (16 <= j && j <= 25) {
					count += 3;
				}
				if (26 <= j && j <= 35) {
					count += 4;
				}

			}
		}
		printf("%d", count);
		ary_student[i].grade = count;
		count = 0;
	}
}

//��ѯ�ɼ�����
void searchByName()
{
	int i, j;

	//grading();

	char name[20];
	int id = 9995;

	system("CLS");

	printf("\n\n������Ҫ��ѯ��ѧ������	\n");
	printf("����: ");

	scanf("%s", name);

	for (i = 0; i < num; i++)
	{
		//�Ƚ�����������ĳ�������Ƿ���ͬ
		if (strcmp(ary_student[i].name, name) == 0)
		{
			id = i;
		}
	}

	if (id == 9995)
	{
		printf("\n���޴���\n");
	}
	else
	{
		printf("\n\n����: %d\n\n", ary_student[id].grade);
	}
	system("pause");
	return main();
}

//����ð������
void decBubbleSort(STUDENT *arr, int len)
{
	int i, j;
	STUDENT temp;
	for (i = 0; i < len - 1; i++)
	{
		for (j = 0; j < len - 1 - i; j++)
			if (arr[j].grade < arr[j + 1].grade)
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
	}
}

//����ð������
void incBubbleSort(STUDENT *arr, int len)
{
	int i, j;
	STUDENT temp;
	for (i = 0; i < len - 1; i++)
	{
		for (j = 0; j < len - 1 - i; j++)
			if (arr[j].grade > arr[j + 1].grade)
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
	}
}

//��������
void decSorting()
{
	int i, j;

	system("CLS");

	printf("\n��������������\n");

	decBubbleSort(ary_student, num);

	printf("\n\n����\t\t�ɼ�\n");

	for (i = 0; i < num; i++)
	{
		printf("%s\t\t%d\n", ary_student[i].name, ary_student[i].grade);
	}

	printf("\n\n��������������˵�\n\n");
	system("pause");
	return main();
}

//��������
void incSorting()
{
	int i, j;

	system("CLS");

	printf("\n��������������\n");

	incBubbleSort(ary_student, num);

	printf("\n\n����\t\t�ɼ�\n");

	for (i = 0; i < num; i++)
	{
		printf("%s\t\t%d\n", ary_student[i].name, ary_student[i].grade);
	}

	printf("\n\n��������������˵�\n\n");
	system("pause");
	return main();

}

//������
void sortByGrades()
{
	int n;

	system("CLS");

	printf("\n\n����������ʽ	\n");
	printf("\n1.�������� ");
	printf("\n2.�������� ");
	printf("\n0.�˳� \n");

	printf("\n����: ");
	scanf("%d", &n);

	switch (n)
	{
	case 1:	decSorting(); break;
	case 2:	incSorting(); break;
	case 0:	return main();
	}
}

//�����Ծ�����ĺ���
void outputAnalysis()
{
	int i, j;

	//������������ͳ��0-60,60-70,70-100�����������������ֱ�Ϊfail, pass��good
	int pass = 0;
	int fail = 0;
	int good = 0;

	//��߷ֺ���ͷ�ͳ��
	int max = 0;
	int min = 100;

	//ƽ����
	int sum = 0;
	int ave = 0;

	//������
	float passRate = 0;

	for (i = 0; i < num; i++)
	{
		//������
		if (ary_student[i].grade < 60)
		{
			fail++;
		}
		if (ary_student[i].grade >= 60 && ary_student[i].grade < 70)
		{
			pass++;
		}
		if (ary_student[i].grade > 70)
		{
			good++;
		}

		//��߷�
		if (ary_student[i].grade > max)
		{
			max = ary_student[i].grade;
		}

		//��ͷ�
		if (ary_student[i].grade < min)
		{
			min = ary_student[i].grade;
		}

		sum += ary_student[i].grade;
	}

	//ƽ����
	ave = sum / num;

	//������
	passRate = ((float)pass + (float)good) / (float)num * 100;

	system("CLS");

	printf("\n�ɼ���\n");

	decBubbleSort(ary_student, num);

	printf("\n\n����\t\t�ɼ�\n");

	for (i = 0; i < num; i++)
	{
		printf("%s\t\t%d\n", ary_student[i].name, ary_student[i].grade);
	}

	printf("\n\n���ο�������ͳ��\n\n");
	printf("\n60������%d��\n60�ֵ�70��%d��\n70������%d��\n\n", fail, pass, good);
	printf("ƽ����: %d\n\n", ave);
	printf("��߷�:%d\n��ͷ�%d\n\n", max, min);
	printf("������:%.2f", passRate);
	printf("%%\n\n");

	//������ⲿ�ļ�

	FILE *fptr2;

	//�ļ������ַ����ͬ�������޸ĸõ�ַ
	if ((fptr2 = fopen(OUTPUT_PATH, "w")) == NULL)
	{
		printf("\nConnot open file!\n");
		getchar();
		exit(1);
	}

	fseek(fptr2, 0, SEEK_SET);

	//�ɼ������

	fprintf(fptr2, "\n�ɼ���\n");
	fprintf(fptr2, "\n\n����\t\t�ɼ�\n");

	for (i = 0; i < num; i++)
	{
		fprintf(fptr2, "%s\t\t%d\n", ary_student[i].name, ary_student[i].grade);
	}

	//����ͳ�����
	fprintf(fptr2, "\n\n���ο�������ͳ��\n\n");
	fprintf(fptr2, "\n60������%d��\n60�ֵ�70��%d��\n70������%d��\n\n", fail, pass, good);
	fprintf(fptr2, "ƽ����: %d\n\n", ave);
	fprintf(fptr2, "��߷�:%d\n��ͷ�%d\n\n", max, min);
	fprintf(fptr2, "������:%.2f", passRate);
	fprintf(fptr2, "%%\n\n");

	fclose(fptr2);

	printf("\n����������д���ⲿ�ļ�.\n");

	printf("\n\n��������������˵�\n\n");
	system("pause");
	return main();

}

//���˵�����
void menuUI()
{
	int input;

	if (gradeSingle == 0)
	{
		grading();
		gradeSingle = 1;
	}


	system("CLS");

	printf("\nģ��ľ�ϵͳ");
	printf("\n");
	printf("\n���������");
	printf("\n1.�鿴��");
	printf("\n2.��������ѯ�ɼ�");
	printf("\n3.���ɼ�����");
	printf("\n4.����ɼ������Ծ����");
	printf("\n0.�˳�����");
	printf("\n\n");

	printf("����������ѡ��: ");
	scanf("%d", &input);

	switch (input)
	{
	case 1:	viewAnswer(); break;
	case 2:	searchByName(); break;
	case 3:	sortByGrades(); break;
	case 4: outputAnalysis(); break;
	case 0: exit(1);
	}

}

//������
int main(void)
{
	if (single == 0)
	{
		readFile();
		single = 1;
	}

	menuUI();

	return 0;
}

