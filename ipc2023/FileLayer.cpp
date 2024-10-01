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
				CFile::Remove(_T("IpcBuff.txt")); // ���� ����
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
			// ���� ����
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
			// ������ ������ �����´�.

			// Ethernet Frame = Header | Data �̹Ƿ�, ���� ��������� ũ���� �����Ͱ� ����ִ��� �𸥴�.
			// �׷��� Ethernet Header ũ��� Ethernet Data�� �ִ� ũ��� Frame�� ũ�⸦ ���Ѵ�.
			int nlength = ETHER_HEADER_SIZE + ETHER_MAX_DATA_SIZE;
			unsigned char* ppayload = new unsigned char[nlength + 1];

			// ������ Frame�� ���̸�ŭ ������ ����(��� ���μ������� ���� ���� Ethernet Frame)��
			// �о�ͼ� ppayload�� �����Ѵ�.
			m_FileDes.Read(ppayload,nlength);
			ppayload[nlength] = '\0';

			// Ethernet �������� ���Ͽ��� ������ Frame�� �Ѱ��ش�. 
			if (!mp_aUpperLayer[0]->Receive(ppayload)) { // �Ѱ����� ���ߴٸ� FALSE
				m_FileDes.Close();
				return FALSE;
			}
			// �����ߴٸ� TRUE�� return
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
