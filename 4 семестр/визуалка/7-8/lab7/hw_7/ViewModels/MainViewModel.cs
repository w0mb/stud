using Avalonia;
using Avalonia.Threading;
using hw_7.Services;
using Microsoft.CodeAnalysis;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Collections.Specialized;
using System.IO;
using System.Reactive;
using System.Reactive.Linq;
using System.Threading;
using System.Threading.Tasks;

namespace hw_7.ViewModels;

public class MainViewModel : ViewModelBase
{
    public UserService _userService = new();
    public ObservableCollection<User> Users { get; set; } = new ObservableCollection<User>();

    private string _loggingFilePath = "D:\\logs.txt";

    public MainViewModel()
    {
        Task.Run(InitData);
    }

    private async void InitData()
    {
        await LoadUsers();

        var collectionObservable = ObservableCollectionFactory.CreateCollectionObserver<User>(Users);
        collectionObservable.Subscribe((eventData) =>
        {
            var collection = eventData.Sender as ObservableCollection<User>;
            using (StreamWriter sw = File.AppendText(_loggingFilePath))
            {

                sw.WriteLine($"{DateTime.Now.ToString("dd.MM.yyyy HH:mm")} | Collection action: {eventData.EventArgs.Action}, New Size: {collection.Count}");
            }
        });

        var itemsObservable = ObservableCollectionFactory.CreateItemsObserver<User>(Users);
        itemsObservable.Subscribe((eventData) => {
            if(eventData.Sender is User user)
            {
                using (StreamWriter sw = File.AppendText(_loggingFilePath))
                {
                    var userName = user.GetType()?.GetProperty(eventData.EventArgs.PropertyName ?? "")?.GetValue(user, null) ?? "UNKNOWN";
                    sw.WriteLine($"{DateTime.Now.ToString("dd.MM.yyyy HH:mm")} | Collection item action: {eventData.EventArgs.PropertyName} changed to {userName}");
                }
            }
        });
    }

    public void AddUser()
    {
        Users.Add(new User()
        {
            Address = new Address(),
            Company = new Company(),
            Email = "",
            Id = new Random().Next(100, 99999),
            Name = "",
            Phone = "",
            Username = "",
            Website = "",
        });
    }

    public void RemoveUser(object? user)
    {
        if(user is User usr) {
            Users.Remove(usr);
        }
    }

    public async Task LoadUsers()
    {
        List<User> data = await _userService.GetUsers();


        Dispatcher.UIThread.Invoke(() =>
        {
            foreach (User user in data)
            {
                Users.Add(user);
            }
        });
    }
}