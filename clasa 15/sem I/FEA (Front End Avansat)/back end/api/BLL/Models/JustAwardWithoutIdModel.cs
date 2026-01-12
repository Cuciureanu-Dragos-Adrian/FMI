using api.Entities;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace api.BLL.Models
{
    public class JustAwardWithoutIdModel
    {
        public string Name { get; set; }
        public int Year { get; set; }

        public JustAwardWithoutIdModel (Award award)
        {
            Name = award.Name;
            Year = award.Year;
        }
    }
}
