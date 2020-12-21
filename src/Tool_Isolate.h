#pragma once

#include "Tools.h"

class Tool_Isolate
	: public BaseTool
{
private:
	int isolationDuration = 5;
	const std::string& parameter;

public:
	Tool_Isolate(GameInfo& info, const std::string& nodeName);

	bool evaluateConditions() override;
	void doAction() override;
};