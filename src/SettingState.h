#pragma once
#include "IState.h"
#include "App.h"

namespace FS
{
	class SettingState : public IState
	{
	private:
		GameDataRef m_data;

	public:
		SettingState(GameDataRef data);
		~SettingState();

		//IState Function
		virtual void VInit();
		virtual void VUpdate(float dt);
		virtual void VResume();
		virtual void VPause();
		virtual void VExit();
	};
}
