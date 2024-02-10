#include <sstream>
#include <iomanip>
#include "movie.h"

using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty, const std::string genre, const std::string rating):
Product(category, name, price, qty)
{
    genre_ = genre;
    rating_ = rating;
}

Movie::~Movie()
{

}

std::set<std::string> Movie::keywords() const {
    std::set<std::string> s1 = parseStringToWords(convToLower(name_));
    std::set<std::string> s2 = parseStringToWords(convToLower(genre_));
    std::set<std::string> partial_total = setUnion(s1, s2);
    return partial_total;
}

std::string Movie::displayString() const {
    std::stringstream ss;
    ss << name_ << "\n" << "Genre: " << genre_ << " Rating: " << rating_ << "\n" << price_ << " " << qty_ << " left." << "\n";
    return ss.str();
}

void Movie::dump(std::ostream& os) const {
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << endl;
}


