#include "mydatastore.h"
#include "util.h"
#include <string>
#include <set>
#include <map>
#include <iostream>
#include <vector>
#include <iostream>
#include <algorithm> 



mydatastore:: mydatastore() 
    {
    }

mydatastore::~mydatastore() //delete everything created dynamically
{
    for(unsigned int i = 0; i< allProducts_.size(); i++){
        delete allProducts_[i];
    }
     for(std::map<std::string, User*>:: iterator it = allUsers_.begin(); it != allUsers_.end(); ++it){
        delete it->second;
    }
     

    //have to also delete users
}
//call keywords function that will return set of keywords
//map of string for everykey word set of product pointers

void mydatastore:: addProduct(Product* p){ //adds product to cart if constraints are met
    allProducts_.push_back(p);
    std::set<std::string> posskeywords = p->keywords();

    std::map<std::string, std::set<Product*>>::iterator scanner; //iterator for keywordmap map

    for(std::set<std::string>::iterator it = posskeywords.begin(); it != posskeywords.end(); ++it){ //iterates throguh and checks if posskeywords are a part of keywordmap
       
        scanner = keywordmap.find(*it);

        if(scanner == keywordmap.end()){ //keyword is not yet in keyword map
            std::set<Product*> matchproducts;
            matchproducts.insert(p);
            keywordmap.insert(make_pair(*it, matchproducts));
        }
        else{ //keyword is already in map
            scanner->second.insert(p);
        }
    }
}

void mydatastore:: addUser(User* u){ //finished but untested
    //allUsers_.insert(u); need to add to map so change 
    std::vector<Product*> cart;
    allUsers_.insert(make_pair(u->getName(),u));
    carts_.insert(make_pair(u->getName(),cart));
}


std::vector<Product*> mydatastore::search(std::vector<std::string>& terms, int type) //ask for terms and number value to determine AND or OR search
{
    std::vector<Product*> results; //result set to be returned
    std::set<Product*> set_results; //result set for setunion and setintersection output
    if(type == 1 && terms.size() == 1) //search type OR
    {
        set_results = keywordmap[terms[0]];
    }
    else if(type == 1) //search type OR
    {
        set_results = keywordmap[terms[0]]; //check if first term is a keyword
        
        if(terms.size()>1){
            for(unsigned int i = 1; i < terms.size(); i++){ //check if other terms are keywords and add to list if so
                set_results = setUnion(set_results, keywordmap[terms[i]]);
            }
        }
    }
    else if(type == 0 && terms.size() == 1){
        set_results = keywordmap[terms[0]];
    }
    else if(type == 0){ //search type AND
        
        set_results = keywordmap[terms[0]]; //check if first term is a keyword
        
        if(terms.size()>1){
            for(unsigned int i = 1; i < terms.size(); i++){ //check for additional keyword intersection
                set_results = setIntersection(set_results, keywordmap[terms[i]]);
            }
        } 
    }
    //convert set output into vector of Product*
    for(std::set<Product*>::iterator it = set_results.begin(); it != set_results.end(); ++it){
        results.push_back(*it);
    }
   
    return results;
}

void mydatastore::addToCart(std::string username, Product* item){ //function to add items to cart 
     if(validUsername(username) == false){ //is the username valid
        std::cout << "Invalid Username" << "\n";
        return;
    }if(carts_.find(username) == carts_.end()){ //they dont have a cart yet
        std::vector<Product*> cartcontent;
        cartcontent.push_back(item);
        carts_.insert(make_pair(username, cartcontent));
    }
    else{ //they got a cart
     carts_[username].push_back(item);
    }
}


void mydatastore::dump(std::ostream& os){ //function to output data onto datafile upon program QUIT
    os << "<products>" << "\n";
    for(unsigned int i = 0; i<allProducts_.size(); i++){ //output products
        allProducts_[i]->dump(os);
    }
    os << "<products>" << "\n" << "<users>" << "\n";
    for(std::map<std::string, User*>::iterator it = allUsers_.begin(); it != allUsers_.end(); ++it){ //output users
        if(it->second != nullptr){
            (*it).second->dump(os);
    }
    }
    os <<"<users>" << "\n";
}

void mydatastore::buyCart(std::string username){ //function to buy cart if constraints are met
    if(validUsername(username) == false){
        std::cout << "Invalid Username" << "\n";
        return;
    }
    else{
        std::vector<Product*> tempcart;
        if(carts_.find(username) != carts_.end()){
            tempcart = carts_.find(username)->second;
            for(int i = tempcart.size()-1; i >= 0; i--){
                if((((allUsers_.find(username)->second)->getBalance() - (tempcart[i])->getPrice() > 0)) && ((tempcart[i])->getQty()) >= 1){
                    (tempcart[i])->subtractQty(1);
                    (allUsers_.find(username)->second)->deductAmount(tempcart[i]->getPrice());
                    carts_.find(username)->second.pop_back();
                }
            }
        }
    }  
}

void mydatastore::viewCart(std::string username){ //function to veiw cart if cart and user are valid
    if(validUsername(username) == false){
        std::cout << "Invalid Username" << "\n";
        return;
    }
    else{
        std::cout << username << "'s cart:" << "\n";
        std::vector<Product*> tempcart;
        tempcart = carts_.find(username)->second;
        int counter = 1;
        for(std::vector<Product*>::iterator it = tempcart.begin(); it != tempcart.end(); ++it){
            std::cout << counter << "\n";
            std::cout << (*it)->displayString(); //not sure how to cout this
            std::cout << "\n";
            counter++;
        }
    }
}
bool mydatastore::validUsername(std::string username){ //function to check for valid username
    
        if (allUsers_.find(username) == allUsers_.end()){
            return false;
        }
    return true;
}

