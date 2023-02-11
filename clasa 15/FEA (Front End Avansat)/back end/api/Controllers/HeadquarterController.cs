using api.BLL.Interfaces;
using api.BLL.Models;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Authorization;

namespace api.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class HeadquarterController : ControllerBase
    {
        private readonly IHeadquarterManager manager;

        public HeadquarterController(IHeadquarterManager headquarterManager)
        {
            this.manager = headquarterManager;
        }

        [HttpGet("headquarters")]
        [Authorize(Policy = "BasicUser")]
        public async Task<IActionResult> GetHeadquarters()
        {
            var headquarters = manager.GetHeadquarters();

            return Ok(headquarters);
        }

        [HttpGet("filterById/{id}")]
        [Authorize(Policy = "BasicUser")]
        public async Task<IActionResult> GetHeadquarterById([FromRoute] string id)
        {
            var headquarter = manager.GetHeadquarterById(id);

            return Ok(headquarter);
        }

        [HttpPost("headquarter")]
        [Authorize(Policy = "Admin")]
        public async Task<IActionResult> Create([FromBody] HeadquarterWithoutIdModel model)
        {
            manager.Create(model);

            return Ok();
        }

        [HttpPut("headquarter")]
        [Authorize(Policy = "Admin")]
        public async Task<IActionResult> Update([FromBody] HeadquarterModel model)
        {
            manager.Update(model);

            return Ok();
        }

        [HttpDelete("{id}")]
        [Authorize(Policy = "Admin")]
        public async Task<IActionResult> Delete([FromRoute] string id)
        {
            manager.Delete(id);

            return Ok();
        }
    }
}
