using Avalonia.Controls;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Threading.Tasks;
using MVVM.Class;
using CommunityToolkit.Mvvm.ComponentModel;

namespace MVVM.ViewModels
{
    public class TreeViewViewModel : BaseViewModel
    {
        private ObservableCollection<User> _dataTree;
        public ObservableCollection<User> DataTree
        {
            get { return _dataTree; }
            set { SetProperty(ref _dataTree, value); }
        }

        private UserService _userService;


        public TreeViewViewModel()
        {
            _userService = new UserService();
           DataTree = new ObservableCollection<User>();
            LoadUsers();
        }

        private async Task LoadUsers()
        {
            List<User> users = await _userService.GetUsers();
            if (users != null)
            {
                foreach (var user in users)
                {
                    DataTree.Add(user);
                }
            }
        }
    }
}
