using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using MVVM.Class;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Threading.Tasks;

namespace MVVM.ViewModels;

public partial class MainViewModel : ObservableObject
{
    [ObservableProperty]private object content;
    [ObservableProperty]private ObservableCollection<BaseViewModel> vmbaseCollection;
    public RelayCommand<object> SwitchViewCommand { get; }
    public MainViewModel() {
        vmbaseCollection = new ObservableCollection<BaseViewModel>
        {
            new DataGridViewModel(),
            new TreeViewViewModel()
        };

        Content = null;
        SwitchViewCommand = new RelayCommand<object>(SwitchView);
    }

    private void SwitchView(object parameter)
    {
        if (parameter is BaseViewModel selectedViewModel)
        {
            Content = selectedViewModel;
        }
    }


}
