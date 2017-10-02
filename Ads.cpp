#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <ctype.h>
#include <algorithm>

#include "Ads.h"

using namespace std;


Ad::Ad()
{
	_title = "";
	_link = "";
	_price = 0;
	_is_photo_present = 0;
}

Ad::~Ad()
{
}

Ad::Ad(string title, string link, double price, bool is_photo_present)
{
	_title = title;
	_link = link;
	_price = price;
	_is_photo_present = is_photo_present;
}

const string& Ad::Get_Title()
{
	return _title;
}

const string& Ad::Get_Link()
{
	return _link;
}

const double& Ad::Get_Price()
{
	return _price;
}

const bool& Ad::Get_Photo_Presence()
{
	return _is_photo_present;
}

const string item_desc_start = "<div class=\"item item_table clearfix js-catalog-item-enum";
const string item_title = "<h3 class=\"title item-description-title\">";
const string item_photo = "<img src=\"";
const string item_price = "</h3> <div class=\"about\">";

void Find_Ads(const char* input_file, vector<Ad>& Adds_to_find)
{
	cout << item_desc_start << endl;
	cout << item_title << endl;
	cout << item_photo << endl;
	cout << item_price << endl;
	string buf_line;
	string title = "";
	string link = "";
	double price = 0;
	bool is_photo_present = 0;
	bool checked_for_photo = 0;
	bool title_var = 0;
	bool price_var = 0;
	bool checked_for_price = 0;
	string::size_type found;

	ifstream parsing_file(input_file);
	if (parsing_file.is_open())
		cout << "File successfully open" << endl;
	else
		cout << "Error opening file" << endl;
	
	while (getline(parsing_file, buf_line))
	{
/*		if ((checked_for_price == 1) && (checked_for_photo == 1) && (link != "") && (title != ""))
		{
			Adds_to_find.emplace_back(title, link, price, is_photo_present);
			cout << "The title is \"" << title << "\"" << endl;
			cout << "		The link is \"" << link << "\"" << endl;
			if (price == 1)
				cout << "		There is a photo" << endl;
			else
				cout << "		There isn't a photo" << endl;
			cout << "		The price is \"" << is_photo_present << "\"" << endl << endl << endl;
		}
*/		
		if (title_var == 1) //this checks the result of looking for the item title description(moved on top for optimization purposes)
		{
			title = buf_line;
			while (title.find("&quot;") != string::npos)
			{
				title.erase(title.find("&quot;"), 6);
			}
			title_var = 0;
			continue;
		}

		if (price_var == 1) //this checks the result of looking for the item price description(moved on top for optimization purposes)
		{
			string buf_string = "";
			for (auto it = buf_line.begin(); it != (buf_line.end() - 2); ++it)
			{
				if (*it == '.')
					break;
				if (isdigit((unsigned char)*it))
				{
					buf_string += *it;
				}
			}
 			price = atof(buf_string.c_str());
			price_var = 0;
			checked_for_price = 1;
			continue;
		}

		found = buf_line.find(item_desc_start);
		if (found != string::npos)
		{
			checked_for_photo = 1;
			if ((checked_for_price == 1) && (checked_for_photo == 1) && (link != "") && (title != ""))
			{
				Adds_to_find.emplace_back(title, link, price, is_photo_present);
			}
			title = "";
			link = "";
			price = 0;
			is_photo_present = 0;
			checked_for_photo = 0;
			checked_for_price = 0;
			continue;
		}
		
		found = buf_line.find(item_title);
		if (found != string::npos)
		{
			title_var = 1;
			found = buf_line.find_first_of('/');
			for (auto it = buf_line.begin(); it != buf_line.end(); ++it)
			{
				if (*(it + found) != '"')
					link += *(it + found);
				else
					break;
			}
			continue;
		}
		
		found = buf_line.find(item_photo);
		if (found != string::npos)
		{
			checked_for_photo = 1;
			is_photo_present = 1;
			continue;
		}
		
		found = buf_line.find(item_price);
		if (found != string::npos)
		{
			price_var = 1;
			continue;
		}
	}
	if ((checked_for_price == 1) && (link != "") && (title != ""))
	{
		Adds_to_find.emplace_back(title, link, price, is_photo_present);
	}
	parsing_file.close();
}

/*vector<Ad> Sort_Ads_By_Price(vector<Ad> ads_for_sorting)
{
	return 
}*/
void Print_Ad(Ad ad)
{
	cout << "The title is \"" << ad.Get_Title() << " \"" << endl;
	cout << "		The link is \"" << ad.Get_Link() << "\"" << endl;
	if (ad.Get_Photo_Presence() == 1)
		cout << "		There is a photo" << endl;
	else
		cout << "		There isn't a photo" << endl;
	cout << "		The price is \"" << ad.Get_Price() << "\"" << endl << endl << endl;
}
void Print_Ads(vector<Ad> ads)
{
	for(auto it = ads.begin(); it != ads.end(); ++it)
	{
		Print_Ad(*it);
	}
}

bool downwards( Ad ad1, Ad ad2)
{
	return ad1.Get_Price() < ad2.Get_Price();
}

bool upwards(Ad ad1, Ad ad2)
{
	return ad1.Get_Price() > ad2.Get_Price();
}

void Sort_Ads_By_Price_Downwards(vector<Ad> ads)
{
	sort(ads.begin(), ads.end(), downwards);
	Print_Ads(ads);
}

void Sort_Ads_By_Price_Upwards(vector<Ad> ads)
{
	sort(ads.begin(), ads.end(), upwards);
	Print_Ads(ads);
}

void Sort_Ads_By_Price_Specified_More(vector<Ad> ads, double price_specified)
{
	for (auto it = ads.begin(); it != ads.end(); ++it)
	{
		if (it->Get_Price() >= price_specified)
			Print_Ad(*it);
	}
}

void Sort_Ads_By_Price_Specified_Less(vector<Ad> ads, double price_specified)
{
	for (auto it = ads.begin(); it != ads.end(); ++it)
	{
		if (it->Get_Price() <= price_specified)
			Print_Ad(*it);
	}
}

void Sort_Ads_By_Photo_Present(vector<Ad> ads, bool photo_requirement)
{
	for (auto it = ads.begin(); it != ads.end(); ++it)
	{
		if (it->Get_Photo_Presence() == photo_requirement)
			Print_Ad(*it);
	}
}

void Sort_Ads_By_Word_Present(vector<Ad> ads, string word_requirement)
{
	for (auto it = ads.begin(); it != ads.end(); ++it)
	{
		if ((it->Get_Title()).find(word_requirement) != string::npos)
			Print_Ad(*it);
	}
}

void Sort_Ads_By_English_Present(vector<Ad> ads)
{
	for (auto it = ads.begin(); it != ads.end(); ++it)
	{
		if ((it->Get_Title()).find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz") != std::string::npos)
			Print_Ad(*it);
	}
}
