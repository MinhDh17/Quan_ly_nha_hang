#pragma once
#include <string>
using namespace std;

struct Mon_An {
	int stt;
	string Ten_mon;
	double gia;
};

//Hóa đơn
struct Node_Mon_An {
	int day;
	int month;
	int year;
	Mon_An mon_an;
	int stt_list;
	Node_Mon_An* next;
	int so_luong;
};

typedef Node_Mon_An* Food_List;

void Init_Food_List(Food_List& L); //Khởi tạo danh sách món ăn
bool IsEmpty(Food_List L); //Kiểm tra rỗng

Node_Mon_An* Search_Ten(Food_List& L, string ten); //Tìm kiếm theo tên món
Node_Mon_An* Search_STT_list(Food_List& L, int stt); // Tìm kiếm theo stt

//Kiểm tra ngày tháng năm
bool Check_Date_Valid(int day, int month, int year);
//Thêm món 
void InsertLast(Food_List& L, Mon_An x, int so_luong, int& stt, int day, int month, int year);
void Add(Food_List& L);

void Display(Food_List L); //Hiển thị danh sách

void Delete(Food_List& L, Node_Mon_An* P); //xóa món trong danh sách

void Change(Food_List& L, int stt, int soluong_change); //sửa món

void Sort(Food_List& L); //sắp xếp theo giá tiền

long long Cal_Price(Food_List L); //tính tiền