#include "FormLogin.h"
#include <wx/wx.h>

#include "client_https.hpp"

//Added for the json-example
#define BOOST_SPIRIT_THREADSAFE
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using namespace std;
//Added for the json-example:
using namespace boost::property_tree;

 
FormLogin::FormLogin(const wxString& title)
: wxFrame((wxFrame *) NULL, wxID_ANY, title, wxPoint(wxID_ANY, wxID_ANY), wxSize(350, 200), 
wxSYSTEM_MENU | wxMINIMIZE_BOX | wxCLOSE_BOX | wxCAPTION | wxCLIP_CHILDREN)
{
    wxPanel *panel = new wxPanel(this, wxID_ANY);
 
    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);


    wxBoxSizer *host_box = new wxBoxSizer(wxHORIZONTAL);
    m_hostnameLabel = new wxStaticText(panel, wxID_ANY, wxT("Hostname: "), wxDefaultPosition, wxSize(80, -1));
    host_box->Add(m_hostnameLabel, 0);
 
    m_hostnameEntry = new wxTextCtrl(panel, wxID_ANY);
    host_box->Add(m_hostnameEntry, 1);
    vbox->Add(host_box, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);

 
    wxBoxSizer *hbox1 = new wxBoxSizer(wxHORIZONTAL);
    m_usernameLabel = new wxStaticText(panel, wxID_ANY, wxT("Username: "), wxDefaultPosition, wxSize(80, -1));
    hbox1->Add(m_usernameLabel, 0);
 
    m_usernameEntry = new wxTextCtrl(panel, wxID_ANY);
    hbox1->Add(m_usernameEntry, 1);
    vbox->Add(hbox1, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);
 
    wxBoxSizer *hbox2 = new wxBoxSizer(wxHORIZONTAL);
    m_passwordLabel = new wxStaticText(panel, wxID_ANY, wxT("Password: "), wxDefaultPosition, wxSize(80, -1));
    hbox2->Add(m_passwordLabel, 0);
 
    m_passwordEntry = new wxTextCtrl(panel, wxID_ANY, wxString(""),
        wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);
    hbox2->Add(m_passwordEntry, 1);
    vbox->Add(hbox2, 0, wxEXPAND | wxLEFT | wxTOP | wxRIGHT, 10);
 
    wxBoxSizer *hbox3 = new wxBoxSizer(wxHORIZONTAL);
    m_buttonLogin = new wxButton(panel, BUTTON_Login, wxT("Login"));
    hbox3->Add(m_buttonLogin);
 
    m_buttonQuit = new wxButton(panel, wxID_EXIT, ("Quit"));
    hbox3->Add(m_buttonQuit);
    vbox->Add(hbox3, 0, wxALIGN_RIGHT | wxTOP | wxRIGHT | wxBOTTOM, 10);
 
    panel->SetSizer(vbox);
    Centre();
}
 
void FormLogin::OnQuit(wxCommandEvent& event)
{
    Close(true);
}
 
void FormLogin::OnLogin(wxCommandEvent& event)
{
    wxString username = m_usernameEntry->GetValue();
    wxString password = m_passwordEntry->GetValue();
    std::string hostname =  std::string(m_hostnameEntry->GetValue());
    std::string auth_piece = "?userName=" + 
                             //std::string(m_usernameEntry->GetValue()) +
                             std::string(username) +
                             "&userPW=" +
                             std::string(password);
 
    if (username.empty() || password.empty()) {
        wxMessageBox(wxT("Username or password must not empty"), wxT("Warning!"), wxICON_WARNING);
    }
    else {
        // debug
        cout << hostname << ":..." << auth_piece << endl;

typedef SimpleWeb::Client<SimpleWeb::HTTPS> HttpsClient;
        //Second Client() parameter set to false: no certificate verification
        HttpsClient client(hostname + ":443", false);
        auto r1=client.request("GET", "/xcatws/nodes" + auth_piece);
        cout << r1->content.rdbuf();
        cout << "test" << endl;

        //wxMessageBox(wxT("Welcome"), wxT("Message!"), wxICON_INFORMATION);
    }
}
 
FormLogin::~FormLogin() {}
 
BEGIN_EVENT_TABLE(FormLogin, wxFrame)
EVT_BUTTON(wxID_EXIT, FormLogin::OnQuit)
EVT_BUTTON(BUTTON_Login, FormLogin::OnLogin)
END_EVENT_TABLE()
