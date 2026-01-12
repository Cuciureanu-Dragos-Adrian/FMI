using api.Entities;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace api.BLL.Models
{
    public class FullGameJoinedModel
    {
        public string Id { get; set; }
        public string Name { get; set; }
        public string ReleaseDate { get; set; }
        public float? Review { get; set; }
        public float? Price { get; set; }

        public string Company { get; set; }
        public List<string> Genres { get; set; }
        public List<JustAwardWithoutIdModel> Awards { get; set; }

        public FullGameJoinedModel(Game game)
        {
            this.Id = game.Id;
            this.Name = game.Name;
            this.ReleaseDate = game.ReleaseDate;
            this.Review = game.Review;
            this.Price = game.Price;
            this.Company = game.Company.Name;
            this.Genres = new List<string>();
            this.Awards = new List<JustAwardWithoutIdModel>();

            foreach(var gamegenre in game.GameGenres)
            {
                Genres.Add(gamegenre.Genre.Name);
            }

            foreach(var award in game.Awards)
            {
                var awardModel = new JustAwardWithoutIdModel(award);

                Awards.Add(awardModel);
            }
        }
    }
}
