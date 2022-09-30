#include <sstream>
#include <iomanip>
#include <iostream>
#include "book.h"
#include "util.h"

Book::Book(const std::string category, const std::string name, double price, int qty, const std::string isbn, const std::string author):
    Product(category,name,price,qty), isbn_(isbn), author_(author) 
    {

    }

void Book::dump(std::ostream& os) const
{
    os << category_ << std::endl << name_ << std::endl << price_ << std::endl << qty_ << isbn_ << author_ << std:: endl;
}

std::string Book::displayString() const
{
    std::string information;
    information = category_ + name_ + "\n" + "Author: " + author_ +"\n" +" ISBN: " + isbn_ + "\n" + "Price: "+ "\n" + std::to_string(price_);
    return information;
}

std::set<std::string> Book::keywords() const{
    std::set<std::string> searchset;
    std::set<std::string> tmp = parseStringToWords(name_ + " " + author_); //remove isbn bc it is solo kewword
    std::set<std::string>::iterator it;
    for(it = tmp.begin(); it != tmp.end(); ++it){
        searchset.insert(*it);
    }
    searchset.insert(isbn_);
    return searchset;
}

Book::~Book()
{}