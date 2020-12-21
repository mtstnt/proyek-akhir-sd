#include "Tools.h"
#include "Commands.h"

BaseTool::BaseTool(GameInfo& info) : info(info) {}

// Check apakah sekarang bisa diexecute tool nya
bool BaseTool::evaluateConditions() 
{
	return isAvailable && cooldown == 0;
}

void BaseTool::setAvailability(bool _isAvailable) 
{
	isAvailable = _isAvailable;
}

void BaseTool::setCooldown(int time)
{
	cooldown = time;
}

int BaseTool::getCooldown() { return cooldown; }

bool BaseTool::getAvailable() const { return isAvailable; }