#include "RasterIOCut.h"


void main()
{
	GDALAllRegister();

	char SrcFilePath[1000] = "E:\\c\\1.tif";  //被裁切的图像路径
	char DstFilePath[1000] = "E:\\opencvtest\\load\\11500.tif";	//裁切后图像的路径
	
	const char* srcfile = SrcFilePath;
	const char* dstfile = DstFilePath;
	int iSizeX1 = 11500;	//定义裁切后图像的宽
	int iSizeY1 = 11500;	//定义裁切后图像的长
	int iStartX1 = 0;
	int iStartY1 = 0;
	ImageCut(srcfile,dstfile,iStartX1,iStartY1,iSizeX1,iSizeY1);

}
