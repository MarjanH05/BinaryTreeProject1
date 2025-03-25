#pragma once

#include <owl/dialog.h>
#include <owl/listbox.h>
#include <string>

class TMainDialog : public owl::TDialog {
public:
    TMainDialog(owl::TWindow* parent = nullptr);

    virtual void SetupWindow();

protected:
    void CmSelectInput();
    void CmSelectExisting();
    void CmPlaceNewOutput();
    void CmProcess();
    void CmCreateEquation();
    LRESULT EvDrawItem(WPARAM wParam, LPARAM lParam);

    bool GetOpenFileNameStr(owl::tstring& fileName);
    bool GetSaveFileNameStr(owl::tstring& fileName, LPCTSTR suggestedName);

    DECLARE_RESPONSE_TABLE(TMainDialog);

    owl::TListBox* ResultsListBox;
};
