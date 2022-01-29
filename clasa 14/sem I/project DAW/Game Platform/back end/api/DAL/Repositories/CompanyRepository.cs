using api.BLL.Models;
using api.DAL.Interfaces;
using api.Entities;
using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace api.DAL.Repositories
{
    public class CompanyRepository : ICompanyRepository
    {
        private Context db;

        public CompanyRepository(Context db)
        {
            this.db = db;
        }

        public Company GetCompanyById(string id)
        {
            var company = db.Companies
                .FirstOrDefault(x => x.Id == id);

            return company;
        }

        public List<CompanyHeadquarterModel> GetCompanies()
        {
            var companyJoinHeadquarter = db.Companies
                .Join(db.Headquarters, c => c.HeadquarterId, h => h.Id, (c, h) => new CompanyHeadquarterModel
                {
                    Id = c.Id,
                    Name = c.Name,
                    Country = h.Country,
                    City = h.City
                }).ToList();


            return companyJoinHeadquarter;
        }

        public List<Company> GetCompanyByEventId(string eventId)
        {
            var companies = db.CompanyEvents
                .Include(x => x.Company)
                .Include(x => x.Event)
                .Where(x => x.EventId == eventId)
                .Select(x => x.Company).ToList();

            return companies;
        }

        public void Create(CompanyWithoutIdModel model)
        {
            var newCompany = new Company
            {
                Id = Guid.NewGuid().ToString(),
                Name = model.Name,
                HeadquarterId = "88ecd0a3-a123-43c3-b8e7-1e0daba0627a"
            };

            db.Companies.Add(newCompany);

            db.SaveChanges();
        }

        public void Update(CompanyModel model)
        {
            var company = GetCompanyById(model.Id);

            company.Name = model.Name;

            db.Companies.Update(company);

            db.SaveChanges();
        }

        public void Delete(string id)
        {
            var company = GetCompanyById(id);

            db.Companies.Remove(company);

            db.SaveChanges();
        }
    }
}
