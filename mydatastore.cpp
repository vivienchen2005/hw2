#include "mydatastore.h"

using namespace std;

void MyDataStore::addProduct(Product* p) {
    products.push_back(p);
    std::set<std::string> keywords = p->keywords();

    for (std::set<std::string>::iterator it = keywords.begin(); it != keywords.end(); ++it) {
        if (term_product_map.find(*it) != term_product_map.end()) { //keyword in map
            term_product_map[*it].insert(p);
        }
        else {
            std::set<Product*> product_set {p};
            term_product_map[*it] = product_set;
        }
    }
    
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

void MyDataStore::add(std::string username, Product* p) { //adds the product to the user given
    user_carts[username].push(p);
}

void MyDataStore::view(std::string username) {
    std::queue<Product*> copy_user_carts = user_carts[username];
    int i = 1;
    while(!copy_user_carts.empty()) {
        cout << "Item " << i << "\n" << copy_user_carts.front()->displayString() << endl;
        copy_user_carts.pop();  
        i++;
    }
}
void MyDataStore::buy(std::string username) {

    User* current_user = getUser(username);
    
    size_t i = 0;
    size_t initial_size = user_carts[username].size();
    while(i < initial_size) {
        Product* current_product = user_carts[username].front();
        
        if ((current_product->getQty() > 0) && (current_user->getBalance() >= current_product->getPrice())) {
            current_product->subtractQty(1);
            current_user->deductAmount(current_product->getPrice());
        }
        else {
            user_carts[username].push(current_product);
        }
        user_carts[username].pop();
        i++;
    }
}

void MyDataStore::dump(std::ostream& ofile) {
    ofile << "<products>" << endl;
    for (int i = 0; i < products.size(); i++) {
        products[i]->dump(ofile);
    }
    ofile << "</products>" << endl;
    ofile << "<users>" << endl;
    for (int i = 0; i < users.size(); i++) {
        users[i]->dump(ofile);
    }
    ofile << "</users>" << endl;
}

