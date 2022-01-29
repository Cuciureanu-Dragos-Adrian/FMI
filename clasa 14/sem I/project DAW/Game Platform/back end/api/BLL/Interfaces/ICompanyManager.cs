using api.BLL.Models;
using api.Entities;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace api.BLL.Interfaces
{
    public interface ICompanyManager
    {
        Company GetCompanyById(string id);
        List<CompanyHeadquarterModel> GetCompanies();
        List<CompanyNameIdModel> GetCompanyByEventId(string eventId);
        //Company Join cu Headquarter
        void Create(CompanyWithoutIdModel model);
        void Update(CompanyModel model);
        void Delete(string id);
    }
}
