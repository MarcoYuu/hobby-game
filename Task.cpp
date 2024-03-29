#include "Task.h"

//--------------------------------------------------------------------------------------//
/*--------------------------------タスククラス------------------------------------------*/
//--------------------------------------------------------------------------------------//
CTask::CTask(CTaskList* task_list)
:TaskList(task_list)
{
	// タスクをアクティブタスクリストに挿入する
	Prev=task_list->ActiveTask->Prev;
	Next=task_list->ActiveTask;
	Prev->Next=Next->Prev=this;
}

CTask::~CTask(void)
{
	// タスクをアクティブタスクリストから削除する
	Prev->Next=Next;
	Next->Prev=Prev;
}

void CTask::operator_delete(void* p, CTaskList* task_list) {

	// タスク
	CTask* task=(CTask*)p;

	// タスクをフリータスクリストに挿入する
	task->Next=task_list->FreeTask->Next;
	task_list->FreeTask->Next=task;
	task_list->NumFreeTask++;

	// フリータスク数が最大タスク数を超えたらエラー
	// （deleteの重複呼び出しなど）
	assert(task_list->NumFreeTask<=task_list->MaxNumTask);
}

void* CTask::operator_new(size_t t, CTaskList* task_list) {

	// クラスサイズが最大サイズを超えたらエラー
	assert(t<=(size_t)task_list->MaxTaskSize);

	// フリータスクがないときはNULLを返す
	if (task_list->NumFreeTask<=0) return NULL;

	// フリータスクを1個取り出す
	CTask* task=task_list->FreeTask->Next;
	task_list->FreeTask->Next=task->Next;
	task_list->NumFreeTask--;
	
	// コンストラクタへ
	return task;
}

//--------------------------------------------------------------------------------------//
/*--------------------------------タスクリストクラス------------------------------------*/
//--------------------------------------------------------------------------------------//
CTaskList::CTaskList(int max_task_size, int max_num_task)
:MaxTaskSize(max_task_size), MaxNumTask(max_num_task), NumFreeTask(max_num_task)
{
	// タスク初期化用のマクロ
	#define TASK(INDEX) ((CTask*)(buf+max_task_size*(INDEX)))

	// タスク用メモリの確保
	buf=new char[max_task_size*(max_num_task+2)];

	// アクティブタスクリストの初期化
	ActiveTask=TASK(0);
	ActiveTask->Prev=ActiveTask->Next=ActiveTask;

	// フリータスクリストの初期化
	FreeTask=TASK(1);
	for (int i=1; i<max_num_task+1; i++) {
		TASK(i)->Next=TASK(i+1);
	}
	TASK(max_num_task+1)->Next=FreeTask;
}

void CTaskList::DeleteTask() 
{
	for (CTaskIter i(this); i.HasNext(); i.Next(), i.Remove());
}

