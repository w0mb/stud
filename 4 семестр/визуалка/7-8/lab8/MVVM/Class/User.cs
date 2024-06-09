using CommunityToolkit.Mvvm.ComponentModel;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MVVM.Class
{
    public class Address
    {
        public string? Street { get; set; }
        public string? Suite { get; set; }
        public string? City { get; set; }
        public string Zipcode { get; set; }
        public Geo Geo { get; set; }
    }

    public class Geo
    {
        public string Lat { get; set; }
        public string Lng { get; set; }
    }

    public class Company
    {
        public string Name { get; set; }
        public string CatchPhrase { get; set; }
        public string Bs { get; set; }
    }

    public partial class User : ObservableObject
    {
        [ObservableProperty]
        private int id;

        [ObservableProperty]
        private string name;

        [ObservableProperty]
        private string username;

        [ObservableProperty]
        private string email;

        [ObservableProperty]
        private Address address;

        [ObservableProperty]
        private string phone;

        [ObservableProperty]
        private string website;

        [ObservableProperty]
        private Company company;
    }
}
