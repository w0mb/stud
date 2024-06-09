using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using Avalonia;
using Avalonia.Controls;
using Avalonia.Controls.Primitives;
using Avalonia.Data;
using Avalonia.Layout;
using Avalonia.Threading;
using hw_11.Entities;
using static Avalonia.AvaloniaProperty;

namespace hw_11.Components;

public class MyVisualizer : TemplatedControl
{
    public static readonly StyledProperty<object> VisualizingObjectProperty =
        Register<MyVisualizer, object>(
            nameof(VisualizingObject)
        );

    public object VisualizingObject
    {
        get => GetValue(VisualizingObjectProperty);
        set => SetValue(VisualizingObjectProperty, value);
    }

    private VisualizerViewModel viewModel = new VisualizerViewModel();

    protected override void OnApplyTemplate(TemplateAppliedEventArgs e)
    {
        base.OnApplyTemplate(e);

        CreateTreeFromObject(VisualizingObject);
        CreateExpanderFromObject(null, viewModel.FieldList);
        
        DataContext = viewModel;
    }

    public void CreateExpanderFromObject(Expander? parent, ObservableCollection<FieldNode>? nodes)
    {
        if (nodes == null || !viewModel.FieldList.Any())
            return;

        var itemsControl = new ItemsControl();

        foreach (var node in nodes)
        {
            if (node.SubNodes != null && node.SubNodes.Any())
            {
                var nodeExpander = new Expander
                {
                    Header = node.Name,
                    Margin = new Avalonia.Thickness(10),
                    HorizontalAlignment = HorizontalAlignment.Stretch
                    
                };


                CreateExpanderFromObject(nodeExpander, node.SubNodes);
                itemsControl.ItemsSource = itemsControl.Items.Append(nodeExpander);
            }
            else
            {
                var nameTb = new TextBlock()
                {
                    Text = node.Name + ": ",
                    VerticalAlignment = VerticalAlignment.Center,
                    HorizontalAlignment = HorizontalAlignment.Stretch,
                };
                var valueTb = new TextBox()
                {
                    Text = node.Value,
                    HorizontalAlignment = HorizontalAlignment.Stretch,
                    HorizontalContentAlignment = HorizontalAlignment.Center
                };

                var stackPanel = new StackPanel()
                {
                    Orientation = Orientation.Horizontal,
                    Children =
                    {
                        nameTb, valueTb
                    }
                };
                itemsControl.ItemsSource = itemsControl.Items.Append(stackPanel);
            }
        }

        if (parent == null)
        {
            viewModel.ExpanderHolder = itemsControl;
        }
        else
        {
            parent.Content = itemsControl;
        }
    }

    public void CreateTreeFromObject(object? obj, ObservableCollection<FieldNode>? branch = null)
    {
        if (obj == null) return;

        if (branch == null)
        {
            branch = viewModel.FieldList;
            branch.Clear();
        }

        var type = obj.GetType();
        var rootNode = new FieldNode(type.Name);
        branch.Add(rootNode);

        if (type.IsClass && type != typeof(string))
        {
            var properties = type.GetProperties();
            foreach (var property in properties)
            {
                var propertyValue = property.GetValue(obj);

                if (propertyValue != null)
                {
                    if (propertyValue.GetType().IsClass && propertyValue.GetType() != typeof(string))
                    {
                        var subNode = new FieldNode(property.Name);
                        rootNode.SubNodes.Add(subNode);
                        CreateTreeFromObject(propertyValue, subNode.SubNodes);
                    }
                    else
                    {
                        rootNode.SubNodes.Add(new FieldNode(property.Name, propertyValue.ToString()));
                    }
                }
                else
                {
                    rootNode.SubNodes.Add(new FieldNode($"{property.Name}", "null"));
                }
            }
        }
    }
}