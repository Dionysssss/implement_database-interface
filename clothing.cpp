#include <sstream>
#include <iomanip>
#include "util.h"
#include "clothing.h"

using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, const string Size, const string Brand) : 
Product(category, name, price, qty),
size_(Size),
brand_(Brand)
{
	setKeyword();
}

Clothing::~Clothing()
{

}

/**
	* Returns the appropriate keywords that this product should be associated with
	*/
std::set<std::string> Clothing::  keywords() const
{
	return keywords_;
}

/**
	* Allows for a more detailed search beyond simple keywords
	*/
bool Clothing::isMatch(vector<string>& searchTerms) const
{
		vector<string>::iterator it;
		for(it=searchTerms.begin();
				it!=searchTerms.end();
				++it)
				{
					if(keywords_.find(*it)==keywords_.end())				//if some searchTerms are not included in the keywords_ return false
					return false;
				}

		return true;
}

/**
	* Returns a string to display the product info for hits of the search
	*/
string Clothing::displayString() const
{
		//string display_out=new string;
		//formate?
	string out;
		out+=name_;
		out+="\n";
		out+="Size: "+size_+" Brand: "+brand_+"\n";
		out+=to_string(price_)+" "+to_string(qty_)+" left";

	

		return out;

}

string Clothing::displayCart() const
{
		string out;    
		out+="name: ";
    out+=name_;
    out+="\n";
    out+="info: ";
    out+="Size: "+size_+" Brand: "+brand_+"\n";
    out+="stock: ";
    out+=qty_;
    out+="price: ";
    out+=price_;
    return out;
}

/**
	* Outputs the product info in the database format
	*/
void Clothing:: dump(std::ostream& os) const
{
	os<<"clothing"<<endl;
	os<<name_<<endl;
	os<<price_<<endl;
	os<<qty_<<endl;
	os<<size_<<endl;
	os<<brand_<<endl;
}

/**
	*Accessors
	*/
string Clothing::getSize() const
{
	return size_;
}

string Clothing::getBrand() const
{
	return brand_;
}

/*
**helper function that get the keyword of the book and set the keyword set
*/
void Clothing::setKeyword()
{
	keywords_.insert(category_);
	keywords_.insert(convToLower(size_));
	set<string> T_brand=parseStringToWords(convToLower(brand_));
	keywords_.insert(T_brand.begin(),T_brand.end());
	set<string> T_name=parseStringToWords(convToLower(name_));
	keywords_.insert(T_name.begin(),T_name.end());

}
