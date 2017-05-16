#ifndef RASTERIOCUT_H
#define RASTERIOCUT_H

#include "gdal.h"
#include "gdal_priv.h"
#include <iostream>



void ImageCut(const char * pszSrcFile, const char* pszDstFile,int iStartX, int iStartY, 
	int iSizeX, int iSizeY/*, const char* pszFormat*/);



#endif

