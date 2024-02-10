#include "mydatastore.h"

using namespace std;

void MyDataStore::addProduct(Product* p) {
    products.push_back(p);
}

void MyDataStore::addUser(User* u) {
    users.push_back(u);
    user_carts[u->getName()] = std::queue<Product*>();
}

User* MyDataStore::getUser(string username) {
    User* current_user = nullptr;
    for (int i = 0; i < users.size(); i++) {
        if (users[i]->getName() == username) {
            current_user = users[i];
            break;
        }
    }
    return current_user;
}
 
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
    std::set<Product*> set;
    for (size_t i = 0; i<terms.size(); i++) { //go through all terms
        if (type == 1) { //OR
            set = setUnion(term_product_map[terms[i]], set); //union: all products with the current term + set
        }
        else{ //AND
            if (i == 0) { //if its the first term
                set = term_product_map[terms[i]];
            }                              
            set = setIntersection(term_product_map[terms[i]], set); //intersection: all products with the current term + set                                
        }
    }
    std::vector<Product*> matches(set.begin(), set.end()); //change set to vector form
    return matches;
}

void MyDataStore::add(std::string username, Product* p) {
    user_carts[username].push(p);
}

void MyDataStore::view(std::string username) {
    std::queue<Product*> copy_user_carts = user_carts[username];
    int i = 1;
    while(!copy_user_carts.empty()) {
        cout << i << " " << copy_user_carts.front()->displayString() << endl;
        copy_user_carts.pop();  
        i++;
    }
}
void MyDataStore::buy(std::string username) {

    std::queue<Product*> copy_user_carts = user_carts[username];
    User* current_user = getUser(username);
    
    while(!copy_user_carts.empty()) {
        Product* current_product = copy_user_carts.front();
        
        if ((current_product->getQty() > 0) && (current_user->getBalance() >= current_product->getPrice())) {
            current_product->subtractQty(1);
            current_user->deductAmount(current_product->getPrice());
            //remove from user_carts[username]
        }
        copy_user_carts.pop();  
    }
}

void MyDataStore::dump(std::ostream& ofile) {
    ofile << "<products>" << endl;
    for (int i = 0; i < products.size(); i++) {
        Product* product = products[i];
        product->dump(ofile);
    }
    ofile << "</products>" << endl;
    ofile << "<users>" << endl;
    for (int i = 0; i < users.size(); i++) {
        User* user = users[i];
        user->dump(ofile);
    }
    ofile << "</users>" << endl;
}

