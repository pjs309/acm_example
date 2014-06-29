#include "stdafx.h"

#include <vector>
#include <string>
#include <map>

#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <windows.h>

using namespace std;
#define _CRT_SECURE_NO_WARNINGS

string GetTimeStamp()
{
	SYSTEMTIME tm;;
	GetLocalTime(&tm);
	char tmp[100] = { 0 };

	sprintf(tmp, "%04d-%02d-%02d %02d:%02d:%02d.%03d",
		tm.wYear,
		tm.wMonth,
		tm.wDay,
		tm.wHour,
		tm.wMinute,
		tm.wSecond,
		tm.wMilliseconds);
	return tmp;
}

//ѧϰacm�������ҵ�ʵ�� 2014-06-27  ============·��������Զ�� �Ὣ���¶�����===========  


/********************************************************************************************
���ʴ�ѧ��������ƾ��������̳� �� ҳ 89
������ ���ʴ�ѧ��������ƾ�����ACM/ICPC�����⼰����
��һ�� �����ַ���
����ȡ����NWERC������ŷ��89C�⡣ ��������: �����ַ���ֻ���ַ���0������1������*����ɣ������ַ���*����ʾ���ַ������ַ���0����1������� 
����һЩ�ַ�����������Щ�ַ����������п����ɵ��ַ����� 
�磺 {10��*1��0* }������{10��01��11��00 } {101��001��*01}������{ 101��001} ע���һ�������С�*01����û�������µ��ַ����� 
�����ʽ: �ӵ�ǰĿ¼�µ��ı��ļ���STRINGS.DAT���������ݡ�
���ļ��ĵ�һ������������m,n����1��m��15,1��n��2500��m��ʾ�ַ����ĳ��ȣ�n��ʾ�ַ����ĸ�����
��������֮����һ���ո����������n��ÿ�и���һ���ַ������ļ��и��е����ס���ĩû�ж���Ŀո� 
�����ʽ: ���������ǰĿ¼�µ��ı��ļ���STRINGS.OUT���У����ļ�ֻ��һ������total����ʾ�������ɵ��ַ����ĸ�����

�����������: �����ļ���STRINGS.DAT
2 3
10
*1
0*

����ļ���STRINGS.OUT

4

�������ݣ� strings1.dat 
3 5 
00* *00 1** 0*0 111

strings2.dat 5 15 
11*10 1100* 01*01 1001* *1110 00100 000*0 11**0 01*** *0111 ***0* 0*0*1 1**00 **10* 10*01

�����:
���            �����ļ���          �ο����          ��ʱ���룩
1             STRINGS1.DAT             7                  5��
2             STRINGS2.DAT            28                 5��


********************************************************************************************/

//����ԭʼ���������п��ܵĴ�
void getAllStrBySingle(vector<string>& newStrInfo,  char *orginStr)
{
	vector<string> strInfo;
	vector<string> tmpStrInfo;
//	strInfo.reserve(1000);
//	tmpStrInfo.reserve(1000);
	
	int orginStrlen = strlen(orginStr);

	for (int i = 0; i < orginStrlen; i++)
	{
		char curChar = orginStr[i];
		int count = strInfo.size();
		tmpStrInfo = strInfo;
		strInfo.clear();
		if (count > 0)
		{
			for (int j = 0; j < count; j++)
			{
				string str = tmpStrInfo[j];
				if (curChar == '*')
				{
					char tempBuf[100];
					sprintf(tempBuf, "%s0", str.c_str());
					strInfo.push_back(tempBuf);
					str += "1";
					strInfo.push_back(str);
				}
				else
				{
					str += curChar;
					strInfo.push_back(str);
				}
			}
		}
		else
		{
			string str;
			if (curChar == '*')
			{
				strInfo.push_back("0");
				str += "1";
				strInfo.push_back("1");
			}
			else
			{
				str += curChar;
				strInfo.push_back(str);
			}
		}
	}

	newStrInfo = strInfo;
}

void addNewStr(map<string, string>& strInfoMap, vector<string> newStrInfo)
{
	int count = newStrInfo.size();

	for (int i = 0; i < count; i++)
	{
		map<string, string>::iterator iter = strInfoMap.find(newStrInfo[i]);
		if (iter == strInfoMap.end())
		{
			strInfoMap[newStrInfo[i]] = newStrInfo[i];
		}
	}
}

void test89c()
{
	char *test_1[] = { "10", "*1", "0*" };
	char *test_2[] = { "00*", "*00", "1**",  "0*0", "111" };
	char *test_3[] = { "11*10", "1100*", "01*01", "1001*", "*1110", "00100", "000*0",
		"11**0", "01***", "*0111", "***0*", "0*0*1", "1**00", "**10*", "10*01" };

	map<string, string> strInfo;
	vector<char**> testInfo;
	vector<int> arrangeInfo;
	vector<int> rightInfo;
	string beginTimeStr;
	string endTimeStr;

	testInfo.push_back(test_1);
	testInfo.push_back(test_2);
	testInfo.push_back(test_3);

	arrangeInfo.push_back(3);
	arrangeInfo.push_back(5);
	arrangeInfo.push_back(15);

	rightInfo.push_back(4);
	rightInfo.push_back(7);
	rightInfo.push_back(28);


	int count = testInfo.size();

	printf("\r\n************%s********************************\r\n", __FUNCTION__);
	for (int i = 0; i < count; i++)
	{
		beginTimeStr = GetTimeStamp();
		char **test = testInfo[i];
		int arrangeLen = arrangeInfo[i];
		strInfo.clear();

		for (int j = 0; j < arrangeLen; j++)
		{
			char *str = test[j];
			vector<string> newStrInfo;
			::getAllStrBySingle(newStrInfo, str);
			::addNewStr(strInfo, newStrInfo);
		}

		endTimeStr = GetTimeStamp();
		printf("\r\n=============================���������ʼ====================================\r\n");
		printf("�������:\r\n\r\n");
		for (int j = 0; j < arrangeLen; j++)
		{
			printf("%s \t", test[j]);
		}

		printf("\r\n\r\n���:\r\n");
		if (strInfo.size() == rightInfo[i])
		{
			printf("\r\n���ɴ�����: %d  is right success!\r\n", strInfo.size());
		}
		else
		{
			printf("\r\n���ɴ�����: %d  is wrong fail!\r\n", strInfo.size());
		}

		printf("beginTimeStr = %s\r\n", beginTimeStr.c_str());
		printf("endTimeStr = %s\r\n", endTimeStr.c_str());

		printf("==================================�����������=======================\r\n");
	}

}


/*******************************************************************************************************************
����ȡ����ICPC����������96E�⡣ ���������� ģʽʶ���һ���ؼ��������б�ͼ�εġ����ġ�����ͼ�ξ���ɨ����ɨ��󣬵õ�һ��ʵ������
��������Ҫ�ҵ���ͼ�εġ����ġ���Ȼ����ܿ�ʼʶ��
��ʵ��������m��n����ɣ�n<=100��m<=100����
��ν�����ģ�i��j����ʹ��i���ϱ�Ԫ�أ���������i�У����ܺ����i���±�Ԫ�أ���������i�У����ܺ�֮��ľ���ֵ��С��
���ҵ�j�����Ԫ�أ���������j�У����ܺ����j���ұ�Ԫ�أ���������j�У����ܺ�֮��ľ���ֵ��С�� ����֪һɨ�����õ�ʵ���������䡰���ġ���
���ж�������ġ�����������һ�������ġ����ɡ�
�����ʽ�� �Ӽ�������һ���ı��ļ����ļ��������ļ���һ����������m��n������m����ʵ������ÿ�и���n��ʵ����
��ÿһ���У�����֮��ֻ��һ���ո�ÿ�е����ס���ĩ�޶���ո�
�����ʽ�� ����������Ļ�ϣ� Center=(xxx,yyy) xxx,yyy�ֱ��ʾ���ĵ��к���.

������������� SAMPLE1.DAT ����Ļ�����

5 5
0.2 0.3 0.2 0.3 0.2
0.2 0.3 0.4 0.2 0.2
0.3 0.4 0.2 0.2 0.4
0.5 0.2 0.2 0.2 0.3
0.3 0.3 0.4 0.4 0.2

Center=(3,3)

�������ݣ� T101.dat 
5 5 
0.34 0.80 0.61 0.42 0.55 
0.80 0.41 0.56 0.95 0.55 
0.26 0.49 0.06 0.93 0.58 
0.19 0.08 0.31 0.84 0.79 
0.12 0.43 0.33 0.50 0.86 

T102.dat 
10 20 

0.24 0.42 0.79 0.90 0.54 0.33 0.48 0.35 0.54 0.60 
0.75 0.30 0.09 0.60 0.33 0.25 0.75 0.52 0.15 0.73
0.40 0.26 0.71 0.50 0.62 0.83 0.84 0.32 0.13 0.58 
0.21 0.80 0.20 0.55 0.49 0.44 0.68 0.54 0.21 0.04 
0.02 0.82 0.57 0.97 0.59 0.47 0.81 0.07 0.05 0.85 
0.80 0.12 0.63 0.69 0.12 0.10 0.49 0.78 0.73 0.82 
0.72 0.22 0.84 0.55 0.36 0.74 0.82 0.68 0.74 0.57 
0.15 0.63 0.94 0.85 0.70 0.51 0.08 0.55 0.93 0.28 
0.00 0.40 0.78 0.36 0.99 0.25 0.27 0.87 0.65 0.01 
0.19 0.20 0.81 0.92 0.31 0.31 0.63 0.86 0.02 0.09 
0.07 0.04 0.38 0.78 0.48 0.05 0.88 0.08 0.78 0.42 
0.48 0.08 0.33 0.92 0.74 1.00 0.10 0.34 0.01 0.45 
0.03 0.51 0.13 0.35 0.76 0.76 0.02 0.06 0.34 0.06 
0.63 0.79 0.82 0.62 0.03 0.55 0.81 0.58 0.67 0.60 
0.64 0.16 0.78 0.56 0.50 0.43 0.32 0.22 0.76 0.35 
0.27 0.01 0.49 0.06 0.27 0.31 0.60 0.34 0.55 0.29 
0.32 0.73 0.52 0.52 0.95 0.96 0.30 0.39 0.03 0.33 
0.46 0.73 0.31 0.39 0.77 0.70 0.25 0.21 0.73 0.85 
0.99 0.73 0.05 0.37 0.89 0.20 0.18 0.25 0.09 0.70 
0.67 0.39 0.81 0.55 0.90 0.70 0.23 0.76 0.50 0.14


�ο����:
���   �����ļ���    ����
1	   T101.DAT     Center=(3,4)
2      T102.DAT     Center=(5,11)

*******************************************************************************************************************/
struct acm_centerStruc
{
	int x;
	int y;

	acm_centerStruc()
	{
		x = 0;
		y = 0;
	}
};

float acm_calcSingleRowSum(float *dataInfo, int count)
{
	float sum = 0; 

	for (int i = 0; i < count; i++)
	{
		sum += dataInfo[i];
	}

	return sum;
}

float acm_calcSingleColSum(float **matrixInfo, int row, int col, int cl)
{
	float sum = 0;

	for (int i = 0; i < row; i++)
	{
		sum += ((float*)(matrixInfo + i * cl))[col];
	}

	return sum;
}

void acm_calMatrixSigleRowOrColSum(float **matrixInfo, int row, int col, float *rowSum, float *colSum)
{
	for (int i = 0; i < row; i++)
	{
		rowSum[i] = acm_calcSingleRowSum((float*)(matrixInfo + i), col);
	}

	for (int i = 0; i < col; i++)
	{
		colSum[i] = acm_calcSingleColSum(matrixInfo, row, i, col);
	}
}

float acm_CalcCompareValue(float *dataInfo, int count, float sum)
{
	float subtract = sum;
	float curSum = 0;
	for (int i = 0; i < count; i++)
	{
		curSum += dataInfo[i];
	}

	return abs(sum - 2 * curSum);
}

void acm_calcCentXOrY(float *dataInfo, int rowOrColCount, vector<int>& centerInfo)
{
	float sum = 0;
	for (int i = 0; i < rowOrColCount; i++)
	{
		sum += dataInfo[i];
	}

	float curCentSum = sum;

	for (int i = 0; i < rowOrColCount; i++)
	{
		float tmpSum = acm_CalcCompareValue(dataInfo, i + 1, sum - dataInfo[i]);
		if (curCentSum < tmpSum)
		{
			continue;
		}

		if (curCentSum > tmpSum)
		{
			centerInfo.clear();
		}

		centerInfo.push_back(i);
	}
}



void acm_calcCetner(float **matrixInfo, int row, int col, vector<acm_centerStruc>& centerInfo)
{
	float *rowSum = (float*)malloc(sizeof(float) * col);
	float *colSum = (float*)malloc(sizeof(float) * row);

	vector<int>  rowCenterInfo;
	vector<int>	 colCenterInfo;

	acm_calMatrixSigleRowOrColSum(matrixInfo, row, col, rowSum, colSum);

	acm_calcCentXOrY(rowSum, row, rowCenterInfo);
	acm_calcCentXOrY(colSum, col, colCenterInfo);

	int rowCenterCount = rowCenterInfo.size();
	int colCenterCount = colCenterInfo.size();

	for (int i = 0; i < rowCenterCount; i++)
	{
		acm_centerStruc center;
		center.x = rowCenterInfo[i];
		for (int j = 0; j < colCenterCount; j++)
		{
			center.y = colCenterInfo[j];
			centerInfo.push_back(center);
		}
	}
}

void test_icpc_961()
{
	float  test_1[5][5] = {
		0.2, 0.3, 0.2, 0.3, 0.2,
		0.2, 0.3, 0.4, 0.2, 0.2,
		0.3, 0.4, 0.2, 0.2, 0.4,
		0.5, 0.2, 0.2, 0.2, 0.3,
		0.3, 0.3, 0.4 ,0.4, 0.2, };

	float test_2[5][5] = {
		0.34, 0.80, 0.61, 0.42, 0.55,
		0.80, 0.41, 0.56, 0.95, 0.55,
		0.26, 0.49, 0.06, 0.93, 0.58,
		0.19, 0.08, 0.31, 0.84, 0.79,
		0.12, 0.43, 0.33, 0.50, 0.86, };

	float test_3[10][20] = {
		0.24, 0.42, 0.79, 0.90, 0.54, 0.33, 0.48, 0.35, 0.54, 0.60,
		0.75, 0.30, 0.09, 0.60, 0.33, 0.25, 0.75, 0.52, 0.15, 0.73,
		0.40, 0.26, 0.71, 0.50, 0.62, 0.83, 0.84, 0.32, 0.13, 0.58,
		0.21, 0.80, 0.20, 0.55, 0.49, 0.44, 0.68, 0.54, 0.21, 0.04,
		0.02, 0.82, 0.57, 0.97, 0.59, 0.47, 0.81, 0.07, 0.05, 0.85,
		0.80, 0.12, 0.63, 0.69, 0.12, 0.10, 0.49, 0.78, 0.73, 0.82,
		0.72, 0.22, 0.84, 0.55, 0.36, 0.74, 0.82, 0.68, 0.74, 0.57,
		0.15, 0.63, 0.94, 0.85, 0.70, 0.51, 0.08, 0.55, 0.93, 0.28,
		0.00, 0.40, 0.78, 0.36, 0.99, 0.25, 0.27, 0.87, 0.65, 0.01,
		0.19, 0.20, 0.81, 0.92, 0.31, 0.31, 0.63, 0.86, 0.02, 0.09,
		0.07, 0.04, 0.38, 0.78, 0.48, 0.05, 0.88, 0.08, 0.78, 0.42,
		0.48, 0.08, 0.33, 0.92, 0.74, 1.00, 0.10, 0.34, 0.01, 0.45,
		0.03, 0.51, 0.13, 0.35, 0.76, 0.76, 0.02, 0.06 ,0.34, 0.06,
		0.63, 0.79, 0.82, 0.62, 0.03, 0.55, 0.81, 0.58, 0.67, 0.60,
		0.64, 0.16, 0.78, 0.56, 0.50, 0.43, 0.32, 0.22, 0.76, 0.35,
		0.27, 0.01, 0.49, 0.06, 0.27, 0.31, 0.60, 0.34, 0.55, 0.29,
		0.32, 0.73, 0.52, 0.52, 0.95, 0.96, 0.30, 0.39, 0.03, 0.33,
		0.46, 0.73, 0.31, 0.39, 0.77, 0.70, 0.25, 0.21, 0.73, 0.85,
		0.99, 0.73, 0.05, 0.37, 0.89, 0.20, 0.18, 0.25, 0.09, 0.70,
		0.67, 0.39, 0.81, 0.55, 0.90, 0.70, 0.23, 0.76, 0.50, 0.14,
	};


	vector<float**> testInfo;
	vector<int>     test_rowInfo;
	vector<int>		test_colInfo;
	vector<acm_centerStruc>  centerInfo;
	vector<acm_centerStruc>  rightInfo;
	acm_centerStruc rightercenter;
	string beginTimeStr;
	string endTimeStr;

	testInfo.push_back((float**)test_1);
	testInfo.push_back((float**)test_2);
	testInfo.push_back((float**)test_3);

	test_rowInfo.push_back(5);
	test_rowInfo.push_back(5);
	test_rowInfo.push_back(10);

	test_colInfo.push_back(5);
	test_colInfo.push_back(5);
	test_colInfo.push_back(10);	

	rightercenter.x = 3;
	rightercenter.y = 3;
	rightInfo.push_back(rightercenter);

	rightercenter.x = 3;
	rightercenter.y = 4;
	rightInfo.push_back(rightercenter);

	rightercenter.x = 5;
	rightercenter.y = 11;
	rightInfo.push_back(rightercenter);

	int count = testInfo.size();

	printf("\r\n************%s********************************\r\n", __FUNCTION__);
	for (int i = 0; i < count; i++)
	{
		beginTimeStr = GetTimeStamp();
		float **test = testInfo[i];
		int row = test_rowInfo[i];
		int col = test_colInfo[i];

		centerInfo.clear();

		endTimeStr = GetTimeStamp();
		printf("\r\n=============================���������ʼ====================================\r\n");
		printf("�������:\r\n\r\n");
	
		for (int m = 0; m < row; m++)
		{
			for (int j = 0; j < col; j++)
			{
				printf("%.02f ", ((float*)(test + m * col))[j]);
			}
			printf("\r\n");
		}

		acm_calcCetner(test, row, col, centerInfo);
		int centCount = centerInfo.size();

		printf("\r\n\r\n���: centerCount = %d\r\n", centCount);
		for (int k = 0; k < centCount; k++)
		{
			if ((centerInfo[k].x == rightInfo[i].x) && (centerInfo[k].y == rightInfo[i].y))
			{
				printf("\r\n center.x =  %d  cent.y = %d is right success!\r\n", centerInfo[k].x, centerInfo[k].y);
			}
			else
			{
				printf("\r\n center.x =  %d  cent.y = %d is right success!\r\n", centerInfo[k].x, centerInfo[k].y);
			}
		}
		

		printf("beginTimeStr = %s\r\n", beginTimeStr.c_str());
		printf("endTimeStr = %s\r\n", endTimeStr.c_str());

		printf("==================================�����������=======================\r\n");
	}

}