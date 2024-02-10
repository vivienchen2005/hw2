#include <sstream>
#include <iomanip>
#include "book.h"

using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, const std::string author, const std::string isbn):
Product(category, name, price, qty)
{
    isbn_ = isbn;
    author_ = author;
}

Book::~Book()
{

}

std::set<std::string> Book::keywords() const {
    std::set<std::string> s1 = parseStringToWords(name_ + " " + author_);
    s1.insert(isbn_); //something about the const in the function
    return s1;
}

std::string Book::displayString() const {
    return name_ + "\n" + "Author: " + author_ + " ISBN: " + isbn_ + "\n" + std::to_string(price_) + " " + std::to_string(qty_) + " left.";
}

void Book::dump(std::ostream& os) const {
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << "\n";
}


