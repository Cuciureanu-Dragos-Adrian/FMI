using api.Entities;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace api.DAL.Interfaces
{
    public interface IGamesRepository
    {
        Game GetGameById(string id);
        List<Game> GetGames();
        List<Game> GetGamesJoined();
        List<Game> GetGamesByName(string name);
        List<Game> GetGamesByCompanyId(string companyId);
        List<Game> GetGamesAlphabeticalAscending();
        List<Game> GetGamesAlphabeticalDescending();
        List<Game> GetGamesReviewAscending();
        List<Game> GetGamesReviewDescending();
        void Create(Game game);
        void Update(Game game);
        void Delete(Game game);
    }
}