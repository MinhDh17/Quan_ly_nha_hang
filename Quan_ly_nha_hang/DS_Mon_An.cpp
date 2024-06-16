#include "DS_Mon_An.h"
#include "DS_Hoa_Don.h"
#include <iostream>
#include <iomanip>
using namespace std;


void Init_Food_List(Food_List& L) {
	L = NULL;
}

bool IsEmpty(Food_List L) {
	return L == NULL;
}

Node_Mon_An* Search_Ten(Food_List& L, string ten) {
	Node_Mon_An* P = L;
	while (P != NULL) {
		if (P->mon_an.Ten_mon == ten) return P;
		else P = P->next;
	}
	return 0;
}

Node_Mon_An* Search_STT_list(Food_List& L, int stt) {
	Node_Mon_An* P = L;
	while (P != NULL) {
		if (P->stt_list == stt) return P;
		else P = P->next;
	}
	return 0;
}

bool Check_Date_Valid(int day, int month, int year) {
	if (year < 0) return false;
	if (month < 1 || month > 12) return false;

	int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	//năm nhuận
	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
		days[1] = 29;
	}

	if (day < 1 || day > days[month - 1]) return false;

	return true;
}

void InsertLast(Food_List& L, Mon_An x, int so_luong, int& stt, int day, int month, int year) {
	//Kiểm tra trùng lặp
	Node_Mon_An* E = Search_Ten(L, x.Ten_mon);

	if (E != NULL) {
		E->so_luong += so_luong;
	}
	else {
		Node_Mon_An* Q = new Node_Mon_An;
		Q->mon_an = x;
		Q->so_luong = so_luong;
		Q->stt_list = stt;
		Q->day = day;
		Q->month = month;
		Q->year = year;
		Q->next = NULL;

		if (IsEmpty(L)) {
			L = Q;
		}
		else {
			Node_Mon_An* P = L;
			while (P->next != NULL) {
				P = P->next;
			}
			P->next = Q;
		}
		stt++;
	}
}

void Add(Food_List& L) {
	string x;
	int choose;
	int day, month, year;

	do {
		cout << "Nhap ngay thang nam tao hoa don (dd mm yyyy): ";
		cin >> day >> month >> year;

		if (!Check_Date_Valid(day, month, year)) {
			cout << "Ngay thang nam khong hop le. Vui long nhap lai!\n";
		}
	} while (!Check_Date_Valid(day, month, year));
	int stt = 1;

	do {
		bool valid_stt = false;
		do {
			cout << "Nhap stt mon an ban muon them: ";
			cin >> choose;

			Mon_An Menu[10] = {
			{ 1, "Bun dau", 40000 },
			{ 2, "Bun cha", 40000 },
			{ 3, "Com rang", 35000 },
			{ 4, "Nem nuong", 35000 },
			{ 5, "Com tam", 45000},
			{ 6, "Xoi", 25000},
			{ 7, "Banh mi", 20000},
			{ 8, "Pho bo", 35000},
			{ 9, "Bun ca", 35000},
			{ 10, "Bun bo hue", 40000},
			};

			bool found = 0;
			Mon_An Food;
			for (int i = 0; i < 10; i++) {
				if (Menu[i].stt == choose) {
					Food = Menu[i];
					found = true;
					break;
				}
			}

			if (found) {
				valid_stt = true;
				int soluong;
				cout << "Nhap so luong ban muon them: ";
				cin >> soluong;
				InsertLast(L, Food, soluong, stt, day, month, year);
			}
			else {
				cout << "Khong co mon an voi stt nay!" << endl;
			}
		} while (!valid_stt);

		do {
			cout << "Ban co muon them mon an khac khong? (Co/Khong): ";
			cin >> x;

			if (x != "Co" && x != "co" && x != "Khong" && x != "khong") {
				cout << "Chi duoc nhap 'Co' hoac 'Khong'! Vui long nhap lai.\n";
			}
		} while (x != "Co" && x != "co" && x != "Khong" && x != "khong");


	} while (x == "Co" || x == "co");
}

void Display(Food_List L) {
	if (IsEmpty(L)) {
		cout << "Danh sach mon an trong!" << endl;
		return;
	}
	Node_Mon_An* P = L;
	cout << "HOA DON MON AN" << endl;
	cout << "Thoi gian: " << P->day << "/" << P->month << "/" << P->year << endl;
	cout << left << setw(5) << "STT" << setw(20) << "Ten mon an" << setw(10) << "Gia" << setw(10) << "So luong" << endl;

	while (P != NULL) {
		cout << left << setw(5) << P->stt_list << setw(20) << P->mon_an.Ten_mon << setw(10) << P->mon_an.gia << setw(10) << P->so_luong << endl;
		P = P->next;
	}
}

void Delete(Food_List& L, Node_Mon_An* P) {
	string x;
	do {
		if (IsEmpty(L)) cout << "Danh sach rong" << endl;
		if (L == P && P->next == NULL) {
			//ds chỉ có 1 phần tử
			L = NULL;
			delete P;
		}
		else {
			if (L == P) {
				//P là nút đầu tiên
				L = P->next;
				delete P;
			}
			else {
				Node_Mon_An* R = L;
				while (R->next != P) R = R->next;
				R->next = P->next;
				delete P;
			}
		}

		do {
			cout << "Ban co muon xoa them mon an khac khong? (Co/Khong): ";
			cin >> x;

			if (x != "Co" && x != "co" && x != "Khong" && x != "khong") {
				cout << "Chi duoc nhap 'Co' hoac 'Khong'! Vui long nhap lai.\n";
			}
		} while (x != "Co" && x != "co" && x != "Khong" && x != "khong");

		if (x == "Co" || x == "co") {
			int stt;
			cout << "Nhap stt mon an muon xoa: ";
			cin >> stt;
			P = Search_STT_list(L, stt);
			if (P == NULL) {
				cout << "Khong tim thay mon an voi stt nay\n";
				break;
			}
		}
		else {
			break;
		}


	} while (x == "Co" || x == "co");

	//Cập nhật lại stt trong list
	Node_Mon_An* C = L;
	int new_stt_list = 1;
	while (C != NULL) {
		C->stt_list = new_stt_list;
		new_stt_list++;
		C = C->next;
	}
}

void Change(Food_List& L, int stt, int soluong_change) {
	string x;
	do {
		Node_Mon_An* P = Search_STT_list(L, stt);
		if (P != NULL) {
			P->so_luong = soluong_change;
			cout << "Thay doi thanh cong!\n";
		}
		else {
			cout << "Khong co mon an voi stt nay trong danh sach\n";
		}

		do {
			cout << "Ban co muon thay doi mon an nao khac khong? (Co/Khong): ";
			cin >> x;

			if (x != "Co" && x != "co" && x != "Khong" && x != "khong") {
				cout << "Chi duoc nhap 'Co' hoac 'Khong'! Vui long nhap lai.\n";
			}
		} while (x != "Co" && x != "co" && x != "Khong" && x != "khong");

		
		if (x == "Co" || x == "co") {
			cout << "Nhap stt mon an muon thay doi: ";
			cin >> stt;
			cout << "Nhap so luong moi: ";
			cin >> soluong_change;
		}
		else {
			break;
		}
	} while (x == "Co" || x == "co");
}

void Sort(Food_List& L) {
	if (IsEmpty(L)) {
		cout << "Danh sach rong!" << endl;
		return;
	}
	bool swapped = 0;
	Node_Mon_An* ptr1;
	Node_Mon_An* lptr = NULL;

	do {
		swapped = 0;
		ptr1 = L;

		while (ptr1->next != lptr) {
			if (ptr1->mon_an.gia > ptr1->next->mon_an.gia) {
				swap(ptr1->mon_an, ptr1->next->mon_an);
				swap(ptr1->so_luong, ptr1->next->so_luong);
				swapped = true;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	} while (swapped);
	//cập nhật lại stt
	Node_Mon_An* current = L;
	int stt = 1;
	while (current != NULL) {
		current->stt_list = stt++;
		current = current->next;
	}
}

long long Cal_Price(Food_List L) {
	Node_Mon_An* P = L;
	long long tong = 0;
	while (P != NULL) {
		tong += P->mon_an.gia * P->so_luong;
		P = P->next;
	}
	return tong;
}