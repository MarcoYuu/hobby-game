#pragma once

#include <stdio.h>
#include <assert.h>

class CTask;
class CTaskList;
class CTaskIter;


//-----------------------------------------------------------------//
//�^�X�N�N���X
//-----------------------------------------------------------------//
class CTask
{
	friend CTaskList;
	friend CTaskIter;

	CTaskList* TaskList;
	CTask *Prev, *Next;

	// �^�X�N���X�g���w�肵�Ȃ�new, delete�𖳌��ɂ���
	void* operator new(size_t t) {}
	void operator delete(void* p) {}

protected:
	// new, delete�̏����F
	// �K�؂�new, delete���Z�q���T�u�N���X�Œ�`����
	static void* operator_new(size_t t, CTaskList* task_list);
	static void operator_delete(void* p, CTaskList* task_list);

public:
	CTask(CTaskList* task_list);
	virtual ~CTask(void);
};

//-----------------------------------------------------------------//
//�^�X�N���X�g�N���X
//-----------------------------------------------------------------//
class CTaskList 
{
	friend CTask;
	friend CTaskIter;

	char *buf;

	CTask *ActiveTask, *FreeTask;

	int MaxTaskSize, MaxNumTask;
	int NumFreeTask;

public:
	// �R���X�g���N�^
	CTaskList(int max_task_size, int max_num_task);
	//�f�X�g���N�^
	~CTaskList()
	{
		delete [] buf;
	}
	
	// �^�X�N�̐�
	int GetNumFreeTask() 
	{ 
		return NumFreeTask; 
	}
	int GetNumActiveTask() 
	{ 
		return MaxNumTask-NumFreeTask; 
	}

	// �S�^�X�N�̏���
	void DeleteTask();
};

//-----------------------------------------------------------------//
//�C�e���[�^�N���X
//-----------------------------------------------------------------//
class CTaskIter 
{
protected:
	CTaskList* TaskList;
	CTask* Task;

public:
	// �R���X�g���N�^
	CTaskIter(CTaskList* task_list)
	: TaskList(task_list), Task(task_list->ActiveTask)
	{
	}

	// ���̗v�f������Ƃ�true
	bool HasNext() 
	{
		return Task->Next!=TaskList->ActiveTask;
	}

	// ���̗v�f��Ԃ�
	CTask* Next() 
	{
		return Task=Task->Next;
	}

	// ���O�ɕԂ����v�f���폜����
	void Remove() 
	{
		Task=Task->Prev;
		delete Task->Next;
	}
};
