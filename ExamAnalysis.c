#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define FILE_PATH "c:/Users/阳/Desktop/sample.txt"
#define OUTPUT_PATH "c:/Users/阳/Desktop/output.txt"

//学生结构体
typedef struct
{
	int id;
	int grade;
	char name[20];
	char answer[36];

}STUDENT;

//存放学生的ary_studnet数组
STUDENT *ary_student;

//number of students
int num = 0;

//文件读取和打分都只执行一次
int single = 0;
int gradeSingle = 0;

//存放答案数组的结构体
typedef struct
{
	char answer[36];
}ANSWERS;

ANSWERS answers;


//读文件函数
void readFile()
{
	int count = 0;
	char temp;

	FILE *fptr1;

	//文件地址，不同环境请修改该地址
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

//统计最多被选答案函数
char mostChosen(int n/*题号*/)
{
	int i, j;


	//ABCD出现的次数
	int numA = 0;
	int numB = 0;
	int numC = 0;
	int numD = 0;

	int max = 0;

	char result;
	char *answers;

	answers = (char*)malloc(num*sizeof(char));

	//将第n题的答案统计放入answers数组
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

//查看答案函数
void viewAnswer()
{
	int i, j;

	//每个答案频次
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

	printf("\n\n根据答题情况统计出的参考答案:	\n");
	printf("\n");
	for (i = 0; i < 35; i++)
	{
		printf("%c", answers.answer[i]);
	}
	printf("\n\n");
	//遍历每个人的每道题打分
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
	printf("\n\n参考答案备选频次:\n\n");
	for (j = 0; j < 35; j++)
	{
		printf("第%d题: %d次\n", j + 1, result[j]);
	}

	system("pause");
	return main();
}

//改卷
void grading()
{
	int count = 0;
	int i, j;


	//找出参考答案
	for (i = 0; i < 35; i++)
	{
		answers.answer[i] = mostChosen(i);
	}


	//遍历每个人的每道题打分
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

//查询成绩函数
void searchByName()
{
	int i, j;

	//grading();

	char name[20];
	int id = 9995;

	system("CLS");

	printf("\n\n请输入要查询的学生姓名	\n");
	printf("姓名: ");

	scanf("%s", name);

	for (i = 0; i < num; i++)
	{
		//比较输入姓名和某个姓名是否相同
		if (strcmp(ary_student[i].name, name) == 0)
		{
			id = i;
		}
	}

	if (id == 9995)
	{
		printf("\n查无此人\n");
	}
	else
	{
		printf("\n\n分数: %d\n\n", ary_student[id].grade);
	}
	system("pause");
	return main();
}

//降序冒泡排序
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

//升序冒泡排序
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

//降序排序
void decSorting()
{
	int i, j;

	system("CLS");

	printf("\n按分数降序排序\n");

	decBubbleSort(ary_student, num);

	printf("\n\n姓名\t\t成绩\n");

	for (i = 0; i < num; i++)
	{
		printf("%s\t\t%d\n", ary_student[i].name, ary_student[i].grade);
	}

	printf("\n\n按任意键返回主菜单\n\n");
	system("pause");
	return main();
}

//升序排序
void incSorting()
{
	int i, j;

	system("CLS");

	printf("\n按分数升序排序\n");

	incBubbleSort(ary_student, num);

	printf("\n\n姓名\t\t成绩\n");

	for (i = 0; i < num; i++)
	{
		printf("%s\t\t%d\n", ary_student[i].name, ary_student[i].grade);
	}

	printf("\n\n按任意键返回主菜单\n\n");
	system("pause");
	return main();

}

//排序函数
void sortByGrades()
{
	int n;

	system("CLS");

	printf("\n\n请输入排序方式	\n");
	printf("\n1.降序排序 ");
	printf("\n2.升序排序 ");
	printf("\n0.退出 \n");

	printf("\n输入: ");
	scanf("%d", &n);

	switch (n)
	{
	case 1:	decSorting(); break;
	case 2:	incSorting(); break;
	case 0:	return main();
	}
}

//分析试卷并输出的函数
void outputAnalysis()
{
	int i, j;

	//分数段人数，统计0-60,60-70,70-100三个分数段人数，分别为fail, pass和good
	int pass = 0;
	int fail = 0;
	int good = 0;

	//最高分和最低分统计
	int max = 0;
	int min = 100;

	//平均分
	int sum = 0;
	int ave = 0;

	//及格率
	float passRate = 0;

	for (i = 0; i < num; i++)
	{
		//分数段
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

		//最高分
		if (ary_student[i].grade > max)
		{
			max = ary_student[i].grade;
		}

		//最低分
		if (ary_student[i].grade < min)
		{
			min = ary_student[i].grade;
		}

		sum += ary_student[i].grade;
	}

	//平均分
	ave = sum / num;

	//及格率
	passRate = ((float)pass + (float)good) / (float)num * 100;

	system("CLS");

	printf("\n成绩单\n");

	decBubbleSort(ary_student, num);

	printf("\n\n姓名\t\t成绩\n");

	for (i = 0; i < num; i++)
	{
		printf("%s\t\t%d\n", ary_student[i].name, ary_student[i].grade);
	}

	printf("\n\n本次考试数据统计\n\n");
	printf("\n60分以下%d人\n60分到70分%d人\n70分以上%d人\n\n", fail, pass, good);
	printf("平均分: %d\n\n", ave);
	printf("最高分:%d\n最低分%d\n\n", max, min);
	printf("及格率:%.2f", passRate);
	printf("%%\n\n");

	//输出到外部文件

	FILE *fptr2;

	//文件输出地址，不同环境请修改该地址
	if ((fptr2 = fopen(OUTPUT_PATH, "w")) == NULL)
	{
		printf("\nConnot open file!\n");
		getchar();
		exit(1);
	}

	fseek(fptr2, 0, SEEK_SET);

	//成绩单输出

	fprintf(fptr2, "\n成绩单\n");
	fprintf(fptr2, "\n\n姓名\t\t成绩\n");

	for (i = 0; i < num; i++)
	{
		fprintf(fptr2, "%s\t\t%d\n", ary_student[i].name, ary_student[i].grade);
	}

	//数据统计输出
	fprintf(fptr2, "\n\n本次考试数据统计\n\n");
	fprintf(fptr2, "\n60分以下%d人\n60分到70分%d人\n70分以上%d人\n\n", fail, pass, good);
	fprintf(fptr2, "平均分: %d\n\n", ave);
	fprintf(fptr2, "最高分:%d\n最低分%d\n\n", max, min);
	fprintf(fptr2, "及格率:%.2f", passRate);
	fprintf(fptr2, "%%\n\n");

	fclose(fptr2);

	printf("\n以上数据已写入外部文件.\n");

	printf("\n\n按任意键返回主菜单\n\n");
	system("pause");
	return main();

}

//主菜单函数
void menuUI()
{
	int input;

	if (gradeSingle == 0)
	{
		grading();
		gradeSingle = 1;
	}


	system("CLS");

	printf("\n模拟改卷系统");
	printf("\n");
	printf("\n请输入操作");
	printf("\n1.查看答案");
	printf("\n2.按姓名查询成绩");
	printf("\n3.按成绩排序");
	printf("\n4.输出成绩单及试卷分析");
	printf("\n0.退出程序");
	printf("\n\n");

	printf("输入数字以选择: ");
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

//主函数
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

