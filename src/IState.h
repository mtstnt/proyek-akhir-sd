#pragma once

namespace FS
{
	class IState
	{
	public:
		virtual void VInit() = 0;
		virtual void VUpdate(float dt) = 0;
		virtual void VResume() = 0;
		virtual void VPause() = 0;
		virtual void VExit() = 0;

		virtual ~IState() {}
	};
}