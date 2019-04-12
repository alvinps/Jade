#pragma once
#include <string>
#include <ostream>

class Product {
  public:

    Product(std::string name, double price, double cost);

    Product(std::istream& ist);
    virtual void save(std::ostream& ost);
    std::string name();
    double price();
    double profit();
    virtual std::string to_string();
  protected:
    std::string _name;
    double _price;
    double _cost;
};
