using api.Entities;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace api.BLL.Models
{
    public class CompanyNameIdModel
    {
        public string Id { get; set; }
        public string Name { get; set; }


        public CompanyNameIdModel(Company company)
        {
            Id = company.Id;
            Name = company.Name;
        }
    }
}
