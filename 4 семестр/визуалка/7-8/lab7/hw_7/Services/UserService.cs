using RestSharp;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace hw_7.Services
{
    public class UserService
    {
        private RestClientOptions _options;
        private RestClient _client;

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
