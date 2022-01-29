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
    public class CompanyManager : ICompanyManager
    {
        private readonly ICompanyRepository repository;

        public CompanyManager(ICompanyRepository companyRepository)
        {
            this.repository = companyRepository;
        }

        public Company GetCompanyById(string id)
        {
            return repository.GetCompanyById(id);
        }

        public List<CompanyHeadquarterModel> GetCompanies()
        {
            return repository.GetCompanies();
        }

        public List<CompanyNameIdModel> GetCompanyByEventId(string eventId)
        {
            var companies = repository.GetCompanyByEventId(eventId);

            var companiesJoined = new List<CompanyNameIdModel>();

            foreach (Company company in companies)
            {
                var model = new CompanyNameIdModel(company);

                companiesJoined.Add(model);
            }

            return companiesJoined;
        }

        public void Create(CompanyWithoutIdModel model)
        {
            repository.Create(model);
        }

        public void Update(CompanyModel model)
        {
            repository.Update(model);
        }

        public void Delete(string id)
        {
            repository.Delete(id);
        }
    }
}
