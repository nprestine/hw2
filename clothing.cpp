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
    os << category_ << std::endl << name_ << std::endl << price_ << std::endl << qty_ << std::endl << brand_ << std::endl << size_ << std:: endl;
}

std::string Clothing::displayString() const
{
    std::string information;
    information = name_ + "\n" + "Size: " + size_ + " Brand: " + brand_ + "\n" + std::to_string(price_).substr(0,5) + " " + std::to_string(qty_) + " left" + "\n";
    return information;
}

std::set<std::string> Clothing::keywords() const{
    std::set<std::string> searchset;
    std::set<std::string> tmp = parseStringToWords(convToLower(brand_));
    std::set<std::string> tmpname = parseStringToWords(convToLower(name_));
    std:: cout << brand_ << name_ << std::endl;
    tmp = setUnion(tmp, tmpname);
    std::set<std::string>::iterator it;
    for(it = tmp.begin(); it != tmp.end(); ++it){
        searchset.insert(*it);
    }
    return searchset;
}

Clothing::~Clothing(){}