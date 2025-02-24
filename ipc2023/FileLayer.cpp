// FileLayer.cpp: implementation of the CFileLayer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "pch.h"
#include "FileLayer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileLayer::CFileLayer(char* pName)
	: CBaseLayer(pName)
{
}

CFileLayer::~CFileLayer()
{
	TRY
	{
		//////////////////////// fill the blank ///////////////////////////////
				CFile::Remove(_T("IpcBuff.txt")); // 파일 제거
		///////////////////////////////////////////////////////////////////////
	}
		CATCH(CFileException, e)
	{
#ifdef _DEBUG
		afxDump << "File cannot be removed\n";
#endif
	}
	END_CATCH
}

BOOL CFileLayer::Send(unsigned char* ppayload, int nlength)
{
	TRY
	{
		CFile m_FileDes(_T("IpcBuff.txt"),
						 CFile::modeCreate | CFile::modeWrite);
	//////////////////////// fill the blank ///////////////////////////////
			// 파일 생성
			m_FileDes.Write(ppayload,nlength);
			m_FileDes.Close();
			///////////////////////////////////////////////////////////////////////
	}
		CATCH(CFileException, e)
	{
#ifdef _DEBUG
		afxDump << "File could not be opened " << e->m_cause << "\n";
#endif
		return FALSE;
	}
	END_CATCH

		return TRUE;
}

BOOL CFileLayer::Receive()
{
	TRY
	{
		CFile m_FileDes(_T("IpcBuff.txt"), CFile::modeRead);

	//////////////////////// fill the blank ///////////////////////////////
			// 파일의 내용을 가져온다.

			// Ethernet Frame = Header | Data 이므로, 현재 어느정도의 크기의 데이터가 들어있는지 모른다.
			// 그래서 Ethernet Header 크기와 Ethernet Data의 최대 크기로 Frame의 크기를 정한다.
			int nlength = ETHER_HEADER_SIZE + ETHER_MAX_DATA_SIZE;
			unsigned char* ppayload = new unsigned char[nlength + 1];

			// 정해진 Frame의 길이만큼 파일의 내용(상대 프로세스에게 전송 받은 Ethernet Frame)을
			// 읽어와서 ppayload를 결정한다.
			m_FileDes.Read(ppayload,nlength);
			ppayload[nlength] = '\0';

			// Ethernet 계층으로 파일에서 가져온 Frame을 넘겨준다. 
			if (!mp_aUpperLayer[0]->Receive(ppayload)) { // 넘겨주지 못했다면 FALSE
				m_FileDes.Close();
				return FALSE;
			}
			// 성공했다면 TRUE를 return
	///////////////////////////////////////////////////////////////////////
			m_FileDes.Close();
	}
		CATCH(CFileException, e)
	{
#ifdef _DEBUG
		afxDump << "File could not be opened " << e->m_cause << "\n";
#endif
		return FALSE;
	}
	END_CATCH

		return TRUE;
}
