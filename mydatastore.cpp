#include "mydatastore.h"
#include "util.h"
#include <iostream>

using namespace std;

Mydatastore::Mydatastore()
{

}

Mydatastore::~Mydatastore()
{

}

void Mydatastore::addProduct(Product* p)
{
	Store_products_.insert(p);
	setupKeywordMap(p);
}

void Mydatastore::addUser(User* u)
{
	Store_users_.insert(u);
	Name_User_.insert(make_pair(u->getName(),u));
}

vector<Product*> Mydatastore::search(vector<string>& terms, int type)
{
	vector<set<Product*>> out;
	vector<Product*> output;
	//search the terms in map
	for(vector<string>::iterator it = terms.begin();
			it != terms.end();
			++it)
			{
				if(Keywords_map_.find(*it) != Keywords_map_.end())
				{
					out.push_back(Keywords_map_.find(*it)->second);
				}
			}
	
	set<Product*>temp=out[0]; //the one who always operate with others
	if(out.size()>1)
	//if there is only 1 element, then no nothing
	{
			if (type == 0) 
			//AND search
			{
				for(unsigned int i=1; i < out.size(); i++)
				{
					temp=setIntersection(temp, out[i]);
				}
			}else 
			if(type == 1) 
			//OR SEARCH
			{
				for(unsigned int i=1; i < out.size(); i++)
				{
				temp=setUnion(temp, out[i]);
				}
			}else
			{
				cout<<"Invalid Command"<<endl;
				return output;
			}
	}

	
	
	//traverse temp to ouput
	for(set<Product*>::iterator it = temp.begin();
			it!= temp.end();
			++it)
			{
				output.push_back(*it);
			}
			
			return output;

}



void Mydatastore::dump(std::ostream& ofile)
{
	//dump products
	ofile<<"<products>"<<endl;
	
	for(set<Product*>::iterator it = Store_products_.begin();
			it != Store_products_.end();
			++it)
			{
				(*it)->dump(ofile);
			}
	ofile<<"</products>"<<endl;
	//dump user
	
	ofile<<"<users>"<<endl;
	for(set<User*>::iterator it = Store_users_.begin();
			it != Store_users_.end();
			++it)
			{
				(*it)->dump(ofile);
			}
	
	
	ofile<<"</users>"<<endl;
	return;
}

/**
	*Add the products to cart
	*/
void Mydatastore::AddtoCart(string Username, Product* P)
{
	User* U=findUser(Username);
	if(U== nullptr)
	{
		cout<<"Can't find this user!"<<endl;
		return;
	}
	map<User*, vector<Product*>>::iterator it = Store_carts_.find(U);
	if(it !=Store_carts_.end())
	{
		it->second.push_back(P);
	}else{
		vector<Product*> cart;
		cart.push_back(P);
		Store_carts_.insert(make_pair(U,cart));

	}
	cout<<"Successfully added:"<<P->getName()<<" to "<<Username<<"!"<<endl;
	return;
}

/**
	*qty -1 and clear the 
	*/

void Mydatastore::BuyCart ( string user)
{
	User* U=findUser(user);
	if(U==nullptr)
	{
		cout<<"Invalide username"<<endl;
		return;
	}

	if(Store_carts_.find(U)==Store_carts_.end())
	{
		cout<<"Cart is empty"<<endl;
		return;
	}

	for(vector<Product*>::iterator it = Store_carts_[U].begin();
			it != Store_carts_[U].end();
			++it)
			{
				if((*it)->getQty()==0)
				{
					cout<<"Can't buy"<<(*it)->getName()<<endl;
					continue;
				}
				double price=(*it)->getPrice();
				if(U->getBalance()>=price)
				{
					(*it)->subtractQty(1);
					U->deductAmount(price);
					cout<<"Successfull buy the product: "<<(*it)->getName()<<endl;
					cout<<"Your current balance: "<<U->getBalance()<<endl;

				}else{
					cout<<"No enough balance to buy: "<<(*it)->getName()<<endl;
					cout<<"Your current balance: "<<U->getBalance()<<endl;
				}
				
				
			}

	Store_carts_.erase(U);
	return;
}

void Mydatastore::ViewCart( string user )
{
	User* U=findUser(user);
	if(U==nullptr)
	{
		cout<<"Invalide username"<<endl;
		return;
	}
	
	if(Store_carts_.find(U)==Store_carts_.end())
	{
		cout<<"Cart is empty"<<endl;
		return;
	}
	int num_in_cart=1;
	for(vector<Product*>::iterator it = Store_carts_[U].begin();
			it != Store_carts_[U].end();
			++it)
			{
				cout<<num_in_cart<<". "<<endl;
				//cout<<"size="<<Store_carts_[U].size()<<endl;
				cout<<(*it)->displayString()<<endl;
				num_in_cart++;
			}
	
}



 

void Mydatastore::ViewStore()
{
	cout<<getStore_products_().size()<<endl;
	for(set<Product*>::iterator it = getStore_products_().begin();
			it != getStore_products_().end();
			++it)
			{
				//cout<<"size="<<Store_carts_[U].size()<<endl;
				cout<<(*it)->displayString()<<"\n"<<endl;
			
			}
}

//Accessors

set<Product*> Mydatastore::getStore_products_()
{
	return Store_products_;
}

set<User*> Mydatastore::getStore_users_()
{
	return Store_users_;
}

User* Mydatastore::findUser(string Username)
{
	if(Name_User_.find(Username)!=Name_User_.end())
	return Name_User_[Username];

	return nullptr;
	
}

/*
 	*setup Keyword Map
	**/

void Mydatastore::setupKeywordMap(Product* P)
{
	printKeywords(P);
	cout<<"size="<<P->keywords().size()<<endl;
         /*<test>*/

	for(set<string>::iterator it=P->keywords().begin();
			it!= P->keywords().end();
			++it)
			{
				cout<<"keyword="<<*it<<endl;
         /*<test>*/

				if(Keywords_map_.find(*it)==Keywords_map_.end())
				//no this keyword in the map
				{
					set<Product*> temp;
					temp.insert(P);
					Keywords_map_.insert(make_pair((*it),temp));
				}else{// has this keyword already
					Keywords_map_[*it].insert(P);
				}
			}
	return;
}

void Mydatastore::printKeywords(Product* P)
{
	cout<<"key words from"<<P->getName()<<endl;
	for(set<string>::iterator it = P->keywords().begin();
			it != P->keywords().end();
			++it)
			{
				cout<<*it<<endl;
			}
	cout<<endl;
}
/*<test>*/