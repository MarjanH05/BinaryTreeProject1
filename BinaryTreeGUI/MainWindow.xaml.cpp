#include "pch.h"
#include <shobjidl.h> 
#include "MainWindow.xaml.h"
#include "../BinaryTree/FileManager.h"
#include "MainWindow.g.cpp"
#include <winrt/Windows.Storage.Pickers.h>
#include <winrt/Windows.Storage.h>
#include <iomanip>  
#include <sstream>  


using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Windows::Storage;
using namespace Windows::Storage::Pickers;

namespace winrt::BinaryTreeGUI::implementation
{
    int32_t MainWindow::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void MainWindow::MyProperty(int32_t /*value*/)
    {
        throw hresult_not_implemented();
    }



    Windows::Foundation::IAsyncAction MainWindow::SelectInputFile_Click(IInspectable const& /*sender*/, RoutedEventArgs const& /*args*/)
    {
        FileOpenPicker picker;
        picker.FileTypeFilter().Append(L".txt");
        auto hwnd = ::GetActiveWindow();
        picker.as<::IInitializeWithWindow>()->Initialize(hwnd);
        StorageFile file = co_await picker.PickSingleFileAsync();
        if (file)
        {
            InputFileTextBox().Text(file.Path());
        }
    }


    Windows::Foundation::IAsyncAction MainWindow::SelectExistingOutput_Click(winrt::Windows::Foundation::IInspectable const& sender,
        winrt::Microsoft::UI::Xaml::RoutedEventArgs const& args)
    {
        FileOpenPicker picker;
        picker.ViewMode(PickerViewMode::List);
        picker.FileTypeFilter().Append(L".txt");

        auto hwnd = ::GetActiveWindow(); 
        picker.as<::IInitializeWithWindow>()->Initialize(hwnd);
        StorageFile file = co_await picker.PickSingleFileAsync();
        if (file)
        {
            OutputFileTextBox().Text(file.Path());
        }
        co_return;
    }

    Windows::Foundation::IAsyncAction MainWindow::PlaceNewOutput_Click(winrt::Windows::Foundation::IInspectable const& sender,
        winrt::Microsoft::UI::Xaml::RoutedEventArgs const& args)
    {
        FileSavePicker picker;
        picker.SuggestedFileName(L"output.txt");
        picker.FileTypeChoices().Insert(L"Text Files", winrt::single_threaded_vector<hstring>({ L".txt" }));
        auto hwnd = ::GetActiveWindow();
        picker.as<::IInitializeWithWindow>()->Initialize(hwnd);
        StorageFile file = co_await picker.PickSaveFileAsync();
        if (file)
        { 
            OutputFileTextBox().Text(file.Path());
        }
        co_return;
    }


    void MainWindow::ProcessButton_Click(IInspectable const& /*sender*/, RoutedEventArgs const& /*args*/)
    {
        try
        {
            std::string inputFile = winrt::to_string(InputFileTextBox().Text());
            std::string outputFile = winrt::to_string(OutputFileTextBox().Text());

            if (inputFile.empty() || outputFile.empty())
            {
                StatusText().Text(L"Please select both input and output files.");
                return;
            }

            ResultsPanel().Children().Clear();

            FileManager fm;
            fm.SetFiles(inputFile, outputFile);
            fm.readFile();

            auto results = fm.GetResults();
            for (const auto& [expression, result] : results)
            {
                auto textBlock = winrt::Microsoft::UI::Xaml::Controls::TextBlock();

                std::ostringstream stream;
                stream << std::fixed << std::setprecision(4) << result;
                std::string formattedResult = stream.str();

                formattedResult.erase(formattedResult.find_last_not_of('0') + 1, std::string::npos);
                if (formattedResult.back() == '.')
                    formattedResult.pop_back();

                std::string displayText = expression + " = " + formattedResult;
                textBlock.Text(winrt::to_hstring(displayText));
                textBlock.Margin({ 0, 5, 0, 0 });
                ResultsPanel().Children().Append(textBlock);
            }

            StatusText().Text(L"Processing complete. Check the output file.");
            InputFileTextBox().Text(L"");
            OutputFileTextBox().Text(L"");
        }
        catch (const std::exception& ex)
        {
            StatusText().Text(winrt::to_hstring(std::string("Error: ") + ex.what()));
        }
    }

}