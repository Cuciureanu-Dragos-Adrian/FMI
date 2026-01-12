using api.BLL.Models;
using api.Entities;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace api.DAL.Interfaces
{
    public interface ICompanyRepository
    {
        Company GetCompanyById(string id);
        List<CompanyHeadquarterModel> GetCompanies();
        List<Company> GetCompanyByEventId(string eventId);
        void Create(CompanyWithoutIdModel model);
        void CreateCompanyAndHeadquarter(CompanyAndHeadquarterModel model);
        void Update(CompanyModel model);
        void UpdateCompanyAndHeadquarter(CompanyHeadquarterModel model);
        void Delete(string id);
        void DeleteCompanyAndHeadquarter(string id);
    }
}
