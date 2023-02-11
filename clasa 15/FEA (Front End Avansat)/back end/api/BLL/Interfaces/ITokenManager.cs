using api.Entities;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace api.BLL.Interfaces
{
    public interface ITokenManager
    {
        Task<string> CreateToken(User user);
    }
}
