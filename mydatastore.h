#ifndef Mydatastore
#include <vector>
#include <map>
#include "datastore.h"
// #include "user.h"
//#include "db_parser.h"

class Mydatastore: public DataStore
{
public:
		Mydatastore();
		~Mydatastore();

		

    /**
     * Adds a product to the data store
     */
      void addProduct(Product* p);

    /**
     * Adds a user to the data store
     */
      void addUser(User* u);

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
      std::vector<Product*> search(std::vector<std::string>& terms, int type);

    /**
     * Reproduce the database file from the current Products and User values
     */
      void dump(std::ostream& ofile);

		/**
		 *Add the products to cart
		 */
		 void AddtoCart(std::string, Product*);

		/**
		 *qty -1 empty the cart
		 */
		 void BuyCart( std::string );

     void ViewCart( std::string );

     void ViewStore();

    /*Accessors*/
     std::set<Product*> getStore_products_();

     std::set<User*> getStore_users_();

     User* findUser(std::string);

     

     

protected:
		

    std::set<Product*> Store_products_;
		std::set<User*> Store_users_;
    
    std::map<std::string, std::set<Product*>> Keywords_map_;
		std::vector<Product*> Cart_;
		std::map<User*, std::vector<Product*>> Store_carts_;

    std::map<std::string, User*> Name_User_;

    void setupKeywordMap(Product*);

};

#endif