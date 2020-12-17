#include"Virus.h"
#include"Tools.cpp"

// parent virus
virus::virus() {
	
}
void virus::moveToFolder() {
	auto sibling = ((Directory*)this->parent)->getChildren();
	if (sibling.size() == 1)
	{
		
	}
}
void virus::deleteFile() {//manggil deleteChild()
	int random = rand() % ((Directory*)this->parent)->getChildren().size();
	//TBC
	while (1)
	{
		if (random == id)
		{
			continue;
		}
		else
		{
			break;
		}
	}
	//Kalau yg kedelete parent child nya gimana?
	((Directory*)this->parent)->deleteChild(random);
}
void virus::updateVirus() {
	//changeName();
}

void virus::changeName() {
	this->name = "Bobi";
}

void virus::changeFilename()
{
}
