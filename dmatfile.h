#pragma once
#include "node.h"
struct DMATHEADER
{
	unsigned int nFileTag;
	unsigned int nFileSize;
	unsigned int nVersion;
	unsigned int nHdrSize;
	unsigned int nAttrCnt;
	unsigned int nRowCnt;
};

struct DMATFILE
{
	DMATHEADER hdr;
	void *pHdl;
};

enum EC_DMAT
{
	DMAT_OK,
	DMAT_FILE_OPEN_FAILED,
	DMAT_FILE_TYPE_ERROR,
	DMAT_FILE_TRUCKED,
	DMAT_UNSUPPORTED_VERSION,
	DMAT_BAD_HEADER,
	DMAT_NO_DATA,
};

EC_DMAT OpenDMat(const char *pFileName, DMATFILE &DMatFile);

void CloseDMat(DMATFILE &DMatFile);

EC_DMAT LoadDMat(DMATFILE &DMatFile, double *pBuf);

EC_DMAT LoadDMatRow(DMATFILE &DMatFile, uint nRow, double *pBuf);