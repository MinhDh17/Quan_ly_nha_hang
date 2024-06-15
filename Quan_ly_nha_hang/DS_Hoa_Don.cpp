#include <iostream>
#include "DS_Hoa_Don.h"
using namespace std;

int stt_hoa_don_list = 1;

void InitList_Hoa_Don(Hoa_Don_List& H) {
	H = NULL;
}

bool IsEmpty_Hoa_Don(Hoa_Don_List H) {
	return H == NULL;
}

void Insert_Last_Hoa_Don(Hoa_Don_List& H, Food_List L) {
	Node_Hoa_Don* Q = new Node_Hoa_Don;
	Q->hoa_don = L;
	Q->stt_hoa_don_list = stt_hoa_don_list;
	Q->next = NULL;

	if (IsEmpty_Hoa_Don(H)) {
		H = Q;
	}
	else {
		Node_Hoa_Don* P = H;
		while (P->next != NULL) {
			P = P->next;
		}
		P->next = Q;
	}
	stt_hoa_don_list++;
}

void Display_Hoa_Don_List(Hoa_Don_List H) {
	if (IsEmpty_Hoa_Don(H)) {
		cout << "Danh sach hoa don trong!" << endl;
		return;
	}
	Node_Hoa_Don* P = H;
	while (P != NULL) {
		cout << "HOA DON " << P->stt_hoa_don_list << endl;
		Display(P->hoa_don);
		P = P->next;
	}
}

Node_Hoa_Don* Search_Stt_Hoa_Don_List(Hoa_Don_List& H, int k) {
	Node_Hoa_Don* P = H;
	while (P != NULL) {
		if (P->stt_hoa_don_list == k) return P;
		else P = P->next;
	}
	return NULL;
}

double Cal_Price_Day(Hoa_Don_List H, int day, int month, int year) {
	double sum = 0;
	Node_Hoa_Don* P = H;
	while (P != NULL) {
		Node_Mon_An* T = P->hoa_don;
		while (T != NULL) {
			if (T->day == day && T->month == month && T->year == year) {
				sum += T->mon_an.gia * T->so_luong;
			}
			T = T->next;
		}
		P = P->next;
	}
	return sum;
}

void Add_Existing_Bill(Hoa_Don_List& H, int stt_hoa_don) {
	Node_Hoa_Don* P = Search_Stt_Hoa_Don_List(H, stt_hoa_don);
	if (P != NULL) {
		Food_List L = P->hoa_don;
		string x;
		int choose;

		Mon_An Menu[10] = {
				{ 1, "Bun dau", 40000 },
				{ 2, "Bun cha", 40000 },
				{ 3, "Com rang", 35000 },
				{ 4, "Nem nuong", 35000 },
				{ 5, "Com tam", 45000 },
				{ 6, "Xoi", 25000 },
				{ 7, "Banh mi", 20000 },
				{ 8, "Pho bo", 35000 },
				{ 9, "Bun ca", 35000 },
				{ 10, "Bun bo hue", 40000 },
		};

		int count = 0;
		Node_Mon_An* C = L;
		while (C != NULL) {
			count++;
			C = C->next;
		}
		int count_list = count + 1;
		do {
			cout << "Nhap stt mon an ban muon them: ";
			cin >> choose;

			bool found = false;
			Mon_An Food;
			for (int i = 0; i < 10; i++) {
				if (Menu[i].stt == choose) {
					Food = Menu[i];
					found = true;
					break;
				}
			}

			if (found) {
				int soluong;
				cout << "Nhap so luong ban muon them: ";
				cin >> soluong;
				InsertLast(L, Food, soluong, count_list, P->hoa_don->day, P->hoa_don->month, P->hoa_don->year);
			}
			else {
				cout << "Khong co mon an nay!" << endl;
			}
			cout << "Ban co muon them mon an khac khong? (Co/Khong): ";
			cin >> x;
		} while (x == "Co" || x == "co");
	}
	else {
		cout << "Khong tim thay hoa don voi so thu tu nay." << endl;
	}
}

void Delete_Hoa_Don(Hoa_Don_List& H, Node_Hoa_Don* P) {
	if (IsEmpty_Hoa_Don(H)) {
		cout << "Danh sach hoa don trong!";
		return;
	}

	if (H == P && P->next == NULL) {
		//ds chỉ có 1 phần tử
		H = NULL;
		delete P;
	}
	else {
		if (H == P) {
			//P là nút đầu tiên
			H = P->next;
			delete P;
		}
		else {
			Node_Hoa_Don* R = H;
			while (R->next != P) R = R->next;
			R->next = P->next;
			delete P;
		}
	}

	Node_Hoa_Don* C = H;
	int new_stt_list = 1;
	while (C != NULL) {
		C->stt_hoa_don_list = new_stt_list;
		new_stt_list++;
		C = C->next;
	}
}

void Export(Hoa_Don_List& H, const string& file_name) {
	ofstream file(file_name);
	if (!file.is_open()) {
		cout << "Không thể mở file để ghi dữ liệu!" << endl;
		return;
	}

	// Ghi tiêu đề của các cột
	file << "STT Hoa Don,Ngay,Thang,Nam,STT Mon An,Ten Mon An,Gia,So Luong\n";

	Node_Hoa_Don* currentHoaDon = H;
	while (currentHoaDon != NULL) {
		Node_Mon_An* currentMonAn = currentHoaDon->hoa_don;

		file << currentHoaDon->stt_hoa_don_list << ","
			<< currentMonAn->day << ","
			<< currentMonAn->month << ","
			<< currentMonAn->year << "\n";
		while (currentMonAn != NULL) {
			file << ",,,,"
				<< currentMonAn->stt_list << ","
				<< currentMonAn->mon_an.Ten_mon << ","
				<< currentMonAn->mon_an.gia << ","
				<< currentMonAn->so_luong << "\n";

			currentMonAn = currentMonAn->next;
		}
		file << "Tong tien:," << Cal_Price(currentHoaDon->hoa_don) << "\n\n";
		currentHoaDon = currentHoaDon->next;
	}

	file.close();
	cout << "Du lieu da xuat ra file " << file_name << " thanh cong!\n";
}