using CommunityToolkit.Mvvm.ComponentModel;
using hw_11.Entities;

namespace hw_11.ViewModels;

public partial class MainViewModel : ObservableObject
{
    [ObservableProperty]
    private User _userData = new User
    {
        id = 1,
        name = "John Doe",
        username = "john.doe",
        email = "john.doe@example.com",
        address = new Address
        {
            street = "200 Oak St",
            suite = "Apt 6",
            city = "Springfield",
            geo = new Geo
            {
                lat = "39.7817",
                lng = "-89.6501"
            }
        },
        phone = "555-0123",
        website = "www.johndoe.com",
        company = new Company
        {
            name = "Doe Industries",
            catchPhrase = "Innovate your world",
            bs = "enhance scalable solutions"
        }
    };
}
