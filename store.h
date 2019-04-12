#pragma once
#include "product.h"
#include "customer.h"
#include "order.h"
#include <vector>
#include <map>
#include <iterator>
#include <istream>

class Store {
  public:
    Store(std::string store_name);
    std::string name(); // Returns the store name
    void save(std::ostream& ost);
    Store(std::istream& ist);
    void add_product(Product* product); // Add a new product to stock
    int number_of_products(); // # of products defined
    Product* get_product(int product);  // Return pointer to selected product
    std::string product_to_string(int product); // string version of a product

    void add_customer(Customer* customer); // Add a new customer to the list
    int number_of_customers();  // # of customers on the list
    std::string customer_to_string(int customer); // string version of a customer

    void place_order(Order order, int customer); // Places a new order
    int number_of_orders(); // # of orders defined
    std::string order_to_string(int order_number); // string version of an order

    double cash();
    void pay_order(int order_number);
    bool order_is_paid(int order_number);
    void fill_order(int order_number);
    bool order_is_filled(int order_number);
    void discard_order(int order_number);
    bool order_is_discarded(int order_number);
    bool order_is_completed(int order_number);
    bool order_is_pending(int order_number);
    std::pair<Order, Customer>& find_order_pair(int order_number);


    friend std::ostream& operator<<(std::ostream& ost, Store& store); 
  private:
    std::string _name;
    std::vector<Product*> _products;
    std::vector<Customer*> _customers;
    std::map<Order, Customer> _orders;
    double _cash_register;
};
