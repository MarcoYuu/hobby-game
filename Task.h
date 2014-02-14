#pragma once

#include <stdio.h>
#include <assert.h>

class CTask;
class CTaskList;
class CTaskIter;


//-----------------------------------------------------------------//
//タスククラス
//-----------------------------------------------------------------//
class CTask
{
	friend CTaskList;
	friend CTaskIter;

	CTaskList* TaskList;
	CTask *Prev, *Next;

	// タスクリストを指定しないnew, deleteを無効にする
	void* operator new(size_t t) {}
	void operator delete(void* p) {}

protected:
	// new, deleteの処理：
	// 適切なnew, delete演算子をサブクラスで定義する
	static void* operator_new(size_t t, CTaskList* task_list);
	static void operator_delete(void* p, CTaskList* task_list);

public:
	CTask(CTaskList* task_list);
	virtual ~CTask(void);
};

//-----------------------------------------------------------------//
//タスクリストクラス
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
	// コンストラクタ
	CTaskList(int max_task_size, int max_num_task);
	//デストラクタ
	~CTaskList()
	{
		delete [] buf;
	}
	
	// タスクの数
	int GetNumFreeTask() 
	{ 
		return NumFreeTask; 
	}
	int GetNumActiveTask() 
	{ 
		return MaxNumTask-NumFreeTask; 
	}

	// 全タスクの消去
	void DeleteTask();
};

//-----------------------------------------------------------------//
//イテレータクラス
//-----------------------------------------------------------------//
class CTaskIter 
{
protected:
	CTaskList* TaskList;
	CTask* Task;

public:
	// コンストラクタ
	CTaskIter(CTaskList* task_list)
	: TaskList(task_list), Task(task_list->ActiveTask)
	{
	}

	// 次の要素があるときtrue
	bool HasNext() 
	{
		return Task->Next!=TaskList->ActiveTask;
	}

	// 次の要素を返す
	CTask* Next() 
	{
		return Task=Task->Next;
	}

	// 直前に返した要素を削除する
	void Remove() 
	{
		Task=Task->Prev;
		delete Task->Next;
	}
};
