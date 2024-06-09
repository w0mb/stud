using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Runtime.CompilerServices;
using Avalonia.Media.Imaging;
using System.IO;
using System.Linq;
using Avalonia.Controls;
using System;
using Avalonia.LogicalTree;

namespace Explorer;
    
internal class Explorer : INotifyPropertyChanged
{
    public Explorer()
    {
        _path = "";
        _directory = [];
        _image = new Bitmap("images\\folder.png");
        SetDirectory();
    }

    public ObservableCollection<CollectionElement> ShownDirectory
    {
        get
        {
            return _directory;
        }
        set
        {
            _ = SetField(ref _directory, value);
        }
    }

    public string CurrentPath
    {
        get
        {
            return _path;
        }
        set
        {
            SetPath(ref _path, value);
        }
    }

    public Bitmap ShownImage
    {
        get
        {
            return _image;
        }
        set
        {
            _image = value;
        }
    }
    private string _path;

    private ObservableCollection<CollectionElement> _directory;

    private Bitmap _image;

    public event PropertyChangedEventHandler? PropertyChanged;

    public void SetDirectory()
    {   
        if (!string.IsNullOrEmpty(_path))
        {
            _directory.Clear();
            ToolTip dotToolTip = new ToolTip
            {
                Content = _path
            };

            string[] directories = Directory.GetDirectories(_path);
            string[] files = Directory.GetFiles(_path);

            _directory.Add(new CollectionElement("..", GetIcon(DeleteLastDirectory(_path)), dotToolTip));

            foreach (string directory in directories)
            {
                ToolTip toolTip = new()
                {
                    Content = directory
                };

                string name = directory.Replace(_path, "");
                _directory.Add(new CollectionElement(name, GetIcon(AddDirectory(_path, name)), toolTip));
            }
            foreach (string file in files)
            {
                List<string> extensions = [".jpg", ".jpeg", ".png", ".bmp", ".gif", ".tiff", ".ico", ".svg"];
                foreach (string extension in extensions)
                {
                    if (file.Contains(extension))
                    {
                        ToolTip toolTip = new ToolTip
                        {
                            Content = file
                        };
                        string name = file.Replace(_path, "");
                        string nextPath = AddDirectory(_path, name);
                        _directory.Add(new CollectionElement(name, GetIcon(nextPath), toolTip));
                    }
                }
            }
        }
        else
        {
            _directory.Clear();
            List<string> diskNames = DriveInfo.GetDrives().Select(disk => disk.Name).ToList();
            foreach (string name in diskNames)
            {
                ToolTip toolTip = new()
                {
                    Content = name
                };

                _directory.Add(new CollectionElement(name, GetIcon(_path), toolTip));
            }
        }
    }

    public static bool ChangeGrid(ref Grid mainGrid, ref ListBox listBox, string name)
    {
        List<string> extensions = [".jpg", ".jpeg", ".png", ".bmp", ".ico", ".svg"];
        string mainGridDefinition = "*, 0";
        string childGridsDefinition = "0.07*, *";
        bool isFound = false;
        
        foreach (string extension in extensions)
        {
            if (name.Contains(extension))
            {
                mainGridDefinition = "0.4*, *";
                childGridsDefinition = "0.33*, *";
                isFound = true;
            }
        }

        mainGrid.ColumnDefinitions = new ColumnDefinitions(mainGridDefinition);
        List<ILogical> childItems = listBox.GetLogicalDescendants().Where(c => c is Grid g).ToList();

        foreach (var item in childItems)
            ((Grid)item).ColumnDefinitions = new ColumnDefinitions(childGridsDefinition);

        return isFound;
    }

    private static string DeleteLastDirectory(string path)
    {
        path = path[..^1];
        if (path.Contains('\\'))
        {
            List<string> splitPath = path.Split('\\').ToList();
            splitPath.RemoveAt(splitPath.Count - 1);
            path = string.Join('\\', splitPath);
            path += "\\";
        }
        else
            path = "";

        return path;
    }

    public static string AddDirectory(string path, string directory)
    {
        path += directory;
        if (!directory.Contains('\\'))
            path += "\\";

        return path;
    }

    private void SetPath(ref string _path, string value)
    {
        if (value.Equals(".."))
            _path = DeleteLastDirectory(_path);
        else
        {
            string tempPath = AddDirectory(_path, value);
            if (Directory.Exists(tempPath))
                _path = tempPath;
        }

        SetDirectory();
    }

    private static Bitmap GetIcon(string path)
    {
        if (Directory.Exists(path))
            return new Bitmap("images\\folder.png");
        if (string.IsNullOrEmpty(path) || path.Count(ch => ch.Equals("\\")) == 1)
            return new Bitmap("images\\disk.png");
        else
            return new Bitmap("images\\file.png");
    }

    protected virtual void OnPropertyChanged([CallerMemberName] string? propertyName = null)
    {
        PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
    }

    protected bool SetField<T>(ref T field, T value, [CallerMemberName] string? propertyName = null)
    {
        if (EqualityComparer<T>.Default.Equals(field, value)) return false;
        field = value;
        OnPropertyChanged(propertyName);
        return true;
    }
}