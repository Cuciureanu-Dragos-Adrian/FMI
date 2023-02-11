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
    public class AwardController : ControllerBase
    {
        private readonly IAwardManager manager;

        public AwardController(IAwardManager awardManager)
        {
            this.manager = awardManager;
        }

        [HttpGet("awards")]
        [Authorize(Policy = "BasicUser")]
        public async Task<IActionResult> GetAwards()
        {
            var awards = manager.GetAwards();

            return Ok(awards);
        }

        [HttpGet("filterById/{id}")]
        [Authorize(Policy = "BasicUser")]
        public async Task<IActionResult> GetAwardById([FromRoute] string id)
        {
            var award = manager.GetAwardById(id);

            return Ok(award);
        }

        [HttpPost("award")]
        [Authorize(Policy = "Admin")]
        public async Task<IActionResult> Create([FromBody] AwardWithoutIdModel model)
        {
            manager.Create(model);

            return Ok();
        }

        [HttpPut("award")]
        [Authorize(Policy = "Admin")]
        public async Task<IActionResult> Update([FromBody] AwardModel model)
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
