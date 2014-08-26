
#include <stdio.h>
#include <stdlib.h>

#include <string.h>//strtok
#include "datatype.h"

int GetStockInfo(StockInfo *Info, char *InputStr);
int Itemcounts(char *InputStr);
int main()
{
	//char buffer[100] = "ㄎ(1227),89.6,1,,1,,0,89600,89600";
	char buffer[100] = "";
	//布嘿,瞷基,栋玂畐,,,箂,,瞷,カ
	char *input = NULL;
	StockInfo Stock_Info;
	int skip1,  skip2,  skip3;
	int info_index = 0;
	FILE *InputFile = fopen("20140811.csv","r+");
	FILE *OutputFile = fopen("Out.csv","w+");
	char * pch;

	if (InputFile==NULL)
	{
		printf("can't open output file");
		return 1;
	}
	if (OutputFile==NULL)
	{
		printf("can't open output file");
		return 1;
	}

	input = buffer;
	Stock_Info.StockName;

	int i = 0;
	while(i <3)//skip header line
	{		
		if(fgets(buffer,128,InputFile)!=NULL)
		{
			i++;
		}
	}
	//print new header line
	fprintf(OutputFile,"布嘿,瞷基,瞷Τ眎计,瞷Τ箂,羆计,カ\n");

	while(!feof(InputFile))
	{
		if(fgets(buffer,128,InputFile)!=NULL)
		{
			GetStockInfo(&Stock_Info,buffer);
			fprintf(OutputFile,"%s,%.2f,%d,%d,%d,%d\n",Stock_Info.StockName,Stock_Info.Price, Stock_Info.Lots,Stock_Info.Shares,Stock_Info.TotalShares,Stock_Info.TotalPrice);
		}
	}
	
	fclose (InputFile);
	fclose (OutputFile);

	return 0;
}

int Itemcounts(char *InputStr)
{
	int counts = 0;
	char * pch;
	pch = strtok (InputStr,",");
	while (pch != NULL)
	{
		counts ++;
		pch = strtok (NULL, ",");
	}
	return counts;
}

int GetStockInfo(StockInfo *Info, char *InputStr)
{
	char * pch;
	int info_index = 0;

//	int ItemCnts = Itemcounts(InputStr);

	pch = strtok (InputStr,",");
	while (pch != NULL)
	{
		switch(info_index)
		{
		case 0://get stock name
			sprintf(Info->StockName, "%s", pch);
			break;
		case 1://get stock price
			Info->Price = atof(pch);
			break;
		case 3://get stock lots
			Info->Lots = atoi(pch);
			break;
		case 4://get stock shares if the stock has no shares
			Info->Shares = atoi(pch);
			break;
		case 5://get stock shares if the stock has shares > 0
			Info->Shares = atoi(pch);
			break;
		default:
			break;
		}

		info_index++ ;
		pch = strtok (NULL, ",");
	}

	Info->TotalShares = Info->Lots*1000 + Info->Shares;
	Info->TotalPrice = Info->TotalShares * Info->Price;
	return 0;
}