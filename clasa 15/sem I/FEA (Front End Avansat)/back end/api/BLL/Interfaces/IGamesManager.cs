using api.BLL.Models;
using api.Entities;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace api.BLL.Interfaces
{
    public interface IGamesManager
    {
        List<Game> GetGames();
        List<FullGameJoinedModel> GetGamesJoined();
        List<FullGameJoinedModel> GetGameByName(string name);
        List<GameNameIdModel> GetGameByCompanyId(string companyId);
        List<FullGameJoinedModel> GetGamesAlphabeticalAscending();
        List<FullGameJoinedModel> GetGamesAlphabeticalDescending();
        List<FullGameJoinedModel> GetGamesReviewAscending();
        List<FullGameJoinedModel> GetGamesReviewDescending();
        List<FullGameJoinedModel> GetGamesWithMinimumReview(float minimumReview);
        FullGameJoinedModel GetGameById(string id);
        void CreateJustGame(JustGameWithoutIdModel model);
        void UpdateJustGame(JustGameModel model);
        void Delete(string id);
    }
}
