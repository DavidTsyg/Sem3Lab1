#pragma once
#include <string>
#include <vector>

using namespace std;

class Ad
{
private:
	string _title;
	string _link;
	double _price;
	bool _is_photo_present;

public:
	const string& Get_Title();
	const string& Get_Link();
	const double& Get_Price();
	const bool& Get_Photo_Presence();
	Ad(string title, string link, double price, bool is_photo_present);
	Ad();
	~Ad();
};
void Find_Ads(const char* input_file, vector<Ad>& Adds_to_find);
void Print_Ads(vector<Ad> ads);
bool downwards(Ad ad1, Ad ad2);
bool upwards(Ad ad1, Ad ad2);
void Sort_Ads_By_Price_Downwards(vector<Ad> ads);
void Sort_Ads_By_Price_Upwards(vector<Ad> ads);
void Sort_Ads_By_Price_Specified_More(vector<Ad> ads, double price_specified);
void Sort_Ads_By_Price_Specified_Less(vector<Ad> ads, double price_specified);
void Sort_Ads_By_Photo_Present(vector<Ad> ads, bool photo_requirement);
void Sort_Ads_By_Word_Present(vector<Ad> ads, string word_requirement);
void Sort_Ads_By_English_Present(vector<Ad> ads);