using Avalonia.Controls;
using Avalonia.Input;
using Avalonia.Media.Imaging;

namespace Explorer;

public partial class MainWindow : Window
{
    public MainWindow()
    {
        InitializeComponent();
    }

    public void DoubleTappedHandler(object sender, TappedEventArgs args)
    {
        if (sender is ListBox listBox)
        {
            Explorer? explorer = (Explorer?)DataContext;

            if (listBox.SelectedItem is CollectionElement element)
                explorer.CurrentPath = element.Name;
        }
    }

    public void TappedHandler(object sender, TappedEventArgs args)
    {
        if (sender is ListBox listBox)
        {
            Explorer? explorer = (Explorer?)DataContext;

            if (listBox.SelectedItem is CollectionElement element)
            {
                if (Explorer.ChangeGrid(ref mainGrid, ref listBox, element.Name))
                    mainImage.Source = new Bitmap(explorer.CurrentPath + "\\" + element.Name);
            }
        }
    }
}