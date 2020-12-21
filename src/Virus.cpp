#include "Virus.h"

// parent virus
virus::virus() {

}

void virus::moveToFolder() {
	
}

void virus::deleteFile() {//manggil deleteChild()
	if (this->parent->as<Directory*>()->getChildren().size() == 1) {
		return;
	}
	
	auto sibling = this->getParent()->as<Directory*>()->getChildren();

	// Jangan sampai delete diri sendiri
	int random;
	do {
		random = rand() % sibling.size();
	} while (sibling[random] == this);

	if (sibling.at(random)->checkType() != Type::Virus)
	{
		/*std::cout << this->getName() << " deletes " << sibling.at(random)->getName() << "\n";*/
		this->parent->as<Directory*>()->deleteChild(sibling.at(random));
	}

	/*std::cout << "Virus: " << this->getName() << " " << this->getParent()->getName() << "\n";*/

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
