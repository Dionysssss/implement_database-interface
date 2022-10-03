#include <sstream>
#include <iomanip>
#include "util.h"
#include "movie.h"

#include <iostream>

using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty, const string Genre, const string Rating) : 
Product(category, name, price, qty),
genre_(Genre),
rating_(Rating)
{
	setKeyword();
}

Movie::~Movie()
{

}

/**
	* Returns the appropriate keywords that this product should be associated with
	*/
std::set<std::string> Movie::  keywords() const
{
	return keywords_;
}

/**
	* Allows for a more detailed search beyond simple keywords
	*/
bool Movie::isMatch(vector<string>& searchTerms) const
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
string Movie::displayString() const
{
		//string display_out=new string;
		//formate?
		string out;
		out+=name_;
		out+="\n";
		out+="Genre: "+genre_+" Rating: "+rating_+"\n";
		out+=to_string(price_)+" "+to_string(qty_)+" left";

		return out;

}

/**
	* Outputs the product info in the database format
	*/
void Movie:: dump(std::ostream& os) const
{
	os<<"movie"<<endl;
	os<<name_<<endl;
	os<<price_<<endl;
	os<<qty_<<endl;
	os<<genre_<<endl;
	os<<rating_<<endl;
}

/**
	*Accessors
	*/
string Movie::getGenre() const
{
	return genre_;
}

string Movie::getRating() const
{
	return rating_;
}

/*
**helper function that get the keyword of the book and set the keyword set
*/
void Movie::setKeyword()
{
	keywords_.insert(convToLower(category_));
	keywords_.insert(convToLower(genre_));
	keywords_.insert(convToLower(rating_));
	set<string> T_name=parseStringToWords(convToLower(name_));
	keywords_.insert(T_name.begin(),T_name.end());

}
