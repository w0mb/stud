using Avalonia;
using Avalonia.Controls;
using Avalonia.Input;
using Avalonia.Controls.Primitives;
using Avalonia.Media;
using Homework_LogicalApp.Controls;
using Homework_LogicalApp.ViewModels;
using ReactiveUI;
using System;
using Avalonia.Threading;
using System.Reactive.Linq;
using System.Reactive;
using Avalonia.LogicalTree;
using System.Linq;
using Avalonia.Interactivity;
using Homework_LogicalApp.Helpers;
using System.Collections.Generic;
using Homework_LogicalApp.Models;
using Avalonia.Platform.Storage;
using System.IO;
using System.Threading.Tasks;
using DynamicData;
using Avalonia.Rendering;
using System.Text.Json;
using Avalonia.Markup.Xaml.MarkupExtensions;

namespace Homework_LogicalApp.Views;

public partial class MainWindow : Window
{
    private Connectable? activeItem;
    private Connectable? connectableFirst;
    public ReactiveCommand<Unit, Unit> ComponentRefreshCommand { get; set; }
    public MainWindow()
    {
        InitializeComponent();
        Loaded += (s, e) => Init();
    }

    private void Init()
    {
        Canvas cnv = this.FindControl<Canvas>("canv") 
            ?? throw new UnhandledErrorException("Canvas not found!");
        ListBox exampleLb = this.FindControl<ListBox>("ExamplesLb") 
            ?? throw new UnhandledErrorException("ExamplesLb not found!");
        MenuItem saveItem = this.FindControl<MenuItem>("saveBtn")
            ?? throw new UnhandledErrorException("saveBtn not found!");
        MenuItem openItem = this.FindControl<MenuItem>("openBtn")
            ?? throw new UnhandledErrorException("openBtn not found!");
        MenuItem exitItem = this.FindControl<MenuItem>("exitBtn")
            ?? throw new UnhandledErrorException("exitBtn not found!");

        saveBtn.Click += HandleSaveClick;
        openItem.Click += HandleOpenClick;
        exitBtn.Click += HandleExitClick;

        if (DataContext is not MainWindowViewModel viewModel) throw new UnhandledErrorException("DataContext not found!");

        foreach (var item in viewModel.Items)
        {
            cnv.Children.Add(item);
        }
        
        exampleLb.DoubleTapped += (s, e) =>
        {
            if (exampleLb.SelectedItem == null) return;
            var selectedControl = (Control)exampleLb.SelectedItem;
            Type type = selectedControl.GetType();
            if (type.IsClass)
            {
                object? instance = Activator.CreateInstance(
                    type, 
                    MainWindowViewModel.GetId(),
                    new Point(Width/2, Height/2));

                if (instance is Connectable newInstance)
                {
                    viewModel.Items.Add(newInstance);
                    cnv.Children.Add(newInstance);
                    newInstance.InvalidateVisual();
                }
            }
        };
        
        var intervalObservable = Observable.Interval(TimeSpan.FromMilliseconds(50))
            .Select(_ => Unit.Default);

        ComponentRefreshCommand = ReactiveCommand.Create(() => {
            foreach (var item in viewModel.Items)
            {
                Dispatcher.UIThread.InvokeAsync(()=> item.InvalidateVisual());
            }
        });

        intervalObservable.InvokeCommand(ComponentRefreshCommand);
    }

    public override void Render(DrawingContext context)
    {
        base.Render(context);
    }

    protected override async void OnKeyDown(KeyEventArgs e)
    {
        base.OnKeyDown(e);
        
        if (DataContext is not MainWindowViewModel viewModel) return;
        var item = GetClickedComponent();
        
        if(e.Key == Key.Escape)
        {
            if(activeItem != null)
            {
                activeItem.IsSelected = false;
                activeItem = null;
            }

            if(connectableFirst != null) {
                connectableFirst.IsSelected = false;
                connectableFirst = null;
            }
        }

        if (e.Key == Key.Delete)
        {
            if (item == null) return;
            if (item is InputControler)
            {
                if (item.output_el is not null)
                {
                    item.output_el!.input_el = null;
                    if (item is not Connector)
                    {
                        foreach (var searchItem in viewModel.Items)
                        {
                            if (searchItem is Connector con)
                            {
                                if (con.input_el.output_el == null || con.output_el!.input_el == null)
                                {
                                    await Console.Out.WriteLineAsync("deleteing connector");
                                    viewModel.Items.Remove(con);
                                    canv.Children.Remove(con);
                                    break;
                                }
                            }
                        }
                    }
                }
                viewModel.Items.Remove(item);
                canv.Children.Remove(item);
            }
            else if (item is OutputControler)
            {
                if (item.input_el is not null)
                {
                    item.input_el!.output_el = null;
                    if (item is not Connector)
                    {
                        foreach (var searchItem in viewModel.Items)
                        {
                            if (searchItem is Connector con)
                            {
                                if (con.input_el.output_el == null || con.output_el!.input_el == null)
                                {
                                    await Console.Out.WriteLineAsync("deleteing connector");
                                    viewModel.Items.Remove(con);
                                    canv.Children.Remove(con);
                                    break;
                                }
                            }
                        }
                    }
                }
                viewModel.Items.Remove(item);
                canv.Children.Remove(item);
            }
            else
            {
                if (item.output_el == null &&  item.input_el == null)
                {
                    viewModel.Items.Remove(item);
                    canv.Children.Remove(item);
                }
                else if (item.output_el == null)
                {
                    if (item.input_el is AndControl a)
                    {
                        a.flushTempArray();
                    }
                    item.input_el!.output_el = null;
                }
                else if (item.input_el == null)
                {
                    item.output_el.input_el = null;
                }
                else
                {
                    if (item.input_el is AndControl a)
                    {
                        a.flushTempArray();
                    }
                    item.input_el.output_el = null;
                    item.output_el.input_el = null;
                }
                
                if (item is not Connector)
                {
                    foreach (var searchItem in viewModel.Items.ToArray())
                    {
                        if (searchItem is Connector con)
                        {
                            if (con.input_el == item|| con.output_el == item)
                            {
                                await Console.Out.WriteLineAsync("deleteing connector");
                                viewModel.Items.Remove(con);
                                canv.Children.Remove(con);
                            }
                        }
                    }
                }
                viewModel.Items.Remove(item);
                canv.Children.Remove(item);
            }
        }
        if (item is InputControler)
        {
            if (e.Key == Key.Q)
            {
                if (item == null) return;
                if (item.CountInput is < 4 and >= 1)
                {
                    Point save = item.Position;
                    item.Width = (item.CountInput + 1) * 20 + 15;
                    await Task.Delay(25);
                    item.SetPosition(save);
                    item.CountInput += 1;
                    item.BoolArrayOut.Add(false);
                }
            }

            if (e.Key == Key.W)
            {
                if (item == null) return;
                if (item.CountInput is <= 4 and > 1)
                {
                    Point save = item.Position;
                    item.Width = (item.CountInput - 1) * 20 + 15;
                    await Task.Delay(25);
                    item.SetPosition(save);
                    item.CountInput -= 1;
                    item.BoolArrayOut.RemoveAt(item.BoolArrayOut.Count - 1);
                }
            }
        }
    }
    
    protected override void OnPointerPressed(PointerPressedEventArgs e)
    {
        base.OnPointerPressed(e);

        if (DataContext is not MainWindowViewModel viewModel) return;
        var pointer = e.GetCurrentPoint(this);
        var item = GetClickedComponent();
        
        if (item is Connector) return;

        if (pointer.Properties.IsRightButtonPressed)
        {
            if (item == null) return;
            item.IsSelected = true;
            activeItem = item;
        }

        if(pointer.Properties.IsMiddleButtonPressed)
        {
            if(connectableFirst == null)
            {
                if (item == null) return;

                item.IsSelected = true;
                connectableFirst = item;
            } 
            else
            {
                if (item == null) return;
                if (connectableFirst.Id == item.Id ||
                    (connectableFirst is InputControler) && (item is InputControler) ||
                    (connectableFirst is OutputControler) && (item is OutputControler))
                    return;

                Connector conn;
                if (connectableFirst is OutputControler || item is InputControler)
                {
                    if (connectableFirst is BufferControl or InverterConrol or OutputControler && connectableFirst.input_el != null) return;
                    else if (connectableFirst.isFull())
                    {
                        Console.WriteLine("isfull");
                        return;
                    }
                    if (item.output_el != null) return;
                    connectableFirst.IsSelected = false;
                    conn = new Connector(MainWindowViewModel.GetId(), item, connectableFirst);
                }
                else
                {
                    if (item is BufferControl or InverterConrol or OutputControler && item.input_el != null) return;
                    else if (item.isFull()) return;
                    if (connectableFirst.output_el != null) return;
                    connectableFirst.IsSelected = false;
                    conn = new Connector(MainWindowViewModel.GetId(), connectableFirst, item);
                }
                viewModel.Items.Add(conn);
                canv.Children.Add(conn);
                connectableFirst = null;

                foreach (var it in viewModel.Items)
                {
                    it.InvalidateVisual();
                }
            }
        }
    }

    private Connectable? GetClickedComponent()
    {
        if (DataContext is not MainWindowViewModel viewModel) return null;
        foreach (var item in viewModel.Items)
        {
            if (item.IsPointerOver)
            {
                return item;
            }
        }

        return null;
    }

    protected override void OnPointerMoved(PointerEventArgs e)
    {
        base.OnPointerMoved(e);
        if (DataContext is not MainWindowViewModel viewModel) throw new UnhandledErrorException("DataContext not found!");
        if (activeItem == null) return;

        var mouse_pos = e.GetCurrentPoint(this as Control);
        if (activeItem is Connectable draggable)
        {
            draggable.SetPosition(mouse_pos.Position);
        }
    }

    protected override void OnPointerReleased(PointerReleasedEventArgs e)
    {
        base.OnPointerReleased(e);
        if (activeItem is Connectable component)
        {
            component.IsSelected = false;
            component.InvalidateVisual();
        }
        activeItem = null;
    }

    public void ClearCanvas()
    {
        if (DataContext is not MainWindowViewModel viewModel)
            throw new InvalidOperationException("DataContext not found!");

        viewModel.Items.Clear();
        var connectables = canv.Children.OfType<Connectable>().ToList();
        foreach (var connectable in connectables)
        {
            canv.Children.Remove(connectable);
        }

        canv.InvalidateVisual();
    }

    public void HandleExitClick(object? s, RoutedEventArgs e)
    {
       ClearCanvas();

    }

    public async void HandleOpenClick(object? s, RoutedEventArgs e)
    {
        if (DataContext is not MainWindowViewModel viewModel) throw new UnhandledErrorException("DataContext not found!");
        
        ClearCanvas();

        var topLevel = TopLevel.GetTopLevel(this);

        var files = await topLevel.StorageProvider.OpenFilePickerAsync(new FilePickerOpenOptions
        {
            Title = "Open Text File",
            AllowMultiple = false,
            FileTypeFilter = new List<FilePickerFileType>
            {
                new FilePickerFileType("sqlite")
                {
                    Patterns = new List<string> { "*.sqlite" }
                }
            }
        });

        if (files.Count != 1) return;

        List<ConnectableModel> Serialized = ComponentRepository.GetAll(files[0].Path.AbsolutePath);

        foreach(var item in Serialized)
        {
            var des = ControlSerializer.Deserialize(item);
            if (des != null && item.Name != "Connector")
            {
                viewModel.Items.Add(des);
                canv.Children.Add(des);
            }
        }

        foreach (var item in Serialized)
        {
            var des = ControlSerializer.Deserialize(item);
            if (des != null && item.Name == "Connector")
            {
                des.input_el = viewModel.Items.FirstOrDefault(e=> e.Id == item.InputId);
                des.output_el = viewModel.Items.FirstOrDefault(e => e.Id == item.OutputId);

                des.output_el.input_el = des.input_el;
                des.input_el.output_el = des.output_el;
                
                viewModel.Items.Add(des);
                canv.Children.Add(des);
                des.InvalidateVisual();

            }
        }

    }
    public async void HandleSaveClick(object? s, RoutedEventArgs e)
    {
        if (DataContext is not MainWindowViewModel viewModel) throw new UnhandledErrorException("DataContext not found!");
        var topLevel = TopLevel.GetTopLevel(this);
        // Start async operation to open the dialog.
        var file = await topLevel.StorageProvider.SaveFilePickerAsync(new FilePickerSaveOptions
        {
            Title = "Save Text File",
            DefaultExtension = ".sqlite",
            FileTypeChoices = new List<FilePickerFileType>
            {
                new FilePickerFileType("sqlite")
                {
                    Patterns = new List<string> { "*.sqlite" }
                }
            }
        });

        if (file is not null)
        {
            foreach (var item in viewModel.Items)
            {
                var serialized = ControlSerializer.Serialize(item);
                ComponentRepository.InsertOne(file.Path.AbsolutePath, serialized);
            }
            
        }
    }
}
