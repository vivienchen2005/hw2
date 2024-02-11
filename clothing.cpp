#include <sstream>
#include <iomanip>
#include "clothing.h"

using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, const std::string size, const std::string brand):
Product(category, name, price, qty)
{
    size_ = size;
    brand_ = brand;
}

Clothing::~Clothing()
{

}

std::set<std::string> Clothing::keywords() const {
    std::set<std::string> s1 = parseStringToWords(name_);
    std::set<std::string> s2 = parseStringToWords(brand_);
    std::set<std::string> partial_total = setUnion(s1, s2);
    return partial_total;
}

std::string Clothing::displayString() const {
    std::stringstream ss;
    ss << name_ << "\n" << "Size: " << size_ << " Brand: " << brand_ << "\n" << price_ << " " << qty_ << " left." << "\n";
    return ss.str();
}

void Clothing::dump(std::ostream& os) const {
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << "\n";
}


