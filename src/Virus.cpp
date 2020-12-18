#include "Virus.h"

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
	if (this->parent->as<Directory*>()->getChildren().size() == 0) {
		return;
	}

	int random = rand() % ((Directory*)this->parent)->getChildren().size();
	auto sibling = this->as<Directory*>()->getParent()->as<Directory*>()->getChildren();
	if (sibling.at(random)->checkType() != Type::Virus)
	{
		//std::cout << "File deleted: " << sibling.at(random)->getName() << std::endl;
		((Directory*)this->parent)->deleteChild(random);
	}
	//else
	//{
	//	std::cout << "Unable to delete" << std::endl;
	//}

	//Kalau yg kedelete parent child nya gimana?

}
void virus::updateVirus() {
	/*int random = rand() % 2;
	switch (random)
	{
	case 0:
		deleteFile();
		break;
	case 1:
		changeName();
		break;
	default:
		break;
	}*/
	deleteFile();
}

void virus::changeName() {
	string bahan = "BeliAyamMCDdapeTbURGERkingTAPIsaOSWendYYrAsaKentUCKY";
	int length = bahan.length();
	int panjang_string_baru = rand() % 7;
	int offset = rand() % (length - panjang_string_baru);
	string substring = bahan.substr(offset, panjang_string_baru);
	this->name = substring + ".exe";
}

void virus::changeFilename()
{
}
