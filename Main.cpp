#include "Main.h"
#include "FormLogin.h"
 
 
bool MainApp::OnInit()
{
 
    FormLogin *formLogin = new FormLogin(wxT("xCAT - extreme Cluster/Cloud Administration Toolkit"));

    //// StatusBar
    //formLogin->CreateStatusBar();
    //formLogin->SetStatusText(_T("Connect..."));

    formLogin->Show(true);
 
    return true;
}
 
wxIMPLEMENT_APP(MainApp);
