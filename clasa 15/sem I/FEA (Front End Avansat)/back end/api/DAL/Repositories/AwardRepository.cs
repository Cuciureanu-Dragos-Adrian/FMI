using api.BLL.Models;
using api.DAL.Interfaces;
using api.Entities;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace api.DAL.Repositories
{
    public class AwardRepository : IAwardRepository
    {
        private Context db;

        public AwardRepository(Context db)
        {
            this.db = db;
        }

        public Award GetAwardById(string id)
        {
            var award = db.Awards
                .FirstOrDefault(x => x.Id == id);

            return award;
        }

        public List<Award> GetAwards()
        {
            var awards = db.Awards.ToList();

            return awards;
        }

        public void Create(AwardWithoutIdModel model)
        {
            var newAward = new Award
            {
                Id = Guid.NewGuid().ToString(),
                Name = model.Name,
                Year = model.Year,
                GameId = model.GameId
            };

            db.Awards.Add(newAward);

            db.SaveChanges();
        }

        public void Update(AwardModel model)
        {
            var award = GetAwardById(model.Id);

            award.Name = model.Name;
            award.Year = model.Year;
            award.GameId = model.GameId;

            db.Awards.Update(award);

            db.SaveChanges();
        }

        public void Delete(string id)
        {
            var award = GetAwardById(id);

            db.Awards.Remove(award);

            db.SaveChanges();
        }
    }
}
