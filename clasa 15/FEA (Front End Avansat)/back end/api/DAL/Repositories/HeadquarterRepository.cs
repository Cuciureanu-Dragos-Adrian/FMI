using api.BLL.Models;
using api.DAL.Interfaces;
using api.Entities;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace api.DAL.Repositories
{
    public class HeadquarterRepository : IHeadquarterRepository
    {
        private Context db;

        public HeadquarterRepository(Context db)
        {
            this.db = db;
        }

        public Headquarter GetHeadquarterById(string id)
        {
            var headquarter = db.Headquarters
                .FirstOrDefault(x => x.Id == id);

            return headquarter;
        }

        public List<Headquarter> GetHeadquarters()
        {
            var headquarters = db.Headquarters.ToList();

            return headquarters;
        }

        public void Create(HeadquarterWithoutIdModel model)
        {
            var newHeadquarter = new Headquarter
            {
                Id = Guid.NewGuid().ToString(),
                Country = model.Country,
                City = model.City,
                Street = model.Street
            };

            db.Headquarters.Add(newHeadquarter);

            db.SaveChanges();
        }

        public void Update(HeadquarterModel model)
        {
            var headquarter = GetHeadquarterById(model.Id);

            headquarter.Country = model.Country;
            headquarter.City = model.City;
            headquarter.Street = model.Street;

            db.Headquarters.Update(headquarter);

            db.SaveChanges();
        }

        public void Delete(string id)
        {
            var headquarter = GetHeadquarterById(id);

            db.Headquarters.Remove(headquarter);

            db.SaveChanges();
        }
    }
}
