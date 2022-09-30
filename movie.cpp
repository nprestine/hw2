#include <sstream>
#include <iomanip>
#include "movie.h"
#include "util.h"

Movie:: Movie(const std::string category, const std::string name, double price, int qty, const std::string genre, const std::string rating):
    Product(category,name,price,qty), genre_(genre), rating_(rating) 
    {

    }

void Movie::dump(std::ostream& os) const
{
    os << category_ << std::endl << name_ << std::endl << price_ << std::endl << qty_ << genre_ << rating_ << std:: endl;
}

std::string Movie::displayString() const
{
    std::string information;
    information = category_ + name_ + "\n" + "Genre: " + genre_ + "\n" +" Rating: " + rating_ + "\n" + "Price: "+ "\n" + std::to_string(price_);
    return information;
}

std::set<std::string> Movie::keywords() const{
    std::set<std::string> searchset;
    std::set<std::string> tmp = parseStringToWords(name_);
    std::set<std::string>::iterator it;
    for(it = tmp.begin(); it != tmp.end(); ++it){
        searchset.insert(*it);
    }
    searchset.insert(genre_);
    return searchset;
}

Movie::~Movie(){}