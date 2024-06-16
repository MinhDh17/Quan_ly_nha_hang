#include <iostream>
#include <iomanip>
#include "DS_Mon_An.h"
#include "DS_Hoa_Don.h"
using namespace std;

void Print_Tab_Menu() {
	cout << "*****He thong quan ly nha hang*****\n";
	cout << "(1) Thuc hien goi mon an\n";
	cout << "(2) Them mon an\n";
	cout << "(3) Sua mon an\n";
	cout << "(4) Xoa mon an\n";
	cout << "(5) Sap xep mon an theo gia tien\n";
	cout << "(6) Hien thi hoa don\n";
	cout << "(7) Tinh tien\n";
	cout << "(8) In danh sach cac hoa don\n";
	cout << "(9) Xoa hoa don\n";
	cout << "(10) Tinh doannh thu theo ngay\n";
	cout << "(11) Xuat hoa don ra file excel\n";
	cout << "(12) Thoat chuong trinh\n";
}

int main() {
	Print_Tab_Menu();

	Hoa_Don_List H;
	InitList_Hoa_Don(H);


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

	int So_Mon = sizeof(Menu) / sizeof(Menu[0]);

	cout << "         *****Menu*****\n";
	cout << left << setw(7) << "STT" << setw(15) << "Ten mon an" << right << setw(10) << "Gia\n";
	for (int i = 0; i < So_Mon; i++) {
		cout << left << setw(7) << Menu[i].stt << setw(15) << Menu[i].Ten_mon << right << setw(10) << Menu[i].gia << endl;
	}
	int stt_hoa_don;
	int x;
	while (1) {
		cout << "\nChon yeu cau cua ban: ";
		cin >> x;
		switch (x) {
		case 1: {
			Food_List L;
			Init_Food_List(L);
			Add(L);
			Insert_Last_Hoa_Don(H, L);
			break;
		}
		case 2: {
			cout << "Nhap stt hoa don muon them mon: ";
			cin >> stt_hoa_don;
			if (Search_Stt_Hoa_Don_List(H, stt_hoa_don) != NULL) {
				Add_Existing_Bill(H, stt_hoa_don);
			}
			else {
				cout << "Khong tim thay hoa don voi stt nay!\n";
			}
			break;
		}
		case 3: {
			int stt_change;
			int soluong_change;
			cout << "Nhap stt hoa don muon sua: ";
			cin >> stt_hoa_don;

			if (Search_Stt_Hoa_Don_List(H, stt_hoa_don) != NULL) {
				cout << "Nhap stt mon an muon sua: ";
				cin >> stt_change;
				cout << "Nhap so luong ban muon thay doi: ";
				cin >> soluong_change;
				Change(Search_Stt_Hoa_Don_List(H, stt_hoa_don)->hoa_don, stt_change, soluong_change);
				cout << "Thay doi thanh cong!\n";
			}
			else {
				cout << "Khong tim thay hoa don voi stt nay!\n";
			}
			break;
		}
		case 4: {
			int k;
			cout << "Nhap so thu tu hoa don muon xoa mon an: ";
			cin >> stt_hoa_don;

			if (Search_Stt_Hoa_Don_List(H, stt_hoa_don) != NULL) {
				cout << "Nhap stt mon an muon xoa: ";
				cin >> k;
				Delete(Search_Stt_Hoa_Don_List(H, stt_hoa_don)->hoa_don, Search_STT_list(Search_Stt_Hoa_Don_List(H, stt_hoa_don)->hoa_don, k));
				cout << "Xoa mon thanh cong!\n";
			}
			else {
				cout << "Khong tim thay hoa don voi stt nay!\n";
			}
			break;
		}
		case 5: {
			cout << "Nhap so thu tu hoa don muon sap xep mon an: ";
			cin >> stt_hoa_don;

			if (Search_Stt_Hoa_Don_List(H, stt_hoa_don) != NULL) {
				Sort(Search_Stt_Hoa_Don_List(H, stt_hoa_don)->hoa_don);
				cout << "Sap xep thanh cong!\n";
				Display(Search_Stt_Hoa_Don_List(H, stt_hoa_don)->hoa_don);
			}
			else {
				cout << "Khong tim thay hoa don voi stt nay!\n";
			}
			break;
		}
		case 6: {
			cout << "Nhap so thu tu hoa don muon in: ";
			cin >> stt_hoa_don;

			if (Search_Stt_Hoa_Don_List(H, stt_hoa_don) != NULL) {
				Display(Search_Stt_Hoa_Don_List(H, stt_hoa_don)->hoa_don);
			}
			else {
				cout << "Khong tim thay hoa don voi stt nay!\n";
			}
			break;
		}
		case 7: {
			cout << "Nhap so thu tu hoa don muon tinh tien: ";
			cin >> stt_hoa_don;

			if (Search_Stt_Hoa_Don_List(H, stt_hoa_don) != NULL) {
				cout << "Tong tien: " << Cal_Price(Search_Stt_Hoa_Don_List(H, stt_hoa_don)->hoa_don) << endl;
			}
			else {
				cout << "Khong tim thay hoa don voi stt nay!\n";
			}
			break;
		}
		case 8: {
			if (H != NULL) {
				Display_Hoa_Don_List(H);
			}
			else {
				cout << "Khong co hoa don nao!\n";
			}
			break;
		}
		case 9: {
			cout << "Nhap stt hoa don muon xoa: ";
			cin >> stt_hoa_don;

			if (Search_Stt_Hoa_Don_List(H, stt_hoa_don) != NULL) {
				Delete_Hoa_Don(H, Search_Stt_Hoa_Don_List(H, stt_hoa_don));
				cout << "Xoa thanh cong!\n";
			}
			else {
				cout << "Khong tim thay hoa don voi stt nay!\n";
			}
			break;
		}
		case 10: {
			int day, month, year;
			cout << "Nhap ngay thang nam (dd mm yyyy) muon tinh doanh thu: ";
			cin >> day >> month >> year;
			long long revenue_by_day = Cal_Price_Day(H, day, month, year);
			if (revenue_by_day > 0) {
				cout << "Tong doanh thu ngay " << day << "/" << month << "/" << year << " la: " << Cal_Price_Day(H, day, month, year) << endl;
			}
			break;
		}
		case 11: {
			Export(H, "hoadon.csv");
			break;
		}
		case 12: {
			cout << "Thoat chuong trinh!\n";
			return 0;
		}
		default: {
			cout << "Lua chon khong hop le. Vui long nhap lai!\n";
			break;
		}

		}
	}
	return 0;
}