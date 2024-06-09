using System.ComponentModel;
using System.Runtime.CompilerServices;
using System.Windows;
using Avalonia.Controls;
using Avalonia.Interactivity;
using MVVM.ViewModels;

namespace MVVM.Views
{
    public partial class MainWindow : Window, INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;

        private BaseViewModel _selectedViewModel;

        public BaseViewModel SelectedViewModel
        {
            get { return _selectedViewModel; }
            set
            {
                _selectedViewModel = value;
                OnPropertyChanged();
            }
        }

        public MainWindow()
        {
            InitializeComponent();
            DataContext = this; // Установка DataContext на само окно
            SelectedViewModel = new DataGridViewModel(); // По умолчанию выбрана DataGridViewModel
        }

        private void RadioButton_Checked(object sender, RoutedEventArgs e)
        {
            if (sender is RadioButton radioButton && radioButton.IsChecked == true)
            {
                if (radioButton.Content.ToString() == "Data Grid View")
                    SelectedViewModel = new DataGridViewModel();
                else if (radioButton.Content.ToString() == "Tree View")
                    SelectedViewModel = new TreeViewViewModel();
            }
        }

        protected virtual void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}
