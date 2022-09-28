#include <sstream>
#include <iomanip>
#include "util.h"
#include "book.h"

using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, const string ISBN, const string Author) : 
Product(category, name, price, qty),
isbn_(ISBN),
author_(Author)
{
	setKeyword();
}

Book::~Book()
{

}

/**
	* Returns the appropriate keywords that this product should be associated with
	*/
std::set<std::string> Book::  keywords() const
{
	return keywords_;
}

/**
	* Allows for a more detailed search beyond simple keywords
	*/
bool Book::isMatch(vector<string>& searchTerms) const
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
string Book::displayString() const
{
		//string display_out=new string;
		//formate?

		string out="keyword hints: ";
		set<string>::iterator it;
		for(it = keywords_.begin();
				it != keywords_.end();
				++it)
				{
					out+=*it+" ";
				}
		return out;

}

/**
	* Outputs the product info in the database format
	*/
void Book:: dump(std::ostream& os) const
{
	os<<"book"<<endl;
	os<<name_<<endl;
	os<<price_<<endl;
	os<<qty_<<endl;
	os<<isbn_<<endl;
	os<<author_<<endl;
}

/**
	*Accessors
	*/
string Book::getISBN() const
{
	return isbn_;
}

string Book::getAuthor() const
{
	return author_;
}

/*
**helper function that get the keyword of the book and set the keyword set
*/
void Book::setKeyword()
{
	keywords_.insert(category_);
	keywords_.insert(isbn_);
	set<string> T_author=parseStringToWords(convToLower(author_));
	keywords_.insert(T_author.begin(),T_author.end());
	set<string> T_name=parseStringToWords(convToLower(name_));
	keywords_.insert(T_name.begin(),T_name.end());
}
