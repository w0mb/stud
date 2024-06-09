using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using Avalonia.Controls;
using Avalonia.Layout;
using CommunityToolkit.Mvvm.ComponentModel;


namespace hw_11.Components;

public class FieldNode
{
    public ObservableCollection<FieldNode>? SubNodes { get; } = new ObservableCollection<FieldNode>();
    public string Name { get; }
    public string Value { get; }

    public FieldNode(string name)
    {
        Name = name;
    }
    
    public FieldNode(string name, string value)
    {
        Name = name;
        Value = value;
    }

    public FieldNode(string name, ObservableCollection<FieldNode> subNodes)
    {
        Name = name;
        SubNodes = subNodes;
    }
}

public partial class VisualizerViewModel : ObservableObject
{
    public ObservableCollection<FieldNode> FieldList { get; set; } = new ObservableCollection<FieldNode>();
    [ObservableProperty] public object? _expanderHolder = null;
}