using api.BLL.Interfaces;
using api.BLL.Models;
using api.DAL.Interfaces;
using api.Entities;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace api.BLL.Managers
{
    public class GamesManager : IGamesManager
    {
        private readonly IGamesRepository repository;

        public GamesManager(IGamesRepository gamesRepository)
        {
            this.repository = gamesRepository;
        }


        public List<Game> GetGames()
        {
            return repository.GetGames();
        }

        public List<FullGameJoinedModel> GetGamesJoined()
        {
            var games = repository.GetGamesJoined();

            var gamesJoined = new List<FullGameJoinedModel>();

            foreach (Game game in games)
            {
                var model = new FullGameJoinedModel(game);

                gamesJoined.Add(model);
            }

            return gamesJoined;
        }

        public List<FullGameJoinedModel> GetGameByName(string name)
        {
            var games = repository.GetGamesByName(name);

            var gamesJoined = new List<FullGameJoinedModel>();

            foreach (Game game in games)
            {
                var model = new FullGameJoinedModel(game);

                gamesJoined.Add(model);
            }

            return gamesJoined;
        }

        public List<GameNameIdModel> GetGameByCompanyId(string companyId)
        {
            var games = repository.GetGamesByCompanyId(companyId);

            var gamesJoined = new List<GameNameIdModel>();

            foreach (Game game in games)
            {
                var model = new GameNameIdModel(game);

                gamesJoined.Add(model);
            }

            return gamesJoined;
        }

        public List<FullGameJoinedModel> GetGamesAlphabeticalAscending()
        {
            var games = repository.GetGamesAlphabeticalAscending();

            var gamesJoined = new List<FullGameJoinedModel>();

            foreach (Game game in games)
            {
                var model = new FullGameJoinedModel(game);

                gamesJoined.Add(model);
            }

            return gamesJoined;
        }

        public List<FullGameJoinedModel> GetGamesAlphabeticalDescending()
        {
            var games = repository.GetGamesAlphabeticalDescending();

            var gamesJoined = new List<FullGameJoinedModel>();

            foreach (Game game in games)
            {
                var model = new FullGameJoinedModel(game);

                gamesJoined.Add(model);
            }

            return gamesJoined;
        }

        public List<FullGameJoinedModel> GetGamesReviewAscending()
        {
            var games = repository.GetGamesReviewAscending();

            var gamesJoined = new List<FullGameJoinedModel>();

            foreach (Game game in games)
            {
                var model = new FullGameJoinedModel(game);

                gamesJoined.Add(model);
            }

            return gamesJoined;
        }

        public List<FullGameJoinedModel> GetGamesReviewDescending()
        {
            var games = repository.GetGamesReviewDescending();

            var gamesJoined = new List<FullGameJoinedModel>();

            foreach (Game game in games)
            {
                var model = new FullGameJoinedModel(game);

                gamesJoined.Add(model);
            }

            return gamesJoined;
        }

        public List<FullGameJoinedModel> GetGamesWithMinimumReview(float minimumReview)
        {
            var games = repository.GetGamesJoined()
                .Where(x => x.Review >= minimumReview).ToList();

            var gamesJoined = new List<FullGameJoinedModel>();

            foreach (Game game in games)
            {
                var model = new FullGameJoinedModel(game);

                gamesJoined.Add(model);
            }

            return gamesJoined;
        }

        public FullGameJoinedModel GetGameById(string id)
        {
            var game = repository.GetGameById(id);

            var fullGame = new FullGameJoinedModel(game);

            return fullGame;
        }

        public void CreateJustGame(JustGameWithoutIdModel model)
        {
            var newGame = new Game
            {
                Id = Guid.NewGuid().ToString(),
                Name = model.Name,
                ReleaseDate = model.ReleaseDate,
                Review = model.Review,
                Price = model.Price,
                CompanyId = "3832a036-07c5-44d4-9587-08be426ab427",
            };

            repository.Create(newGame);
        }

        public void UpdateJustGame(JustGameModel model)
        {
            var game = repository.GetGameById(model.Id);

            game.Name = model.Name;
            game.ReleaseDate = model.ReleaseDate;
            game.Review = model.Review;
            game.Price = model.Price;

            repository.Update(game);
        }

        public void Delete(string id)
        {
            var game = repository.GetGameById(id);

            repository.Delete(game);
        }
    }
}
