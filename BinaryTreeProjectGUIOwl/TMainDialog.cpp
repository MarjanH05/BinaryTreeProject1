#include "TMainDialog.h"

#include <owl/applicat.h>
#include <owl/control.h>
#include <owl/framewin.h>
#include <owl/inputdia.h>

#include <commdlg.h>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <fstream>

#include "Resource.h"
#include "FileProcessor.h"
#include "../BinaryTree/FileManager.h"



DEFINE_RESPONSE_TABLE1(TMainDialog, TDialog)
EV_COMMAND(IDC_SELECT_INPUT_BUTTON, CmSelectInput),
EV_COMMAND(IDC_SELECT_EXISTING_BUTTON, CmSelectExisting),
EV_COMMAND(IDC_PLACE_NEW_BUTTON, CmPlaceNewOutput),
EV_COMMAND(IDC_PROCESS_BUTTON, CmProcess),
EV_COMMAND(IDC_CREATE_EQUATION, CmCreateEquation),
EV_MESSAGE(WM_DRAWITEM, EvDrawItem),
END_RESPONSE_TABLE;


TMainDialog::TMainDialog(owl::TWindow* parent)
    : TDialog(parent, IDD_BINARYTREEGUI)
    , ResultsListBox(new owl::TListBox(this, IDC_RESULTS_LIST))
    , ImageStatic(new owl::TStatic(this, IDC_LOGO_STATIC))
    , StatusStatic(new owl::TStatic(this, IDC_STATUS_STATIC))
    , InputFileEdit(new owl::TEdit(this, IDC_INPUT_FILE_EDIT))
    , OutputFileEdit(new owl::TEdit(this, IDC_OUTPUT_FILE_EDIT))
{
}

void TMainDialog::SetupWindow() {
    TDialog::SetupWindow();

    HICON hIcon = ::LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MYICON));
    if (hIcon)
    {
        ::SendMessage(GetHandle(), WM_SETICON, ICON_BIG, (LPARAM)hIcon);
        ::SendMessageA(GetHandle(), WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
    }

    HBITMAP hBitmap = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_COMPUTAIRLOGO), IMAGE_BITMAP, 800, 200, LR_SHARED);

    if (hBitmap)
    {
        ImageStatic->SetImage(hBitmap);
    }
    else
    {
        MessageBox(_T("Failed to load image"), _T("Error"), MB_OK | MB_ICONERROR);
    }

}

bool TMainDialog::GetOpenFileNameStr(owl::tstring& fileName)
{

    OPENFILENAME ofn = { 0 };
    TCHAR szFile[MAX_PATH] = _T("");
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = GetHandle();
    ofn.lpstrFilter = _T("Text Files\0*.txt\0");
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = MAX_PATH;

    if (GetOpenFileName(&ofn)) {
        fileName = szFile;
        return true;
    }
    return false;
}

bool TMainDialog::GetSaveFileNameStr(owl::tstring& fileName, LPCTSTR suggestedName)
{
    OPENFILENAME ofn = { 0 };
    TCHAR szFile[MAX_PATH] = _T("");
    _tcscpy_s(szFile, suggestedName);
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = GetHandle();
    ofn.lpstrFilter = _T("Text Files\0*.txt\0");
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_OVERWRITEPROMPT;

    if (GetSaveFileName(&ofn)) {
        fileName = szFile;
        return true;
    }
    return false;
}

void TMainDialog::CmSelectInput()
{
    owl::tstring fileName;
    if (GetOpenFileNameStr(fileName)) {
        InputFileEdit->SetText(fileName.c_str());
    }
}

void TMainDialog::CmSelectExisting()
{
    owl::tstring fileName;
    if (GetOpenFileNameStr(fileName)) {
        OutputFileEdit->SetText(fileName.c_str());
    }
}

void TMainDialog::CmPlaceNewOutput()
{
    owl::tstring fileName;
    if (GetSaveFileNameStr(fileName, _T("output.txt"))) {
        OutputFileEdit->SetText(fileName.c_str());
    }
}

void TMainDialog::CmProcess()
{
    TCHAR inputFileBuffer[MAX_PATH] = _T("");
    TCHAR outputFileBuffer[MAX_PATH] = _T("");

    GetDlgItemText(IDC_INPUT_FILE_EDIT, inputFileBuffer, MAX_PATH);
    GetDlgItemText(IDC_OUTPUT_FILE_EDIT, outputFileBuffer, MAX_PATH);

    owl::tstring wsInputFile(inputFileBuffer);
    owl::tstring wsOutputFile(outputFileBuffer);
    if (wsInputFile.empty() || wsOutputFile.empty()) {
        MessageBox(_T("Please select both input and output files."), _T("Error"), MB_OK | MB_ICONERROR);
        return;
    }

    ResultsListBox->ClearList();
    std::string inputFile(wsInputFile.begin(), wsInputFile.end());
    std::string outputFile(wsOutputFile.begin(), wsOutputFile.end());

    try {
        auto results = UIUtils::ProcessFiles(inputFile, outputFile);
        for (const auto& [expression, value] : results) {
            std::string formattedResult = UIUtils::FormatResult(value);
            owl::tstring displayText = owl::tstring(expression.begin(), expression.end()) + _T(" = ") + owl::tstring(formattedResult);
            ResultsListBox->AddString(displayText.c_str());
        }
        StatusStatic->SetText(_T("Processing complete. Check the output file."));
        InputFileEdit->SetText(_T(""));
        OutputFileEdit->SetText(_T(""));
    }
    catch (const std::exception& ex) {
        StatusStatic->SetText(_T("Error: ") + owl::tstring(ex.what()));
    }
}

void TMainDialog::CmCreateEquation()
{
    TCHAR buffer[256] = _T("");
    while (true)
    {
        owl::TInputDialog dlg(this, _T("Enter Equation"), _T("Equation:"), buffer, 256);
        if (dlg.Execute() != IDOK)
            break;

        owl::tstring equation(buffer);
        if (equation.empty())
        {
            MessageBox(_T("No equation entered."), _T("Info"), MB_OK);
            break;
        }

        try {
            std::string strEquation(equation.begin(), equation.end());
            Tree tree{};
            tree.buildTree(strEquation);
            auto root = tree.root;

            EvaluatorLoader loader = LoadCalculationDll();
            IEvaluator* evaluator = loader.create();

            double result = evaluator->Evaluate(root);
            int saveResponse = MessageBox(owl::tstring(strEquation.begin(), strEquation.end()) + _T(" = ") + std::to_string(result), _T("Save Result?"), MB_YESNO | MB_ICONQUESTION);

            if (saveResponse == IDYES) {
                owl::tstring filePath;
                if (GetOpenFileNameStr(filePath))
                {
                    std::wofstream outFile(filePath, std::ios::app);
                    if (outFile.is_open())
                    {
                        outFile << std::wstring(equation.begin(), equation.end()) << _T(" = ") << result << std::endl;
                        MessageBox(_T("Result saved successfully!"), _T("Success"), MB_OK | MB_ICONINFORMATION);
                    }
                    else
                    {
                        MessageBox(_T("Failed to save the file."), _T("Error"), MB_OK | MB_ICONERROR);
                    }
                }
            }
        }
        catch (const std::exception& ex)
        {
            owl::tstring werr = _T("Error: ") + owl::tstring(ex.what());
            MessageBox(werr.c_str(), _T("Error"), MB_OK | MB_ICONERROR);
        }
    }
}

LRESULT TMainDialog::EvDrawItem(WPARAM wParam, LPARAM lParam)
{
    const DRAWITEMSTRUCT* drawInfo = reinterpret_cast<const DRAWITEMSTRUCT*>(lParam);

    HDC hdc = drawInfo->hDC;
    RECT rect = drawInfo->rcItem;

    HBRUSH hBrush = CreateSolidBrush(RGB(124, 124, 124));
    FillRect(hdc, &rect, hBrush);
    DeleteObject(hBrush);

    ::SetTextColor(hdc, RGB(255, 255, 255));
    SetBkMode(hdc, TRANSPARENT);
    TCHAR text[256];
    GetDlgItemText(IDC_PROCESS_BUTTON, text, 256);
    DrawText(hdc, text, -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    HBRUSH hBorderBrush = CreateSolidBrush(RGB(0, 0, 0));
    FrameRect(hdc, &rect, hBorderBrush);
    DeleteObject(hBorderBrush);
    return 0;
}
