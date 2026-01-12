using api.BLL.Models;
using api.Entities;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace api.BLL.Interfaces
{
    public interface IAwardManager
    {
        Award GetAwardById(string id);
        List<Award> GetAwards();
        void Create(AwardWithoutIdModel model);
        void Update(AwardModel model);
        void Delete(string id);
    }
}
