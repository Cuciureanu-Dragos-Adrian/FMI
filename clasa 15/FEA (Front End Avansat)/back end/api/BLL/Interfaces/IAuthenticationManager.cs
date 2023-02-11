using api.BLL.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace api.BLL.Interfaces
{
    public interface IAuthenticationManager
    {
        Task SignUpUser(SignUpUserModel signupUserModel);
        Task SignUpAdmin(SignUpUserModel signupUserModel);
        Task<TokenModel> LogIn(LogInUserModel loginUserModel);
    }
}
