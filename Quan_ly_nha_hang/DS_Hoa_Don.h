#pragma once
#include "DS_Mon_An.h"
#include <fstream>
using namespace std;

struct Node_Hoa_Don {
	int stt_hoa_don_list;
	Food_List hoa_don;
	Node_Hoa_Don* next;
};

typedef Node_Hoa_Don* Hoa_Don_List;

//Khởi tạo
void InitList_Hoa_Don(Hoa_Don_List& H);
//Kiểm tra rỗng
bool IsEmpty_Hoa_Don(Hoa_Don_List H);
//Thêm
void Insert_Last_Hoa_Don(Hoa_Don_List& H, Food_List L);
//in
void Display_Hoa_Don_List(Hoa_Don_List H);
//tìm kiếm hóa đơn theo stt
Node_Hoa_Don* Search_Stt_Hoa_Don_List(Hoa_Don_List& H, int k);
//tính doanh thu trong ngày
long long Cal_Price_Day(Hoa_Don_List H, int day, int month, int year);
//thêm món vào hóa đơn có sẵn
void Add_Existing_Bill(Hoa_Don_List& H, int stt_hoa_don);
//Xóa hóa đơn
void Delete_Hoa_Don(Hoa_Don_List& H, Node_Hoa_Don* P);

//excel
void Export(Hoa_Don_List& H, const string& file_name);