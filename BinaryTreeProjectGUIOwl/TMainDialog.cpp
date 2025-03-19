#include "TMainDialog.h"
#include <owl/applicat.h>
#include <owl/control.h>
#include <owl/framewin.h>
#include <owl/inputdia.h>

#include <windows.h>
#include <commdlg.h>
#include <sstream>
#include <iomanip>
#include <stdexcept>

#include "Resource.h"
#include "FileProcessor.h"
#include "../BinaryTree/FileManager.h"

using namespace owl;

DEFINE_RESPONSE_TABLE1(TMainDialog, TDialog)
EV_COMMAND(IDC_SELECT_INPUT_BUTTON, CmSelectInput),
EV_COMMAND(IDC_SELECT_EXISTING_BUTTON, CmSelectExisting),
EV_COMMAND(IDC_PLACE_NEW_BUTTON, CmPlaceNewOutput),
EV_COMMAND(IDC_PROCESS_BUTTON, CmProcess),
EV_COMMAND(IDC_CREATE_EQUATION, CmCreateEquation), 
END_RESPONSE_TABLE;

TMainDialog::TMainDialog(owl::TWindow* parent)
    : TDialog(parent, IDD_BINARYTREEGUI), ResultsListBox(new owl::TListBox(this, IDC_RESULTS_LIST)) {
}

bool TMainDialog::GetOpenFileNameStr(owl::tstring& fileName)
{
    OPENFILENAME ofn = { NULL };
    TCHAR szFile[MAX_PATH] = _T("");
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = GetHandle();
    ofn.lpstrFilter = _T("Text Files\0*.txt\0");
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = MAX_PATH;

    if (GetOpenFileName(&ofn))
    {
        fileName = szFile;
        return true;
    }
    return false;
}

bool TMainDialog::GetSaveFileNameStr(owl::tstring& fileName, LPCTSTR suggestedName) {
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
    if (GetOpenFileNameStr(fileName))
    {
        SetDlgItemText(IDC_INPUT_FILE_EDIT, fileName.c_str());
    }
}

void TMainDialog::CmSelectExisting() {
    owl::tstring fileName;
    if (GetOpenFileNameStr(fileName)) {
        SetDlgItemText(IDC_OUTPUT_FILE_EDIT, fileName.c_str());
    }
}

void TMainDialog::CmPlaceNewOutput() {
    owl::tstring fileName;
    if (GetSaveFileNameStr(fileName, _T("output.txt"))) {
        SetDlgItemText(IDC_OUTPUT_FILE_EDIT, fileName.c_str());
    }
}

void TMainDialog::CmProcess() {
    TCHAR inputFileBuffer[MAX_PATH] = _T("");
    TCHAR outputFileBuffer[MAX_PATH] = _T("");
    GetDlgItemText(IDC_INPUT_FILE_EDIT, inputFileBuffer, MAX_PATH);
    GetDlgItemText(IDC_OUTPUT_FILE_EDIT, outputFileBuffer, MAX_PATH);

    owl::tstring wsInputFile(inputFileBuffer), wsOutputFile(outputFileBuffer);
    if (wsInputFile.empty() || wsOutputFile.empty()) {
        SetDlgItemText(IDC_STATUS_STATIC, _T("Please select both input and output files."));
        return;
    }

    ResultsListBox->ClearList();
    std::string inputFile(wsInputFile.begin(), wsInputFile.end());
    std::string outputFile(wsOutputFile.begin(), wsOutputFile.end());

    try {
        auto results = ProcessFiles(inputFile, outputFile);
        for (const auto& [expression, value] : results) {
            std::string formattedResult = FormatResult(value);
            owl::tstring displayText = owl::tstring(expression.begin(), expression.end()) + _T(" = ") + owl::tstring(formattedResult.begin(), formattedResult.end());
            ResultsListBox->AddString(displayText.c_str());
        }
        SetDlgItemText(IDC_STATUS_STATIC, _T("Processing complete. Check the output file."));
        SetDlgItemText(IDC_INPUT_FILE_EDIT, _T(""));
        SetDlgItemText(IDC_OUTPUT_FILE_EDIT, _T(""));
    }
    catch (const std::exception& ex) {
        owl::tstring werr = _T("Error: ") + owl::tstring(ex.what(), ex.what() + strlen(ex.what()));
        SetDlgItemText(IDC_STATUS_STATIC, werr.c_str());
    }
}

void TMainDialog::CmCreateEquation()
{
    TCHAR buffer[256] = _T("");
    while (true) {
        owl::TInputDialog dlg(this, _T("Enter Equation"), _T("Equation:"), buffer, 256);
        if (dlg.Execute() != IDOK) break;

        owl::tstring equation(buffer);
        if (equation.empty())
        {
            MessageBox(_T("No equation entered."), _T("Info"), MB_OK);
            continue;
        }

        try {
            std::string strEquation(equation.begin(), equation.end());
            Tree tree;
            tree.buildTree(strEquation);
            auto root = tree.root;

            EvaluatorLoader loader = LoadCalculationDll();
            IEvaluator* evaluator = loader.create();
            double result = evaluator->Evaluate(root);

            int saveResponse = MessageBox(owl::tstring(strEquation.begin(), strEquation.end()) + _T(" = ") + std::to_string(result), _T("Save Result?"), MB_YESNO | MB_ICONQUESTION);

            if (saveResponse == IDYES)
            {
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
            owl::tstring werr = _T("Error: ") + owl::tstring(ex.what(), ex.what() + strlen(ex.what()));
            MessageBox(werr.c_str(), _T("Error"), MB_OK | MB_ICONERROR);
        }
    }
}
