#include "Task.h"

//--------------------------------------------------------------------------------------//
/*--------------------------------�^�X�N�N���X------------------------------------------*/
//--------------------------------------------------------------------------------------//
CTask::CTask(CTaskList* task_list)
:TaskList(task_list)
{
	// �^�X�N���A�N�e�B�u�^�X�N���X�g�ɑ}������
	Prev=task_list->ActiveTask->Prev;
	Next=task_list->ActiveTask;
	Prev->Next=Next->Prev=this;
}

CTask::~CTask(void)
{
	// �^�X�N���A�N�e�B�u�^�X�N���X�g����폜����
	Prev->Next=Next;
	Next->Prev=Prev;
}

void CTask::operator_delete(void* p, CTaskList* task_list) {

	// �^�X�N
	CTask* task=(CTask*)p;

	// �^�X�N���t���[�^�X�N���X�g�ɑ}������
	task->Next=task_list->FreeTask->Next;
	task_list->FreeTask->Next=task;
	task_list->NumFreeTask++;

	// �t���[�^�X�N�����ő�^�X�N���𒴂�����G���[
	// �idelete�̏d���Ăяo���Ȃǁj
	assert(task_list->NumFreeTask<=task_list->MaxNumTask);
}

void* CTask::operator_new(size_t t, CTaskList* task_list) {

	// �N���X�T�C�Y���ő�T�C�Y�𒴂�����G���[
	assert(t<=(size_t)task_list->MaxTaskSize);

	// �t���[�^�X�N���Ȃ��Ƃ���NULL��Ԃ�
	if (task_list->NumFreeTask<=0) return NULL;

	// �t���[�^�X�N��1���o��
	CTask* task=task_list->FreeTask->Next;
	task_list->FreeTask->Next=task->Next;
	task_list->NumFreeTask--;
	
	// �R���X�g���N�^��
	return task;
}

//--------------------------------------------------------------------------------------//
/*--------------------------------�^�X�N���X�g�N���X------------------------------------*/
//--------------------------------------------------------------------------------------//
CTaskList::CTaskList(int max_task_size, int max_num_task)
:MaxTaskSize(max_task_size), MaxNumTask(max_num_task), NumFreeTask(max_num_task)
{
	// �^�X�N�������p�̃}�N��
	#define TASK(INDEX) ((CTask*)(buf+max_task_size*(INDEX)))

	// �^�X�N�p�������̊m��
	buf=new char[max_task_size*(max_num_task+2)];

	// �A�N�e�B�u�^�X�N���X�g�̏�����
	ActiveTask=TASK(0);
	ActiveTask->Prev=ActiveTask->Next=ActiveTask;

	// �t���[�^�X�N���X�g�̏�����
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

