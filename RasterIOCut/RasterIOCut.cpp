#include "RasterIOCut.h"




using namespace std;


/************************************************************************/
/* @biref 图像矩形裁切                  */
/* @param pszSrcFile   输入文件路径
/* @param pszDstFile	输出文件路径
/* @param iStartX	起始列号
/* @param iStartY	起始行号
/* @param iSizeX	裁切列数	
/* @param iSizeY	裁切行数
/* @param 
/* @param 
/************************************************************************/

void ImageCut(const char * pszSrcFile, const char* pszDstFile,int iStartX, int iStartY, 
	int iSizeX, int iSizeY/*, const char* pszFormat*/)
{

	GDALAllRegister();
	GDALDataset *pSrcDS = (GDALDataset*)GDALOpen(pszSrcFile, GA_ReadOnly);
	GDALDataType eDT1 = pSrcDS->GetRasterBand(1)->GetRasterDataType();
		
	const char* Informat;
	GDALDriverH hDriver;

	int iBandCount1 = pSrcDS->GetRasterCount();

	//根据裁切范围确定裁切后的图像宽高
	/*int iDstWidth = iSizeX;
	int iDstHeight = iSizeY;
	*/
	double adfGeoTransform[6] = {0};
	pSrcDS->GetGeoTransform(adfGeoTransform);
	 
	hDriver = GDALGetDatasetDriver(pSrcDS);
	Informat = GDALGetDriverShortName(hDriver);
	//计算裁切后的图像的左上角坐标
	adfGeoTransform[0] = adfGeoTransform[0] + iStartX*adfGeoTransform[1] + 
		iStartY*adfGeoTransform[2];
	adfGeoTransform[3] = adfGeoTransform[3] + iStartX*adfGeoTransform[4] + 
		iStartY*adfGeoTransform[5];

	//创建输出文件并设置空间参考和坐标信息
	GDALDriver *poDriver = GetGDALDriverManager()->GetDriverByName(Informat);
	GDALDataset * pDstDS = poDriver->Create( pszDstFile, iSizeX, iSizeY, iBandCount1, eDT1, NULL);
	pDstDS->SetGeoTransform(adfGeoTransform);
	pDstDS->SetProjection(pSrcDS->GetProjectionRef());

	//int ysize1=pSrcDS->GetRasterYSize();
	//int xsize1=pSrcDS->GetRasterXSize();

	int *pBandMap = new int[iBandCount1];
	for(int i = 0; i < iBandCount1; i++ )
		pBandMap[i]= i+1;
	//下面要根据数据类型来判断，申请不同类型的缓存来进行处理，这里仅仅以8Bit图像进行演示
	if (eDT1 == GDT_Byte)
	{
		//申请所有数据所需要的缓存，如果图像太大应该用分块处理
		// 申请所有数据所需要的缓存，如果图像太大应该用分块处理

		//char *pDataBuff = new char[iDstWidth*iDstHeight*iBandCount1];	////////////////30000 30000内存申请不到了需要分块！！！！！10000*10000可以
	/*	char *pDataBuff = new char[xsize1/2*ysize1/2*iBandCount1];

		pSrcDS->RasterIO(GF_Read, 0,0,xsize1/2, ysize1/2, pDataBuff, xsize1/2,  ysize1/2, eDT1, iBandCount1, pBandMap, 0, 0, 0);
		pDstDS->RasterIO(GF_Write, 0, 0,  xsize1/2,  ysize1/2, pDataBuff,  xsize1/2,  ysize1/2, eDT1, iBandCount1, pBandMap, 0, 0, 0);

		pSrcDS->RasterIO(GF_Read, 0,ysize1/2,xsize1/2, ysize1/2, pDataBuff, xsize1/2,  ysize1/2, eDT1, iBandCount1, pBandMap, 0, 0, 0);
		pDstDS->RasterIO(GF_Write, 0, ysize1/2,  xsize1/2,  ysize1/2, pDataBuff,  xsize1/2,  ysize1/2, eDT1, iBandCount1, pBandMap, 0, 0, 0);

		pSrcDS->RasterIO(GF_Read, xsize1/2,0,xsize1/2, ysize1/2, pDataBuff, xsize1/2,  ysize1/2, eDT1, iBandCount1, pBandMap, 0, 0, 0);
		pDstDS->RasterIO(GF_Write, xsize1/2, 0,  xsize1/2,  ysize1/2, pDataBuff,  xsize1/2,  ysize1/2, eDT1, iBandCount1, pBandMap, 0, 0, 0);

		pSrcDS->RasterIO(GF_Read, xsize1/2,ysize1/2,xsize1/2, ysize1/2, pDataBuff, xsize1/2,  ysize1/2, eDT1, iBandCount1, pBandMap, 0, 0, 0);
		pDstDS->RasterIO(GF_Write, xsize1/2, ysize1/2,  xsize1/2,  ysize1/2, pDataBuff,  xsize1/2,  ysize1/2, eDT1, iBandCount1, pBandMap, 0, 0, 0);

*/
		char *pDataBuff = new char[iSizeX*iSizeY*iBandCount1];

		pSrcDS->RasterIO(GF_Read, iStartX,iStartY,iSizeX, iSizeY, pDataBuff, iSizeX,  iSizeY, eDT1, iBandCount1, pBandMap, 0, 0, 0);
		pDstDS->RasterIO(GF_Write, 0, 0,  iSizeX,  iSizeY, pDataBuff,  iSizeX,  iSizeY, eDT1, iBandCount1, pBandMap, 0, 0, 0);

	}

	else
	{
		//
	}

	delete(pBandMap);
	GDALClose((GDALDatasetH)pSrcDS);
	GDALClose((GDALDatasetH)pDstDS);
	
}