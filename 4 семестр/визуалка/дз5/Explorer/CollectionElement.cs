using Avalonia.Controls;
using Avalonia.Media.Imaging;

class CollectionElement(string name, Bitmap icon, ToolTip toolTip)
{
    public string Name
    {
        get
        {
            return _name;
        }
        set
        {
            _name = value;
        }
    }

    public Bitmap Icon
    {
        get
        {
            return _icon;
        }
        set
        {
            _icon = value;
        }
    }

    public ToolTip ToolTip
    {
        get
        {
            return _toolTip;
        }
        set
        {
            _toolTip = value;
        }
    }

    private string _name = name;
    private Bitmap _icon = icon;

    private ToolTip _toolTip = toolTip;
}