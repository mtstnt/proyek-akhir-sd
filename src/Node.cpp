#include "Node.h"
#include "DirectoryTree.h"

void Directory::deleteChild(Node * node)
{
	for (int i = 0; i < children.size(); i++) {
		if (children[i] == node) {
			if (children[i]->checkType() == Type::Directory) {
				Directory* childAsDir = children[i]->as<Directory*>();
				for (int j = 0; j < childAsDir->getChildren().size(); j++) {
					childAsDir->deleteChild(childAsDir->getChildren()[j]);
				}
			}
			else if (children[i]->checkType() == Type::Virus) {
				auto& ref = treeRef->getVirusesList();

				/*std::cout << "Virus: ";
				std::cout << children[i]->getName() << " ";
				std::cout << children[i]->as<virus*>()->getID() << std::endl;

				std::cout << "Virus List: ";
				for (auto* f : ref) {
					std::cout << f->getID() << " ";
				}
				std::cout << std::endl;*/

				bool found = false;
				for (int j = 0; j < ref.size(); j++) {
					if (ref[j]->getID() == node->as<virus*>()->getID()) {
						ref.erase(ref.begin() + j);
						found = true;
						break;
					}
				}
				if (!found) {
					std::cout << "Not found!\n";
				}
			}
			delete children[i];
			children.erase(children.begin() + i);
			return;
		}
	}
}
