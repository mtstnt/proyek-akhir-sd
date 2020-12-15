#pragma once
#include "Includes.h"
#include "Commands.h"


class BaseTool
{
protected:
	GameInfo& info;
	const char* uniqueName;

	// Check apakah skrg bisa diexecute?
	// Tidak sedang diblokir oleh virus.
	bool isAvailable = true;

	// Sedang cooldown sejak penggunaan terakhir.
	unsigned int MAX_COOLDOWN;
	unsigned int cooldown = 0;

public:
	BaseTool(GameInfo& info) : info(info) {}

	// Check apakah sekarang bisa diexecute tool nya
	virtual bool evaluateConditions() {
		if (!isAvailable) return false;
		if (cooldown > 0) return false;

		return true;
	}

	// Execute action, di dlm directory treenya GameInfo
	virtual void doAction() = 0;

	void setAvailability(bool _isAvailable) {
		isAvailable = _isAvailable;
	}

	void restartCooldown() { cooldown = MAX_COOLDOWN; }

	int getCooldown() { return cooldown; }

	bool getAvailable() const { return isAvailable;  }
};

class ToolDetectVirus : public BaseTool
{
protected:
	const char* uniqueName = "detector";

public:
	ToolDetectVirus(GameInfo& info) : BaseTool(info) {}

	void doAction() override {
		
	}
};

