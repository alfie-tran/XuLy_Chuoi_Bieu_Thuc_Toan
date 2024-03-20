// XuLy_Chuoi_Bieu_Thuc_Toan.cpp :
//

#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
using namespace std;

// Hàm tô màu.
void textcolor(int x)
{
	HANDLE mau;
	mau = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau, x);
}

void XuatVecter(vector<string>a) {
	for (int i = 0; i < a.size() - 1; i++)
	{
		cout << a[i] << " ";
	}
	cout << a[a.size() - 1] << endl;
}


string KetQuaBieuThucKhongNgoac(string s) {
	vector<string>a;
	//cach 2: dung ham strtok
	char* temp;
	char* p = strtok_s((char*)s.c_str(), " ", &temp);
	while (p != NULL) {
		a.push_back(p); //push_back: tu dong gia han phan tu vector va truyen p vao
		p = strtok_s(NULL, " ", &temp);
	}
	for (int i = 1; i < a.size(); i += 2)
	{
		// * / trước, + - sau
		if (a[i] == "*" || a[i] == "/") {
			/*cout << "\n\n";
			for (int j = 0; j < a.size(); j++)
			{
				if (j >= i - 1 && j <= i + 1)
					textcolor(14);
				cout << a[j] << " ";

				textcolor(7);
			}*/
			float x = stof(a[i - 1]);
			float y = stof(a[i + 1]);
			float ketqua;
			if (a[i] == "*") {
				ketqua = x * y;
			}
			else if (a[i] == "/") {
				ketqua = x / y;
			}

			//chuyen so --> chuoi
			a[i - 1] = to_string(ketqua);
			//xóa a[i] và a[i+1]
			a.erase(a.begin() + i);
			a.erase(a.begin() + i); // do sau lần xóa vị trí i lúc này i+1 đc lùi lại thành i nên ko đc xóa i+1 mà phải xóa i

			/*cout << endl;
			for (int j = 0; j < a.size(); j++)
			{
				if(j == i - 1)
					textcolor(14);
				cout << a[j] << " ";

				textcolor(7);
			}*/
			i -= 2; //phải lùi về 2 cho biến i bởi sau khi xóa thì index đã bị thay đổi cho nên nếu ko lùi sẽ bị bỏ qua 1 số phép toán

			//XuatVecter(a);
		}
	}
	for (int i = 1; i < a.size(); i += 2)
	{
		if (a[i] == "+" || a[i] == "-") {
			/*cout << "\n\n";
			for (int j = 0; j < a.size(); j++)
			{
				if (j >= i - 1 && j <= i + 1)
					textcolor(14);
				cout << a[j] << " ";
				textcolor(7);
			}*/
			float x = stof(a[i - 1]);
			float y = stof(a[i + 1]);
			float kq;
			if (a[i] == "+") {
				kq = x + y;
			}
			else if (a[i] == "-") {
				kq = x - y;
			}
			a[i - 1] = to_string(kq);
			a.erase(a.begin() + i);
			a.erase(a.begin() + i);

			//cout << endl;
			//for (int j = 0; j < a.size(); j++)
			//{				
			//	if (j == i - 1) {
			//		textcolor(14); //màu vàng
			//	}
			//	cout << a[j] << " ";
			//	textcolor(7); //trở lại bình thường
			//}
			i -= 2;

			//XuatVecter(a);
		}
	}
	return a[0];
}

string TinhKetQuaBieuThucToanHoc(string s) {
	//chủ động thêm vào dấu mở ngoặc ở đầu và đóng ngoặc ở cuối b.thức toán
	s.insert(0, "(");
	s.insert(s.length(), ")"); // <=> s += ")"
	vector<int> a;
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] == '(')
			a.push_back(i); // push_back: them phan tu cuoi cung o vector a
		else if (s[i] == ')') {
			int end = i;
			int start = a[a.size() - 1];
			//cout << "start = " << start << " end = " << end << endl;

			string bieuthuctrongngoac = s.substr(start + 1, end - 1 - start); //end - 1 - (start + 1) + 1
			string ketqua = KetQuaBieuThucKhongNgoac(bieuthuctrongngoac);
			s.erase(start, end - start + 1); //xoa doan bieu thuc có ngoac da tinh ra ket qua 
			s.insert(start, ketqua);

			i = start + ketqua.length() - 1;

			a.erase(a.begin() + a.size() - 1);
		}
	}
	return s;
}
int main()
{
	string s = "1 + 2 * ((3 - 4) / 5)";
	//string s = "1 - 2 + 3 / 4 * (5 - 6 * 7) / 2 + (9 - 1 * 8) + 5";
	//string s = "90 - (5 * 8 / (4 + 6) - 3 / (2 + 1) * 23) / 100";
	cout << "Bieu thuc can tinh s = " << s << endl;

	string kq = TinhKetQuaBieuThucToanHoc(s);
	cout << "Ket qua s = " << kq << endl;




	//textcolor(7); //màu trở lại bt
	/* cách tra mã màu dùng vòng for
	textcolor(i)
	*/

	return 0;
}
