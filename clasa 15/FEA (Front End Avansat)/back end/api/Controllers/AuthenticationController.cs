using api.BLL.Interfaces;
using api.BLL.Models;
using Microsoft.AspNetCore.Mvc;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace api.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class AuthenticationController : ControllerBase
    {
        private IAuthenticationManager authenticationManager;

        public AuthenticationController(IAuthenticationManager authenticationManager)
        {
            this.authenticationManager = authenticationManager;
        }

        [HttpPost("signupUser")]
        public async Task<IActionResult> SignUp([FromBody] SignUpUserModel model)
        {
            try
            {
                await authenticationManager.SignUpUser(model);

                return Ok();
            }
            catch (Exception ex)
            {
                return BadRequest("Something failed");
            }
        }

        [HttpPost("signupAdmin")]
        public async Task<IActionResult> SignUpAdmin([FromBody] SignUpUserModel model)
        {
            try
            {
                await authenticationManager.SignUpAdmin(model);

                return Ok();
            }
            catch (Exception ex)
            {
                return BadRequest("Something failed");
            }
        }

        [HttpPost("login")]
        public async Task<IActionResult> Login([FromBody] LogInUserModel model)
        {
            try
            {
                var tokens = await authenticationManager.LogIn(model);

                if (tokens != null)
                    return Ok(tokens);
                else
                {
                    return BadRequest("Something failed");
                }
            }
            catch (Exception ex)
            {
                return BadRequest("Exception caught");
            }
        }
    }
}
