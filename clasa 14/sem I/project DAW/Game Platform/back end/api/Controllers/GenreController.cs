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
    public class GenreController : ControllerBase
    {
        private readonly IGenreManager manager;

        public GenreController(IGenreManager genreManager)
        {
            this.manager = genreManager;
        }

        [HttpGet("genres")]
        [Authorize(Policy = "BasicUser")]
        public async Task<IActionResult> GetGenres()
        {
            var genres = manager.GetGenres();

            return Ok(genres);
        }

        [HttpGet("filterById/{id}")]
        [Authorize(Policy = "BasicUser")]
        public async Task<IActionResult> GetGenreById([FromRoute] string id)
        {
            var @genre = manager.GetGenreById(id);

            return Ok(@genre);
        }

        [HttpPost("genre")]
        [Authorize(Policy = "Admin")]
        public async Task<IActionResult> Create([FromBody] GenreWithoutIdModel model)
        {
            manager.Create(model);

            return Ok();
        }

        [HttpPut("genre")]
        [Authorize(Policy = "Admin")]
        public async Task<IActionResult> Update([FromBody] GenreModel model)
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
