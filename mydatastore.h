#include "datastore.h"
#include <string>
#include <set>
#include <vector>
#include <map>

class mydatastore: public DataStore{
public:
    mydatastore();
    ~mydatastore();

void addUser(User* u);
void addProduct(Product* p);
std::vector<Product*> search(std::vector<std::string>& terms, int type); //ask for terms and number value to determine AND or OR search
void dump(std::ostream& os);
void addToCart(std::string username, Product* p);
void buyCart(std::string username);
void viewCart(std::string username);
bool validUsername(std::string username);

private:
std::map<std::string, std::set<Product*>> keywordmap;
std::vector<Product*> allProducts_;
std::map<std::string, User*> allUsers_;
std::map<std::string, std::vector<Product*>> carts_;

};




