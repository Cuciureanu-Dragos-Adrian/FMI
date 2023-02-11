using api.BLL.Interfaces;
using api.BLL.Models;
using api.Entities;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace api.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class GameController : ControllerBase
    {
        private readonly IGamesManager manager;

        public GameController(IGamesManager gamesManager)
        {
            this.manager = gamesManager;
        }

        [HttpGet("fullGames")]
        [Authorize(Policy = "BasicUser")]
        public async Task<IActionResult> GetGames()
        {
            var games = manager.GetGames();

            return Ok(games);
        }

        [HttpGet("fullGamesJoined")]
        [Authorize(Policy = "BasicUser")]
        public async Task<IActionResult> GetGamesJoined()
        {
            var games = manager.GetGamesJoined();

            return Ok(games);
        }

        [HttpGet("filterById/{id}")]
        [Authorize(Policy = "BasicUser")]
        public async Task<IActionResult> GetById([FromRoute] string id)
        {
            var game = manager.GetGameById(id);

            return Ok(game);
        }

        [HttpGet("filterByName/{name}")]
        [Authorize(Policy = "BasicUser")]
        public async Task<IActionResult> GetByName([FromRoute] string name)
        {
            var games = manager.GetGameByName(name);

            return Ok(games);
        }

        [HttpGet("filterByCompanyId/{companyId}")]
        [Authorize(Policy = "BasicUser")]
        public async Task<IActionResult> GetGameByCompanyId([FromRoute] string companyId)
        {
            var games = manager.GetGameByCompanyId(companyId);

            return Ok(games);
        }

        [HttpGet("filterByAlphabeticalAscending")]
        [Authorize(Policy = "BasicUser")]
        public async Task<IActionResult> GetGamesAlphabeticalAscending()
        {
            var games = manager.GetGamesAlphabeticalAscending();

            return Ok(games);
        }

        [HttpGet("filterByAlphabeticalDescending")]
        [Authorize(Policy = "BasicUser")]
        public async Task<IActionResult> GetGamesAlphabeticalDescending()
        {
            var games = manager.GetGamesAlphabeticalDescending();

            return Ok(games);
        }

        [HttpGet("filterByReviewAscending")]
        [Authorize(Policy = "BasicUser")]
        public async Task<IActionResult> GetGamesReviewAscending()
        {
            var games = manager.GetGamesReviewAscending();

            return Ok(games);
        }

        [HttpGet("filterByReviewDescending")]
        [Authorize(Policy = "BasicUser")]
        public async Task<IActionResult> GetGamesReviewDescending()
        {
            var games = manager.GetGamesReviewDescending();

            return Ok(games);
        }

        [HttpGet("filterByMinimumReview/{minimumReview}")]
        [Authorize(Policy = "BasicUser")]
        public async Task<IActionResult> GetGamesWithMinimumReview([FromRoute] float minimumReview)
        {
            var games = manager.GetGamesWithMinimumReview(minimumReview);

            return Ok(games);
        }

        [HttpPost("justGame")]
        [Authorize(Policy = "Admin")]
        public async Task<IActionResult> CreateJustGame([FromBody] JustGameWithoutIdModel gameModel)
        {
            manager.CreateJustGame(gameModel);

            var games = manager.GetGamesJoined();
            return Ok(games);
        }

        [HttpPut("justGame")]
        [Authorize(Policy = "Admin")]
        public async Task<IActionResult> UpdateJustGame([FromBody] JustGameModel gameModel)
        {
            manager.UpdateJustGame(gameModel);

            var games = manager.GetGamesJoined();
            return Ok(games);
        }

        [HttpDelete("{id}")]
        [Authorize(Policy = "Admin")]
        public async Task<IActionResult> Delete([FromRoute] string id)
        {
            manager.Delete(id);

            var games = manager.GetGamesJoined();
            return Ok(games);
        }
    }
}
