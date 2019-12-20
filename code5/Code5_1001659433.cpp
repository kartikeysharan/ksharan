//Kartikey Sharan
//1001659433

#include <iostream>
#include <gtkmm.h>
class MainWindow : public Gtk::Window
{
    public:
    MainWindow();
    void on_Ok_click(Gtk::Entry *guessentry);
    void on_Cancel_click(void);
};
void MainWindow::on_Cancel_click()
{
    hide();
}
void MainWindow::on_Ok_click(Gtk::Entry *guessentry)
{
    if(guessentry->get_text()=="Ben10" || guessentry->get_text()=="ben10" || guessentry->get_text()=="ben 10" || guessentry->get_text()=="Ben 10" || guessentry->get_text()=="ben 10" || guessentry->get_text()=="Ben Tennyson" || guessentry->get_text()=="ben tennyson" || guessentry->get_text()=="Benny boy"  )
    {
        Gtk::MessageDialog *rightguess = Gtk::manage(new Gtk::MessageDialog{"you guessed <span fgcolor='#0000ff'>Correctly</span>!!",true,Gtk::MESSAGE_WARNING});
        add(*rightguess);
        rightguess->run();
        rightguess->close();
        hide();
    }
    else
    {
        Gtk::MessageDialog *wrongguess = Gtk::manage(new Gtk::MessageDialog{"you guessed <span fgcolor='#ff0000'>Not correctly</span>!!",true,Gtk::MESSAGE_ERROR});
        wrongguess->set_secondary_text("Try again",false);
        add(*wrongguess);
        wrongguess->run();
        wrongguess->close();
    }
    
}
MainWindow::MainWindow()
{
    set_default_size(500,200);
    set_title("Welcome to my guessing game");
    set_position(Gtk::WIN_POS_CENTER);
    Gtk::Box *MainVBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 0));
    add(*MainVBox);
    Gtk::MenuBar *MyHintBar = Gtk::manage(new Gtk::MenuBar());
    MainVBox->pack_start(*MyHintBar, Gtk::PACK_SHRINK, 0);
    Gtk::Box *vBox1 = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 0));
    MainVBox->add(*vBox1);
    Gtk::MenuItem *MyFileMenu = Gtk::manage(new Gtk::MenuItem("_Family Hint", true));
    MyHintBar->append(*MyFileMenu);
    Gtk::Menu *MyFileSubMenu = Gtk::manage(new Gtk::Menu());
    MyFileMenu->set_submenu(*MyFileSubMenu);
    Gtk::MenuItem *GrandFather = Gtk::manage(new Gtk::MenuItem("Max Tennyson", false));
    MyFileSubMenu->append(*GrandFather);
    Gtk::MenuItem *Sister = Gtk::manage(new Gtk::MenuItem("Gwen Tennyson", false));
    MyFileSubMenu->append(*Sister);
    
    Gtk::MenuItem *DifferentFormsMenu = Gtk::manage(new Gtk::MenuItem("_Different Forms", true));
    MyHintBar->append(*DifferentFormsMenu);
    Gtk::Menu *DifferentFormsSubMenu = Gtk::manage(new Gtk::Menu());
    DifferentFormsMenu->set_submenu(*DifferentFormsSubMenu);
    Gtk::MenuItem *Form1 = Gtk::manage(new Gtk::MenuItem("Four Arms", false));
    DifferentFormsSubMenu->append(*Form1);
    Gtk::MenuItem *Form2 = Gtk::manage(new Gtk::MenuItem("Grey Matter", false));
    DifferentFormsSubMenu->append(*Form2);
    Gtk::MenuItem *Form3 = Gtk::manage(new Gtk::MenuItem("Heat Blast", false));
    DifferentFormsSubMenu->append(*Form3);
    
    Gtk::MenuItem *VillainsMenu = Gtk::manage(new Gtk::MenuItem("_Villains Hint", true));
    MyHintBar->append(*VillainsMenu);
    Gtk::Menu *VillainsSubMenu = Gtk::manage(new Gtk::Menu());
    VillainsMenu->set_submenu(*VillainsSubMenu);
    Gtk::MenuItem *Villain1 = Gtk::manage(new Gtk::MenuItem("Vilgax", false));
    VillainsSubMenu->append(*Villain1);
    Gtk::MenuItem *Villain2 = Gtk::manage(new Gtk::MenuItem("Kevin Levin", false));
    VillainsSubMenu->append(*Villain2);
    Gtk::MenuItem *Villain3 = Gtk::manage(new Gtk::MenuItem("Dark Matter", false));
    VillainsSubMenu->append(*Villain3);
    
    Gtk::Label *text = Gtk::manage(new Gtk::Label{"What's the name of this character?"});
    vBox1->add(*text);

    Gtk::Image *image=Gtk::manage(new Gtk::Image{"Ben10.png"});
    Gtk::Box *vBox2 = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 0));
    vBox2->add(*image);
    MainVBox->add(*vBox2);
    Gtk::Box *box1 = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL,0));
    Gtk::Box *vBox3 = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 0));
    vBox3->add(*box1);
    MainVBox->add(*vBox3);
    Gtk::VButtonBox *buttonbox=Gtk::manage(new Gtk::VButtonBox());
    box1->add(*buttonbox);
    Gtk::Box *box2 = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL,0));
    box1->add(*box2);
    
    Gtk::Button *Ok=Gtk::manage(new Gtk::Button("                                   Ok                                   "));
    buttonbox->add(*Ok);
    Ok->set_focus_on_click(true);
    Ok->set_border_width(4);
    Gtk::Button *Cancel=Gtk::manage(new Gtk::Button("               Cancel               "));
    buttonbox->add(*Cancel);
    Cancel->set_focus_on_click(true);
    Cancel->set_border_width(4);
    
    Gtk::Entry *guessentry=Gtk::manage(new Gtk::Entry());
    guessentry->set_text("Enter your guess here");
    box2->add(*guessentry);
    guessentry->grab_focus();
    guessentry->set_activates_default();
   
    guessentry->signal_activate().connect(sigc::bind<Gtk::Entry*>(sigc::mem_fun(*this,&MainWindow::on_Ok_click),guessentry));
    Cancel->signal_clicked().connect(sigc::mem_fun(*this,&MainWindow::on_Cancel_click),guessentry);
    Ok->signal_clicked().connect(sigc::bind<Gtk::Entry*>(sigc::mem_fun(*this,&MainWindow::on_Ok_click),guessentry));;
    MainVBox->show_all();
    
}
int main(int argc, char * argv[])
{
   auto app = Gtk::Application::create(argc, argv, "app.window");
   MainWindow MyWindow;
   return app->run(MyWindow);
}
