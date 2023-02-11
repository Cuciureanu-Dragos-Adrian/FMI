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
    public class AwardManager : IAwardManager
    {
        private readonly IAwardRepository repository;

        public AwardManager(IAwardRepository awardRepository)
        {
            this.repository = awardRepository;
        }

        public Award GetAwardById(string id)
        {
            return repository.GetAwardById(id);
        }

        public List<Award> GetAwards()
        {
            return repository.GetAwards();
        }

        public void Create(AwardWithoutIdModel model)
        {
            repository.Create(model);
        }

        public void Update(AwardModel model)
        {
            repository.Update(model);
        }

        public void Delete(string id)
        {
            repository.Delete(id);
        }
    }
}
