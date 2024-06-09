using RestSharp;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MVVM.Class
{
    public class UserService
    {
        private RestClient _client;
        private RestClientOptions _options;
        public UserService()
        {
            _options = new RestClientOptions("https://jsonplaceholder.typicode.com");
            _client = new RestClient(_options);
        }

        public async Task<List<User>> GetUsers()
        {
            var response = await _client.GetJsonAsync<List<User>>("users");

            return response;
        }
    }
}
