#ifndef MAINWIN_H
#define MAINWIN_H

#include <gtkmm.h>
#include "store.h"
#include <exception>
#include <fstream>
#include <iostream>
enum class Action{Show, Fill, Pay, Discard };

class Mainwin : public Gtk::Window
{
    public:
        Mainwin();
        virtual ~Mainwin();
    protected:
        void on_quit_click();            // Exit the program
        void on_view_orders_click();     // Select an order to view
        void on_view_products_click();   // View all products
        void on_create_order_click();    // Create a new order
        void on_create_coffee_click();   // Create a new coffee product
        void on_create_donut_click();    // Create a new donut product
        void on_list_customers_click();  // List all customers
        void on_new_customer_click();    // Create a new customer
        void on_about_click();           // About dialog
        void on_fill_click();
        void on_pay_click();
        void on_discard_click();
        void on_test_click();
        void on_load_click();
        void on_save_click();
        void on_new_file_click();





    private:
        std::string _filename = "untitled.javadonut";
        Store _store;
        Gtk::Label *msg;                      // Status message display
        Gtk::Label *cash;
        Gtk::MenuItem *menuitem_new_order;    // Create -> Order
        Gtk::MenuItem *menuitem_new_coffee;   // Create -> Coffee
        Gtk::MenuItem *menuitem_new_donut;    // Create -> Donut
        void set_message(std::string message);
        void update_cash();
        void process_order(Action action);
};
#endif 

