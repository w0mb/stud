using CommunityToolkit.Mvvm.ComponentModel;
using MVVM.Class;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MVVM.ViewModels
{
    public class DataGridViewModel : BaseViewModel
    {
        private ObservableCollection<User> _dataGrid;
        public ObservableCollection<User> DataGrid
        {
            get { return _dataGrid; }
            set { SetProperty(ref _dataGrid, value); }
        }

        private UserService _userService;


        public DataGridViewModel()
        {
            _userService = new UserService();
            DataGrid = new ObservableCollection<User>();
            LoadUsers();
        }

        private async Task LoadUsers()
        {
            List<User> users = await _userService.GetUsers();
            if (users != null)
            {
                foreach (var user in users)
                {
                    DataGrid.Add(user);
                }
            }
        }
    }
}
