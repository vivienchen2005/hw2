#include "datastore.h"
#include <string>
#include <set>
#include <vector>
#include <queue>
#include <map>
#include "product.h"
#include "user.h"
#include "util.h"

class MyDataStore : public DataStore {
public:
    ~MyDataStore() { 
        for (int i = 0; i < users.size(); i++) {
            delete users[i];
        }
        for (int i = 0; i < products.size(); i++) {
            delete products[i];
        }
        user_carts.clear();
    }

    /**
     * Adds a product to the data store
     */
    void addProduct(Product* p);

    /**
     * Adds a user to the data store
     */
    void addUser(User* u);
    User* getUser(std::string username);

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
    std::vector<Product*> search(std::vector<std::string>& terms, int type);

    void add(std::string username, Product* p);
    void view(std::string username);
    void buy(std::string username);

    /**
     * Reproduce the database file from the current Products and User values
     */
    void dump(std::ostream& ofile);

private:
    std::vector<Product*> products;
    std::vector<User*> users;
    std::map<std::string, std::queue<Product*>> user_carts;
    std::map<std::string, std::set<Product*>> term_product_map; //map of a keyword to all products w the keyword
};
