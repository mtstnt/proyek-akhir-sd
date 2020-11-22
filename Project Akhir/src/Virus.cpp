#include"Virus.h"
#include"Tools.cpp"

// parent virus
virus::virus() {
	turn = false;
}
void virus::moveToFolder() {

}
void virus::deleteFile() {

}
void virus::endTurn() {
	if (!t.getTurn()) { turn = true; }
	else { turn = false; }
}

// virus jenis 1
V1::V1() {

}
void V1::moveToFolder() {

}
void V1::deleteFile() {

}
void V1::endTurn() {

}

// virus jenis 2
V2::V2() {

}
void V2::moveToFolder() {

}
void V2::deleteFile() {

}
void V2::endTurn() {

}

// virus jenis 2
V3::V3() {

}
void V3::moveToFolder() {

}
void V3::deleteFile() {

}
void V3::endTurn() {

}