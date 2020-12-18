#pragma once
#include "IState.h"
#include "App.h"

namespace FS
{
	class CreditState : public IState
	{
	private:
		GameDataRef m_data;
	public:
		CreditState(GameDataRef data);
		~CreditState();

		//IState Function
		virtual void VInit();
		virtual void VUpdate(float dt);
		virtual void VResume();
		virtual void VPause();
		virtual void VExit();
	};
}



