// Sem3Lab1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Ads.h"
#include <iostream>
#include <windows.h>
#include <locale.h>

using namespace std;
/*
ostream & operator<<(ostream & out, char* s)
{
	char buf[512], *p = buf;
	CharToOem(s, buf);
	while (*p)
		out << *p++;
	return out;
}
*/

int main()
{
	vector<Ad> my_ads;
	string input_file;
	cout << "Input filename" << endl;
	cin >> input_file;
	Find_Ads(input_file.c_str(), my_ads);
//	Print_Ads(my_ads);
//	Sort_Ads_By_Price_Downwards(my_ads);
//	Sort_Ads_By_Price_Upwards(my_ads);
//	Sort_Ads_By_Price_Specified_More(my_ads, 5000);
//	Sort_Ads_By_Price_Specified_Less(my_ads, 5000);
//	Sort_Ads_By_Photo_Present(my_ads, 0);
//	Sort_Ads_By_Word_Present(my_ads, "Ad");
	Sort_Ads_By_English_Present(my_ads);
	system("pause");
	return 0;
}

