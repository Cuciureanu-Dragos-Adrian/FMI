using api.BLL.Interfaces;
using api.BLL.Models;
using api.Entities;
using Microsoft.AspNetCore.Identity;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace api.BLL.Managers
{
    public class AuthenticationManager : IAuthenticationManager
    {
        private readonly UserManager<User> userManager;
        private readonly SignInManager<User> signInManager;
        private readonly ITokenManager tokenManager;

        public AuthenticationManager(UserManager<User> userManager, SignInManager<User> signInManager,
            ITokenManager tokenManager)
        {
            this.userManager = userManager;
            this.signInManager = signInManager;
            this.tokenManager = tokenManager;
        }

        public async Task SignUpUser(SignUpUserModel signUpUserModel)
        {
            var user = new User
            {
                Email = signUpUserModel.Email,
                UserName = signUpUserModel.Username
            };

            if (signUpUserModel.Password == signUpUserModel.VerifyPassword)
            {
                var result = await userManager.CreateAsync(user, signUpUserModel.Password);
                if (result.Succeeded)
                {
                    await userManager.AddToRoleAsync(user, "USER");
                }
                else
                {
                    throw new ArgumentException("Account wasn't made!");
                }
            }
            else
            {
                throw new ArgumentException("PasswordVerification is different from Password!");
            }
        }

        public async Task SignUpAdmin(SignUpUserModel signUpUserModel)
        {
            var user = new User
            {
                Email = signUpUserModel.Email,
                UserName = signUpUserModel.Username
            };

            if (signUpUserModel.Password == signUpUserModel.VerifyPassword)
            {
                var result = await userManager.CreateAsync(user, signUpUserModel.Password);

                if (result.Succeeded)
                {
                    await userManager.AddToRoleAsync(user, "ADMIN");
                }
                else
                {
                    throw new ArgumentException("Account wasn't made!");
                }
            }
            else
            {
                throw new ArgumentException("PasswordVerification is different from Password!");
            }
        }

        public async Task<TokenModel> LogIn(LogInUserModel loginUserModel)
        {
            var email = await userManager.FindByEmailAsync(loginUserModel.Username);
            if (email == null)
            {
                var user = await userManager.FindByNameAsync(loginUserModel.Username);

                if (user != null)
                {
                    var result = await signInManager.CheckPasswordSignInAsync(user, loginUserModel.Password, false);
                    if (result.Succeeded)
                    {
                        //Create token
                        var token = await tokenManager.CreateToken(user); //new manager responsible with creating the token

                        return new TokenModel { Token = token };
                    }
                }
            }
            else
            {
                var result = await signInManager.CheckPasswordSignInAsync(email, loginUserModel.Password, false);

                if (result.Succeeded)
                {
                    //Create token
                    var token = await tokenManager.CreateToken(email); //new manager responsible with creating the token

                    return new TokenModel { Token = token };
                }
            }

            

            return null;
        }
    }
}
