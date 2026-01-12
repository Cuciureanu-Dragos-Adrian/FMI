using api.DAL.Interfaces;
using api.Entities;
using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace api.DAL.Repositories
{
    public class GamesRepository : IGamesRepository
    {
        private Context db;

        public GamesRepository(Context db)
        {
            this.db = db;
        }


        public Game GetGameById(string id)
        {
            var game = GetGamesJoined()
                .FirstOrDefault(x => x.Id == id);


            return game;
        }

        public List<Game> GetGames()
        {
            var games = db.Games.ToList();

            return games;
        }

        public List<Game> GetGamesJoined()
        {
            var games = db.Games
                .Include(x => x.Company)
                .Include(x => x.GameGenres)
                .ThenInclude(x => x.Genre)
                .Include(x => x.Awards)
                .ToList();

            return games;
        }
        

        public List<Game> GetGamesByName(string name)
        {
            var games = db.Games
                .Include(x => x.Company)
                .Where(x => x.Name.ToLower().Contains(name.ToLower())).ToList();

            return games;
        }

        public List<Game> GetGamesByCompanyId(string companyId)
        {
            var games = GetGamesJoined()
                .Where(x => x.Company.Id == companyId).ToList();

            return games;
        }

        public List<Game> GetGamesAlphabeticalAscending()
        {
            var games = GetGamesJoined().OrderBy(x => x.Name).ToList();

            return games;
        }

        public List<Game> GetGamesAlphabeticalDescending()
        {
            var games = GetGamesJoined().OrderByDescending(x => x.Name).ToList();

            return games;
        }

        public List<Game> GetGamesReviewAscending()
        {
            var games = GetGamesJoined().OrderBy(x => x.Review).ToList();

            return games;
        }

        public List<Game> GetGamesReviewDescending()
        {
            var games = GetGamesJoined().OrderByDescending(x => x.Review).ToList();

            return games;
        }

        public void Create(Game game)
        {
            db.Games.Add(game);

            db.SaveChanges();
        }

        public void Update(Game game)
        {
            db.Games.Update(game);

            db.SaveChanges();
        }

        public void Delete(Game game)
        {
            db.Games.Remove(game);

            db.SaveChanges();
        }
    }
}
