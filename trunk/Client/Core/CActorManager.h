//============== IV: Multiplayer - http://code.iv-multiplayer.com ==============
//
// File: CActorManager.h
// Project: Client.Core
// Author(s): jenksta
//            Sebihunter
// License: See LICENSE in root directory
//
//==============================================================================

#pragma once

#include "Scripting.h"
#include "CPlayerManager.h"

 struct _Actor
 {
	unsigned int    uiActorIndex;
	CIVModelInfo *  pModelInfo;
	String		    strName;
	CVector3	    vecPosition;	
	bool		    bNametag;
	int			    iNametagColor;
	bool			bFrozen;			
	bool			bHelmet;
	bool			bStateincar;
	EntityId		vehicleId;
	int				iSeatid;
	unsigned int	uiBlipId;
 };

class CActorManager
{
private:
	bool m_bActive[MAX_ACTORS];
	_Actor m_Actors[MAX_ACTORS];

public:
	CActorManager();
	~CActorManager();

	void			Create(EntityId actorId, int iModelId, CVector3 vecPosition, float fHeading, String strName, bool bTogglename, int iColor, bool bFrozen, bool bHelmet);
	bool			Delete(EntityId actorId);
	void			SetPosition(EntityId actorId, CVector3 vecPosition);
	CVector3		GetPosition(EntityId actorId);
	void			SetHeading(EntityId actorId, float fHeading);
	String			GetName(EntityId actorId) { return m_Actors[actorId].strName; }
	bool			IsNameTagEnabled(EntityId actorId) { return m_Actors[actorId].bNametag; }
	void			SetName(EntityId actorId, String strName);
	int				GetNametagColor(EntityId actorId) { return m_Actors[actorId].iNametagColor; }
	bool			ToggleNametag(EntityId actorId, bool bShow);
	void			SetColor(EntityId actorId, int Color);
	bool			ToggleFrozen(EntityId actorId, bool bFrozen);
	bool			ToggleHelmet(EntityId actorId, bool bHelmet);
	void			WarpIntoVehicle(EntityId actorId, EntityId vehicleId, int iSeatId);
	void			RemoveFromVehicle(EntityId actorId);
	bool			IsCharOnScreen(EntityId actorId);
	bool			DoesExist(EntityId actorId) { return m_bActive[actorId]; };
	unsigned int	GetScriptingHandle(EntityId actorId);
	void			ForceAnimation(EntityId actorId, const char * szGroup, const char * szAnim);
	float	        GetHealth(EntityId actorId);
	float			GetArmour(EntityId actorId);
};
