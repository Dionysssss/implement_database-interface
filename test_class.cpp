#include "book.h"
//#include "clothing.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]){

  filebuf fb;
  fb.open ("test_base/test2.txt", std::ios::out);
  ostream os(&fb);
  
  
	Book b1("book","Data Abstraction & Problem Solving with C++",79.99,20,"978-013292372-9","Carrano and Henry");
	cout<<b1.getAuthor()<<endl;
	cout<<b1.displayString()<<endl;
	b1.dump(os);

	fb.close();

	return 1;
}