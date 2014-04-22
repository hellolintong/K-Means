#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include "dmatfile.h"
#include "node.h"


EC_DMAT OpenDMat(const char *pFileName, DMATFILE& DMatFile)
{
	DMATHEADER tmpHdr;
	memset(&tmpHdr, 0, sizeof(tmpHdr));

	std::auto_ptr<std::ifstream> filePtr(new std::ifstream);

	filePtr->open(pFileName, std::ios::in | std::ios::binary);
	int nVal;
	if (!filePtr->is_open())
	{
		return DMAT_FILE_OPEN_FAILED;
	}
	filePtr->read((char*)&nVal, 4);
	if (nVal != *(int*)"DMAT")
	{
		return DMAT_FILE_TYPE_ERROR;
	}
	tmpHdr.nFileTag = (uint)nVal;

	filePtr->read((char*)&nVal, 4);
	filePtr->seekg(0, std::ios::end);
	tmpHdr.nFileSize = (uint)filePtr->tellg();
	if ((uint)nVal != tmpHdr.nFileSize)
	{
		return DMAT_FILE_TRUCKED;
	}

	filePtr->seekg(8, std::ios::beg);
	filePtr->read((char*)&nVal, 4);
	if (nVal != 0)
	{
		return DMAT_UNSUPPORTED_VERSION;
	}
	tmpHdr.nVersion = (uint)nVal;

	filePtr->read((char*)&nVal, 4);
	if (nVal != sizeof(DMATHEADER))
	{
		return DMAT_BAD_HEADER;
	}
	tmpHdr.nHdrSize = (uint)nVal;

	filePtr->read((char*)&nVal, 4);
	tmpHdr.nAttrCnt = (uint)nVal;

	filePtr->read((char*)&nVal, 4);
	tmpHdr.nRowCnt = (uint)nVal;

	uint nDataCnt = tmpHdr.nAttrCnt * tmpHdr.nRowCnt;
	if (nDataCnt * sizeof(double) + sizeof(DMATHEADER) != tmpHdr.nFileSize)
	{
		return DMAT_FILE_TRUCKED;
	}

	if (0 == nDataCnt)
	{
		return DMAT_NO_DATA;
	}

	DMatFile.hdr = tmpHdr;
	DMatFile.pHdl = (void*)filePtr.get();
	filePtr.release();

	return DMAT_OK;
}

void CloseDMat(DMATFILE &DMatFile)
{
	delete (std::ifstream*)(DMatFile.pHdl);
}

EC_DMAT LoadDMat(DMATFILE &DMatFile, double *pBuf)
{
	std::ifstream *pFile = (std::ifstream*)DMatFile.pHdl;
	pFile->seekg(DMatFile.hdr.nHdrSize, std::ios::beg);
	uint nDataCnt = DMatFile.hdr.nAttrCnt * DMatFile.hdr.nRowCnt;
	pFile->read((char*)pBuf, nDataCnt*sizeof(double));
	return DMAT_OK;
}
EC_DMAT LoadDMatRow(DMATFILE &DMatFile, uint nRow, double *pBuf)
{
	if (nRow >= DMatFile.hdr.nRowCnt)
	{
		return DMAT_FILE_TRUCKED;
	}
	std::ifstream *pFile = (std::ifstream*)DMatFile.pHdl;
	uint nBeg = DMatFile.hdr.nHdrSize + nRow * DMatFile.hdr.nAttrCnt * sizeof(double);
	pFile->seekg(nBeg, std::ios::beg);
	pFile->read((char*)pBuf, DMatFile.hdr.nAttrCnt * sizeof(double));
	return DMAT_OK;
}