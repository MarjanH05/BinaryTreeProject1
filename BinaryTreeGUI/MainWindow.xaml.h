#pragma once
#include <MainWindow.g.h>
#include <winrt/Microsoft.UI.Windowing.h>

#include "../BinaryTree/TreeNode.h"

namespace winrt::BinaryTreeGUI::implementation
{
    struct MainWindow : MainWindowT<MainWindow>
    {
        MainWindow()
        {
            auto appWindow = this->AppWindow();
            appWindow.SetIcon(L"C:\\Users\\Marjan Hussain\\source\\repos\\BinaryTree\\BinaryTreeGUI\\Assets\\menu_one.ico");
            InitializeComponent();
        }


        int32_t MyProperty();
        void MyProperty(int32_t value);
        Windows::Foundation::IAsyncAction SelectInputFile_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& args);
        Windows::Foundation::IAsyncAction SelectExistingOutput_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& args);
        Windows::Foundation::IAsyncAction PlaceNewOutput_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void ProcessButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& args);
    };
}

namespace winrt::BinaryTreeGUI::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}
