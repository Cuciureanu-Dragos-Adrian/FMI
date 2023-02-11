using api.BLL.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace api.Entities
{
    public class Company
    {
        public string Id { get; set; }
        public string Name { get; set; }

        public string HeadquarterId { get; set; }
        public virtual Headquarter Headquarter {get; set;}
        public virtual ICollection<Game> Games { get; set; }
        public virtual ICollection<CompanyEvent> CompanyEvents { get; set; }
    }
}
