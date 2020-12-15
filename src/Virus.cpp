#include"Virus.h"
#include"Tools.cpp"

// parent virus
virus::virus() {
	
}
void virus::moveToFolder() {

}
void virus::deleteFile() {//manggil deleteChild()
	((Directory*)this->parent)->deleteChild(rand() % 9);
}
void virus::updateVirus() {

}

//// virus jenis 1
//V1::V1() {
//
//}
//void V1::moveToFolder() {
//
//}
//void V1::deleteFile() {
//
//}
//
//// virus jenis 2
//V2::V2() {
//
//}
//void V2::moveToFolder() {
//
//}
//void V2::deleteFile() {
//
//}
//
//// virus jenis 2
//V3::V3() {
//
//}
//void V3::moveToFolder() {
//
//}
//void V3::deleteFile() {
//
//}