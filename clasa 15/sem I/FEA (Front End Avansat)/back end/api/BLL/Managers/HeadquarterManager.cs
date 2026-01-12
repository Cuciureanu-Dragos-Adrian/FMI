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
    public class HeadquarterManager : IHeadquarterManager
    {
        private readonly IHeadquarterRepository repository;

        public HeadquarterManager(IHeadquarterRepository headquarterRepository)
        {
            this.repository = headquarterRepository;
        }

        public Headquarter GetHeadquarterById(string id)
        {
            return repository.GetHeadquarterById(id);
        }

        public List<Headquarter> GetHeadquarters()
        {
            return repository.GetHeadquarters();
        }

        public void Create(HeadquarterWithoutIdModel model)
        {
            repository.Create(model);
        }

        public void Update(HeadquarterModel model)
        {
            repository.Update(model);
        }

        public void Delete(string id)
        {
            repository.Delete(id);
        }
    }
}
