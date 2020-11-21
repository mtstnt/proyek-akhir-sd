#pragma once
#include <memory>
#include <stack>

#include "IState.h"

namespace FS
{
	typedef std::unique_ptr<IState> StateRef;

	class StateMachine
	{
	private:
		std::stack<StateRef> m_states;
		StateRef m_newState;

		bool m_isAdding = false;
		bool m_isRemoving = false;
		bool m_isReplacing = false;

		bool m_stackEmpty = false;
	public:
		StateMachine() {}
		~StateMachine() {}

		void AddState(StateRef newState, bool isReplacing = false);
		void RemoveState();
		void ProcessStateChanges();

		StateRef& GetActiveState();
		bool StackEmpty();
		int StackAllocated();
	};
}

