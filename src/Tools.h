#pragma once
#include "Includes.h"
#include "GameInfo.h"

class BaseTool
{
protected:
	GameInfo& info;
	const char* uniqueName;

	// Check apakah skrg bisa diexecute?
	// Tidak sedang diblokir oleh virus.
	bool isAvailable = true;

	// Sedang cooldown sejak penggunaan terakhir.
	int MAX_COOLDOWN = 5;
	int cooldown = 0;

	std::string response;

public:
	BaseTool(GameInfo& info);

	// Check apakah sekarang bisa diexecute tool nya
	virtual bool evaluateConditions();

	// Execute action, di dlm directory treenya GameInfo
	virtual void doAction() = 0;

	void setAvailability(bool _isAvailable);

	void setCooldown(int time);
	void decrementCooldown() { cooldown--; }

	int getCooldown();

	bool getAvailable() const;

	const std::string& getResponse() const {
		return response;
	}
};
