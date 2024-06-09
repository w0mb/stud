using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Weather
{
    internal class CurrentWeather
    {
        public Coords Coord { get; set; }
        public WeatherInfo[] Weather { get; set; }
        public string _base { get; set; }
        public MainInfo Main { get; set; }
        public int Visibility { get; set; }
        public WindInfo Wind { get; set; }
        public RainInfo Rain { get; set; }
        public CloudsInfo Clouds { get; set; }
        public int Dt { get; set; }
        public SysInfo Sys { get; set; }
        public int Timezone { get; set; }
        public int Id { get; set; }
        public string Name { get; set; }
        public int Cod { get; set; }

        public class Coords
        {
            public float Lon { get; set; }
            public float Lat { get; set; }
        }

        public class MainInfo
        {
            public float Temp { get; set; }
            public float Feels_like { get; set; }
            public float Temp_min { get; set; }
            public float Temp_max { get; set; }
            public int Pressure { get; set; }
            public int Humidity { get; set; }
            public int Sea_level { get; set; }
            public int Grnd_level { get; set; }
        }

        public class WindInfo
        {
            public float Speed { get; set; }
            public int Deg { get; set; }
            public float Gust { get; set; }
        }

        public class RainInfo
        {
            public float _1h { get; set; }
        }

        public class CloudsInfo
        {
            public int All { get; set; }
        }

        public class SysInfo
        {
            public int Type { get; set; }
            public int Id { get; set; }
            public string Country { get; set; }
            public int Sunrise { get; set; }
            public int Sunset { get; set; }
        }

        public class WeatherInfo
        {
            public int Id { get; set; }
            public string Main { get; set; }
            public string Description { get; set; }
            public string Icon { get; set; }
        }
    }
}
