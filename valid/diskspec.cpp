#pragma warning(disable:4996);
#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
#include<float.h>
#include<string>
#include<string.h>
using namespace std;

float to_float(string s)
{
	int i = 0, n = 0;
	int point_index = s.find('.',15);
	float result = 0, under_0 = 0;//under_0存储小数部分  
	if (count(s.begin(), s.end(), '.') == 0)
	{
		return 0;//字符串里只能有1个或0个小数点，不然出错退出  
	}
	if (s.find('.',15) != -1)//字符串里有小数点  
	{
		if ((point_index == 0) || (point_index == s.size() - 1))//小数点位置合理，不能在字符串第1位,且不能在最后一位  
		{
			return 0;
		}
		for (i = 0; i <= point_index - 1; i++)//计算整数部分  
		{
			if (s[i] >= '0'&&s[i] <= '9')
			{
				result = result * 10 + s[i] - 48;
			}
		}
		for (i = s.size() - 1; i >= point_index - 1; i--)//计算小数部分  
		{
			if (s[i] >= '0'&&s[i] <= '9')
			{
				if (i == point_index - 1)
				{
					under_0 = under_0 * 0.1 + 0;//i=小数点前一位，under_0+0  
				}
				else
				{
					under_0 = under_0 * 0.1 + s[i] - 48;
				}
			}
		}
		result = result + under_0;//把整数部分和小数部分相加  
	}
	else//字符串只有整数部分  
	{
		for (i = 0; i <= s.size() - 1; i++)
		{
			if (s[i] >= '0'&&s[i] <= '9')
			{
				result = result * 10 + s[i] - 48;
			}
		}
	}

	return result;
}
int main(int argc, char* argv[]) {
	FILE  *inputFile;
	FILE  *outputFile;
	char writebuffer[1024];
	inputFile = fopen(argv[1], "r");
	outputFile = fopen(argv[2], "w+");
	while (fgets(writebuffer, 1024, inputFile) != NULL) {
		string strTemp = string(writebuffer);
		float number = 0.0;
		if (string::npos != strTemp.find("Bulk sector transfer time")) {
			number = to_float(strTemp);
			fprintf(outputFile, " Bulk sector transfer time =  %f, \n", number / stof(argv[3]));
		}
		else if (string::npos != strTemp.find("Read hit over. after read")) {
			number = to_float(strTemp);
			fprintf(outputFile, " Read hit over. after read = %f, \n", number / stof(argv[3]));
		}
		else if (string::npos != strTemp.find("Read hit over. after write")) {
			number = to_float(strTemp);
			fprintf(outputFile, " Read hit over. after write = %f, \n", number / stof(argv[3]));
		}
		else if (string::npos != strTemp.find("Read miss over. after read")) {
			number = to_float(strTemp);
			fprintf(outputFile, " Read miss over. after read = %f, \n", number / stof(argv[3]));
		}
		else if (string::npos != strTemp.find("Read miss over. after write")) {
			number = to_float(strTemp);
			fprintf(outputFile, " Read miss over. after write = %f, \n", number / stof(argv[3]));
		}
		else if (string::npos != strTemp.find("Write hit over. after read")) {
			number = to_float(strTemp);
			fprintf(outputFile, " Write hit over. after read = %f, \n", number / stof(argv[3]));
		}
		else if (string::npos != strTemp.find("Write hit over. after write")) {
			number = to_float(strTemp);
			fprintf(outputFile, " Write hit over. after write = %f, \n", number / stof(argv[3]));
		}
		else if (string::npos != strTemp.find("Write miss over. after read")) {
			number = to_float(strTemp);
			fprintf(outputFile, " Write miss over. after read = %f, \n", number / stof(argv[3]));
		}
		else if (string::npos != strTemp.find("Write miss over. after write")) {
			number = to_float(strTemp);
			fprintf(outputFile, "  Write miss over. after write = %f, \n", number / stof(argv[3]));
		}
		else if(string::npos != strTemp.find("disksim_disk IBM_DNES-309170W_validate {")){

			fprintf(outputFile, "  %s \n ", "disksim_disk seagate {");
		}
		else if (string::npos != strTemp.find("Model = source")) {
		
			fprintf(outputFile, "  %s \n", "Model = source seagate.model,");
		}else{
		
			fprintf(outputFile, "  %s ", strTemp.c_str());
		}

	}
	std::fclose(outputFile);
	std::fclose(inputFile);

	return 0;
}
