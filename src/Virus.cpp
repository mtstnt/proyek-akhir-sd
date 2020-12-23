#include "Includes.h"
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

	auto& sibling = this->getParent()->as<Directory*>()->getChildren();

	// Jangan sampai delete diri sendiri
	int random;
	do {
		random = rand() % sibling.size();
	} while (sibling[random] == this);

	Directory* parent_as_directory = this->parent->as<Directory*>();

	switch (sibling.at(random)->checkType())
	{
		// Kalau type file, delete langsung
	case Type::File:
		parent_as_directory->deleteChild(sibling.at(random));
	break;
		// Kalau directory, maka masuk ke directory itu
	case Type::Directory:
	{
		Directory* found_directory = sibling.at(random)->as<Directory*>();

		if (found_directory->getChildren().size() == 0) {
			parent_as_directory->deleteChild(found_directory);
			break;
		}

		found_directory->getChildren().push_back(this);

		// Delete diri sendiri di vector child directory lama.
		for (int i = 0; i < parent_as_directory->getChildren().size(); i++) {
			if (this == parent_as_directory->getChildren()[i]) {
				parent_as_directory->getChildren().erase(
					parent_as_directory->getChildren().begin() + i
				);
				break;
			}
		}

		this->setParent(found_directory);
	}
	break;
	case Type::Virus: break;
	default: 
		// Shouldnt be here
		assert(0);
		break;
	}
}

void virus::updateVirus() {
	int random = rand() % 5;
	switch (random)
	{
	case 0:
	case 1:
	case 3:
	case 4:
		deleteFile();
		break;
	case 2:
		changeName();
		break;
	default:
		// Shouldnt be here
		assert(0);
		break;
	}
}

void virus::changeName() {
	string bahan = "BeliAyamMCDdapeTbURGERkingTAPIsaOSWendYYrAsaKentUCKY";
	int length = bahan.length();
	int panjang_string_baru = rand() % 7;
	int offset = rand() % (length - panjang_string_baru);
	string substring = bahan.substr(offset, panjang_string_baru);
	this->name = substring + ".exe";
}
