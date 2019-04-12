#include "mainwin.h"
#include "customer.h"
#include <iostream>
#include <gtkmm.h>
#include "dialogs.h"
#include<string>



// /////////
// Help Menu


void Mainwin::on_fill_click() {
	msg->set_text("");
	Gtk::Dialog *dialog = new Gtk::Dialog{"Please, Select an Order to Fill", *this};

	Gtk::Label l_current;
	dialog->get_vbox()->pack_start(l_current, Gtk::PACK_SHRINK);

	Gtk::HBox hb_orders;
	Gtk::Label label1{"Order:"};
	label1.set_width_chars(15);
	hb_orders.pack_start(label1, Gtk::PACK_SHRINK);

	Gtk::ComboBoxText combo_orders;
	for(int i=0; i<_store.number_of_orders(); ++i) {
		combo_orders.append(std::to_string(i));
	}
	hb_orders.pack_start(combo_orders, Gtk::PACK_SHRINK);
	dialog->get_vbox()->pack_start(hb_orders, Gtk::PACK_SHRINK);

    // Show dialog
	dialog->add_button("Close", 0);
	dialog->add_button("Show", 1);
	dialog->add_button("Fill", 2);
	dialog->show_all();

	int result; 

	while (true) {
		result = dialog->run();
		if (result == 0) {delete dialog; return;}
		else if(result ==1) {l_current.set_text(_store.order_to_string(combo_orders.get_active_row_number()));}
		else if(result ==2)
		{
			int order_num = combo_orders.get_active_row_number();
			_store.fill_order(order_num);   
			int return_val = Gtk::MessageDialog{*this,"The requested order was filled. Thank you"}.run();
			msg->set_text("The requested order was filled. Thank you");
			delete dialog;
			break;
		}
	}
}

void Mainwin::on_pay_click() {

	msg->set_text("");
	Gtk::Dialog *dialog = new Gtk::Dialog{"Please, select an Order to Pay", *this};


	Gtk::Label l_current;
	dialog->get_vbox()->pack_start(l_current, Gtk::PACK_SHRINK);

	Gtk::HBox hb_orders;
	Gtk::Label label1{"Order:"};
	label1.set_width_chars(15);
	hb_orders.pack_start(label1, Gtk::PACK_SHRINK);

	Gtk::ComboBoxText combo_orders;
	for(int i=0; i<_store.number_of_orders(); ++i) {
		combo_orders.append(std::to_string(i));
	}
	hb_orders.pack_start(combo_orders, Gtk::PACK_SHRINK);
	dialog->get_vbox()->pack_start(hb_orders, Gtk::PACK_SHRINK);

    // Show dialog
	dialog->add_button("Close", 0);
	dialog->add_button("Show", 1);
	dialog->add_button("Pay Now", 2);
	dialog->show_all();

    int result; // of the dialog (1 = OK)
    while (true) {
    	result = dialog->run();
    	if (result == 0) {delete dialog; return;}
    	else if(result ==1) {l_current.set_text(_store.order_to_string(combo_orders.get_active_row_number()));}
    	else if(result ==2)
    		{	int order_num = combo_orders.get_active_row_number();
    			try{
    				_store.pay_order(order_num);
    			}
    			catch(int x){
    				int return_va = Gtk::MessageDialog{*this,"Payment wasn't processed..."}.run();

    			}


    			int return_val = Gtk::MessageDialog{*this,"Successfully Paid..."}.run();
    			msg->set_text("Successfully Paid...");
    			cash->set_text("Cash: $"+ std::to_string(_store.cash()));
    			
    			delete dialog;
    			return;
    		}
    	}

    }

    void Mainwin::on_discard_click() {

    	msg->set_text("");
    	Gtk::Dialog *dialog = new Gtk::Dialog{"Please, Select an Order to Discard", *this};

    	Gtk::Label l_current;
    	dialog->get_vbox()->pack_start(l_current, Gtk::PACK_SHRINK);

    	Gtk::HBox hb_orders;
    	Gtk::Label label1{"Order:"};
    	label1.set_width_chars(15);
    	hb_orders.pack_start(label1, Gtk::PACK_SHRINK);

    	Gtk::ComboBoxText combo_orders;
    	for(int i=0; i<_store.number_of_orders(); ++i) {
    		combo_orders.append(std::to_string(i));
    	}
    	hb_orders.pack_start(combo_orders, Gtk::PACK_SHRINK);
    	dialog->get_vbox()->pack_start(hb_orders, Gtk::PACK_SHRINK);

    // Show dialog
    	dialog->add_button("Close", 0);
    	dialog->add_button("Show", 1);
    	dialog->add_button("Discard", 2);
    	dialog->show_all();

    	int result; 
    	while (true) {
    		result = dialog->run();
    		if (result == 0) {delete dialog; return;}
    		else if(result ==1) {l_current.set_text(_store.order_to_string(combo_orders.get_active_row_number()));}
    		else if(result ==2)
    		{
    			int order_num = combo_orders.get_active_row_number()-1;
    			_store.discard_order(order_num);
    			int x = Gtk::MessageDialog{*this,"Successfully discarded the selected order..."}.run();
    			msg->set_text("Successfully discarded the selected order..");
    			delete dialog;
    			return;
    		}
    	}
    }

    void Mainwin::on_load_click(){
    	Gtk::FileChooserDialog dialog("Please choose a file",Gtk::FileChooserAction::FILE_CHOOSER_ACTION_OPEN);

    	auto filter_rvms = Gtk::FileFilter::create();
    	filter_rvms->set_name("JAVADONUT files");
    	filter_rvms->add_pattern("*.javadonut");
    	dialog.add_filter(filter_rvms);

    	auto filter_text = Gtk::FileFilter::create();
    	filter_text->set_name("Text files");
    	filter_text->add_mime_type("text/plain");
    	dialog.add_filter(filter_text);

    	auto filter_any = Gtk::FileFilter::create();
    	filter_any->set_name("Any files");
    	filter_any->add_pattern("*");
    	dialog.add_filter(filter_any);

    	dialog.set_filename("untitled.javadonut");

    	dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
    	dialog.add_button("_Open", Gtk::RESPONSE_OK);

    	int result = Dialogs::run_dialog(&dialog);


    	if (result == Gtk::RESPONSE_OK) {
    		std::ifstream ifs{dialog.get_filename()};
    		if (ifs) _store = Store{ifs};
    		else{int a = Gtk::MessageDialog{*this, "Unable to load,Sorry! " + dialog.get_filename()}.run();
    		return;
    	}

    	msg->set_text("File has been loaded successfully...");
    }


    
}
void Mainwin::on_save_click(){
	
	std::string CANCEL_X = "Exit";
	Gtk::FileChooserDialog dialog("Please choose a file",Gtk::FileChooserAction::FILE_CHOOSER_ACTION_SAVE);
	auto filter_javas = Gtk::FileFilter::create();
	filter_javas->set_name("JAVADONUT files");
	filter_javas->add_pattern("*.javadonut");
	dialog.add_filter(filter_javas);

	auto filter_text = Gtk::FileFilter::create();
	filter_text->set_name("Text files");
	filter_text->add_mime_type("text/plain");
	dialog.add_filter(filter_text);
	
	auto filter_any = Gtk::FileFilter::create();
	filter_any->set_name("Any files");
	filter_any->add_pattern("*");
	dialog.add_filter(filter_any);

	dialog.set_filename("untitled.javadonut");

	dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
	dialog.add_button("_Save", Gtk::RESPONSE_OK);

	int result = Dialogs::run_dialog(&dialog);

	if (result == Gtk::RESPONSE_OK) {
		std::ofstream ofs{dialog.get_filename()};
		if (ofs) {
			_store.save(ofs);
			_filename = dialog.get_filename();

		} else {
			Dialogs::message("####Unable to save to " + dialog.get_filename(), "ERROR");
		}
	}
	msg->set_text("File has been saved successfully...");
	
}


void Mainwin::on_new_file_click(){}


void Mainwin::on_about_click() {
	Gtk::AboutDialog dialog{};
	dialog.set_transient_for(*this);
	dialog.set_program_name("Java and Donut Express");
	auto logo = Gdk::Pixbuf::create_from_file("logo.png");
	dialog.set_logo(logo);
	dialog.set_version("Version 1.0.0");
	dialog.set_copyright("Copyright 2018");
	dialog.set_license_type(Gtk::License::LICENSE_GPL_3_0);
	std::vector< Glib::ustring > authors = {"Alvin Poudel Sharma"};
	dialog.set_authors(authors);
	std::vector< Glib::ustring > artists = {
		"JADE Logo is licensed under the Creative Commons Attribution Share-Alike 3.0 License by SaxDeux https://commons.wikimedia.org/wiki/File:Logo_JADE.png",
		"STUDENT ID: 1001555230."
		
	};
	dialog.set_artists(artists);
	dialog.run();
}

void Mainwin::on_quit_click() {         // Exit the program
	close();
}
