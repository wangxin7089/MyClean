#include "stdafx.h"
#include "MyThreadPool.h"


CMyThreadPool::CMyThreadPool(void)
{

	m_bFlagQuit = true;
	m_hSemphore = NULL;
	m_lCreateThreadNum= 0;
	m_lMaxThreadNum = 0;
	m_lRunThreadNum = 0;
}


CMyThreadPool::~CMyThreadPool(void)
{
}

//1.�����̳߳�
bool CMyThreadPool::CreateThreadPool(long lMinThreadNum, long lMaxThreadNum,long lMaxItaskNum)
{
	//У�����
	if(lMinThreadNum <=0 || lMaxThreadNum < lMinThreadNum|| lMaxItaskNum <=0)
	{
		return false;
	}
	//��ʼ���߳��е���Դ
	m_hSemphore = CreateSemaphore(NULL,0,lMaxItaskNum,NULL);
	if(!m_qItask.InitQueue(lMaxItaskNum/5))
	{
		return false;
	}

	//�����̳߳�
	for(long i = 0; i <lMinThreadNum;i++ )
	{
		HANDLE hThread = (HANDLE)_beginthreadex(0,0,&ThreadProc,this,0,0);
		if(hThread)
		{
			m_lstThread.push_back(hThread);
		}
	}

	m_lCreateThreadNum = lMinThreadNum;
	m_lMaxThreadNum = lMaxThreadNum;

	return true;
}

//2.�����̳߳�
void  CMyThreadPool::DestroyThreadPool()
{
	m_bFlagQuit = false;
	auto ite = m_lstThread.begin();
	while(ite != m_lstThread.end())
	{

		if(WAIT_TIMEOUT == WaitForSingleObject(*ite,100))
		{
			TerminateThread(*ite,-1);
		}
		CloseHandle(*ite);
		*ite = NULL;
		ite++;
	}

	if(m_hSemphore)
	{
		CloseHandle(m_hSemphore);
		m_hSemphore = NULL;
	}

	//�������
	Itask *pItask = NULL;
	
	while(!m_qItask.empty())
	{
		if(m_qItask.pop(pItask))
		{
			delete pItask;
		     pItask = NULL;
		}
	
	}

	m_qItask.UnInitQueue();
}

//3.�̺߳���
unsigned _stdcall CMyThreadPool::ThreadProc( void * lpvoid )
{
	CMyThreadPool *pthis = (CMyThreadPool *)lpvoid;
	Itask *pItask = NULL;
	while(pthis->m_bFlagQuit)
	{
	      //���ź���
		if(WaitForSingleObject(pthis->m_hSemphore,INFINITE)!= WAIT_OBJECT_0)
		{
			continue;
		}
		//����Ա�л�״̬   ---- ���� ---����---����
	 	//pthis->m_lRunThreadNum++;
		InterlockedIncrement(&pthis->m_lRunThreadNum);
		//�Ӷ�����ȥ����
		while(!pthis->m_qItask.empty())
		{
			
			if(!pthis->m_qItask.pop(pItask))
			{
				break;
			}
			pItask->RunItask();

			delete pItask;
			pItask = NULL;

		}

		//����Ա�л�״̬   ����---- ����
		//pthis->m_lRunThreadNum--;
		InterlockedDecrement(&pthis->m_lRunThreadNum);
	}

	return 0;
}

//4.Ͷ������
bool CMyThreadPool::PushItask(Itask *pItask)
{
	if(pItask == NULL) return false;

	//��������뵽������
	//m_lock.Lock();
	//m_qItask.push(pItask);
	//m_lock.UnLock();
	
	
	 while(!m_qItask.push(pItask))
	 {
		 Sleep(10);
		
	 }

	//1. �п��з���Ա
	//�ͷ��ź���
	if(m_lRunThreadNum < m_lCreateThreadNum)
	{
	    ReleaseSemaphore(m_hSemphore,1,NULL);
	}
	else if(m_lRunThreadNum == m_lCreateThreadNum &&m_lCreateThreadNum < m_lMaxThreadNum )    //2.��û�п��з���Ա����������
	{ 

	     //�ɷ���Ա----�ɻ�
		HANDLE hThread = (HANDLE)_beginthreadex(0,0,&ThreadProc,this,0,0);
		if(hThread)
		{
			m_lstThread.push_back(hThread);
		}
		m_lCreateThreadNum++;
		ReleaseSemaphore(m_hSemphore,1,NULL);

	}
	else
	{
		//3 ������  ----���˵ȴ�
	}

	





	return true;
}
