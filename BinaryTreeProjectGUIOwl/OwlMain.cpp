#include <owl/applicat.h>
#include <owl/framewin.h>
#include "TMainDialog.h"

class TBinaryTreeApp : public owl::TApplication {
public:
    TBinaryTreeApp() : TApplication() {}

    void InitInstance() override {
        TMainDialog dlg(0);
        dlg.Execute();
        PostQuitMessage(0);
    }
};

int OwlMain(int argc, _TCHAR* argv[]) {

    TBinaryTreeApp app;
    app.Run();
    return 0;
}