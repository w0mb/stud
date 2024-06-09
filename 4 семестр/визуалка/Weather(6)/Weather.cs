using Avalonia.Media;
using Avalonia.Media.Imaging;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Numerics;
using System.Runtime.CompilerServices;
using System.Text.Json;
using System.Threading.Tasks;

namespace Weather;

internal class Weather : INotifyPropertyChanged
{
    public Weather()
    {
        _weatherService = new WeatherService.WeatherService();
        CityName = "No data :(";
        SetBackground();
    }

    public async Task SetAllComponents()
    {
        WeatherObject = GetJsonWeather();
        CityName = "City name: " + WeatherObject.Name;
        Description = "Current weather: " + WeatherObject.Weather[0].Description;

        double roundTemp = Math.Round(WeatherObject.Main.Temp_min - 273.15, 1);
        MinTemp = roundTemp.ToString() + "А";
        roundTemp = Math.Round(WeatherObject.Main.Temp_max - 273.15, 1);
        MaxTemp = roundTemp.ToString() + "А";
        roundTemp = Math.Round(WeatherObject.Main.Temp - 273.15, 1);
        Temp = "Temperature: " + roundTemp.ToString() + "А" + "\tMin: " + MinTemp + "\tMax: " + MaxTemp;

        Humidity = "Humidity: " + WeatherObject.Main.Humidity.ToString() + "%";
        Wind = "Wind: " + WeatherObject.Wind.Speed.ToString() + " m/s";
        AirPressure = "Air pressure: " + WeatherObject.Main.Pressure.ToString() + " mm";
        Visibility = "Visibility: " + (WeatherObject.Visibility / 1000).ToString() + " km";

        OnPropertyChanged(null);
    }

    public CurrentWeather GetJsonWeather()
    {
        string jsonString = Task.Run(async () => await Task.FromResult(_weatherService.GetDataSync(true))).Result;

        JsonSerializerOptions jsonSerializerOptions = new JsonSerializerOptions()
        {
            PropertyNamingPolicy = JsonNamingPolicy.CamelCase,
        };

        return JsonSerializer.Deserialize<CurrentWeather>(jsonString, jsonSerializerOptions);
    }

    public void SetBackground()
    {
        var imageBrush = new ImageBrush
        {
            Source = new Bitmap(_path + "images\\day.jpg"),
            Stretch = Stretch.Fill,
            TileMode = TileMode.Tile
        };

        Background = imageBrush;
    }

    public async Task SetProperty(string str)
    {
        CityName = str;
        OnPropertyChanged(nameof(CityName));
    }

    public ImageBrush Background { get; set; }
    public string CityName { get; set; }
    public string Description { get; set; }
    public string Temp { get; set; }
    public string MinTemp { get; set; }
    public string MaxTemp { get; set; }
    public string Humidity { get; set; }
    public string Wind { get; set; }
    public string AirPressure { get; set; }
    public string Visibility { get; set; }

    private CurrentWeather WeatherObject { get; set; }

    private readonly WeatherService.WeatherService _weatherService;

    private string _cityName;

    private readonly string _path = "C:\\Users\\ekate\\№рс\\Weather\\";

    public event PropertyChangedEventHandler? PropertyChanged;

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