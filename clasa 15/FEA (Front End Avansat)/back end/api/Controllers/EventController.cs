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
    public class EventController : ControllerBase
    {
        private readonly IEventManager manager;

        public EventController(IEventManager eventManager)
        {
            this.manager = eventManager;
        }

        [HttpGet("events")]
        [Authorize(Policy = "BasicUser")]
        public async Task<IActionResult> GetEvents()
        {
            var events = manager.GetEvents();

            return Ok(events);
        }

        [HttpGet("filterById/{id}")]
        [Authorize(Policy = "BasicUser")]
        public async Task<IActionResult> GetEventById([FromRoute] string id)
        {
            var @event = manager.GetEventById(id);

            return Ok(@event);
        }

        [HttpPost("event")]
        [Authorize(Policy = "Admin")]
        public async Task<IActionResult> Create([FromBody] EventWithoutIdModel model)
        {
            manager.Create(model);

            return Ok();
        }

        [HttpPut("event")]
        [Authorize(Policy = "Admin")]
        public async Task<IActionResult> Update([FromBody] EventModel model)
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
