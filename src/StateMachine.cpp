#include "StateMachine.h"

namespace FS
{
	void FS::StateMachine::AddState(StateRef newState, bool isReplacing)
	{
		m_isAdding = true;
		m_isReplacing = isReplacing;

		m_newState = std::move(newState);
	}

	void FS::StateMachine::RemoveState()
	{
		m_isRemoving = true;
	}

	void FS::StateMachine::ProcessStateChanges()
	{
		//std::cout << R"(Size)" <<m_states.size() << std::endl;
		if (m_isRemoving && !m_states.empty())
		{
			m_states.pop();
			if (!m_states.empty())
			{
				m_states.top()->VResume();
			}
			else
			{
				m_stackEmpty = true;
			}
			m_isRemoving = false;
		}

		if (m_isAdding)
		{

			if (!m_states.empty())
			{
				if (m_isReplacing)
				{
					m_states.pop();
				}
				else
				{
					m_states.top()->VPause();
				}
			}

			m_states.push(std::move(m_newState));
			m_states.top()->VInit();
			m_isAdding = false;
		}
	}

	StateRef& FS::StateMachine::GetActiveState()
	{
		return m_states.top();
	}
	bool StateMachine::StackEmpty()
	{
		return m_stackEmpty;
	}
	int StateMachine::StackAllocated()
	{
		return m_states.size();
	}
}