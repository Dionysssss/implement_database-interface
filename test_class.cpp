#include "book.h"
#include "clothing.h"
#include "movie.h"
#include "util.h"
#include "mydatastore.h"
#include <set>
// #include "product.h"
//#include "clothing.h"
#include <iostream>
#include <fstream>


using namespace std;

int main(int argc, char* argv[]){

  // filebuf fb;
  // fb.open ("test_base/test2.txt", std::ios::out);
  // ostream os(&fb);
  
  
	Book b1("book","Data Abstraction & Problem Solving with C++",79.99,20,"978-013292372-9","Carrano and Henry");
	Book b2("book","a book2",79.99,20,"978-013292372-9","Carrano and Henry");
	Book b3("book","a book3",79.99,20,"978-013292372-9","Carrano and Henry");
	// cout<<b1.getAuthor()<<endl;
	// cout<<b1.displayString()<<endl;
	// b1.dump(os);

	// fb.close();
	// Mydatastore* ds=new Mydatastore;
	// Mydatastore ds2;
	// cout<<ds->Store_products_.empty()<<endl;
	// cout<<ds2.Store_products_.empty()<<endl;

	// ds2.addProduct(&b1);
	// ds2.addProduct(&b2);

	//cout<<ds2.Store_products_.empty()<<endl;
	// ds.addProduct(&b1);
	// ds.addProduct(&b2);
	// ds.addProduct(&b3);


	set<Product*> a1;
	set<Product*> a2;
	set<Product*> overlap;
	set<Product*> union_;

	a1.insert(&b1);
	a1.insert(&b2);

	a2.insert(&b1);
	a2.insert(&b3);

	overlap = setIntersection(a1, a2);
	union_ = setUnion(a1, a2);

	for(set<Product*>::iterator it=overlap.begin(); it != overlap.end(); ++it)
	{
		cout<<(*it)->displayString()<<endl;
	}	

	for( set<Product*>::iterator it=union_.begin(); it != union_.end(); ++it)
	{
		cout<<(*it)->displayString()<<endl;
	}

	// set<Product> set2;

	// set1.insert(b1,b2);
	// set2.insert(b1,b3);

	//delete ds;

	return 1;
}