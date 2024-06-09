using Avalonia.Controls;
using Avalonia.Input;
using Avalonia.Interactivity;
using System.Threading.Tasks;

namespace Weather;

public partial class MainWindow : Window
{
    public MainWindow()
    {
        InitializeComponent();
    }

    private void TappedHandler(object? sender, TappedEventArgs e)
    {
        Weather? weather = (Weather?)DataContext;

        if (weather == null)
            return;

        Task.Run(async () =>
        {
            await weather.SetProperty("Loading data...");
        });
        Task.Run(async () =>
        {
            await weather.SetAllComponents();
        });
    }
}