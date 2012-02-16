//============== IV: Multiplayer - http://code.iv-multiplayer.com ==============
//
// File: CIVPedTaskManager.cpp
// Project: Client.Core
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==============================================================================

#include "CIVPedTaskManager.h"
#include "CIVTask.h"
#include "CClientTaskManager.h"
#include "CGame.h"
#include "COffsets.h"

extern CClientTaskManager * g_pClientTaskManager;

CIVPedTaskManager::CIVPedTaskManager(IVPedTaskManager * pPedTaskManager, CIVPed * pPed)
{
	m_pPedTaskManager = pPedTaskManager;
	m_pPed = pPed;
}

void CIVPedTaskManager::SetTask(CIVTask * pTask, int iType, bool bForceNewTask)
{
	// Do we have a valid ped task manager pointer?
	if(m_pPedTaskManager)
	{
		// Ensure the task type is valid
		if(iType < TASK_PRIORITY_MAX)
		{
			IVPedTaskManager * pPedTaskManager = m_pPedTaskManager;
			IVTask * pGameTask = (pTask ? pTask->GetTask() : NULL);
			_asm
			{
				push bForceNewTask
				push iType
				push pGameTask
				mov ecx, pPedTaskManager
				call COffsets::FUNC_CPedTaskManager__SetTaskPriority
			}
		}
	}
}

void CIVPedTaskManager::RemoveTask(int iType)
{
	// Do we have a valid ped task manager pointer?
	if(m_pPedTaskManager)
	{
		// Ensure the task type is valid
		if(iType < TASK_PRIORITY_MAX)
		{
			// Make sure its not the default task (We will crash without it)
			if(iType != TASK_PRIORITY_DEFAULT)
				SetTask(NULL, iType);
		}
	}
}

CIVTask * CIVPedTaskManager::GetTask(int iType)
{
	// Do we have a valid ped task manager pointer?
	if(m_pPedTaskManager)
	{
		// Ensure the task type is valid
		if(iType < TASK_PRIORITY_MAX)
			return g_pClientTaskManager->GetClientTaskFromGameTask(m_pPedTaskManager->m_primaryTasks[iType]);
	}

	return NULL;
}

void CIVPedTaskManager::SetTaskSecondary(CIVTask * pTask, int iType)
{
	// Do we have a valid ped task manager pointer?
	if(m_pPedTaskManager)
	{
		// Ensure the task type is valid
		if(iType < TASK_SECONDARY_MAX)
		{
			IVPedTaskManager * pPedTaskManager = m_pPedTaskManager;
			IVTask * pGameTask = (pTask ? pTask->GetTask() : NULL);
			_asm
			{
				push iType
				push pGameTask
				mov ecx, pPedTaskManager
				call COffsets::FUNC_CPedTaskManager__SetTaskSecondary
			}
		}
	}
}

void CIVPedTaskManager::RemoveTaskSecondary(int iType)
{
	// Do we have a valid ped task manager pointer?
	if(m_pPedTaskManager)
	{
		// Ensure the task type is valid
		if(iType < TASK_SECONDARY_MAX)
			SetTaskSecondary(NULL, iType);
	}
}

CIVTask * CIVPedTaskManager::GetTaskSecondary(int iType)
{
	// Do we have a valid ped task manager pointer?
	if(m_pPedTaskManager)
	{
		// Ensure the task type is valid
		if(iType < TASK_SECONDARY_MAX)
			return g_pClientTaskManager->GetClientTaskFromGameTask(m_pPedTaskManager->m_secondaryTasks[iType]);
	}

	return NULL;
}

void CIVPedTaskManager::SetTaskMovement(CIVTask * pTask, int iType)
{
	// Do we have a valid ped task manager pointer?
	if(m_pPedTaskManager)
	{
		// Ensure the task type is valid
		if(iType < TASK_MOVEMENT_MAX)
		{
			IVPedTaskManager * pPedTaskManager = m_pPedTaskManager;
			IVTask * pGameTask = (pTask ? pTask->GetTask() : NULL);
			_asm
			{
				push iType
				push pGameTask
				mov ecx, pPedTaskManager
				call COffsets::FUNC_CPedTaskManager__SetTaskMovement
			}
		}
	}
}

void CIVPedTaskManager::RemoveTaskMovment(int iType)
{
	// Do we have a valid ped task manager pointer?
	if(m_pPedTaskManager)
	{
		// Ensure the task type is valid
		if(iType < TASK_MOVEMENT_MAX)
			SetTaskMovement(NULL, iType);
	}
}

CIVTask * CIVPedTaskManager::GetTaskMovement(int iType)
{
	// Do we have a valid ped task manager pointer?
	if(m_pPedTaskManager)
	{
		// Ensure the task type is valid
		if(iType < TASK_MOVEMENT_MAX)
			return g_pClientTaskManager->GetClientTaskFromGameTask(m_pPedTaskManager->m_movementTasks[iType]);
	}

	return NULL;
}

void CIVPedTaskManager::ClearTasks(int iAbortPriority)
{
	// Do we have a valid ped task manager pointer?
	if(m_pPedTaskManager)
	{
		// Clear priority tasks
		for(int i = 0; i < TASK_PRIORITY_MAX; i++)
		{
			CIVTask * pTask = GetTask(i);

			if(pTask)
				pTask->MakeAbortable(m_pPed, iAbortPriority, NULL);
		}

		// Clear secondary tasks
		for(int i = 0; i < TASK_SECONDARY_MAX; i++)
		{
			CIVTask * pTask = GetTaskSecondary(i);

			if(pTask)
				pTask->MakeAbortable(m_pPed, iAbortPriority, NULL);
		}

		// Clear movement tasks
		for(int i = 0; i < TASK_MOVEMENT_MAX; i++)
		{
			CIVTask * pTask = GetTaskMovement(i);

			if(pTask)
				pTask->MakeAbortable(m_pPed, iAbortPriority, NULL);
		}
	}
}