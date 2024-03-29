#pragma once
#include "product.h"
#include <vector>
#include <iostream>

enum Darkness {Blonde, Light, Medium, Dark, Extra_dark};
const std::vector<std::string> darkness_to_string =
        {"Blonde", "Light", "Medium", "Dark", "Extra Dark"};

enum Shot {None, Chocolate, Vanilla, Peppermint, Hazelnut};
const std::vector<std::string> shot_to_string =
    {"none", "chocolate", "vanilla", "peppermint", "hazelnut"};

class Java : public Product {
  public:
    Java(std::string name, double price, double cost, Darkness darkness);
    Java(std::istream& ist);

    void add_shot(Shot shot);
    void save(std::ostream& ost)override;
    std::string to_string() override;
  protected:
    Darkness _darkness;
    std::vector<Shot> _shots;
};
    
