#include "mainwin.h"
#include "java.h"
#include "donut.h"
#include "customer.h"
#include <ostream>
#include <iostream>
#include <regex>


Mainwin::Mainwin() : _store{Store{"JADE"}} {

    // /////////////////
    // G U I   S E T U P
    // /////////////////

    set_title("Java and Donut Express (JADE)");
    set_icon_from_file("window_logo.png");
    set_default_size(1200, 600);

    // Put a vertical box container as the Window contents
    Gtk::Box *vbox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 0));
    add(*vbox);

    // ///////
    // M E N U
    // Add a menu bar as the top item in the vertical box
    Gtk::MenuBar *menubar = Gtk::manage(new Gtk::MenuBar());
    vbox->pack_start(*menubar, Gtk::PACK_SHRINK, 0);

    //     F I L E
    // Create a File menu and add to the menu bar
    Gtk::MenuItem *menuitem_file = Gtk::manage(new Gtk::MenuItem("_File", true));
    menubar->append(*menuitem_file);
    Gtk::Menu *filemenu = Gtk::manage(new Gtk::Menu());
    menuitem_file->set_submenu(*filemenu);

    // Append Quit to the File menu
    
    Gtk::MenuItem *menuitem_new = Gtk::manage(new Gtk::MenuItem("_New", true));
    menuitem_new->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_new_file_click));
    filemenu->append(*menuitem_new);


    Gtk::MenuItem *menuitem_load = Gtk::manage(new Gtk::MenuItem("_Open", true));
    menuitem_load->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_load_click));
    filemenu->append(*menuitem_load);

    Gtk::MenuItem *menuitem_save = Gtk::manage(new Gtk::MenuItem("_Save", true));
    menuitem_save->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_save_click));
    filemenu->append(*menuitem_save);


    Gtk::MenuItem *menuitem_saveas = Gtk::manage(new Gtk::MenuItem("_Save As", true));
    menuitem_saveas->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_save_click));
    filemenu->append(*menuitem_saveas);


    Gtk::MenuItem *menuitem_properties = Gtk::manage(new Gtk::MenuItem("_Properties", true));
    menuitem_properties->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_save_click));
    filemenu->append(*menuitem_properties);

    Gtk::MenuItem *menuitem_quit = Gtk::manage(new Gtk::MenuItem("_Quit", true));
    menuitem_quit->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_quit_click));
    filemenu->append(*menuitem_quit);

    //Edit

    Gtk::MenuItem *menuitem_edit = Gtk::manage(new Gtk::MenuItem("_Edit", true));
    menubar->append(*menuitem_edit);
    Gtk::Menu *editmenu = Gtk::manage(new Gtk::Menu());
    menuitem_edit->set_submenu(*editmenu);

    //     V I E W
    // Create a View menu and add to the menu bar
    Gtk::MenuItem *menuitem_view = Gtk::manage(new Gtk::MenuItem("_View", true));
    menubar->append(*menuitem_view);
    Gtk::Menu *viewmenu = Gtk::manage(new Gtk::Menu());
    menuitem_view->set_submenu(*viewmenu);

    //         A L L   O R D E R S
    // Append All Orders to the File menu
    Gtk::MenuItem *menuitem_all_orders = Gtk::manage(new Gtk::MenuItem("All _Orders", true));
    menuitem_all_orders->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_view_orders_click));
    viewmenu->append(*menuitem_all_orders);

    //         A L L   P R O D U C T S
    // Append All Products to the File menu
    Gtk::MenuItem *menuitem_all_products = Gtk::manage(new Gtk::MenuItem("All _Products", true));
    menuitem_all_products->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_view_products_click));
    viewmenu->append(*menuitem_all_products);

    //         L I S T   C U S T O M E R S
    // Append List Customers to the View menu
    Gtk::MenuItem *menuitem_list_customers = Gtk::manage(new Gtk::MenuItem("All _Customers", true));
    menuitem_list_customers->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_list_customers_click));
    viewmenu->append(*menuitem_list_customers);

    //     C R E A T E   
    // Create a Create menu and add to the menu bar
    Gtk::MenuItem *menuitem_create = Gtk::manage(new Gtk::MenuItem("_Create", true));
    menubar->append(*menuitem_create);
    Gtk::Menu *createmenu = Gtk::manage(new Gtk::Menu());
    menuitem_create->set_submenu(*createmenu);

    //           N E W   O R D E R
    // Append New Order to the Create menu
    menuitem_new_order = Gtk::manage(new Gtk::MenuItem("_Order", true));
    menuitem_new_order->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_create_order_click));
    createmenu->append(*menuitem_new_order);

    //           N E W   C O F F E E
    // Append New Coffee to the Create menu
    menuitem_new_coffee = Gtk::manage(new Gtk::MenuItem("_Coffee", true));
    menuitem_new_coffee->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_create_coffee_click));
    createmenu->append(*menuitem_new_coffee);

    //           N E W   D O N U T
    // Append New Donut to the Create menu
    menuitem_new_donut = Gtk::manage(new Gtk::MenuItem("_Donut", true));
    menuitem_new_donut->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_create_donut_click));
    createmenu->append(*menuitem_new_donut);

    //           N E W   C U S T O M E R
    // Append New Customer to the Create menu
    Gtk::MenuItem *menuitem_new_customer = Gtk::manage(new Gtk::MenuItem("_Customer", true));
    menuitem_new_customer->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_new_customer_click));
    createmenu->append(*menuitem_new_customer);


    Gtk::MenuItem *menuitem_process = Gtk::manage(new Gtk::MenuItem("_Process", true));
    menubar->append(*menuitem_process);
    Gtk::Menu *processmenu = Gtk::manage(new Gtk::Menu());
    menuitem_process->set_submenu(*processmenu);

    Gtk::MenuItem *menuitem_fill = Gtk::manage(new Gtk::MenuItem("_Fill Order", true));
    menuitem_fill->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_fill_click));
    processmenu->append(*menuitem_fill);

    Gtk::MenuItem *menuitem_pay = Gtk::manage(new Gtk::MenuItem("_Pay Order", true));
    menuitem_pay->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_pay_click));
    processmenu->append(*menuitem_pay);

    Gtk::MenuItem *menuitem_discard = Gtk::manage(new Gtk::MenuItem("_Discard Order", true));
    menuitem_discard->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_discard_click));
    processmenu->append(*menuitem_discard);


    //     H E L P
    // Create a Help menu and add to the menu bar
    Gtk::MenuItem *menuitem_help = 
        Gtk::manage(new Gtk::MenuItem("_Help", true));
    menubar->append(*menuitem_help);
    Gtk::Menu *helpmenu = Gtk::manage(new Gtk::Menu());
    menuitem_help->set_submenu(*helpmenu);

    //           A B O U T
    // Append About to the Help menu
    Gtk::MenuItem *menuitem_about = Gtk::manage(new Gtk::MenuItem("About", true));
    menuitem_about->signal_activate().connect(
        sigc::mem_fun(*this, &Mainwin::on_about_click));
    helpmenu->append(*menuitem_about);

    // /////////////
    // T O O L B A R
    // Add a toolbar to the vertical box below the menu
    Gtk::Toolbar *toolbar = Gtk::manage(new Gtk::Toolbar);
    vbox->add(*toolbar);

    // P R O D U C T S
    //
    //     V I E W   A L L   O R D E R S
    // View all orders currently defined
    Gtk::Image* view_orders_image = Gtk::manage(new Gtk::Image{"orderlist.png"});
    Gtk::ToolButton *view_orders_button = Gtk::manage(new Gtk::ToolButton{*view_orders_image});
    view_orders_button->set_tooltip_markup("View all orders");
    view_orders_button->signal_clicked().connect(sigc::mem_fun(*this, &Mainwin::on_view_orders_click));
    toolbar->append(*view_orders_button);

    //     C R E A T E   O R D E R
    // Create a new order
    Gtk::Image* create_order_image = Gtk::manage(new Gtk::Image{"order.png"});
    Gtk::ToolButton *create_order_button = Gtk::manage(new Gtk::ToolButton{*create_order_image});
    create_order_button->set_tooltip_markup("Create a new order");
    create_order_button->signal_clicked().connect(sigc::mem_fun(*this, &Mainwin::on_create_order_click));
    toolbar->append(*create_order_button);

    Gtk::SeparatorToolItem *sep0 = Gtk::manage(new Gtk::SeparatorToolItem());
    toolbar->append(*sep0);


    Gtk::Image* fill_image = Gtk::manage(new Gtk::Image{"fill.png"});
    Gtk::ToolButton *fill_button = Gtk::manage(new Gtk::ToolButton{*fill_image});
    fill_button->set_tooltip_markup("Fill an order");
    fill_button->signal_clicked().connect(sigc::mem_fun(*this, &Mainwin::on_fill_click));
    toolbar->append(*fill_button);

    Gtk::Image* dollar_image = Gtk::manage(new Gtk::Image{"dollar.png"});
    Gtk::ToolButton *pay_button = Gtk::manage(new Gtk::ToolButton{*dollar_image});
    pay_button->set_tooltip_markup("Pay an order");
    pay_button->signal_clicked().connect(sigc::mem_fun(*this, &Mainwin::on_pay_click));
    toolbar->append(*pay_button);

    Gtk::Image* delete_image = Gtk::manage(new Gtk::Image{"discard.png"});
    Gtk::ToolButton *discard_button = Gtk::manage(new Gtk::ToolButton{*delete_image});
    discard_button->set_tooltip_markup("discard an order");
    discard_button->signal_clicked().connect(sigc::mem_fun(*this, &Mainwin::on_discard_click));
    toolbar->append(*discard_button);
    







    //     V I E W   A L L   P R O D U C T S
    // View all products currently defined
    Gtk::Image* view_all_image = Gtk::manage(new Gtk::Image{"list_products.png"});
    Gtk::ToolButton *view_all_button = Gtk::manage(new Gtk::ToolButton{*view_all_image});
    view_all_button->set_tooltip_markup("View all products");
    view_all_button->signal_clicked().connect(sigc::mem_fun(*this, &Mainwin::on_view_products_click));
    toolbar->append(*view_all_button);

    //     N E W   J A V A
    // Create a new Java type
    Gtk::Image* new_java_image = Gtk::manage(new Gtk::Image{"new_java.png"});
    Gtk::ToolButton *new_java_button = Gtk::manage(new Gtk::ToolButton{*new_java_image});
    new_java_button->set_tooltip_markup("Create a new Java product");
    new_java_button->signal_clicked().connect(sigc::mem_fun(*this, &Mainwin::on_create_coffee_click));
    toolbar->append(*new_java_button);

    //     N E W   D O N U T
    // Create a new Donut type
    Gtk::Image* new_donut_image = Gtk::manage(new Gtk::Image{"new_donut.png"});
    Gtk::ToolButton *new_donut_button = Gtk::manage(new Gtk::ToolButton{*new_donut_image});
    new_donut_button->set_tooltip_markup("Create a new Donut product");
    new_donut_button->signal_clicked().connect(sigc::mem_fun(*this, &Mainwin::on_create_donut_click));
    toolbar->append(*new_donut_button);

    Gtk::SeparatorToolItem *sep1 = Gtk::manage(new Gtk::SeparatorToolItem());
    toolbar->append(*sep1);

    // C U S T O M E R S
    //
    //      L I S T   C U S T O M E R S
    // List customers icon
    Gtk::Image *list_customers_image = Gtk::manage(new Gtk::Image{"list_customers.png"});
    Gtk::ToolButton *list_customers_button = Gtk::manage(new Gtk::ToolButton(*list_customers_image));
    list_customers_button->set_tooltip_markup("List all customers");
    list_customers_button->signal_clicked().connect(sigc::mem_fun(*this, &Mainwin::on_list_customers_click));
    toolbar->append(*list_customers_button);

    //     N E W   C U S T O M E R
    // Add a new customer icon
    Gtk::Image *new_customer_image = Gtk::manage(new Gtk::Image{"new_customer.png"});
    Gtk::ToolButton *new_customer_button = Gtk::manage(new Gtk::ToolButton(*new_customer_image));
    new_customer_button->set_tooltip_markup("Create a new customer");
    new_customer_button->signal_clicked().connect(sigc::mem_fun(*this, &Mainwin::on_new_customer_click));
    toolbar->append(*new_customer_button);

    // M A I N   A R E A
    Gtk::Label* main_area = Gtk::manage(new Gtk::Label);
    main_area->set_hexpand(true);    
    main_area->set_vexpand(true);
    vbox->add(*main_area);

    // S T A T U S   B A R   D I S P L A Y
    // Provide a status bar for program messages
    msg = Gtk::manage(new Gtk::Label());
    msg->set_hexpand(true);
    vbox->add(*msg);
    cash = Gtk::manage(new Gtk::Label());
    cash->set_hexpand(true);
    cash->set_text("Cash: $ 0.0");

    vbox->add(*cash);
    // Make the box and everything in it visible
    vbox->show_all();
}

Mainwin::~Mainwin() { }

// /////////////////
// C A L L B A C K S
// /////////////////

void Mainwin::on_view_orders_click() { // Select an order to view
    msg->set_text("");
    Gtk::Dialog *dialog = new Gtk::Dialog{"Select an Order", *this};

    // Show selected order 
    Gtk::Label l_current;
    dialog->get_vbox()->pack_start(l_current, Gtk::PACK_SHRINK);

    // List orders
    Gtk::HBox b_orders;

    Gtk::Label l_orders{"Order:"};
    l_orders.set_width_chars(15);
    b_orders.pack_start(l_orders, Gtk::PACK_SHRINK);

    Gtk::ComboBoxText c_orders;
    for(int i=0; i<_store.number_of_orders(); ++i) {
        c_orders.append(std::to_string(i));
    }
    b_orders.pack_start(c_orders, Gtk::PACK_SHRINK);
    dialog->get_vbox()->pack_start(b_orders, Gtk::PACK_SHRINK);

    // Show dialog
    dialog->add_button("Close", 0);
    dialog->add_button("Show", 1);
    dialog->show_all();

    int result; // of the dialog (1 = OK)

    while (true) {
        result = dialog->run();
        if (result == 0) {delete dialog; return;}
        l_current.set_text(_store.order_to_string(c_orders.get_active_row_number()));
    }
}

void Mainwin::on_view_products_click() { // View all products
    msg->set_text("");
    std::ostringstream oss;
    oss << _store << std::endl;
    Gtk::MessageDialog d{*this, "List of Products"}; 
    d.set_secondary_text(oss.str());
    int result = d.run();
}

void Mainwin::on_new_customer_click() {
    Gtk::Dialog *dialog = new Gtk::Dialog("Create a Customer", *this);

    // Name
    Gtk::HBox b_name;

    Gtk::Label l_name{"Name:"};
    l_name.set_width_chars(15);
    b_name.pack_start(l_name, Gtk::PACK_SHRINK);

    Gtk::Entry e_name;
    e_name.set_max_length(50);
    b_name.pack_start(e_name, Gtk::PACK_SHRINK);
    dialog->get_vbox()->pack_start(b_name, Gtk::PACK_SHRINK);

    // Phone Number
    Gtk::HBox b_phone;

    Gtk::Label l_phone{"Phone:"};
    l_phone.set_width_chars(15);
    b_phone.pack_start(l_phone, Gtk::PACK_SHRINK);

    Gtk::Entry e_phone;
    e_phone.set_max_length(50);
    b_phone.pack_start(e_phone, Gtk::PACK_SHRINK);
    dialog->get_vbox()->pack_start(b_phone, Gtk::PACK_SHRINK);

    // Show dialog
    dialog->add_button("Cancel", 0);
    dialog->add_button("Create", 1);
    dialog->show_all();

    int result;
    std::string name, phone;
    std::regex re_phone{"[(]?(\\d{3,3}[-)])?\\d{3,3}-\\d{4,4}"};
    bool fail = true;  // set to true if any data is invalid

    while (fail) {
        fail = false;  // optimist!
        result = dialog->run();
        if (result != 1) {delete dialog; return;}
        name = e_name.get_text();
        if (name.size() == 0) {
            e_name.set_text("### Invalid ###");
            fail = true;
        }
        phone = e_phone.get_text();
        if(!std::regex_match(phone,re_phone)) {
            e_phone.set_text("### Invalid ###");
            fail = true;
        }        
    }
    Customer* customer = new Customer{name, phone};
    _store.add_customer(customer);
    msg->set_text("Created customer " + name);

    delete dialog;
}

void Mainwin::on_list_customers_click() {
    msg->set_text("");
    msg->set_text("");
    std::ostringstream oss;
    for (int i=0; i<_store.number_of_customers(); ++i) {
        oss <<  _store.customer_to_string(i) << std::endl;
    }
    Gtk::MessageDialog d{*this, "List of Customers"};
    d.set_secondary_text(oss.str());
    int result = d.run();
}
