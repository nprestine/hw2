#include <sstream>
#include <iomanip>
#include "clothing.h"
#include "util.h"

Clothing:: Clothing(const std::string category, const std::string name, double price, int qty, const std::string size, const std::string brand):
    Product(category,name,price,qty), size_(size), brand_(brand) 
    {

    }

void Clothing::dump(std::ostream& os) const
{
    os << category_ << std::endl << name_ << std::endl << price_ << std::endl << qty_ << brand_ << size_ << std:: endl;
}

std::string Clothing::displayString() const
{
    std::string information;
    information = category_ + name_ + "\n" + "Brand:  " + brand_ + "\n" +"Size: " + size_ + "\n" + "Price: "+ "\n" + std::to_string(price_);
    return information;
}

std::set<std::string> Clothing::keywords() const{
    std::set<std::string> searchset;
    std::set<std::string> tmp = parseStringToWords(name_ + " " + brand_);
    std::set<std::string>::iterator it;
    for(it = tmp.begin(); it != tmp.end(); ++it){
        searchset.insert(*it);
    }
    return searchset;
}

Clothing::~Clothing(){}