using api.BLL.Models;
using api.Entities;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace api.BLL.Interfaces
{
    public interface IHeadquarterManager
    {
        Headquarter GetHeadquarterById(string id);
        List<Headquarter> GetHeadquarters();
        void Create(HeadquarterWithoutIdModel model);
        void Update(HeadquarterModel model);
        void Delete(string id);
    }
}
